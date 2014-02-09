#include "cbsnews.h"

void ExtractCBSNews(ListNode *Vars, char *Line)
{
char *ptr, *Tempstr=NULL, *Token=NULL;

#define CBSNEWS_ITEM_START "var sourc =  '"
#define CBSNEWS_ITEM_END "'"

if (strstr(Line,CBSNEWS_ITEM_START))
{

		GenericExtractFromLine(Line, "tmpitem",CBSNEWS_ITEM_START,CBSNEWS_ITEM_END,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);

		Token=CopyStr(Token,GetVar(Vars,"tmpitem"));
		if (StrLen(Token) > 7)
		{
			ptr=strstr(Token+7,"http://");

			if (ptr) Tempstr=CopyStrLen(Tempstr,Token,ptr-Token);
			else Tempstr=CopyStr(Tempstr,Token);
			SetVar(Vars,"item:mp4",Tempstr);
			
			if (StrLen(ptr)) SetVar(Vars,"item:m4v",ptr);
		}
			
}

DestroyString(Tempstr);
DestroyString(Token);
}

