#include "outputfiles.h"


ListNode *OutputFiles;


//---------------- Functions to do with files and file names ----------

//Strip out characters that make it difficult to specify a file on the 
//command line, such as '&' or ';' '>' that mean something to the shell
char *MakeFilesystemSafeName(char *Buffer, char *Path)
{
char *Str=NULL;
char BadChars[]="'\"()/?*&<>; ";
char *ptr;

Str=CopyStr(Buffer,"");
ptr=Path;
while (ptr && (*ptr != '\0'))
{
	if (strchr(BadChars,*ptr)) Str=AddCharToStr(Str,'_');
	else Str=AddCharToStr(Str,*ptr);
	ptr++;
}
return(Str);
}


//guess the extension of a file, some sites don't have extensions
//on their filenames
char *GuessExtn(char *ContentType, char *Format, char *ID)
{
static char *Extn=NULL;
char *ptr;

Extn=CopyStr(Extn,".flv");

if (StrLen(ID)) 
{
	ptr=strchr(ID,'.');
	if (StrLen(ptr)) Extn=CopyStr(Extn,ptr);
}

if (StrLen(Format)) Extn=MCopyStr(Extn,".",Format,NULL);

if (StrLen(ContentType))
{
ptr=NULL;
if (strcasecmp(ContentType,"audio/mp3")==0) ptr=".mp3";
else if (strcasecmp(ContentType,"audio/mpeg")==0) ptr=".mp3";
else if (strcasecmp(ContentType,"video/x-flv")==0) ptr=".flv";
else if (strcasecmp(ContentType,"video/flv")==0) ptr=".flv";
else if (strcasecmp(ContentType,"video/mp4")==0) ptr=".mp4";
else if (strcasecmp(ContentType,"video/3gpp")==0) ptr=".3gp";
else if (strcasecmp(ContentType,"audio/webm")==0) ptr=".webm";
else if (strcasecmp(ContentType,"video/webm")==0) ptr=".webm";
if (StrLen(ptr)) Extn=CopyStr(Extn,ptr);
}

return(Extn);
}


//URL is used to provide a unique MD5 so that two downloads from
//different sites with the same title don't overwrite each other
char *GetSaveFilePath(char *RetStr, char *Title, char *URL)
{
char *ptr=NULL;
char *Tempstr=NULL, *MD5=NULL;


if (StrLen(Title)) ptr=Title;
else 
{
		//Assume the filename is the document part of the url
		ptr=strrchr(URL,'?');
		if (ptr) *ptr='\0';


		ptr=strrchr(URL,'/');
		if (ptr) ptr++;
		else ptr=URL;
}

Tempstr=MakeFilesystemSafeName(RetStr, ptr);
ptr=strrchr(Tempstr,'.');

//some titles might have '.' in them, but not have an extension
//only assume it's an extension if it's under six chars long
if (ptr && (StrLen(ptr) < 6)) *ptr='\0';

if (! (Flags & FLAG_RESUME))
{
	HashBytes(&MD5,"md5",URL,StrLen(URL),ENCODE_HEX);
	Tempstr=MCatStr(Tempstr,"-",MD5,NULL);
}

//Some stupid sites start pagenames with a space, and we don't want this in the filename
StripLeadingWhitespace(Tempstr);

DestroyString(MD5);

return(Tempstr);
}


//Open the file we are going to save the move to. Check in the user 
//filename preference stored in the global variable 'SaveFilePath'
//If that's set to '-' then open stdout and write to that, if it's
//set to anything else, then use that as the filename. Otherwise
//build the filename from available info.
STREAM *OpenSaveFile(char *Path, double *FileSize, int ResumeDownload)
{
STREAM *S=NULL;
struct stat FStat;

*FileSize=0;

if (strcmp(Path,"-")==0)
{
	S=STREAMFromFD(1);
	STREAMSetTimeout(S,0);
}
else
{
	S=STREAMOpenFile(Path,O_CREAT | O_RDWR);

	if (! STREAMLock(S,LOCK_EX|LOCK_NB)) 
	{
		if (! (Flags & FLAG_QUIET)) fprintf(stderr,"Already downloading this item!\n");
		fflush(NULL);
		exit(0);
	}

	//Filesize can be used to resume a part download
	if (ResumeDownload)
	{
		fstat(S->in_fd,&FStat);
		*FileSize=(double) FStat.st_size;
		STREAMSeek(S,0,SEEK_END);
	}
}


return(S);
}

STREAM *OpenCacheFile(char *Title, char *URL)
{
char *Tempstr=NULL;
STREAM *S=NULL;
glob_t Glob;

Tempstr=GetSaveFilePath(Tempstr, Title, URL);
Tempstr=CatStr(Tempstr,".*");

glob(Tempstr,0,0,&Glob);

if (Glob.gl_pathc > 0)
{
S=STREAMOpenFile(Glob.gl_pathv[0],O_RDONLY);
}

globfree(&Glob);

DestroyString(Tempstr);

return(S);
}

void OpenOutputFiles(char *Title, char *URL, double *FileSize)
{
char *Tempstr=NULL;
ListNode *Curr;
int val=0, Resume=FALSE;

if ((Flags & FLAG_RESUME) && (ListSize(OutputFiles)==1)) Resume=TRUE;

Curr=ListGetNext(OutputFiles);
while (Curr)
{
	if (StrLen(Curr->Tag)==0) 
	{
		Tempstr=GetSaveFilePath(Tempstr, Title, URL);
		Curr->Item=OpenSaveFile(Tempstr, FileSize, Resume);
	}
	else if (strcmp(Curr->Tag,"-")==0) Curr->Item=STREAMFromFD(1); 
	else Curr->Item=OpenSaveFile(Curr->Tag, FileSize, Resume);

Curr=ListGetNext(Curr);
}


DestroyString(Tempstr);
}


void WriteOutputFiles(char *Data, int Len)
{
ListNode *Curr;

Curr=ListGetNext(OutputFiles);
while (Curr)
{
if (Curr->Item) STREAMWriteBytes((STREAM *) Curr->Item,Data,Len);
Curr=ListGetNext(Curr);
}
}

void CloseOutputFiles(char *Extn)
{
ListNode *Curr;
char *Tempstr=NULL;
STREAM *S;

Curr=ListGetNext(OutputFiles);
while (Curr)
{
if ((Curr->Item) && (strcmp(Curr->Tag,"-") !=0))
{
 S=(STREAM *) Curr->Item;
 if (! StrLen(Curr->Tag)) 
 {
		Tempstr=MCopyStr(Tempstr,S->Path,Extn,NULL);
		rename(S->Path,Tempstr);
 }
 STREAMClose(S);
}
Curr=ListGetNext(Curr);
}
DestroyString(Tempstr);
}


void AddOutputFile(char *Path, int SingleOutput)
{
//if 'SingleOutput' is set then overwrite any existing outputs, this should be the
//only one
if (SingleOutput) ListClear(OutputFiles,NULL);

if (! OutputFiles) OutputFiles=ListCreate();
ListAddNamedItem(OutputFiles,Path,NULL);


}


char *OutputFilesGetFilePath()
{
ListNode *Curr;
STREAM *S;

Curr=ListGetNext(OutputFiles);
while (Curr)
{
S=(STREAM *) Curr->Item;
if (S && (strcmp(Curr->Tag,"-") !=0)) return(S->Path);
Curr=ListGetNext(Curr);
}

return("");
}
