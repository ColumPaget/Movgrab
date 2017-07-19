#include "Process.h"
#define _GNU_SOURCE
#include "errno.h"
#include "includes.h"
#include "Time.h"
#include <pwd.h>
#include <sys/file.h>
#include <sys/mount.h>
#include <sys/resource.h>
#include "FileSystem.h"
#include "Log.h"
#include <sched.h>
#include <sys/wait.h>


/*This is code to change the command-line of a program as visible in ps */

extern char **environ;
char *TitleBuffer=NULL;
int TitleLen=0;


//The command-line args that we've been passed (argv) will occupy a block of contiguous memory that
//contains these args and the environment strings. In order to change the command-line args we isolate
//this block of memory by iterating through all the strings in it, and making copies of them. The
//pointers in 'argv' and 'environ' are then redirected to these copies. Now we can overwrite the whole
//block of memory with our new command-line arguments.
void ProcessTitleCaptureBuffer(char **argv)
{
char *end=NULL, *tmp;
int i;

TitleBuffer=*argv;
end=*argv;
for (i=0; argv[i] !=NULL; i++)
{
//if memory is contiguous, then 'end' should always wind up
//pointing to the next argv
if (end==argv[i])
{
	while (*end != '\0') end++;
	end++;
}
}

//we used up all argv, environ should follow it
if (argv[i] ==NULL)
{
	for (i=0; environ[i] !=NULL; i++)
	if (end==environ[i])
	{
	while (*end != '\0') end++;
	end++;
	}
}

//now we replace argv and environ with copies
for (i=0; argv[i] != NULL; i++) argv[i]=strdup(argv[i]);
for (i=0; environ[i] != NULL; i++) environ[i]=strdup(environ[i]);

//These might point to argv[0], so make copies of these too
#ifdef __GNU_LIBRARY__
extern char *program_invocation_name;
extern char *program_invocation_short_name;

program_invocation_name=strdup(program_invocation_name);
program_invocation_short_name=strdup(program_invocation_short_name);
#endif


TitleLen=end-TitleBuffer;
}


void ProcessSetTitle(char *FmtStr, ...)
{
va_list args;

		if (! TitleBuffer) return;
		memset(TitleBuffer,0,TitleLen);

    va_start(args,FmtStr);
		vsnprintf(TitleBuffer,TitleLen,FmtStr,args);
    va_end(args);
}




int WritePidFile(char *ProgName)
{
char *Tempstr=NULL;
int fd;


if (*ProgName=='/') Tempstr=CopyStr(Tempstr,ProgName);
else Tempstr=FormatStr(Tempstr,"/var/run/%s.pid",ProgName);

fd=open(Tempstr,O_CREAT | O_WRONLY,0600);
if (fd > -1)
{
  fchmod(fd,0644);
  if (flock(fd,LOCK_EX|LOCK_NB) ==0)
  {
  ftruncate(fd,0);
  Tempstr=FormatStr(Tempstr,"%d\n",getpid());
  write(fd,Tempstr,StrLen(Tempstr));
  }
  else
  {
		RaiseError(ERRFLAG_ERRNO, "WritePidFile", "Failed to lock pid file %s. Program already running?",Tempstr);
    close(fd);
    fd=-1;
  }
}
else RaiseError(ERRFLAG_ERRNO, "WritePidFile", "Failed to open pid file %s",Tempstr);

//Don't close 'fd'!

DestroyString(Tempstr);

return(fd);
}


void CloseOpenFiles()
{
      int i;

      for (i=3; i < 1024; i++) close(i);
}



int SwitchUID(int uid)
{
const char *ptr;

  if ((uid==-1) || (setresuid(uid,uid,uid) !=0))
	{
		RaiseError(ERRFLAG_ERRNO, "SwitchUID", "Switch user failed. uid=%d",uid);
		ptr=LibUsefulGetValue("SwitchUserAllowFail");
		if (ptr && (strcasecmp(ptr,"yes")==0)) return(FALSE);
		exit(1);
	}
  return(TRUE);
}


int SwitchUser(const char *NewUser)
{
int uid;

	uid=LookupUID(NewUser);
	if (uid==-1) return(FALSE);
	return(SwitchUID(uid));
}


int SwitchGID(int gid)
{
const char *ptr;
	
	if ((gid==-1) || (setgid(gid) !=0))
	{
		RaiseError(ERRFLAG_ERRNO, "SwitchGID", "Switch group failed. gid=%d",gid);
		ptr=LibUsefulGetValue("SwitchGroupAllowFail");
		if (ptr && (strcasecmp(ptr,"yes")==0)) return(FALSE);
		exit(1);
	}
  return(TRUE);
}

int SwitchGroup(const char *NewGroup)
{
int gid;

	gid=LookupGID(NewGroup);
	if (gid==-1) return(FALSE);
	return(SwitchGID(gid));
}



