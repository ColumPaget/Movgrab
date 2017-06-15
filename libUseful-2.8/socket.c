#include "socket.h"
#include "ConnectionChain.h"
#include "URL.h"
#include "unix_socket.h"

#include <arpa/inet.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <unistd.h>


#ifdef linux
#include <linux/netfilter_ipv4.h>
#endif


int IsIP4Address(const char *Str)
{
const char *ptr;
int dot_count=0;
int AllowDot=FALSE;

if (! StrValid(Str)) return(FALSE);

for (ptr=Str; *ptr != '\0'; ptr++)
{
	if (*ptr == '.') 
	{
		if (! AllowDot) return(FALSE);
		dot_count++;
		AllowDot=FALSE;
	}
	else 
	{
		if (! isdigit(*ptr)) return(FALSE);
		AllowDot=TRUE;
	}
}

if (dot_count != 3) return(FALSE);

return(TRUE);
}


int IsIP6Address(const char *Str)
{
const char *ptr;
const char *IP6CHARS="0123456789abcdefABCDEF:%";
int result=FALSE;

if (! StrValid(Str)) return(FALSE);

ptr=Str;
if (*ptr == '[') ptr++;

for (; *ptr != '\0'; ptr++)
{
 //dont check after a '%', as this can be a netdev postfix
 if (*ptr=='%') break;
 if (*ptr==']') break;

 //require at least one ':'
 if (*ptr==':') result=TRUE;

 if (! strchr(IP6CHARS,*ptr)) return(FALSE);
}

return(result);
}




/* This is a simple function to decide if a string is an IP address as   */
/* opposed to a host/domain name.                                        */

int IsIPAddress(const char *Str)
{
if (IsIP4Address(Str) || IsIP6Address(Str)) return(TRUE);
return(FALSE);
}


char *LookupHostIP(const char *Host)
{
struct hostent *hostdata;

   hostdata=gethostbyname(Host);
   if (!hostdata) 
   {
     return(NULL);
   }

//inet_ntoa shouldn't need this cast to 'char *', but it emitts a warning
//without it
return((char *) inet_ntoa(*(struct in_addr *) *hostdata->h_addr_list));
}





int IsSockConnected(int sock)
{
struct sockaddr_in sa;
socklen_t salen;
int result;

if (sock==-1) return(FALSE);
salen=sizeof(sa);
result=getpeername(sock,(struct sockaddr *) &sa, &salen);
if (result==0) return(TRUE);
if (errno==ENOTCONN) return(SOCK_CONNECTING);
return(FALSE);
}


//Socket options wrapped in ifdef statements to handle systems that lack certain options
int SockSetOptions(int sock, int SetFlags, int UnsetFlags)
{
int result;

result=TRUE;
#ifdef SO_BROADCAST
if (SetFlags & SOCK_BROADCAST) result=setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &result,sizeof(int));
#endif

#ifdef SO_DONTROUTE
if (SetFlags & SOCK_DONTROUTE) result=setsockopt(sock, SOL_SOCKET, SO_DONTROUTE, &result,sizeof(int));
#endif

#ifdef SO_REUSEPORT
if (SetFlags & SOCK_REUSEPORT) result=setsockopt(sock, SOL_SOCKET, SO_REUSEPORT, &result,sizeof(int));
#endif

#ifdef IP_TRANSPARENT
if (SetFlags & SOCK_TPROXY) result=setsockopt(sock, IPPROTO_IP, IP_TRANSPARENT, &result,sizeof(int));
#endif

#ifdef SO_PASSCRED
if (SetFlags & SOCK_PEERCREDS) result=setsockopt(sock, SOL_SOCKET, SO_PASSCRED, &result,sizeof(int));
#endif

#ifdef SO_KEEPALIVE
//Default is KEEPALIVE ON
setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, &result,sizeof(int));
#endif

if (SetFlags & CONNECT_NONBLOCK) fcntl(sock,F_SETFL,O_NONBLOCK);


#ifdef SO_BROADCAST
if (UnsetFlags & SOCK_BROADCAST) result=setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &result,sizeof(int));
#endif

