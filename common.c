#include "common.h"

char *FileTypes[]={".flv",".mp3",".mp4",".mov",".wma",".m4a",".m4v",".wmv",".webm",".avi",".3gp",NULL};
char *ItemSelectionArg=NULL;

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

