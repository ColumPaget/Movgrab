#include "containerfiles.h"
#include "outputfiles.h"
#include "servicetypes.h"


#define M3U_STREAMINFO 1
#define M3U_PLAYLIST   2

char *ContainerTypes[]={".m3u",".m3u8",".pls",".asx",NULL};

int GetContainerFileType(char *URL)
{
char *Tempstr=NULL, *ptr;
int val;


Tempstr=CopyStr(Tempstr,URL);
//strip off any 'http GET' style arguments
ptr=strrchr(Tempstr,'?');
if (ptr) *ptr='\0';

//get path file extension
ptr=strrchr(Tempstr,'.');

val=MatchTokenFromList(ptr,ContainerTypes,0);

DestroyString(Tempstr);

return(val);
}


int DownloadStream(char *URL, char *Title, ListNode *Items, int Flags)
{
STREAM *Con=NULL, *S=NULL;
ListNode *Curr;
char *Tempstr=NULL, *ptr;
char *Token=NULL;
int Port;
double len=0, ApproxDocSize=0, BytesRead=0;

	Curr=ListGetNext(Items);

	if (Flags & (FLAG_TEST | FLAG_TEST_SITES) )
	{
		if (Flags & FLAG_TEST) fprintf(stderr,"TEST MODE: would have downloaded '%s' url=%s\n",Title,Curr->Item);
		if (Curr) return(TRUE);
		return(FALSE);
	}

	OpenOutputFiles(Title,URL,&BytesRead);
	while (Curr)
	{
		if (strncmp((char *) Curr->Item,"http:",5)==0) Tempstr=CopyStr(Tempstr,(char *) Curr->Item);
		else
		{
			Tempstr=CopyStr(Tempstr,URL);
			ptr=strrchr(Tempstr,'/');
			if (ptr) *ptr='\0';
			Tempstr=MCatStr(Tempstr,"/",(char *) Curr->Item,NULL);
		}

		Con=ConnectAndRetryUntilDownload(Tempstr, 0, 0);
		if (Con)
		{
			ptr=STREAMGetValue(Con,"HTTP:content-length");
			if (ptr) len=atof(ptr);
			if (ApproxDocSize==0) ApproxDocSize=ListSize(Items) * len;
			TransferItem(Con, Title, Curr->Item, "", len, ApproxDocSize,  &BytesRead, BytesRead==0);
			STREAMClose(Con);
		}
		Curr=ListGetNext(Curr);
	}
	CloseOutputFiles();

DestroyString(Tempstr);
DestroyString(Token);

return(TRUE);
}


void M3UParseStreamInfo(char *Line, char **Resolution, char **Bandwidth)
{
char *Name=NULL, *Value=NULL, *ptr;

ptr=GetToken(Line,":",&Name,0);
ptr=GetNameValuePair(ptr,",","=",&Name,&Value);
while (ptr)
{
	StripLeadingWhitespace(Name);
	StripTrailingWhitespace(Name);
	StripLeadingWhitespace(Value);
	StripTrailingWhitespace(Value);
	if (strcasecmp(Name,"RESOLUTION")==0) *Resolution=CopyStr(*Resolution,Value);
	if (strcasecmp(Name,"BANDWIDTH")==0) *Bandwidth=CopyStr(*Bandwidth,Value);
ptr=GetNameValuePair(ptr,",","=",&Name,&Value);
}

DestroyString(Name);
DestroyString(Value);
}