char *GetCurrUserHomeDir()
{
struct passwd *pwent;

    pwent=getpwuid(getuid());
    if (! pwent)
		{
			RaiseError(ERRFLAG_ERRNO, "getpwuid","Failed to get info for current user");
			return(NULL);
		}
    return(pwent->pw_dir);
}



void ColLibDefaultSignalHandler(int sig)
{

}


int CreateLockFile(char *FilePath, int Timeout)
{
int fd, result;

SetTimeout(Timeout);
fd=open(FilePath, O_CREAT | O_RDWR, 0600);
if (fd <0) 
{
	RaiseError(ERRFLAG_ERRNO, "lockfile","failed to open file %s", FilePath);
	return(-1);
}

result=flock(fd,LOCK_EX);
alarm(0);

if (result==-1)
{
	RaiseError(ERRFLAG_ERRNO, "lockfile","failed to lock file %s", FilePath);
  close(fd);
  return(-1);
}
return(fd);
}

void InitSigHandler(int sig)
{
}




void ProcessContainerInit(int tunfd, int linkfd, pid_t Child)
{
int i;
ListNode *Connections=NULL;
STREAM *TunS=NULL, *LinkS=NULL, *S;
char *Token=NULL;
const char *ptr;
struct sigaction sa;

	if ((linkfd > -1) && (tunfd > -1))
	{
	Connections=ListCreate();
	LinkS=STREAMFromFD(linkfd);
	STREAMSetFlushType(LinkS, FLUSH_ALWAYS, 0, 0);
	if (LinkS) ListAddItem(Connections, LinkS);

	TunS=STREAMFromFD(tunfd);
	STREAMSetFlushType(TunS, FLUSH_ALWAYS, 0, 0);
	if (TunS) ListAddItem(Connections, TunS);
	}
	

	//this process is init, the child will carry on executation
	if (chroot(".") == -1) RaiseError(ERRFLAG_ERRNO, "chroot", "failed to chroot to curr directory");
	ProcessSetTitle("init");
	
	memset(&sa,0,sizeof(sa));
	sa.sa_handler=InitSigHandler;
	sa.sa_flags=SA_NOCLDSTOP;
	sigaction(SIGCHLD, &sa,NULL);
	while (Connections)
	{
	S=STREAMSelect(Connections, NULL);
	if (S==TunS) STREAMSendFile(S, LinkS, BUFSIZ, SENDFILE_KERNEL);
	else if (S==LinkS) STREAMSendFile(S, TunS, BUFSIZ, SENDFILE_KERNEL);
	if (waitpid(Child,NULL,WNOHANG) == -1) break;
	}

	waitpid(Child,NULL,0);
	
	FileSystemUnMount("/proc","rmdir");
	FileSystemUnMount("/","recurse,rmdir");

	STREAMClose(TunS);
	STREAMClose(LinkS);

	_exit(0);
}