#ifdef SO_DONTROUTE
if (UnsetFlags & SOCK_DONTROUTE) result=setsockopt(sock, SOL_SOCKET, SO_DONTROUTE, &result,sizeof(int));
#endif

#ifdef SO_REUSEPORT
if (UnsetFlags & SOCK_REUSEPORT) result=setsockopt(sock, SOL_SOCKET, SO_REUSEPORT, &result,sizeof(int));
#endif

#ifdef IP_TRANSPARENT
if (UnsetFlags & SOCK_TPROXY) result=setsockopt(sock, IPPROTO_IP, IP_TRANSPARENT, &result,sizeof(int));
#endif

#ifdef SO_PASSCRED
if (UnsetFlags & SOCK_PEERCREDS) result=setsockopt(sock, SOL_SOCKET, SO_PASSCRED, &result,sizeof(int));
#endif

result=FALSE;
#ifdef SO_KEEPALIVE
if (SetFlags & SOCK_NOKEEPALIVE) setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, &result,sizeof(int));
#endif
}





int SockSetAttribute(int sock, int Attrib, int Value)
{


}

int SockGetAttribute(int sock, int Attrib, int Value)
{


}


int IP6SockAddrCreate(struct sockaddr **ret_sa, const char *Addr, int Port)
{
struct sockaddr_in6 *sa6;
char *Token=NULL, *ptr;
socklen_t salen;


  sa6=(struct sockaddr_in6 *) calloc(1,sizeof(struct sockaddr_in6));
  if (StrValid(Addr))
  {
		if (IsIP4Address(Addr))
		{
			Token=MCopyStr(Token,"::ffff:",Addr,NULL);
			ptr=Token;
		}
		else
		{
    ptr=GetToken(Addr, "%",&Token,0);
    if (StrValid(ptr)) sa6->sin6_scope_id=if_nametoindex(ptr);

    ptr=Token;
    if (*ptr == '[')
    {
      ptr=strchr(Token,']');
      if (ptr) *ptr='\0';
      ptr=Token+1;
    }
		}

    inet_pton(AF_INET6, ptr, &(sa6->sin6_addr));
  }
  else sa6->sin6_addr=in6addr_any;
  sa6->sin6_port=htons(Port);
  sa6->sin6_family=AF_INET6;

  *ret_sa=(struct sockaddr *) sa6;
  salen=sizeof(struct sockaddr_in6);


DestroyString(Token);

return(salen);
}


int IP4SockAddrCreate(struct sockaddr **ret_sa, const char *Addr, int Port)
{
	struct sockaddr_in *sa4;
	socklen_t salen;

  sa4=(struct sockaddr_in *) calloc(1,sizeof(struct sockaddr_in));
  if (! StrValid(Addr)) sa4->sin_addr.s_addr=INADDR_ANY;
	else sa4->sin_addr.s_addr=StrtoIP(Addr);

  sa4->sin_port=htons(Port);
  sa4->sin_family=AF_INET;
  *ret_sa=(struct sockaddr *) sa4;
  salen=sizeof(struct sockaddr_in);
	return(salen);
}


int SockAddrCreate(struct sockaddr **ret_sa, const char *Host, int Port)
{
const char *p_Addr="";
socklen_t salen;

if (StrValid(Host))
{
if (! IsIPAddress(Host)) p_Addr=LookupHostIP(Host);
else p_Addr=Host;
}

#ifdef USE_INET6
return(IP6SockAddrCreate(ret_sa, p_Addr, Port));
#endif

return(IP4SockAddrCreate(ret_sa, p_Addr, Port));
}




int BindSock(int Type, const char *Address, int Port, int Flags)
{
	int result;
	struct sockaddr *sa;
	socklen_t salen;
	int fd;


	salen=SockAddrCreate(&sa, Address, Port);
	if (salen==0) return(-1);
	fd=socket(sa->sa_family, Type, 0);
	result=bind(fd, sa, salen);
	free(sa);

	if (result !=0)
	{
		close(fd);
		return(-1);
	}

	//No reason to pass server/listen fdets across an exec
	if (Flags & BIND_CLOEXEC) fcntl(fd, F_SETFD, FD_CLOEXEC);
	result=1;
	setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&result,sizeof(result));
	if (Flags & BIND_LISTEN) result=listen(fd,10);


	return(fd);
}


