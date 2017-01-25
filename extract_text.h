
#ifndef MOVGRAB_EXTRACT_H
#define MOVGRAB_EXTRACT_H

#include "common.h"


#define EXTRACT_DEQUOTE  1
#define EXTRACT_WITHIN_QUOTES 2
#define EXTRACT_WITHIN_HTMLTAG 4
#define EXTRACT_INCLUDE_START 8
#define EXTRACT_GUESSTYPE 16
#define EXTRACT_DESLASHQUOTE 32
#define EXTRACT_DEHTMLQUOTE 64
#define EXTRACT_HTTP_ONLY 128
#define EXTRACT_NOSPACES 256


//This function Extracts Text from a line that's found between two specified
//chunks of text 'ItemStart' and 'ItemEnd'
char *GenericExtractFromLine(char *Line, const char *ItemName, const char *ItemStart, const char *ItemEnd, ListNode *Vars, int Flags);
void GenericTitleExtract(const char *Line, ListNode *Vars);

#endif
	
