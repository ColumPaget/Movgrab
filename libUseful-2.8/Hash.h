#ifndef LIBUSEFUL_HASH_H
#define LIBUSEFUL_HASH_H

//if you load Hash.h you'll want Encodings.h too
#include "Encodings.h"
#include "file.h"
#include "includes.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef struct t_hash HASH;

typedef void (*HASH_UPDATE)(HASH *Hash, const char *Data, int DataLen);
typedef HASH *(*HASH_CLONE)(HASH *Hash);
typedef int (*HASH_FINISH)(HASH *Hash, char **RetStr);

struct t_hash
{
char *Type;
//this is a placeholder used only by classlibraries for scripting langauges
int Encoding;
char *Key1;
unsigned int Key1Len;
char *Key2;
unsigned int Key2Len;
void *Ctx;
HASH_UPDATE Update;
HASH_FINISH Finish;
HASH_CLONE Clone;
};

int HashEncodingFromStr(const char *Str);
char *HashAvailableTypes(char *RetStr);
HASH *HashInit(const char *Type);
int HashFinish(HASH *Hash, int Encoding, char **Return);
void HMACSetKey(HASH *HMAC, const char *Key, int Len);
void HashDestroy(HASH *Hash);
int HashBytes(char **Return, const char *Type, const char *text, int len, int Encoding);
int HashBytes2(const char *Type, int Encoding, const char *text, int len, char **RetStr);
int HashFile(char **Return, const char *Type, const char *Path, int Encoding);
int PBK2DF2(char **Return, char *Type, char *Bytes, int Len, char *Salt, int SaltLen, uint32_t Rounds, int Encoding);

#ifdef __cplusplus
}
#endif



#endif
