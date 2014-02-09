#include "download.h"
#include "outputfiles.h"
#include "display.h"

/*
Functions relating to connecting to hosts and downloading webpages.
All the HTTP stuff is in here
*/ 


char *Proxy=NULL;
extern int STREAMTimeout;

STREAM *ConnectAndSendHeaders(char *URL, int Flags, double BytesRange)
{
STREAM *Con;
char *Tempstr=NULL, *Method=NULL;
HTTPInfoStruct *Info;
static char *LastPage=NULL;

if (StrLen(Proxy)) HTTPSetProxy(Proxy);

if (Flags & FLAG_POST) Method=CopyStr(Method,"POST");
else Method=CopyStr(Method,"GET");

Info=HTTPInfoFromURL(Method, URL);
//if (DLFlags & DL_NOREDIRECT) Info->Flags |=HTTP_NOREDIRECT;
if (Flags & FLAG_HTTPS) Info->Flags |= HTTP_SSL|HTTP_SSL_REWRITE;
if (Flags & FLAG_DEBUG3) Info->Flags |= HTTP_DEBUG;


if (StrLen(LastPage)) SetVar(Info->CustomSendHeaders,"Referer",LastPage); 

LastPage=CopyStr(LastPage,Tempstr);
if (BytesRange > 0)
{
	Tempstr=FormatStr(Tempstr,"bytes=%lld-",(long long) BytesRange);
	SetVar(Info->CustomSendHeaders,"Range",Tempstr); 
}

Con=HTTPTransact(Info);
if ((! Con) && (! (Flags & FLAG_QUIET))) 
{
	if (StrLen(Info->ResponseCode)) fprintf(stderr,"ERROR: Server %s item '%s' not retrieved\nResponseCode: %s\n",Info->Host, Info->Doc,Info->ResponseCode);
	else fprintf(stderr,"ERROR: Connection failed to %s can't get file=%s \n",Info->Host, Info->Doc);
}
DestroyString(Tempstr);
DestroyString(Method);

return(Con);
}



STREAM *ConnectAndRetryUntilDownload(char *URL, int Flags, double BytesRead)
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





int TransferItem(STREAM *Con, char *Title, char *URL, char *Format, double SegmentSize, double DocSize, double *BytesRead, int PrintName)
{
char *Tempstr=NULL;
int result, RetVal=FALSE, PrintDownloadName;
double ReadThisTime=0;

DisplayProgress(Title, Format, *BytesRead, DocSize, PrintName);
Tempstr=SetStrLen(Tempstr,BUFSIZ);
result=STREAMReadBytes(Con,Tempstr,BUFSIZ);
while (result != EOF) 
{
	ReadThisTime +=result;
	(*BytesRead) +=result;

	DisplayProgress(Title, Format, *BytesRead,DocSize,FALSE);

	WriteOutputFiles(Tempstr,result);
	if ((SegmentSize > 0) && (ReadThisTime >= SegmentSize))
	{
		 break;
	}
	result=STREAMReadBytes(Con,Tempstr,BUFSIZ);
}
RetVal=TRUE;

//give a bit of time for 'player' program to finish
sleep(3);

DisplayProgress(Title, Format, *BytesRead,DocSize,FALSE);

DestroyString(Tempstr);

return(RetVal);
}



//----- Download an actual Video ----------------------
int DownloadItem(char *URL, char *Title, char *Format, int Flags)
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

if (! (Flags & FLAG_TEST_SITES)) OpenOutputFiles(Title,URL,&BytesRead);

if (! Con) Con=ConnectAndRetryUntilDownload(URL, Flags, BytesRead);
if (Con)
{
	//Some sites throttle excessively
	STREAMSetTimeout(Con,STREAMTimeout);


	Token=CopyStr(Token,STREAMGetValue(Con,"HTTP:Content-Range"));
	if (StrLen(Token))
	{
		ptr=strrchr(Token,'/');
		ptr++;
		DocSize=strtod(ptr,NULL);
	}
	else
	{
		Token=CopyStr(Token,STREAMGetValue(Con,"HTTP:content-length"));
		if (StrLen(Token)) DocSize=strtod(Token,NULL);
	}

	if (Flags & FLAG_TEST_SITES) RetVal=TRUE;
	else
	{
		RetVal=TransferItem(Con,Title, URL, Format, DocSize, DocSize, &BytesRead,TRUE);

		Tempstr=CopyStr(Tempstr,URL);
		ptr=strrchr(Tempstr,'?');
		if (ptr) *ptr='\0';

		Extn=CopyStr(Extn,GuessExtn(GetVar(Con->Values,"HTTP:Content-Type"), Format, Tempstr));
		CloseOutputFiles(Extn);
	}
	STREAMClose(Con);
}


DestroyString(ContentType);
DestroyString(Tempstr);
DestroyString(Extn);
DestroyString(Token);

return(RetVal);
}



int DownloadPage(char *URL, int Type, char *Title, int DLFlags)
{
char *ptr, *Args=NULL;
char *Tempstr=NULL, *Token=NULL;
int Port;
STREAM *S;
int RetVal=FALSE;

if (Flags & (FLAG_DEBUG)) fprintf(stderr,"Next URL: %s\n",URL);
S=ConnectAndSendHeaders(URL, Flags, 0);

if (S) if (ExtractItemInfo(S, Type, URL, Title, DLFlags)) RetVal=TRUE;
else if (! (Flags & FLAG_QUIET)) fprintf(stderr,"ERROR: failed to Connect to %s\n",URL);

DestroyString(Tempstr);
DestroyString(Token);

return(RetVal);
}

