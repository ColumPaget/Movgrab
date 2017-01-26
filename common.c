#include "common.h"

char *FileTypes[]={".flv",".mp3",".mp4",".mov",".wma",".m4a",".m4v",".wmv",".webm",".avi",".3gp","m3u8",NULL};
char *ItemSelectionArg=NULL;
char *NowPlayingFile=NULL;
char *FormatPreference=NULL;
char *Username=NULL, *Password=NULL;
char *Proxy=NULL;
char *ProgName=NULL, *CmdLine=NULL, *UserAgent=NULL;
int STREAMTimeout=3000;





char *FileTypeFromURL(char *URL)
{
static char *Tempstr=NULL;
char *ptr;

Tempstr=CopyStr(Tempstr,URL);
ptr=strrchr(Tempstr,'?');
if (ptr) *ptr='\0';
ptr=strrchr(Tempstr,'.');
if (ptr) ptr++;
return(ptr);
}


char *ItemCodeFromFileExtension(char *RetBuf, const char *Default, const char *URL)
{
char *Tempstr=NULL, *Path=NULL, *RetStr=NULL, *start, *ptr;


Path=CopyStr(Path, URL);
ptr=strrchr(Path, '?');
if (ptr) *ptr='\0';

//we don't want to wind up treating part of a server name or an ip address
//as a file extension, so here we sure that we're beyond any '/' or ':'
start=Path;
ptr=strchr(start, ':');
while (ptr)
{
start=ptr+1;
ptr=strchr(start, ':');
}

ptr=strchr(start, '/');
while (ptr)
{
start=ptr+1;
ptr=strchr(start, '/');
}

ptr=strrchr(start,'.');
if (ptr)
{
ptr++;
RetStr=MCopyStr(RetBuf,"item:",ptr,NULL);
}
else RetStr=CopyStr(RetBuf,Default);

DestroyString(Tempstr);
return(RetStr);
}


void VarsAddDownloadItem(const char *ItemName, const char *URL, ListNode *Vars, int AddFlags)
{
const char *ptr;
char *Token=NULL;

    //Do this without disturbing ptr, as we must return ptr
    ptr=ItemName;
    if (AddFlags & EXTRACT_GUESSTYPE)
    {
      Token=ItemCodeFromFileExtension(Token, ItemName, URL);
      if (StrValid(Token)) ptr=Token;
    }

    SetVar(Vars,ptr,URL);
    if (Flags & FLAG_DEBUG2) fprintf(stderr,"Extracted Item: [%s] [%s]\n",ptr,URL);

DestroyString(Token);
}
