#include "SpawnPrograms.h"
#include "Log.h"
#include "pty.h"
#include "file.h"
#include "string.h"
#include <sys/ioctl.h>
#include <sys/resource.h>

//This is the function we call in the child process for 'SpawnCommand' 
int BASIC_FUNC_EXEC_COMMAND(void *Command)
{
int result;

result=execl("/bin/sh","/bin/sh","-c",(char *) Command,NULL);

return(result);
}

pid_t ForkWithContext(const char *User, const char *Dir, const char *Group)
{
pid_t pid;

LogFileFlushAll(TRUE);
pid=fork();
if (pid==0)
{
	if (StrLen(Dir)) chdir(Dir);
	if (StrLen(Group)) SwitchGroup(Group);
	if (StrLen(User)) SwitchUser(User);
}
return(pid);
}


int ForkWithIO(int StdIn, int StdOut, int StdErr)
{
pid_t pid;
int fd;

pid=ForkWithContext(NULL, NULL, NULL);
if (pid==0)
{
	if (StdIn > -1) 
	{
		if (StdIn !=0) 
		{
			close(0);
			dup(StdIn);
		}
	}
	else
	{
		fd=open("/dev/null",O_RDONLY);
		dup(fd);
		close(fd);
	}

	if (StdOut > -1) 
	{
		if (StdOut !=1) 
		{
			close(1);
			dup(StdOut);
		}
	}
	else
	{
		fd=open("/dev/null",O_WRONLY);
		dup(fd);
		close(fd);
	}

	if (StdErr > -1) 
	{
		if (StdErr !=2) 
		{
		close(2);
		dup(StdErr);
		}
	}
}


return(pid);
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

result=ForkWithContext(NULL, NULL, NULL);
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




void SpawnApplyConfig(const char *Config, int Flags)
{
char *User=NULL, *Group=NULL, *Dir=NULL;
char *Name=NULL, *Value=NULL;
const char *ptr;
struct rlimit limit;
rlim_t val;

int i;

//set all signal handlers to default
if (Flags & SPAWN_SIGDEF)
{
for (i =0; i < NSIG; i++) signal(i,SIG_DFL);
}

//Set controlling tty to be stdin. This means that CTRL-C, SIGWINCH etc is handled for the 
//stdin file descriptor, not for any oher 
if (Flags & SPAWN_DAEMON) demonize();
else
{
	if (Flags & SPAWN_SETSID) setsid();
	if (Flags & SPAWN_CTRL_TTY) tcsetpgrp(0, getpgrp());
}

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
	else if (strcasecmp(Name,"mem")==0) 
	{
		val=(rlim_t) ParseHumanReadableDataQty(Value, 0);
		limit.rlim_cur=val;
		limit.rlim_max=val;
		setrlimit(RLIMIT_DATA, &limit);
	}
	else if (strcasecmp(Name,"fsize")==0) 
	{
		val=(rlim_t) ParseHumanReadableDataQty(Value, 0);
		limit.rlim_cur=val;
		limit.rlim_max=val;
		setrlimit(RLIMIT_FSIZE, &limit);
	}
	else if (strcasecmp(Name,"files")==0) 
	{
		val=(rlim_t) ParseHumanReadableDataQty(Value, 0);
		limit.rlim_cur=val;
		limit.rlim_max=val;
		setrlimit(RLIMIT_NOFILE, &limit);
	}
	else if (strcasecmp(Name,"coredumps")==0) 
	{
		val=(rlim_t) ParseHumanReadableDataQty(Value, 0);
		limit.rlim_cur=val;
		limit.rlim_max=val;
		setrlimit(RLIMIT_CORE, &limit);
	}
	else if ( (strcasecmp(Name,"procs")==0) || (strcasecmp(Name,"nproc")==0) )
	{
		val=(rlim_t) ParseHumanReadableDataQty(Value, 0);
		limit.rlim_cur=val;
		limit.rlim_max=val;
		setrlimit(RLIMIT_NPROC, &limit);
	}
	ptr=GetNameValuePair(ptr,"\\S","=",&Name,&Value);
}

// This allows us to chroot into a whole different unix directory tree, with its own
// password file etc
if (Flags & SPAWN_CHROOT) chroot(".");

if (StrLen(Dir)) chdir(Dir);

//Always do group first, otherwise we'll lose ability to switch user/group
if (StrLen(Group)) SwitchGroup(Group);
if (StrLen(User)) SwitchUser(User);

//Must do this last! After parsing Config, and also after functions like
//SwitchUser that will need access to /etc/passwd
if (Flags & SPAWN_JAIL) chroot(".");

DestroyString(Name);
DestroyString(Value);
DestroyString(User);
DestroyString(Group);
DestroyString(Dir);
}


