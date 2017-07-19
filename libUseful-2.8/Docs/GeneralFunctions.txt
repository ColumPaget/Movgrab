#ifndef LIBUSEFUL_GENERAL_H
#define LIBUSEFUL_GENERAL_H

#include <stdio.h>
#include "defines.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {OSINFO_TYPE, OSINFO_ARCH, OSINFO_RELEASE, OSINFO_HOSTNAME, OSINFO_UPTIME, OSINFO_TOTALMEM, OSINFO_FREEMEM,  OSINFO_LOAD, OSINFO_HOMEDIR, OSINFO_TMPDIR, OSINFO_PROCS, OSINFO_USERINFO} EOSInfo;

void xmemset(volatile char *Str, char fill, off_t size);
int ptr_incr(const char **ptr, int count);
const char *traverse_quoted(const char *ptr);
int xsetenv(const char *Name, const char *Value);
unsigned int fnv_hash(unsigned const char *key, int NoOfItems);

char *CommaList(char *RetStr, const char *AddStr);
void *ArrayGetItem(void *array[], int pos);

int HexStrToBytes(char **Buffer, char *HexStr);
char *BytesToHexStr(char *Buffer, char *Bytes, int len);
char *EncodeBytes(char *Buffer, const char *Bytes, int len, int Encoding);

int GenerateRandomBytes(char **RetBuff, int ReqLen, int Encoding);
char *GetRandomData(char *RetBuff, int len, char *AllowedChars);
char *GetRandomHexStr(char *RetBuff, int len);
char *GetRandomAlphabetStr(char *RetBuff, int len);


double FromMetric(const char *Data, int Type);
const char *ToMetric(double Size, int Type);


int LookupUID(const char *User);
int LookupGID(const char *Group);

const char *OSSysInfoString(int Info);
unsigned long OSSysInfoLong(int Info);


#ifdef __cplusplus
}
#endif


#endif
