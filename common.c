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
