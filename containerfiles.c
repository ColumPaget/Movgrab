#include "containerfiles.h"
#include "outputfiles.h"
#include "servicetypes.h"
#include "download.h"


#define M3U_STREAMINFO 1
#define M3U_PLAYLIST   2

const char *ContainerTypes[]={".m3u",".m3u8",".pls",".asx",NULL};
int ContainerIDs[]={TYPE_CONTAINERFILE_M3U8, TYPE_CONTAINERFILE_M3U8, TYPE_CONTAINERFILE_PLS, TYPE_CONTAINERFILE_ASX};

int GetContainerFileType(const char *URL)
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
if (val==-1) return(TYPE_NONE);

if (Flags & FLAG_DEBUG2) fprintf(stderr,"CONTAINERTYPE: %s\n",ContainerTypes[val]);
return(ContainerIDs[val]);
}


int DownloadStream(const char *URL, const char *Title, ListNode *Items, int Flags)
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


void M3UStreamVarName(const char *Config, char **VarName)
{
char *Name=NULL, *Value=NULL;
char *Resolution=NULL, *Codec=NULL, *Bandwidth=NULL;
const char *ptr;

ptr=GetNameValuePair(Config, ",", "=", &Name, &Value);
while (ptr)
{
	StripTrailingWhitespace(Name);
	StripTrailingWhitespace(Value);
	if (strcasecmp(Name,"resolution")==0) Resolution=CopyStr(Resolution, Value);
	if (strcasecmp(Name,"codec")==0) Codec=CopyStr(Codec, Value);
	if (strcasecmp(Name,"bandwidth")==0) Bandwidth=CopyStr(Bandwidth, Value);
	while (isspace(*ptr)) ptr++;
	ptr=GetNameValuePair(ptr, ",", "=", &Name, &Value);
}

if (StrValid(Resolution)) *VarName=MCopyStr(*VarName, "item:m3u8-stream:", Resolution, NULL);
else *VarName=MCopyStr(*VarName, "item:m3u8-stream:", Bandwidth, NULL);

DestroyString(Name);
DestroyString(Value);
DestroyString(Codec);
DestroyString(Resolution);
DestroyString(Bandwidth);
}





int M3UStreamDownload(STREAM *ManifestCon, const char *URL, const char *Title)
{
STREAM *Con=NULL;
char *Tempstr=NULL, *BasePath=NULL, *Line=NULL;
const char *ptr;
ListNode *Segments, *Curr;
int result;
double BytesRead=0;

Segments=ListCreate();
ptr=strrchr(URL, '/');
if (ptr)
{
	BasePath=CopyStrLen(BasePath, URL, ptr - URL);
	Line=STREAMReadLine(Line,ManifestCon);
	while (Line)
	{
		StripLeadingWhitespace(Line);
		StripTrailingWhitespace(Line);
		
		if (*Line != '#')
		{
			Tempstr=MCopyStr(Tempstr, BasePath, "/", Line, NULL);
			ListAddItem(Segments, CopyStr(NULL, Tempstr));
		}
	Line=STREAMReadLine(Line,ManifestCon);
	}

	OpenOutputFiles(Title, URL, &BytesRead);
	Tempstr=SetStrLen(Tempstr,BUFSIZ);
	Curr=ListGetNext(Segments);
	while (Curr)
	{
		Con=ConnectAndRetryUntilDownload(Curr->Item, 0, 0);
		if (Con)
		{
		TransferItem(Con, Title, URL, "m3u8-stream", 0, 0, &BytesRead, FALSE);
		STREAMClose(Con);
		}

	Curr=ListGetNext(Curr);
	}
	CloseOutputFiles();
}

ListDestroy(Segments, DestroyString);
DestroyString(Tempstr);
DestroyString(BasePath);
DestroyString(Line);
}


