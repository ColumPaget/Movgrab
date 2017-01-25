#include "extract_text.h"



//This function Extracts Text from a line that's found between two specified
//chunks of text 'ItemStart' and 'ItemEnd'
char *GenericExtractFromLine(char *Line, const char *ItemName, const char *ItemStart, const char *ItemEnd, ListNode *Vars, int ExtractFlags)
{
char *ptr, *ptr2, *Token=NULL, *Item=NULL;
int len;
int GTF=0;

		len=StrLen(ItemStart);
		if (ExtractFlags & EXTRACT_WITHIN_QUOTES) GTF=GETTOKEN_QUOTES;

		if (len) ptr=GetToken(Line,ItemStart,&Token,0);
		else ptr=Line;

		if (! StrValid(ItemEnd)) Token=CopyStr(Token,ptr);
		else ptr=GetToken(ptr,ItemEnd,&Token,GTF);
		
		//check if the start string occurs more than once in the Token that we've grabbed
		if (len) ptr2=strstr(Token,ItemStart);
		else ptr2=NULL;

		while (ptr2)
		{
		ptr2+=len;
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
    else if (ExtractFlags & EXTRACT_DEHTMLQUOTE) Item=HtmlUnQuote(Item,Token);
    else if (ExtractFlags & EXTRACT_DESLASHQUOTE) Item=UnQuoteStr(Item,Token);
    else Item=CopyStr(Item,Token);
		StripLeadingWhitespace(Item);
		StripTrailingWhitespace(Item);

		len=StrLen(Item);
		if (len > 0)
		{
		ptr2=Item+len-1;
		if ((ExtractFlags & EXTRACT_WITHIN_HTMLTAG) && (*ptr2=='/')) *ptr2='\0';
		StripQuotes(Item);

		if (ExtractFlags & EXTRACT_NOSPACES) strrep(Item,' ','+');
		if ((ExtractFlags & EXTRACT_HTTP_ONLY) && (strncmp(Item,"https:",6)==0))
		{
			Token=MCopyStr(Token,"http:",Item+6,NULL);
			Item=CopyStr(Item,Token);
		}

		VarsAddDownloadItem(ItemName, Item, Vars, ExtractFlags);
		}

DestroyString(Token);
DestroyString(Item);

return(ptr);
}
	

void GenericTitleExtract(const char *Line, ListNode *Vars)
{
if (strstr(Line,"<title>")) GenericExtractFromLine(Line, "Title:html","<title>","</title>", Vars,EXTRACT_DEQUOTE);

if (strstr(Line,"<meta name=\"title\" content=\"")) 
{
	GenericExtractFromLine(Line, "Title:meta","<meta name=\"title\" content=\"","\"", Vars,EXTRACT_DEQUOTE);
}

if (strstr(Line,"<meta property=\"og:title\" content=\"")) 
{
	GenericExtractFromLine(Line, "Title:meta","<meta property=\"og:title\" content=\"", "\"", Vars,EXTRACT_DEQUOTE);
}
}