//This Function eliminates characters from a string that can be used to trivially achieve code-exec via the shell
char *MakeShellSafeString(char *RetStr, const char *String, int SafeLevel)
{
char *Tempstr=NULL;
char *BadChars=";|&`";

if (SafeLevel==SHELLSAFE_BLANK) 
{
	Tempstr=CopyStr(RetStr,String);
	strmrep(Tempstr,BadChars,' ');
}
else Tempstr=QuoteCharsInStr(RetStr,String,BadChars);

if (strcmp(Tempstr,String) !=0) 
{
	//if (EventCallback) EventCallback(String);
}
return(Tempstr);
}


void SwitchProgram(const char *CommandLine, int Flags, const char *Config)
{
char **argv, *ptr;
char *Token=NULL, *SafeStr=NULL;
int i;

if (Flags & SPAWN_TRUST_COMMAND) SafeStr=CopyStr(SafeStr,CommandLine);
else SafeStr=MakeShellSafeString(SafeStr, CommandLine, 0);

SafeStr=MakeShellSafeString(SafeStr,CommandLine,0);
argv=(char **) calloc(101,sizeof(char *));
ptr=SafeStr;
for (i=0; i < 100; i++)
{
	ptr=GetToken(ptr,"\\S",&Token,GETTOKEN_QUOTES);
	if (! ptr) break;
	argv[i]=CopyStr(argv[i],Token);
}

SpawnApplyConfig(Config, Flags);

DestroyString(Token);
DestroyString(SafeStr);

/* we are the child so we continue */
execv(argv[0],argv);
//no point trying to free stuff here, we will no longer
//be the main program
}




pid_t SpawnWithIO(const char *CommandLine, int Flags, const char *Config, int StdIn, int StdOut, int StdErr)
{
pid_t pid;

pid=ForkWithIO(StdIn,StdOut,StdErr);
if (pid==0)
{
SwitchProgram(CommandLine, Flags, Config);
_exit(pid);
}

return(pid);
}


int Spawn(const char *ProgName, int Flags, const char *Config)
{
int pid;

pid=ForkWithIO(0,1,2);
if (pid==0)
{
	SwitchProgram(ProgName, Flags, Config);
	_exit(pid);
}
return(pid);
}


