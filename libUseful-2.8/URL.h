#ifndef LIBUSEFUL_URL
#define LIBUSEFUL_URL

#include "includes.h"

#ifdef __cplusplus
extern "C" {
#endif

const char *ParseHostDetails(const char *Data,char **Host,char **Port,char **User, char **Password);
void ParseURL(const char *URL, char **Proto, char **Host, char **Port, char **User, char **Password, char **Path, char **Args);
void ParseConnectDetails(const char *Str, char **Type, char **Host, char **Port, char **User, char **Pass, char **InitDir);
void ParseConnectHop(const char *Line, int *Type,  char **Host, char **User, char **Password, char **KeyFile, int *Port);
char *ResolveURL(char *RetStr, const char *Parent, const char *SubItem);

#ifdef __cplusplus
}
#endif

#endif
