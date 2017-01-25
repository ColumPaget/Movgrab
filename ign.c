#include "ign.h"

const char *IGN_DecodeLine(const char *Data, ListNode *Vars)
{
const char *ptr;
char *Name=NULL, *Value=NULL, *URL=NULL;
int height=0, width=0;

ptr=GetNameValuePair(Data,",",":",&Name,&Value);
while (ptr)
{
StripQuotes(Name);
StripQuotes(Value);

if (strcmp("url",Name)==0) URL=CopyStr(URL,Value);
if (strcmp("width",Name)==0) width=atoi(Value);
if (strcmp("height",Name)==0) height=atoi(Value);
ptr=GetNameValuePair(ptr,",",":",&Name,&Value);
}

if (width && height && StrLen(URL)) 
{
	Value=FormatStr(Value,"item:mp4:%dx%d",width,height);
	SetVar(Vars,Value,URL);
}

DestroyString(Name);
DestroyString(Value);
DestroyString(URL);

return(ptr);
}

void IGN_DecodeFormats(const char *Data, ListNode *Vars)
{
const char *ptr;
char *Token=NULL;

ptr=strstr(Data,"{\"url\":");
while (ptr)
{
ptr++;
ptr=GetToken(ptr,"}",&Token,0);
IGN_DecodeLine(Token, Vars);
ptr=strstr(ptr,"{\"url\":");
}

DestroyString(Token);
}