void ProcessContainer(const char *Config)
{
char *ROMounts=NULL, *RWMounts=NULL;
char *Links=NULL, *PLinks=NULL;
char *HostName=NULL, *Dir=NULL;
char *Name=NULL, *Value=NULL;
char *Tempstr=NULL, *ptr;
int i, val, Flags=0;
pid_t pid, child;

ROMounts=CopyStr(ROMounts, "/etc,/bin,/usr/bin,/lib,/usr/lib");
ptr=GetNameValuePair(Config,"\\S","=",&Name,&Value);
while (ptr)
{
if (strcasecmp(Name,"hostname")==0) HostName=CopyStr(HostName, Value);
else if (strcasecmp(Name,"dir")==0) Dir=CopyStr(Dir, Value);
else if (strcasecmp(Name,"container")==0) if (StrValid(Value)) Dir=CopyStr(Dir, Value);
else if (strcasecmp(Name,"+net")==0) Flags |= PROC_CONTAINER_NET;
else if (strcasecmp(Name,"+mnt")==0) ROMounts=MCatStr(ROMounts,",",Value,NULL);
else if (strcasecmp(Name,"mnt")==0) ROMounts=CopyStr(ROMounts,Value);
else if (strcasecmp(Name,"+wmnt")==0) RWMounts=MCatStr(RWMounts,",",Value,NULL);
else if (strcasecmp(Name,"wmnt")==0) RWMounts=CopyStr(RWMounts,Value);
else if (strcasecmp(Name,"+link")==0) Links=MCatStr(Links,",",Value,NULL);
else if (strcasecmp(Name,"link")==0) Links=CopyStr(Links,Value);
else if (strcasecmp(Name,"+plink")==0) PLinks=MCatStr(PLinks,",",Value,NULL);
else if (strcasecmp(Name,"plink")==0) PLinks=CopyStr(PLinks,Value);

ptr=GetNameValuePair(ptr,"\\S","=",&Name,&Value);
}

pid=getpid();

#ifdef HAVE_UNSHARE
#ifdef CLONE_NEWPID
unshare(CLONE_NEWPID);
#endif

//fork again because CLONE_NEWPID only takes effect after another fork, and creates an 'init' process
child=fork();
if (child==0)
{
#ifdef CLONE_NEWNET
  if (! (Flags & PROC_CONTAINER_NET)) unshare(CLONE_NEWNET);
#endif

  //do these all individually because any one of them might be rejected
#ifdef CLONE_NEWIPC
  unshare(CLONE_NEWIPC);
#endif

#ifdef CLONE_NEWUTS
  unshare(CLONE_NEWUTS);
#endif

#ifdef CLONE_FS
  unshare(CLONE_FS);
#endif

  val=StrLen(HostName);
  if (val != 0) sethostname(HostName, val);
  else sethostname("container", 9);

#ifdef CLONE_NEWNS
  unshare(CLONE_NEWNS);
#endif
}
else ProcessContainerInit(-1, -1, child);
#endif

	if (StrValid(Dir)) Tempstr=FormatStr(Tempstr,Dir,pid);
	else Tempstr=FormatStr(Tempstr,"%d.container",pid);

	mkdir(Tempstr,700); 
	FileSystemMount("",Tempstr,"tmpfs","");
	chdir(Tempstr);

	ptr=GetToken(ROMounts,",",&Value,GETTOKEN_QUOTES);
	while (ptr)
	{
	FileSystemMount(Value,"","bind","ro");
	ptr=GetToken(ptr,",",&Value,GETTOKEN_QUOTES);
	}

	ptr=GetToken(RWMounts,",",&Value,GETTOKEN_QUOTES);
	while (ptr)
	{
	FileSystemMount(Value,"","bind","");
	ptr=GetToken(ptr,",",&Value,GETTOKEN_QUOTES);
	}

	ptr=GetToken(Links,",",&Value,GETTOKEN_QUOTES);
	while (ptr)
	{
	link(Value,GetBasename(Value));
	ptr=GetToken(ptr,",",&Value,GETTOKEN_QUOTES);
	}

	ptr=GetToken(PLinks,",",&Value,GETTOKEN_QUOTES);
	while (ptr)
	{
	MakeDirPath(Value,0777);
	link(Value,Value);
	ptr=GetToken(ptr,",",&Value,GETTOKEN_QUOTES);
	}


	mkdir("proc",0700);
	FileSystemMount("","proc","proc","");

	if (chroot(".") == -1) RaiseError(ERRFLAG_ERRNO, "chroot", "failed to chroot to curr directory");
	if (! (LibUsefulFlags & LU_ATEXIT_REGISTERED)) atexit(LibUsefulAtExit);
	LibUsefulFlags |= LU_CONTAINER | LU_ATEXIT_REGISTERED;
	
DestroyString(Tempstr);
DestroyString(HostName);
DestroyString(Name);
DestroyString(Value);
DestroyString(Links);
DestroyString(PLinks);
DestroyString(Dir);
}


