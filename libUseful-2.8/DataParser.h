#ifndef LIBUSEFUL_DATAPARSE_H
#define LIBUSEFUL_DATAPARSE_H

#include "includes.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {PARSER_JSON, PARSER_XML, PARSER_YAML, PARSER_CONFIG, PARSER_INI, PARSER_FORK} EParsers;

#define ITEM_ROOT   0
#define ITEM_VALUE  1
#define ITEM_ENTITY 2
#define ITEM_ARRAY  3

typedef struct
{
int Type;
char *Document;
char *Path;
ListNode *Items;
ListNode *Curr;
} PARSER;


int ParserType(const char *Type);
PARSER *ParserCreate(int Type);
void ParserAddString(PARSER *P, const char *Str);
void ParserParseDocument(PARSER *P, const char *Doc);
ListNode *ParserGetPrev(PARSER *P);
ListNode *ParserGetNext(PARSER *P);
ListNode *ParserFindItem(PARSER *P, const char *Name);
ListNode *ParserOpenItem(PARSER *P, const char *Name);
PARSER *ParserFork(PARSER *P, const char *Name);
const char *ParserGetValue(PARSER *P, const char *Name);

#ifdef __cplusplus
}
#endif


#endif
