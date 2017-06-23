#include "download.h"
#include "outputfiles.h"
#include "display.h"
#include "containerfiles.h"
#include "servicetypes.h"
#include "settings.h"

/*
Functions relating to connecting to hosts and downloading webpages.
All the HTTP stuff is in here
*/ 

ListNode *DownloadQueue=NULL;

STREAM *ConnectAndSendHeaders(const char *URL, int Flags, double BytesRange)
{
STREAM *Con;
char *Tempstr=NULL, *Method=NULL, *ptr, *rcode;
HTTPInfoStruct *Info;
static char *LastPage=NULL;

if (Flags & FLAG_POST) Method=CopyStr(Method,"POST");
else Method=CopyStr(Method,"GET");

Info=HTTPInfoFromURL(Method, URL);
//if (DLFlags & DL_NOREDIRECT) Info->Flags |=HTTP_NOREDIRECT;
if (Flags & FLAG_DEBUG3) Info->Flags |= HTTP_DEBUG;
//Info->Flags |= HTTP_DEBUG;

if (StrValid(LastPage)) SetVar(Info->CustomSendHeaders,"Referer",LastPage); 

LastPage=CopyStr(LastPage, URL);
if (BytesRange > 0)
{
	Tempstr=FormatStr(Tempstr,"bytes=%lld-",(long long) BytesRange);
	SetVar(Info->CustomSendHeaders,"Range",Tempstr); 
}

SetVar(Info->CustomSendHeaders,"Icy-MetaData","1");

Con=HTTPTransact(Info);
if ((! Con) && (! (Flags & FLAG_QUIET))) 
{
	if (StrValid(Info->ResponseCode)) fprintf(stderr,"ERROR: Server %s item '%s' not retrieved\nResponseCode: %s\n",Info->Host, Info->Doc,Info->ResponseCode);
	else fprintf(stderr,"ERROR: Connection failed to %s can't get file=%s \n",Info->Host, Info->Doc);
}
else if (StrValid(Info->ResponseCode) && (*Info->ResponseCode !='2')) 
{
 fprintf(stderr,"ERROR: Document unavailable. HTTP-Response: %s \n",STREAMGetValue(Con, "HTTP:ResponseCode"));
 STREAMClose(Con);
 Con=NULL;
}
else if (Flags & FLAG_DEBUG) 
{
	ptr=STREAMGetValue(Con, "SSL-Cipher");
	if (StrValid(ptr)) fprintf(stderr,"HTTP-Response: %s SSL-Cipher: %s\n",STREAMGetValue(Con, "HTTP:ResponseCode"), STREAMGetValue(Con, "SSL-Cipher"));
	else fprintf(stderr,"HTTP Response: %s\n",STREAMGetValue(Con, "HTTP:ResponseCode"));
}

DestroyString(Tempstr);
DestroyString(Method);

return(Con);
}



STREAM *ConnectAndRetryUntilDownload(const char *URL, int Flags, double BytesRead)
{
STREAM *Con;
int i;
char *Tempstr=NULL, *ptr;


for (i=0; i < 20; i++)
{
Con=ConnectAndSendHeaders(URL, Flags, BytesRead);

if (! (Flags & FLAG_RETRY_DOWNLOAD)) break;

if (Con)
{
Tempstr=CopyStr(Tempstr,STREAMGetValue(Con,"HTTP:Content-Type"));
if (Flags & FLAG_DEBUG) fprintf(stderr,"ContentType: %s\n",Tempstr);

//If the Content Type is not text, then we have the video
//else read the text, disconnect, and reconnect
ptr=STREAMGetValue(Con,"HTTP:Content-Length");
if ((strcmp(ptr,"0") !=0) && (strncmp(Tempstr,"text/",5) !=0)) break;

Tempstr=STREAMReadLine(Tempstr,Con);
while (Tempstr) Tempstr=STREAMReadLine(Tempstr,Con);
STREAMClose(Con);
Con=NULL;
}

if (Flags & FLAG_TEST_SITES) break;

fprintf(stderr,"Failed to get item. Sleeping 5s and retrying\n");
sleep(5);
CheckForKeyboardInput();

}

DestroyString(Tempstr);

return(Con);
}


void ICYReadString(STREAM *Con, char **Title)
{
int len, remaining, result;
uint8_t icysize;
char *Tempstr=NULL, *Name=NULL, *Value=NULL, *ptr;

	result=STREAMReadBytes(Con,&icysize,1);
	if (icysize > 0) 
	{
		len=icysize * 16;
		remaining=len;
		Tempstr=SetStrLen(Tempstr, len);
		len=0;
		while (remaining > 0)
		{
		result=STREAMReadBytes(Con,Tempstr + len, remaining);
		if (result==EOF) break;
		remaining-=result;
		len+=result;
		}

		Name=CopyStr(Name,"");		
		ptr=GetNameValuePair(Tempstr, ";", "=", &Name, &Value);
		while (ptr)
		{
		if (strcasecmp(Name,"StreamTitle")==0) *Title=CopyStr(*Title, Value);
		ptr=GetNameValuePair(ptr, ";", "=", &Name, &Value);
		}
	}

DestroyString(Tempstr);
DestroyString(Name);
DestroyString(Value);
}