int GetHostARP(const char *IP, char **Device, char **MAC)
{
char *Tempstr=NULL, *Token=NULL;
int result=FALSE;
const char *ptr;
FILE *F;

Tempstr=SetStrLen(Tempstr, 255);
F=fopen("/proc/net/arp","r");
if (F)
{
	*Device=CopyStr(*Device,"remote");
	*MAC=CopyStr(*MAC,"remote");
	//Read Title Line
	fgets(Tempstr,255,F);

	while (fgets(Tempstr,255,F))
	{
		StripTrailingWhitespace(Tempstr);
		ptr=GetToken(Tempstr," ",&Token,0);
		if (strcmp(Token,IP)==0)
		{
			while (isspace(*ptr)) ptr++;
			ptr=GetToken(ptr," ",&Token,0);

			while (isspace(*ptr)) ptr++;
			ptr=GetToken(ptr," ",&Token,0);

			while (isspace(*ptr)) ptr++;
			ptr=GetToken(ptr," ",MAC,0);
			strlwr(*MAC);

			while (isspace(*ptr)) ptr++;
			ptr=GetToken(ptr," ",&Token,0);

			while (isspace(*ptr)) ptr++;
			ptr=GetToken(ptr," ",Device,0);

			result=TRUE;
		}
	}
fclose(F);
}

DestroyString(Tempstr);
DestroyString(Token);

return(result);
}


/* This is a bit of kernel magic to decide where the client was trying */
/* to connect to before it got transparently proxied */
int GetSockDestination(int sock, char **Host, int *Port)
{
int salen;
struct sockaddr_storage sa;
char *Tempstr=NULL;
int result=FALSE;

#ifdef SO_ORIGINAL_DST
salen=sizeof(struct sockaddr_in);

if (getsockopt(sock, SOL_IP, SO_ORIGINAL_DST, (char *) &sa, &salen) ==0)
{
        *Host=SetStrLen(*Host,NI_MAXHOST);
        Tempstr=SetStrLen(Tempstr,NI_MAXSERV);
        salen=sizeof(struct sockaddr_storage);
        getnameinfo((struct sockaddr *) &sa, salen, *Host, NI_MAXHOST, Tempstr, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);
        *Port=atoi(Tempstr);
}

result=TRUE;
#endif

DestroyString(Tempstr);

return(result);
}