/* This creates a child process that we can talk to using a couple of pipes*/
pid_t PipeSpawnFunction(int *infd,int  *outfd,int  *errfd, BASIC_FUNC Func, void *Data, int Flags, const char *Config)
{
pid_t pid;
int channel1[2], channel2[2], channel3[2], DevNull=-1;

if (infd) pipe(channel1);
if (outfd) pipe(channel2);
if (errfd) pipe(channel3);

pid=ForkWithContext(NULL,NULL,NULL);
if (pid==0)
{
	/* we are the child */
	if (infd) close(channel1[1]);
	else if (DevNull==-1) DevNull=open("/dev/null",O_RDWR);
	if (outfd) close(channel2[0]);
	else if (DevNull==-1) DevNull=open("/dev/null",O_RDWR);
	if (errfd) close(channel3[0]);
	else if (DevNull==-1) DevNull=open("/dev/null",O_RDWR);
	
	/*close stdin, stdout and stderr*/
	close(0);
	close(1);
	close(2);
	/*channel 1 is going to be our stdin, so we close the writing side of it*/
	if (infd) dup(channel1[0]);
	else dup(DevNull);
	/* channel 2 is stdout */
	if (outfd) dup(channel2[1]);
	else dup(DevNull);
	/* channel 3 is stderr */
	if (errfd)
	{
		//Yes, we can pass an integer value as errfd, even though it's an int *. 
		//This is probably a bad idea, and will likely be changed in future releases
		if (errfd==(int *) COMMS_COMBINE_STDERR) dup(channel2[1]);
		else dup(channel3[1]);
	}
	else dup(DevNull);
	
	
	SpawnApplyConfig(Config, Flags);
	Func(Data);
	exit(0);
	}
else // This is the parent process, not the spawned child
{
	/* we close the appropriate halves of the link */
	if (infd) 
	{
		close(channel1[0]);
		*infd=channel1[1];
	}
	if (outfd)
	{
		close(channel2[1]);
		*outfd=channel2[0];
	}
	if (errfd)
	{
		close(channel3[1]);	
		//Yes, we can pass an integer value as errfd, even though errfd is an int *. 
		//This is probably a bad idea, and will likely be changed in future releases
		if (errfd != (int *) COMMS_COMBINE_STDERR) *errfd=channel3[0];
	}
}

return(pid);
}



pid_t PipeSpawn(int *infd,int  *outfd,int  *errfd, const char *Command, int Flags, const char *Config)
{
return(PipeSpawnFunction(infd,outfd,errfd, BASIC_FUNC_EXEC_COMMAND, (void *) Command, Flags, Config));
}




pid_t PseudoTTYSpawnFunction(int *ret_pty, BASIC_FUNC Func, void *Data, int Flags, const char *Config)
{
pid_t pid=-1;
int tty, pty, i;

if (GrabPseudoTTY(&pty, &tty, Flags))
{
pid=ForkWithContext(NULL,NULL,NULL);
if (pid==0)
{
for (i=0; i < 4; i++) close(i);
close(pty);

setsid();
ioctl(tty,TIOCSCTTY,0);

dup(tty);
dup(tty);
dup(tty);

///now that we've dupped it, we don't need to keep it open
//as it will be open on stdin/stdout
close(tty);

SpawnApplyConfig(Config, Flags);
Func((char *) Data);
_exit(0);
}

close(tty);
}

*ret_pty=pty;
return(pid);
}


pid_t PseudoTTYSpawn(int *pty, const char *Command, int Flags, const char *Config)
{
return(PseudoTTYSpawnFunction(pty, BASIC_FUNC_EXEC_COMMAND, (void *) Command, Flags, Config));
}





STREAM *STREAMSpawnFunction(BASIC_FUNC Func, void *Data, int Flags, const char *Config)
{
int to_fd, from_fd, *iptr;
pid_t pid=0;
STREAM *S=NULL;
char *Tempstr=NULL;

if (Flags & COMMS_BY_PTY)
{
	pid=PseudoTTYSpawn(&to_fd, Tempstr, Flags, Config);
}
else 
{
	iptr=NULL;
	if (Flags & COMMS_COMBINE_STDERR) iptr=(int *) COMMS_COMBINE_STDERR;
	pid=PipeSpawnFunction(&to_fd, &from_fd, iptr, Func, Data, Flags, Config);
}

if (pid > 0) S=STREAMFromDualFD(from_fd, to_fd);
if (S)
{
	STREAMSetFlushType(S,FLUSH_LINE,0,0);
	Tempstr=FormatStr(Tempstr,"%d",pid);
	STREAMSetValue(S,"PeerPID",Tempstr);
}

DestroyString(Tempstr);
return(S);
}


STREAM *STREAMSpawnCommand(const char *Command, int Flags, const char *Config)
{
STREAM *S=NULL;
char *Tempstr=NULL;

if (Flags & SPAWN_TRUST_COMMAND) Tempstr=CopyStr(Tempstr,Command);
else Tempstr=MakeShellSafeString(Tempstr, Command, 0);

S=STREAMSpawnFunction(BASIC_FUNC_EXEC_COMMAND, Tempstr, Flags, Config);
DestroyString(Tempstr);
return(S);
}
