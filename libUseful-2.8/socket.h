#ifndef LIBUSEFUL_SOCK
#define LIBUSEFUL_SOCK

#include "includes.h"

#define CONNECT_NONBLOCK 1
#define CONNECT_SSL 2
#define CONNECT_HTTP_PROXY 4
#define CONNECT_SOCKS_PROXY 8
#define SOCK_NOKEEPALIVE 16
#define SOCK_BROADCAST 32
#define SOCK_DONTROUTE 64
#define SOCK_REUSEPORT 128
#define SOCK_TPROXY 256
#define SOCK_PEERCREDS 512

#define SOCK_CONNECTED 1
#define SOCK_CONNECTING -1

#define BIND_LISTEN  1
#define BIND_CLOEXEC 2


#ifdef __cplusplus
extern "C" {
#endif

int IsIP4Address(const char *Str);
int IsIP6Address(const char *Str);
int IsIPAddress(const char *);

const char *GetInterfaceIP(const char *Interface);
int GetHostARP(const char *IP, char **Device, char **MAC);

int ICMPSend(int sock, const char *Host, int Type, int Code, int TTL, char *Data, int len);
int UDPOpen(const char *Addr, int Port,int NonBlock);
int UDPSend(int sock, const char *Host, int Port, char *Data, int len);
int UDPRecv(int sock,  char *Buffer, int len, char **Host, int *Port);


/* Server Socket Funcs*/
int IPServerInit(int Type, const char *Address, int Port);
int IPServerAccept(int ServerSock,char **Addr);

STREAM *STREAMServerInit(const char *URL);
STREAM *STREAMServerAccept(STREAM *Serv);

int GetSockDetails(int fd, char **LocalAddress, int *LocalPort, char **RemoteAddress, int *RemotePort);
int GetSockDestination(int sock, char **Host, int *Port);

/* Client Socket Funcs*/
int IsSockConnected(int sock);
int TCPReconnect(int sock, const char *Host, int Port, int Flags);
int TCPConnect(const char *Host, int Port, int Flags);
/* int CheckForData(int sock); */
int SendText(int sock, char *Text);
int ReadText(int sock, char *Buffer, int MaxLen);
int ReadToCR(int fd, char *Buffer, int MaxLen);

int STREAMTCPConnect(STREAM *S, const char *Host, int Port, int TTL, int ToS, int Flags);
int STREAMProtocolConnect(STREAM *S, const char *Proto, const char *Host, unsigned int Port, int Flags);
int STREAMConnect(STREAM *S, const char *URL, int Flags);
int STREAMIsConnected(STREAM *S);
int DoPostConnect(STREAM *S, int Flags);

/* IP Address and host lookup functions */
char *GetRemoteIP(int sock);
char *LookupHostIP(const char *Host);
char *IPStrToHostName(const char *);
char *IPtoStr(unsigned long);
unsigned long StrtoIP(const char *);


#ifdef __cplusplus
}
#endif


#endif