const char *GetInterfaceIP(const char *Interface)
{
 int fd, result;
 struct ifreq ifr;

 fd = socket(AF_INET, SOCK_DGRAM, 0);
 if (fd==-1) return("");

 ifr.ifr_addr.sa_family = AF_INET;
 strncpy(ifr.ifr_name, Interface, IFNAMSIZ-1);
 result=ioctl(fd, SIOCGIFADDR, &ifr);
 if (result==-1) return("");
 close(fd);

 return(inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
}


#ifdef __GNU_LIBRARY__


#include <netinet/ip_icmp.h>

/*--------------------------------------------------------------------*/
/*--- checksum - standard 1s complement checksum                   ---*/
/*--------------------------------------------------------------------*/
unsigned short checksum(void *b, int len)
{
    unsigned short *buf = b;
    unsigned int sum=0;
    unsigned short result;

    for ( sum = 0; len > 1; len -= 2 )
        sum += *buf++;
    if ( len == 1 )
        sum += *(unsigned char*)buf;
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    result = ~sum;
    return result;
}


int ICMPSend(int sock, const char *Host, int Type, int Code, int TTL, char *Data, int len)
{
struct icmphdr *ICMPHead;
char *Tempstr=NULL;
int packet_len;
static int seq=0;
struct sockaddr_in sa;
int result;

result=TTL;
if (setsockopt(sock, SOL_IP, IP_TTL, &result, sizeof(int)) != 0) return(0);

packet_len=len+sizeof(struct icmphdr);
Tempstr=(char *) calloc(1, packet_len+1);
ICMPHead=(struct icmphdr *) Tempstr;
ICMPHead->type=ICMP_ECHO;
ICMPHead->un.echo.id=getpid();
ICMPHead->un.echo.sequence=seq++;
if ((len > 0) && Data) memcpy(Tempstr + sizeof(struct icmphdr), Data, len);
ICMPHead->checksum=checksum(Tempstr, packet_len);

memset(&sa, 0, sizeof(sa));
sa.sin_family=AF_INET;
sa.sin_port=0;
sa.sin_addr.s_addr=StrtoIP(Host);
result=sendto(sock, Tempstr, packet_len, 0, (struct sockaddr*) &sa, sizeof(struct sockaddr));

DestroyString(Tempstr);

return(result);
}

#endif




int UDPOpen(const char *Addr, int Port, int Flags)
{
	int fd;

	fd=BindSock(SOCK_DGRAM, Addr, Port, 0);
	if (fd > -1) SockSetOptions(fd, Flags, 0);
	return(fd);
}



int UDPRecv(int sock,  char *Buffer, int len, char **Addr, int *Port)
{
	char *Tempstr=NULL;
	struct sockaddr_in sa;
	socklen_t salen;
	int result;
	int fd;

	salen=sizeof(sa);
	result=recvfrom(sock, Buffer, len,0, (struct sockaddr *) &sa, &salen);
	if (result > -1)
	{
	*Addr=SetStrLen(*Addr,NI_MAXHOST);
	Tempstr=SetStrLen(Tempstr,NI_MAXSERV);
	getnameinfo((struct sockaddr *) &sa, salen, *Addr, NI_MAXHOST, Tempstr, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);

	*Port=atoi(Tempstr);
	}

	DestroyString(Tempstr);

return(result);
}



int UDPSend(int sock, const char *Host, int Port, char *Data, int len)
{
struct sockaddr *sa=NULL;
socklen_t salen;
int result;

salen=SockAddrCreate(&sa, Host, Port);
if (salen==0) return(-1);

result=sendto(sock, Data, len, 0, sa , salen);
free(sa);
return(result);
}



int STREAMSendDgram(STREAM *S, const char *Host, int Port, char *Data, int len)
{
return(UDPSend(S->out_fd, Host, Port, Data, len));
}




#ifdef USE_INET6
int IPServerInit(int Type, const char *Address, int Port)
{
int sock;
//struct sockaddr_storage sa;
struct sockaddr_in *sa4;
struct sockaddr_in6 *sa6;
int result;
const char *p_Addr=NULL, *ptr;


if (! IsIPAddress(Address)) p_Addr=GetInterfaceIP(Address);
else p_Addr=Address;

if (Type==0) Type=SOCK_STREAM;
sock=BindSock(Type, p_Addr, Port, BIND_CLOEXEC | BIND_LISTEN);

return(sock);
}

#else 

int IPServerInit(int Type, const char *Address, int Port)
{
struct sockaddr_in sa;
int result;
const char *ptr=NULL;
socklen_t salen;
int sock;


if (StrLen(Address))
{
if (IsIP6Address(Address)) return(-1);
else if (IsIP4Address(Address)) ptr=Address;
else ptr=GetInterfaceIP(Address);
}

if (Type==0) Type=SOCK_STREAM;
sock=BindSock(Type, ptr, Port, BIND_CLOEXEC | BIND_LISTEN);

return(sock);
}

#endif


int IPServerAccept(int ServerSock, char **Addr)
{
struct sockaddr_storage sa;
socklen_t salen;
int sock;

salen=sizeof(sa);
sock=accept(ServerSock,(struct sockaddr *) &sa, &salen);
if (Addr && (sock > -1)) 
{
*Addr=SetStrLen(*Addr,NI_MAXHOST);
getnameinfo((struct sockaddr *) &sa, salen, *Addr, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
}
return(sock);
}



STREAM *STREAMServerInit(const char *URL)
{
char *Proto=NULL, *Host=NULL, *Token=NULL;
int fd=-1, Port=0, Type;
STREAM *S=NULL;

ParseURL(URL, &Proto, &Host, &Token,NULL, NULL,NULL,NULL);
if (StrValid(Token)) Port=atoi(Token);

switch (*Proto)
{
case 'u':
if (strcmp(Proto,"udp")==0) 
{
	fd=IPServerInit(SOCK_DGRAM,Host,Port);
	Type=STREAM_TYPE_UDP;
}
else if (strcmp(Proto,"unix")==0) 
{
	fd=UnixServerInit(SOCK_STREAM,Host);
	Type=STREAM_TYPE_UNIX_SERVER;
}
else if (strcmp(Proto,"unixdgram")==0) 
{
	fd=UnixServerInit(SOCK_DGRAM,Host);
	Type=STREAM_TYPE_UNIX_DGRAM;
}
else if (strcmp(Proto,"uproxy")==0) 
{
	fd=IPServerInit(SOCK_DGRAM,Host,Port);
	Type=STREAM_TYPE_UPROXY;
	if (fd > -1) SockSetOptions(fd,SOCK_TPROXY,0);
}
break;

case 't':
if (strcmp(Proto,"tcp")==0) 
{
	fd=IPServerInit(SOCK_STREAM,Host,Port);
	Type=STREAM_TYPE_TCP_SERVER;
}
else if (strcmp(Proto,"tproxy")==0)
{
	fd=IPServerInit(SOCK_STREAM,Host,Port);
	Type=STREAM_TYPE_TPROXY;
	if (fd > -1) SockSetOptions(fd,SOCK_TPROXY,0);
}
break;
}

if (fd > -1)
{
	S=STREAMFromFD(fd);
	S->Type=Type;
}

DestroyString(Proto);
DestroyString(Host);
DestroyString(Token);

return(S);
}


STREAM *STREAMServerAccept(STREAM *Serv)
{
char *Tempstr=NULL, *DestIP=NULL;
STREAM *S=NULL;
int fd=-1, type=0, DestPort=0;

if (! Serv) return(NULL);

switch (Serv->Type)
{
case STREAM_TYPE_UNIX_SERVER:
fd=UnixServerAccept(Serv->in_fd);
type=STREAM_TYPE_UNIX_ACCEPT;
break;

case STREAM_TYPE_TCP_SERVER:
fd=IPServerAccept(Serv->in_fd, &Tempstr);
type=STREAM_TYPE_TCP_ACCEPT;
break;

case STREAM_TYPE_TPROXY:
fd=IPServerAccept(Serv->in_fd, &Tempstr);
GetSockDestination(fd, &DestIP, &DestPort);
type=STREAM_TYPE_TCP_ACCEPT;
break;

default:
return(Serv);
break;
}

if (fd > -1) 
{
S=STREAMFromFD(fd);

if (strncmp(Tempstr,"::ffff:",7)==0) STREAMSetValue(S,"Peer",Tempstr+7);
else STREAMSetValue(S,"Peer",Tempstr);
if (StrValid(DestIP))
{
	if (strncmp(DestIP,"::ffff:",7)==0) STREAMSetValue(S,"DestIP",DestIP+7);
	else STREAMSetValue(S,"DestIP",DestIP);
	Tempstr=FormatStr(Tempstr, "%d",DestPort);
	STREAMSetValue(S,"DestPort",Tempstr);
}
S->Type=type;
}

DestroyString(Tempstr);
DestroyString(DestIP);
return(S);
}




#ifdef USE_INET6
int GetSockDetails(int sock, char **LocalAddress, int *LocalPort, char **RemoteAddress, int *RemotePort)
{
socklen_t salen;
int result;
struct sockaddr_storage sa;
char *Tempstr=NULL, *ptr;

*LocalPort=0;
*RemotePort=0;
*LocalAddress=CopyStr(*LocalAddress,"");
*RemoteAddress=CopyStr(*RemoteAddress,"");

salen=sizeof(struct sockaddr_storage);
result=getsockname(sock, (struct sockaddr *) &sa, &salen);

if (result==0)
{
	*LocalAddress=SetStrLen(*LocalAddress,NI_MAXHOST);
	Tempstr=SetStrLen(Tempstr,NI_MAXSERV);
	getnameinfo((struct sockaddr *) &sa, salen, *LocalAddress, NI_MAXHOST, Tempstr, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);
	*LocalPort=atoi(Tempstr);

	if ((strncmp(*LocalAddress,"::ffff:",7)==0) && strchr(*LocalAddress,'.')) 
	{
		ptr=*LocalAddress;
		ptr+=7;
		memmove(*LocalAddress,ptr,StrLen(*LocalAddress)-6);
	}
	

	//Set Address to be the same as control sock, as it might not be INADDR_ANY
	result=getpeername(sock, (struct sockaddr *) &sa, &salen);

	if (result==0)
	{
		*RemoteAddress=SetStrLen(*RemoteAddress,NI_MAXHOST);
		Tempstr=SetStrLen(Tempstr,NI_MAXSERV);
		getnameinfo((struct sockaddr *) &sa, salen, *RemoteAddress, NI_MAXHOST, Tempstr, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);
		*RemotePort=atoi(Tempstr);

		if ((strncmp(*RemoteAddress,"::ffff:",7)==0) && strchr(*RemoteAddress,'.')) 
		{
		ptr=*RemoteAddress;
		ptr+=7;
		memmove(*RemoteAddress,ptr,StrLen(*RemoteAddress)-6);
		}
	}

	//We've got the local sock, so lets still call it a success
	result=0;
}

DestroyString(Tempstr);

if (result==0) return(TRUE);
return(FALSE);
}

#else

int GetSockDetails(int sock, char **LocalAddress, int *LocalPort, char **RemoteAddress, int *RemotePort)
{
socklen_t salen;
int result;
struct sockaddr_in sa;

*LocalPort=0;
*RemotePort=0;
*LocalAddress=CopyStr(*LocalAddress,"");
*RemoteAddress=CopyStr(*RemoteAddress,"");

salen=sizeof(struct sockaddr_in);
result=getsockname(sock, (struct sockaddr *) &sa, &salen);

if (result==0)
{
	*LocalAddress=CopyStr(*LocalAddress,IPtoStr(sa.sin_addr.s_addr));
	*LocalPort=ntohs(sa.sin_port);

	//Set Address to be the same as control sock, as it might not be INADDR_ANY
	result=getpeername(sock, (struct sockaddr *) &sa, &salen);

	if (result==0)
	{
		*RemoteAddress=CopyStr(*RemoteAddress,IPtoStr(sa.sin_addr.s_addr));
		*RemotePort=ntohs(sa.sin_port);
	}

	//We've got the local sock, so lets still call it a success
	result=0;
}

if (result==0) return(TRUE);
return(FALSE);
}

#endif



/* Users will probably only use this function if they want to reconnect   */
/* a broken connection, or reuse a socket for multiple connections, hence */
/* the name... */
int IPReconnect(int sock, const char *Host, int Port, int Flags)
{
socklen_t salen;
int result;
struct sockaddr *sa;


salen=SockAddrCreate(&sa, Host, Port);
if (salen==0) return(-1);

SockSetOptions(sock, Flags, 0);

result=connect(sock,(struct sockaddr *) sa, salen);
if (result==0) result=TRUE;

if ((result==-1) && (Flags & CONNECT_NONBLOCK) && (errno == EINPROGRESS)) result=FALSE;

free(sa);
return(result);
}




int TCPConnectWithAttributes(const char *LocalHost, const char *Host, int Port, int Flags, int TTL, int ToS)
{
int sock, result;

sock=BindSock(SOCK_STREAM, LocalHost, 0, 0);

if (TTL > 0) setsockopt(sock, IPPROTO_IP, IP_TTL, &TTL, sizeof(int));
if (ToS > 0) setsockopt(sock, IPPROTO_IP, IP_TOS, &ToS, sizeof(int));

result=IPReconnect(sock,Host,Port,Flags);
if (result==-1)
{
close(sock);
return(-1);
}

return(sock);

}


int TCPConnect(const char *Host, int Port, int Flags)
{
return(TCPConnectWithAttributes("", Host, Port, Flags, 0, 0));
}






char *GetRemoteIP(int sock)
{
struct sockaddr_in sa;
socklen_t salen;
int result;

salen=sizeof(struct sockaddr_in);
result=getpeername(sock,(struct sockaddr *) &sa, &salen);
if  (result==-1)  
{
if (errno==ENOTSOCK)  return("127.0.0.1");
else return("0.0.0.0");
}

return((char *) inet_ntoa(sa.sin_addr));
}


char *IPStrToHostName(const char *IPAddr)
{
struct sockaddr_in sa;
struct hostent *hostdata=NULL;

inet_aton(IPAddr,& sa.sin_addr);
hostdata=gethostbyaddr(&sa.sin_addr.s_addr,sizeof((sa.sin_addr.s_addr)),AF_INET);
if (hostdata) return(hostdata->h_name);
else return("");
}




char *IPtoStr(unsigned long Address)
{
struct sockaddr_in sa;
sa.sin_addr.s_addr=Address;
return((char *) inet_ntoa(sa.sin_addr));

}

unsigned long StrtoIP(const char *Str)
{
struct sockaddr_in sa;
if (inet_aton(Str,&sa.sin_addr)) return(sa.sin_addr.s_addr);
return(0);
}


int STREAMIsConnected(STREAM *S)
{
int result=FALSE;

if (! S) return(FALSE);
result=IsSockConnected(S->in_fd);
if (result==TRUE)
{
	if (S->State & SS_CONNECTING)
	{
		S->State |= SS_CONNECTED;
		S->State &= (~SS_CONNECTING);
	}
}
if ((result==SOCK_CONNECTING) && (! (S->State & SS_CONNECTING))) result=FALSE;
return(result);
}



int STREAMDoPostConnect(STREAM *S, int Flags)
{
int result=FALSE;
char *ptr;
struct timeval tv;

if (! S) return(FALSE);
if ((S->in_fd > -1) && (S->Timeout > 0) )
{
  tv.tv_sec=S->Timeout;
  tv.tv_usec=0;
  if (FDSelect(S->in_fd, SELECT_WRITE, &tv) != SELECT_WRITE)
  {
    close(S->in_fd);
    S->in_fd=-1;
    S->out_fd=-1;
  }
}

if (S->in_fd > -1)
{
//We will have been non-blocking during connection, but if we don't 
//really want the stream to be non blocking, we unset that here
if (! (Flags & CONNECT_NONBLOCK))  STREAMSetFlags(S, 0, SF_NONBLOCK);

S->Type=STREAM_TYPE_TCP;
result=TRUE;
STREAMSetFlushType(S,FLUSH_LINE,0,0);
if (Flags & CONNECT_SSL) DoSSLClientNegotiation(S, Flags);

ptr=GetRemoteIP(S->in_fd);

if (ptr) 
{
	if (strncmp(ptr,"::ffff:",7)==0) ptr+=7;
	STREAMSetValue(S,"PeerIP",ptr);
}
}

return(result);
}

extern char *GlobalConnectionChain;

int STREAMTCPConnect(STREAM *S, const char *Host, int Port, int TTL, int ToS, int Flags)
{
ListNode *Curr, *LastHop;
char *Token=NULL, *ptr;
int HopNo=0, result=FALSE;


if (! STREAMGetValue(S, "ConnectHop:0"))
{
if (StrValid(GlobalConnectionChain))  STREAMAddConnectionHop(S, GlobalConnectionChain);
}

//Find the last hop, used to decide what ssh command to use
Curr=ListGetNext(S->Values);
while (Curr)
{
GetToken(Curr->Tag,":",&Token,0);
if (strcasecmp(Token,"ConnectHop")==0) LastHop=Curr;
if (strcasecmp(Curr->Tag,"TTL")==0) TTL=atoi(Curr->Item);
if (strcasecmp(Curr->Tag,"ToS")==0) ToS=atoi(Curr->Item);
Curr=ListGetNext(Curr);
}


Curr=ListGetNext(S->Values);
while (Curr)
{
	GetToken(Curr->Tag,":",&Token,0);

	if (strcasecmp(Token,"ConnectHop")==0)
	{
		result=STREAMProcessConnectHop(S, (char *) Curr->Item,Curr==LastHop);
		HopNo++;
	}

	if (! result) break;
	Curr=ListGetNext(Curr);
}

//If we're not handling the connection through 'Connect hops' then
//just connect to host

if ((HopNo==0) && StrValid(Host))
{
	if (Flags & CONNECT_NONBLOCK) S->Flags |= SF_NONBLOCK;
	
	//Flags are handled in this function
	S->in_fd=TCPConnectWithAttributes(STREAMGetValue(S, "LocalAddress"), Host,Port,Flags,TTL,ToS);

	S->out_fd=S->in_fd;
	if (S->in_fd > -1) result=TRUE;
}


if (result==TRUE)
{
	if (Flags & CONNECT_NONBLOCK) 
	{
		S->State |=SS_CONNECTING;
		S->Flags |=SF_NONBLOCK;
	}
	else
	{
		S->State |=SS_CONNECTED;
		result=STREAMDoPostConnect(S, Flags);
	}
}

return(result);
}

//This is a lower-level connect function that assumes a URL has
//already been broken up into parts
int STREAMProtocolConnect(STREAM *S, const char *Proto, const char *Host, unsigned int Port, int Flags)
{
int result=FALSE, fd;
unsigned int TTL=0, ToS=0;

STREAMSetFlushType(S,FLUSH_LINE,0,0);
if (strcasecmp(Proto,"fifo")==0) 
{
	mknod(Host, S_IFIFO|0666, 0);
	S->in_fd=open(Host, O_RDWR);
	S->out_fd=S->in_fd;
}
else if ((strcasecmp(Proto,"unix")==0) || (strcasecmp(Proto,"unixstream")==0)) result=STREAMConnectUnixSocket(S, Host, SOCK_STREAM);
else if (strcasecmp(Proto,"unixdgram")==0) result=STREAMConnectUnixSocket(S, Host, SOCK_DGRAM);
else if ((strcasecmp(Proto,"udp")==0) || (strcasecmp(Proto,"bcast")==0)) 
{
	fd=UDPOpen("", 0, Flags);
	if (fd > -1) 
	{
		S->in_fd=fd;
		S->out_fd=fd;
		S->Type=STREAM_TYPE_UDP;
		result=IPReconnect(fd,Host,Port,0);
		if (strcasecmp(Proto,"bcast")==0) SockSetOptions(fd, SOCK_BROADCAST, 0);
	}
}
else if (
					(strcasecmp(Proto,"ssl")==0) || 
					(strcasecmp(Proto,"tls")==0) 
) result=STREAMTCPConnect(S, Host, Port, TTL, ToS, Flags | CONNECT_SSL);
else result=STREAMTCPConnect(S, Host, Port, TTL, ToS, Flags);


return(result);
}



int STREAMConnect(STREAM *S, const char *URL, int Flags)
{
int result=FALSE;
unsigned int Port=0;
char *Proto=NULL, *Host=NULL, *Token=NULL, *Path=NULL;

ParseURL(URL, &Proto, &Host, &Token,NULL, NULL,&Path,NULL);
S->Path=CopyStr(S->Path,URL);
if (StrValid(Token)) Port=strtoul(Token,0,10);
result=STREAMProtocolConnect(S, Proto, Host, Port, Flags);

DestroyString(Token);
DestroyString(Proto);
DestroyString(Host);
DestroyString(Path);

return(result);
}


