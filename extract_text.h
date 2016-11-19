
#ifndef MOVGRAB_EXTRACT_H
#define MOVGRAB_EXTRACT_H

#include "common.h"


#define EXTRACT_DEQUOTE  1
#define EXTRACT_WITHIN_QUOTES 2
#define EXTRACT_NOSPACES 4
#define EXTRACT_INCLUDE_START 8
#define EXTRACT_GUESSTYPE 16
#define EXTRACT_DESLASHQUOTE 32
#define EXTRACT_DEHTMLQUOTE 64


//This function Extracts Text from a line that's found between two specified
//chunks of text 'ItemStart' and 'ItemEnd'
char *GenericExtractFromLine(char *Line, const char *ItemName, const char *ItemStart, const char *ItemEnd, ListNode *Vars, int Flags);

#endif
	
