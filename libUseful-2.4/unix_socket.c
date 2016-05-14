#include "unix_socket.h"
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>


int OpenUnixSocket(const char *Path, int Type)
{
int sock;
struct sockaddr_un sa;
int val;

if (Type==0) Type=SOCK_STREAM;

sock=socket(AF_UNIX, Type, FALSE);
if (sock==-1) return(-1);

memset(&sa,0,sizeof(struct sockaddr_un));
sa.sun_family=AF_UNIX;
strcpy(sa.sun_path,Path);
val=sizeof(sa);
if (connect(sock,(struct sockaddr *) &sa,val)==0) return(sock);

close(sock);
return(-1);
}



int STREAMConnectUnixSocket(STREAM *S, const char *Path, int ConType)
{

	S->in_fd=OpenUnixSocket(Path, ConType);
	if (S->in_fd==-1) return(FALSE);
	S->out_fd=S->in_fd;
	S->Type=ConType;

	return(TRUE);
}



int InitUnixServerSock(int Type, const char *Path)
{
int sock;
struct sockaddr_un sa;
socklen_t salen;
int result;

if (Type==0) Type=SOCK_STREAM;
sock=socket(AF_UNIX, Type, 0);
if (sock <0) return(-1);

//No reason to pass server/listen sockets across an exec
fcntl(sock, F_SETFD, FD_CLOEXEC);

result=1;
salen=sizeof(result);
strcpy(sa.sun_path,Path);
sa.sun_family=AF_UNIX;
salen=sizeof(struct sockaddr_un);
result=bind(sock,(struct sockaddr *) &sa, salen);

if ((result==0) && (Type==SOCK_STREAM))
{
 result=listen(sock,10);
}

if (result==0) return(sock);
else
{
close(sock);
return(-1);
}
}



int UnixServerSockAccept(int ServerSock)
{
struct sockaddr_un sa;
socklen_t salen;
int sock;

salen=sizeof(sa);
sock=accept(ServerSock,(struct sockaddr *) &sa,&salen);
return(sock);
}



