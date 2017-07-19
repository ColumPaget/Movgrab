#ifndef LIBUSEFUL_ERRORS_H
#define LIBUSEFUL_ERRORS_H

#define ERRFLAG_ERRNO 1

#define RaiseError(flags, type, fmt, ...) InternalRaiseError(flags, type, __FILE__, __LINE__, fmt, ##__VA_ARGS__)


typedef void (*ERROR_CALLBACK)(int flags, const char *where, const char *file, int line, const char *ErrorString);
extern ERROR_CALLBACK libUsefulErrorCallback;

void libUsefulDefaultErrorCallback(int flags, const char *where, const char *file, int line,  const char *String);
char *GetErrorString(char *Buffer);
void InternalRaiseError(int flags, const char *type, const char *file, int line, const char *FmtStr, ...);

#endif
