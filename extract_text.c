#include "extract_text.h"


//This function Extracts Text from a line that's found between two specified
//chunks of text 'ItemStart' and 'ItemEnd'
char *GenericExtractFromLine(char *Line, const char *ItemName, const char *ItemStart, const char *ItemEnd, ListNode *Vars, int ExtractFlags)
{
char *ptr, *ptr2, *Token=NULL, *Item=NULL;
int ilen;
int GTF=0;

		ilen=StrLen(ItemStart);
		if (ExtractFlags & EXTRACT_WITHIN_QUOTES) GTF=GETTOKEN_QUOTES;

		if (ilen) ptr=GetToken(Line,ItemStart,&Token,0);
		else ptr=Line;

		if (! StrValid(ItemEnd)) Token=CopyStr(Token,ptr);
		else ptr=GetToken(ptr,ItemEnd,&Token,GTF);
		
		//check if the start string occurs more than once in the Token that we've grabbed
		if (ilen) ptr2=strstr(Token,ItemStart);
		else ptr2=NULL;

		while (ptr2)
		{
		ptr2+=ilen;
		memmove(Token,ptr2,Token+StrLen(Token)-ptr2+1);
		//because of memmove we can strstr in Token again	
		ptr2=strstr(Token,ItemStart);
		}

		if (ExtractFlags & EXTRACT_INCLUDE_START) 
		{
			Item=MCopyStr(Item,ItemStart,Token,NULL);
			Token=CopyStr(Token,Item);
		}


    if (ExtractFlags & EXTRACT_DEQUOTE) Item=HTTPUnQuote(Item,Token);
    else if (ExtractFlags & EXTRACT_DEHTMLQUOTE) Item=HtmlDeQuote(Item,Token);
    else if (ExtractFlags & EXTRACT_DESLASHQUOTE) Item=DeQuoteStr(Item,Token);
    else Item=CopyStr(Item,Token);
		StripLeadingWhitespace(Item);
		StripTrailingWhitespace(Item);
		StripQuotes(Item);

		if (ExtractFlags & EXTRACT_NOSPACES)
		{
			ptr2=strchr(Item,' ');
			while (ptr2)
			{
				*ptr2='+';
				ptr2=strchr(ptr2,' ');
			}
		}

		//Do this without disturbing ptr, as we must return ptr
		ptr2=ItemName;
		if (ExtractFlags & EXTRACT_GUESSTYPE) 
		{
			Token=ItemCodeFromFileExtension(Token, ItemName, Item);
			if (StrValid(Token)) ptr2=Token;
		}

		SetVar(Vars,ptr2,Item);
		if (Flags & FLAG_DEBUG2) fprintf(stderr,"Extracted Item: [%s] [%s]\n",ptr2,Item);

DestroyString(Token);
DestroyString(Item);

return(ptr);
}
	