int M3UStreamInfo(STREAM *S, char *Title, char *URL, char *FirstLine, int Flags)
{
	char *Tempstr=NULL, *Doc=NULL, *Resolution=NULL, *Bandwidth=NULL, *ptr;
	ListNode *Vars=NULL;
	int RetVal=FALSE;

	Vars=ListCreate();
	Tempstr=CopyStr(Tempstr,FirstLine);
	while (Tempstr)
	{
	StripTrailingWhitespace(Tempstr);
  if (Flags & (FLAG_DEBUG2 | FLAG_DEBUG3)) fprintf(stderr,"%s\n",Tempstr);

	if (strncmp("#EXT-X-STREAM-INF",Tempstr,StrLen("#EXT-X-STREAM-INF"))==0) M3UParseStreamInfo(Tempstr, &Resolution, &Bandwidth);
	else if (*Tempstr != '#') 
	{
		if (strncasecmp(Tempstr,"http",4) !=0) 
		{
			Doc=CopyStr(Doc,URL);
			ptr=strrchr(Doc,'/');
			if (ptr) *ptr='\0';
			Doc=MCatStr(Doc,"/",Tempstr,NULL);
		}
		else Doc=CopyStr(Doc,Tempstr);

		ptr=FileTypeFromURL(Doc);
		if (strcmp(ptr,"m3u8")==0) ptr="stream";
		if (StrLen(Resolution)) 
		{
			if (StrLen(ptr)) Tempstr=MCopyStr(Tempstr,"item:",ptr,":",Resolution,NULL);
			else Tempstr=MCopyStr(Tempstr,"item:stream:",Resolution,NULL);
		}
		else if (StrLen(Bandwidth)) 
		{
			if (StrLen(ptr)) Tempstr=MCopyStr(Tempstr,"item:",ptr,":",Bandwidth,NULL);
			else Tempstr=MCopyStr(Tempstr,"item:stream:",Bandwidth,NULL);
		}
		else Tempstr=CopyStr(Tempstr,"ID");
		SetVar(Vars,Tempstr,Doc);
	}
	Tempstr=STREAMReadLine(Tempstr,S);
	}

	ptr=GetVar(Vars,"ID");
	if (! StrLen(ptr)) Type=SelectDownloadFormat(Vars, TYPE_REFERENCE, FALSE);
	ptr=GetVar(Vars,"ID");
	if (StrLen(ptr)) RetVal=DownloadM3U(ptr, Title, Flags);

	ListDestroy(Vars,DestroyString);
	DestroyString(Tempstr);
	DestroyString(Resolution);
	DestroyString(Bandwidth);
	DestroyString(Doc);

	return(RetVal);
}


int DownloadM3U(char *URL, char *Title, int Flags)
{
char *Tempstr=NULL, *ID=NULL, *Doc=NULL, *ptr;
int Port=0, BytesRead=0, len=0, count=0;
int RetVal=FALSE;
ListNode *Items, *Curr;
int M3UType=M3U_PLAYLIST;
STREAM *Con;

if (Flags & FLAG_DEBUG) fprintf(stderr,"M3U STREAM: %s\n",URL);


Items=ListCreate();
Con=ConnectAndRetryUntilDownload(URL, 0, 0);
if (Con)
{
Tempstr=STREAMReadLine(Tempstr,Con);
while (Tempstr)
{
StripTrailingWhitespace(Tempstr);
StripLeadingWhitespace(Tempstr);

if (Flags & (FLAG_DEBUG2 | FLAG_DEBUG3)) fprintf(stderr,"%s\n",Tempstr);
if (StrLen(Tempstr))
{
	if (strncmp("#EXT-X-STREAM-INF",Tempstr,StrLen("#EXT-X-STREAM-INF"))==0)
	{
			RetVal=M3UStreamInfo(Con,Title,URL,Tempstr,Flags);
			M3UType=M3U_STREAMINFO;
	}
	else if (strncmp("#EXT-X-MEDIA-SEQUENCE",Tempstr,StrLen("#EXT-X-MEDIA-SEQUENCE"))==0) M3UType=M3U_PLAYLIST;
	else if (*Tempstr != '#') 
	{
		if (strncasecmp(Tempstr,"http",4) !=0) 
		{
			Doc=CopyStr(Doc,URL);
			ptr=strrchr(Doc,'/');
			if (ptr) *ptr='\0';
			Doc=MCatStr(Doc,"/",Tempstr,NULL);
		}
		else Doc=CopyStr(Doc,Tempstr);
		ListAddItem(Items,CopyStr(NULL,Doc));
	}
}

Tempstr=STREAMReadLine(Tempstr,Con);
}

STREAMClose(Con);
if (M3UType == M3U_PLAYLIST) RetVal=DownloadStream(URL, Title, Items, Flags);
}

ListDestroy(Items,DestroyString);
DestroyString(Tempstr);
DestroyString(Doc);
DestroyString(ID);


return(RetVal);
}