int TransferItem(STREAM *Con, const char *InitialTitle, const char *URL, const char *Format, double SegmentSize, double DocSize, double *BytesRead, int PrintName)
{
char *Buffer=NULL, *Title=NULL, *Tempstr=NULL, *ptr;
int result, RetVal=FALSE, val;
double ReadThisTime=0;
unsigned long IcyInterval=0, BlockRemaining=0;

Title=CopyStr(Title, InitialTitle);
ptr=STREAMGetValue(Con,"HTTP:icy-metaint");
if (StrValid(ptr)) IcyInterval=strtoul(ptr,NULL,10);

DisplayProgress(Title, Format, *BytesRead, DocSize, PrintName);

while (1) 
{
	if (BlockRemaining==0)
	{
		if (IcyInterval) BlockRemaining=IcyInterval;
		else BlockRemaining=BUFSIZ;
		Buffer=SetStrLen(Buffer,BlockRemaining);
	}

	result=STREAMReadBytes(Con,Buffer,BlockRemaining);
	if (result==EOF) break;
	
	ReadThisTime +=result;
	(*BytesRead) +=result;
	BlockRemaining-=result;

	if (IcyInterval && (BlockRemaining==0)) 
	{
		Tempstr=CopyStr(Tempstr,Title);
		ICYReadString(Con, &Tempstr);
		if (strcmp(Tempstr, Title) !=0)
		{
		Title=CopyStr(Title, Tempstr);
		DisplayProgress(Title, Format, *BytesRead,DocSize,TRUE);
		}
		else DisplayProgress(Title, Format, *BytesRead,DocSize,FALSE);
	}
	else DisplayProgress(Title, Format, *BytesRead,DocSize,FALSE);

	WriteOutputFiles(Buffer,result);
	if ((SegmentSize > 0) && (ReadThisTime >= SegmentSize))
	{
		 break;
	}
}
RetVal=TRUE;

DisplayProgress(Title, Format, *BytesRead,DocSize,FALSE);

DestroyString(Tempstr);
DestroyString(Buffer);
DestroyString(Title);

return(RetVal);
}



//----- Download an actual Video ----------------------
int DownloadItem(const char *URL, const char *Title, const char *Format, int Flags)
{
STREAM *Con=NULL, *S=NULL;
char *Tempstr=NULL, *Token=NULL, *ptr;
char *ContentType=NULL;
int RetVal=FALSE;
char *Extn=NULL;
double DocSize=0, BytesRead=0;


if (Flags & FLAG_TEST) 
{
	fprintf(stderr,"TEST MODE: would have downloaded '%s' url=%s\n",Title,URL);
	return(FALSE);
}

if (Flags & FLAG_DEBUG) fprintf(stderr,"Next URL: %s\n",URL);




if (! Con) Con=ConnectAndRetryUntilDownload(URL, Flags, BytesRead);
if (Con)
{
	ContentType=CopyStr(ContentType, STREAMGetValue(Con,"HTTP:Content-Type"));
	//Some sites throttle excessively
	STREAMSetTimeout(Con, Settings.STREAMTimeout);

	if (strncmp(Format,"m3u8-stream:",12)==0) RetVal=M3UStreamDownload(Con, URL, Title);
	else
	{
	if (! (Flags & FLAG_TEST_SITES)) OpenOutputFiles(Title,URL,&BytesRead);
	Token=CopyStr(Token,STREAMGetValue(Con,"HTTP:Content-Range"));
	if (StrValid(Token))
	{
		ptr=strrchr(Token,'/');
		ptr++;
		DocSize=strtod(ptr,NULL);
	}
	else
	{
		Token=CopyStr(Token,STREAMGetValue(Con,"HTTP:content-length"));
		if (StrValid(Token)) DocSize=strtod(Token,NULL);
	}

	if (Flags & FLAG_TEST_SITES) RetVal=TRUE;
	else
	{
		if (Flags & FLAG_PLAYER_AUTO) SelectPlayer(ContentType);
		RetVal=TransferItem(Con,Title, URL, Format, DocSize, DocSize, &BytesRead,TRUE);

		Tempstr=CopyStr(Tempstr,URL);
		ptr=strrchr(Tempstr,'?');
		if (ptr) *ptr='\0';

		Extn=CopyStr(Extn,GuessExtn(ContentType, Format, Tempstr));
		CloseOutputFiles(Extn);
	}
	}

	STREAMClose(Con);
}


DestroyString(ContentType);
DestroyString(Tempstr);
DestroyString(Extn);
DestroyString(Token);

return(RetVal);
}



int DownloadPage(const char *URL, int Type, const char *Title, int DLFlags)
{
char *ptr, *Args=NULL;
char *Tempstr=NULL, *Token=NULL;
int Port;
STREAM *S;
int RetVal=FALSE;


if (Flags & (FLAG_DEBUG)) fprintf(stderr,"Next URL: %s\n",URL);
S=ConnectAndSendHeaders(URL, Flags, 0);

if (S) 
{
	if (ExtractItemInfo(S, Type, URL, Title, DLFlags)) RetVal=TRUE;
}
else if (! (Flags & FLAG_QUIET)) fprintf(stderr,"ERROR: failed to Connect to %s\n",URL);

DestroyString(Tempstr);
DestroyString(Token);

return(RetVal);
}

