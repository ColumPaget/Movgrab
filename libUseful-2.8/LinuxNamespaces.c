
void JailMount(const char *Dir)
{
const char *ptr;

ptr=Dir;
if (*ptr=='/') ptr++;
MakeDirPath(ptr,0700);
mount(Dir,ptr,"",MS_BIND,NULL);
mount(NULL,ptr,"",MS_REMOUNT|MS_BIND|MS_RDONLY,NULL);
}

void InitSigHandler(int sig)
{

}

void JailInitProcess(int tunfd, int linkfd, pid_t Child, const char *Dirs)
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
	chroot(".");
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

	ptr=GetToken(Dirs, ":", &Token, GETTOKEN_QUOTES);
	while (ptr)
	{
		umount(Token);
		rmdir(Token);
		ptr=GetToken(ptr, ":", &Token, GETTOKEN_QUOTES);
	}
	umount("/proc");
	rmdir("/proc");

	STREAMClose(TunS);
	STREAMClose(LinkS);

	_exit(0);
}


void LinuxNamespaceJail(int netfd, const char *HostName, const char *Dir, const char *Mounts, const char *Setup)
{
int i, val;
char *Token=NULL;
const char *ptr;
int tunfd;

unshare(CLONE_NEWPID);

//fork again because CLONE_NEWPID only takes effect after another fork, and creates an 'init' process
if (fork()==0)
{
	unshare(CLONE_NEWNET);

	//do these all individually because any one of them might be rejected
	unshare(CLONE_NEWIPC);
	unshare(CLONE_NEWUTS);
	//unshare(CLONE_NEWNS);

	val=StrLen(HostName);
	if (val > 0) sethostname(HostName, val);

	//we must create this here so it can be setup by the setup
	//script. However, only the init child process will need
	//the file descriptor long term
	tunfd=TunIface("eth0");
	if (StrValid(Setup)) system(Setup);

	//must after most unshares
	mkdir("proc/",0777);
	mount(NULL,"proc","proc",0,NULL);
	mkdir("tmp/",0777);
	mount(NULL,"tmp","tmpfs",0,NULL);


	//these are mounted before forking off the init process
	//to prevent race conditions. The init process will be
	//the last process running in the jail though, and it
	//will do the umounts
	chdir(Dir);
	ptr=GetToken(Mounts, ":", &Token, GETTOKEN_QUOTES);
	while (ptr)
	{
	Token=SlashTerminateDirectoryPath(Token);
	JailMount(Token);
	ptr=GetToken(ptr, ":", &Token, GETTOKEN_QUOTES);
	}

	//do last as we lose our root capabilities
	//unshare(CLONE_NEWUSER);

	//NB NOT EQUAL ZERO
	val=fork();
	if (val !=0) JailInitProcess(tunfd, netfd, val, Mounts);
	else close(tunfd);

	//this process is the child of the init fork
}
else 
{
	while(waitpid(-1,NULL,0) !=-1);
	_exit(0);
}

DestroyString(Token);
}


int NetPipeParse(const char *Value)
{
const char *ptr;
int retfd, otherfd;

otherfd=strtol(Value, &ptr, 10);
ptr++;
retfd=strtol(ptr, &ptr, 10);

close(otherfd);
return(retfd);
}