int DownloadPLS(char *URL, char *Title, int Flags)
{
char *Tempstr=NULL, *Token=NULL, *ptr;
int Port=0, len=0;
STREAM *Con=NULL;
int RetVal=FALSE;
ListNode *Items;

if (Flags & FLAG_DEBUG) fprintf(stderr,"PLS STREAM: %s\n",URL);

Items=ListCreate();
Con=ConnectAndRetryUntilDownload(URL, 0, 0);
if (Con)
{
Tempstr=STREAMReadLine(Tempstr,Con);
while (Tempstr)
{
StripTrailingWhitespace(Tempstr);
StripLeadingWhitespace(Tempstr);

  if (Flags & (FLAG_DEBUG2 | FLAG_DEBUG3)) fprintf(stderr,"%s\n",Tempstr);
if (StrLen(Tempstr))
{
	ptr=GetToken(Tempstr,"=",&Token,0);
	if (strncmp(Token,"File",4)==0) ListAddItem(Items,CopyStr(NULL,ptr));
}

Tempstr=STREAMReadLine(Tempstr,Con);
}

//Close the Connection and Download the next stage
STREAMClose(Con);

RetVal=DownloadStream(URL, Title, Items, Flags);
}
	
ListDestroy(Items,DestroyString);
DestroyString(Tempstr);

return(RetVal);
}


int DownloadASX(char *URL, char *Title, int Flags)
{
char *Tempstr=NULL, *Token=NULL, *ptr;
int Port=0, len=0;
int RetVal=FALSE;
STREAM *Con=NULL;
ListNode *Items;

if (Flags & FLAG_DEBUG) fprintf(stderr,"ASX STREAM: %s\n",URL);

Items=ListCreate();
Con=ConnectAndRetryUntilDownload(URL, 0, 0);
if (Con)
{
Tempstr=STREAMReadLine(Tempstr,Con);
while (Tempstr)
{
StripTrailingWhitespace(Tempstr);
StripLeadingWhitespace(Tempstr);

  if (Flags & (FLAG_DEBUG2 | FLAG_DEBUG3)) fprintf(stderr,"%s\n",Tempstr);
	if (StrLen(Tempstr) && (strncasecmp(Tempstr,"<Ref href",9)==0))
	{
		ptr=GetToken(Tempstr,"=",&Token,0);
		while (isspace(*ptr)) ptr++;
		if (*ptr=='"') ptr++;
		ptr=GetToken(ptr,"\"",&Token,0);

		ListAddItem(Items,CopyStr(NULL,Token));
	}

Tempstr=STREAMReadLine(Tempstr,Con);
}

STREAMClose(Con);

RetVal=DownloadStream(URL, Title, Items, Flags);
}
	
ListDestroy(Items,DestroyString);
DestroyString(Tempstr);


return(RetVal);
}


int DownloadContainer(char *Path, char *Title, int Flags)
{
char *ptr;
int val, RetVal=FALSE;

val=GetContainerFileType(Path);

switch (val)
{
	case CONT_M3U:
	case CONT_M3U8:
   RetVal=DownloadM3U(Path, Title, Flags);
	break;

	case CONT_PLS:
    RetVal=DownloadPLS(Path, Title, Flags);
	break;

	case CONT_ASX:
  	RetVal=DownloadASX(Path, Title, Flags);
	break;
}

return(RetVal);
}
