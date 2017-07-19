#include "Errors.h"
#include "includes.h"
#include <errno.h>

ERROR_CALLBACK libUsefulErrorCallback=libUsefulDefaultErrorCallback;

char *ErrorString;

char *GetErrorString(char *Buffer)
{

}

void libUsefulDefaultErrorCallback(int flags, const char *where, const char *file, int line,  const char *String)
{
const char *ptr="";

if (flags & ERRFLAG_ERRNO) ptr=strerror(errno);
fprintf(stderr, "ERROR: %s %s:%d %s. %s\n", where, file, line, String, ptr);
}


void InternalRaiseError(int flags, const char *where, const char *file, int line, const char *FmtStr, ...)
{
char *Tempstr=NULL;
va_list args;

if (libUsefulErrorCallback)
{
va_start(args,FmtStr);
Tempstr=VFormatStr(Tempstr,FmtStr,args);
va_end(args);

libUsefulErrorCallback(flags, where, file, line, Tempstr);
}

DestroyString(Tempstr);
}
