//Movgrab. A downloader for movie/media websites.
//Written by Colum Paget.
//Copyright 2010 Colum Paget.


/****  Gnu Public Licence ****/
/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version. 
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "servicetypes.h"
#include "containerfiles.h"
#include "download.h"
#include "outputfiles.h"
#include "youtube.h"
#include "ehow.h"
#include "display.h"



int Flags=0;
ListNode *DownloadQueue=NULL;
STREAM *StdIn=NULL;
int Type=TYPE_NONE;

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





//-------- Go through the processes involved in getting a video file
int GrabMovie(char *Path, int MovType)
{
int i;
char *Proto=NULL, *Server=NULL, *Doc=NULL, *Tempstr=NULL, *Title=NULL;
char *NextPath=NULL;
char *ptr, *Token=NULL;
int Port;
int RetVal=FALSE;

if (!StrLen(Path)) return(FALSE);

Type=MovType;
NextPath=CopyStr(NextPath,Path);
ParseURL(Path,&Proto,&Server,&Tempstr,NULL,NULL,&Doc,NULL);
if (Tempstr) Port=atoi(Tempstr);

if (Proto && (strcasecmp(Proto,"https")==0) )
{
	if (! SSLAvailable)
	{
		printf("SSL NOT COMPILED IN! Switching from 'https' to 'http'\n");
		NextPath=MCopyStr(NextPath,"http://",Server,"/",ptr);
	}
}

if (Type==TYPE_NONE) Type=IdentifyServiceType(Path);


if (Type==TYPE_NONE)
{
if (! (Flags & FLAG_QUIET)) fprintf(stderr,"Unrecognized url type. Falling Back to 'generic youtube frontend'.\n Try using the -t option to force the service type ( \"movgrab -?\" for more details )\n");
Type=TYPE_GENERIC;
}

NextPath=SiteSpecificPreprocessing(NextPath, Path, Proto, Server, Port, Doc, &Type, &Title, &Flags);
if (DownloadPage(NextPath, Type, Title, Flags)) RetVal=TRUE;

DestroyString(Tempstr);
DestroyString(Server);
DestroyString(Doc);
DestroyString(NextPath);
DestroyString(Token);
DestroyString(Title);
DestroyString(Proto);

return(RetVal);
}






main(int argc, char *argv[])
{
ListNode *Curr, *Next;
int OverrideType=TYPE_NONE;
char *Tempstr=NULL;
int result;

//HTTPSetFlags(HTTP_NOCOMPRESS);
StdIn=STREAMFromFD(0);
STREAMSetTimeout(StdIn,0);
ParseEnvironmentVariables();
UserAgent=MCopyStr(UserAgent,"Movgrab ",Version,NULL);

DownloadQueue=ListCreate();
FormatPreference=CopyStr(FormatPreference,"mp4,flv,webm,m4v,mov,mpg,mpeg,wmv,avi,3gp,mp3,m4a,wma,m3u8,m3u8-stream,reference");
AddOutputFile("", TRUE);

ParseCommandLine(argc, argv, DownloadQueue, &OverrideType);
CheckSettings();
if (StrValid(Proxy)) 
{
	if (strncmp(Proxy,"http:",5)==0) HTTPSetProxy(Proxy);
	else if (strncmp(Proxy,"https:",6)==0) HTTPSetProxy(Proxy);
	else if (! SetGlobalConnectionChain(Proxy))
	{
		printf("ERROR: Failed to set proxy settings to '%s'\n",Proxy);
		exit(1);
	}
}

HTTPSetUserAgent(UserAgent);


if (Flags & FLAG_PRINT_USAGE) PrintUsage();
else if (Flags & FLAG_PRINT_VERSION) PrintVersion();
else if (! (Flags & FLAG_STDIN))
{
	if (ListSize(DownloadQueue)==0) PrintUsage();
}


while (1)
{
	if ((Flags & FLAG_STDIN) && (ListSize(DownloadQueue)==0) )
	{
		Tempstr=STREAMReadLine(Tempstr,StdIn);
		StripTrailingWhitespace(Tempstr);
		ListAddItem(DownloadQueue,CopyStr(NULL,Tempstr));
	}

	Curr=ListGetNext(DownloadQueue);
	while (Curr)
	{
		if (Flags & FLAG_TEST_SITES)
		{
			fprintf(stderr,"Checking %-20s ",Curr->Tag);
			fflush(NULL);
		}


		result=GrabMovie((char *) Curr->Item,OverrideType);
		Next=ListGetNext(Curr); //must do this after grab movie
																//incase more items added while grabbing

			if (Flags & FLAG_TEST_SITES) 
			{
				if (result) fprintf(stderr," okay\n");
				else fprintf(stderr," BROKEN\n");
			}
			
		ListDeleteNode(Curr);
		HTTPClearCookies();

		Curr=Next;
	}

	if (Flags & FLAG_TEST_SITES) break;
	if (! (Flags & FLAG_STDIN)) break;
}

}