int ProcessApplyConfig(const char *Config)
{
char *User=NULL, *Group=NULL, *Dir=NULL, *HostName=NULL;
char *Name=NULL, *Value=NULL;
const char *ptr;
struct rlimit limit;
rlim_t val;
int Flags=0, i;
long uid=0, gid=0;

User=CopyStr(User,"");
Group=CopyStr(Group,"");
ptr=GetNameValuePair(Config,"\\S","=",&Name,&Value);
while (ptr)
{
	if (strcasecmp(Name,"User")==0) User=CopyStr(User, Value);
	else if (strcasecmp(Name,"Group")==0) Group=CopyStr(Group, Value);
	else if (strcasecmp(Name,"Dir")==0) Dir=CopyStr(Dir, Value);
	else if (strcasecmp(Name,"PidFile")==0) WritePidFile(Value);
	else if (strcasecmp(Name,"prio")==0) setpriority(PRIO_PROCESS, 0, atoi(Value));
	else if (strcasecmp(Name,"nice")==0) setpriority(PRIO_PROCESS, 0, atoi(Value));
	else if (strcasecmp(Name,"priority")==0) setpriority(PRIO_PROCESS, 0, atoi(Value));
	else if (strcasecmp(Name,"chroot")==0) Flags |= PROC_CHROOT;
	else if (strcasecmp(Name,"sigdef")==0) Flags |= PROC_SIGDEF;
	else if (strcasecmp(Name,"sigdefault")==0) Flags |= PROC_SIGDEF;
	else if (strcasecmp(Name,"setsid")==0) Flags |= PROC_SETSID;
	else if (strcasecmp(Name,"daemon")==0) Flags |= PROC_DAEMON;
	else if (strcasecmp(Name,"demon")==0) Flags |= PROC_DAEMON;
	else if (strcasecmp(Name,"ctrltty")==0) Flags |= PROC_CTRL_TTY;
	else if (strcasecmp(Name,"jail")==0) Flags |= PROC_JAIL;
	else if (strcasecmp(Name,"container")==0) Flags |= PROC_CONTAINER;
	else if (strcasecmp(Name,"trust")==0) Flags |= SPAWN_TRUST_COMMAND;
	else if (strcasecmp(Name,"noshell")==0) Flags |= SPAWN_NOSHELL;
	else if (strcasecmp(Name,"mem")==0) 
	{
		val=(rlim_t) FromMetric(Value, 0);
		limit.rlim_cur=val;
		limit.rlim_max=val;
		setrlimit(RLIMIT_DATA, &limit);
	}
	else if (strcasecmp(Name,"fsize")==0) 
	{
		val=(rlim_t) FromMetric(Value, 0);
		limit.rlim_cur=val;
		limit.rlim_max=val;
		setrlimit(RLIMIT_FSIZE, &limit);
	}
	else if (strcasecmp(Name,"files")==0) 
	{
		val=(rlim_t) FromMetric(Value, 0);
		limit.rlim_cur=val;
		limit.rlim_max=val;
		setrlimit(RLIMIT_NOFILE, &limit);
	}
	else if (strcasecmp(Name,"coredumps")==0) 
	{
		val=(rlim_t) FromMetric(Value, 0);
		limit.rlim_cur=val;
		limit.rlim_max=val;
		setrlimit(RLIMIT_CORE, &limit);
	}
	else if ( (strcasecmp(Name,"procs")==0) || (strcasecmp(Name,"nproc")==0) )
	{
		val=(rlim_t) FromMetric(Value, 0);
		limit.rlim_cur=val;
		limit.rlim_max=val;
		setrlimit(RLIMIT_NPROC, &limit);
	}
	ptr=GetNameValuePair(ptr,"\\S","=",&Name,&Value);
}



//set all signal handlers to default
if (Flags & PROC_SIGDEF)
{
for (i =0; i < NSIG; i++) signal(i,SIG_DFL);
}

//Set controlling tty to be stdin. This means that CTRL-C, SIGWINCH etc is handled for the 
//stdin file descriptor, not for any oher 
if (Flags & PROC_DAEMON) demonize();
else
{
	if (Flags & PROC_SETSID) setsid();
	if (Flags & PROC_CTRL_TTY) tcsetpgrp(0, getpgrp());
}



// This allows us to chroot into a whole different unix directory tree, with its own
// password file etc
if (Flags & PROC_CHROOT)
{
	if (chroot(".") == -1) RaiseError(ERRFLAG_ERRNO, "chroot", "failed to chroot to curr directory");
}

//Look these up now. If PROC_CHROOT then we expect /etc/group and /etc/passwd within the 
//chroot. if PROC_JAIL or PROC_CONTAINER, we are still in root filesystem, and grab uid gid
//before our later chroot
if (StrValid(User)) uid=LookupUID(User);
if (StrValid(Group)) gid=LookupGID(Group);


if (StrValid(Dir)) chdir(Dir);

if (Flags & PROC_CONTAINER) ProcessContainer(Config);

//Always do group first, otherwise we'll lose ability to switch user/group
if (gid > 0) SwitchGID(gid);
if (uid > 0) SwitchUID(uid);



//Must do this last! After parsing Config, and also after functions like
//SwitchUser that will need access to /etc/passwd
if (Flags & PROC_JAIL) 
{
	if (chroot(".") == -1) RaiseError(ERRFLAG_ERRNO, "chroot", "failed to chroot to curr directory");
}

DestroyString(HostName);
DestroyString(Value);
DestroyString(Group);
DestroyString(User);
DestroyString(Name);
DestroyString(Dir);

return(Flags);
}


/* This function turns our process into a demon */
int demonize()
{
int result, i=0;

LogFileFlushAll(TRUE);
//Don't fork with context here, as a demonize involves two forks, so
//it's wasted work here.
result=fork();
if (result != 0) exit(0);

/*we can only get to here if result= 0 i.e. we are the child process*/
setsid();

result=fork();
if (result !=0) exit(0);
umask(0);

/* close stdin, stdout and std error, but only if they are a tty. In some  */
/* situations (like working out of cron) we may not have been given in/out/err */
/* and thus the first files we open will be 0,1,2. If we close them, we will have */
/* closed files that we need! Alternatively, the user may have used shell redirection */
/* to send output for a file, and I'm sure they don't want us to close that file */

//for (i=0; i < 3; i++)
{
  if (isatty(i))
  {
    close(i);
    /* reopen to /dev/null so that any output gets thrown away */
    /* but the program still has somewhere to write to         */
    open("/dev/null",O_RDWR);
  }
}


return(1);
}
