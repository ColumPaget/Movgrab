#include "common.h"
#include "download.h"

char *FileTypes[]={".flv",".mp3",".mp4",".mov",".wma",".m4a",".m4v",".wmv",".webm",".avi",".3gp","m3u8",NULL};
char *ItemSelectionArg=NULL;
char *NowPlayingFile=NULL;
char *FormatPreference=NULL;
char *Username=NULL, *Password=NULL;
char *Proxy=NULL;
char *ProgName=NULL, *CmdLine=NULL, *UserAgent=NULL;
int STREAMTimeout=300;
STREAM *StdIn=NULL;
int Flags=0;


char *BuildURL(char *RetStr, const char *Parent, const char *SubItem)
{
char *Proto=NULL, *Host=NULL, *Port=NULL, *Path=NULL;
char *BasePath=NULL;

ParseURL(Parent,&Proto,&Host,&Port,NULL,NULL,&Path,NULL);
if (StrValid(Port)) BasePath=FormatStr(BasePath, "%s://%s:%s/", Proto,Host,Port);
else BasePath=FormatStr(BasePath, "%s://%s/", Proto,Host);

//if it starts with '/' then we don't append to existing path
if (*SubItem=='/') RetStr=MCopyStr(RetStr, BasePath, SubItem, NULL);
else RetStr=MCopyStr(RetStr, BasePath, Path, "/", SubItem, NULL);

DestroyString(Proto);
DestroyString(Host);
DestroyString(Port);
DestroyString(Path);
DestroyString(BasePath);

return(RetStr);
}

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


int CheckForKeyboardInput()
{
char *Tempstr=NULL;
int result=FALSE;

if (STREAMCheckForBytes(StdIn))
{
  Tempstr=STREAMReadLine(Tempstr,StdIn);
  StripTrailingWhitespace(Tempstr);
  if (StrLen(Tempstr))
  {
    ListAddItem(DownloadQueue,CopyStr(NULL,Tempstr));
    if (! (Flags & FLAG_QUIET)) fprintf(stderr,"\r\nQUEUED: %s\n",Tempstr);
    result=TRUE;
  }
}
DestroyString(Tempstr);

return(result);
}

