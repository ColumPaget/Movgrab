#include "display.h"
#include "outputfiles.h"
#include "settings.h"

int DisplayTitleWidth=50;
extern char *CmdLine, *ProgName;




int DisplayAvailableFormats(ListNode *Vars, char *Formats, int ShowSize)
{
char *URL=NULL, *Token=NULL, *TokenID=NULL, *Tempstr=NULL, *ptr;
STREAM *S;
int result=TRUE;

fprintf(stderr, "\nAvailable media formats: ");

ptr=GetToken(Formats," ",&Token,0);
while (ptr)
{
if (StrValid(Token)) TokenID=MCopyStr(TokenID,"item:",Token,NULL);

URL=CopyStr(URL,GetVar(Vars,TokenID));

if (strcmp(Token,"reference") !=0)
{
	fprintf(stderr,"%s",Token);

	if (ShowSize)
	{
	S=HTTPMethod("HEAD",URL,NULL,NULL,NULL,NULL,0);
	if (S)
	{
		Tempstr=CopyStr(Tempstr,STREAMGetValue(S,"HTTP:ResponseCode"));
		if (strcmp(Tempstr,"200")==0)
		{
			Tempstr=CopyStr(Tempstr,STREAMGetValue(S,"HTTP:Content-length"));
			fprintf(stderr, " (%s)",ToMetric(strtod(Tempstr,NULL),FALSE));
			STREAMClose(S);
		}
	}
	}
}
fprintf(stderr,", ");

ptr=GetToken(ptr," ",&Token,0);
}

fprintf(stderr,"\n\n",Tempstr);

DestroyString(Token);
DestroyString(TokenID);
DestroyString(Tempstr);
DestroyString(URL);

return(result);
}


void WriteNowPlayingFile(const char *Title)
{
STREAM *S;

S=STREAMFileOpen(Settings.NowPlayingFile, SF_WRONLY | SF_CREAT | SF_TRUNC);
if (S)
{
STREAMWriteLine(Title, S);
STREAMWriteLine("\n", S);
STREAMClose(S);
}
}


//Display progress of download
void DisplayProgress(const char *FullTitle, const char *Format, double bytes_read, double DocSize, int PrintName)
{
double Percent=0, Bps=0, ETAsecs=0;
char *HUDocSize=NULL, *BpsStr=NULL, *ETAStr=NULL, *Title=NULL;
static time_t SpeedStart=0, LastDisplay=0;
static double PrevBytesRead=0;
time_t Now;

time(&Now);
if (bytes_read==0) SpeedStart=Now;

if (CheckForKeyboardInput()) PrintName=TRUE;


if ((DisplayTitleWidth > 0) && (StrLen(FullTitle) > DisplayTitleWidth))
{
	Title=CopyStrLen(Title, FullTitle, DisplayTitleWidth);
	Title=CatStr(Title,"...");
}
else Title=CopyStr(Title, FullTitle);

if (! (Flags & FLAG_QUIET)) 
{
if (PrintName) 
{
	fprintf(stderr,"\nGetting: %s  Size: %s  Format: %s\n",Title,ToMetric(DocSize,0), Format);
	if (StrValid(Settings.NowPlayingFile)) WriteNowPlayingFile(Title);
}
}

if ((Now != SpeedStart) && (Now != LastDisplay))
{
BpsStr=CopyStr(BpsStr,"");
if (SpeedStart > 0)
{
	Bps=(bytes_read - PrevBytesRead) / (Now-SpeedStart);
	BpsStr=MCopyStr(BpsStr,ToMetric(Bps,0),"/s ",NULL);
}

if (DocSize)
{
	HUDocSize=CopyStr(HUDocSize,ToMetric(DocSize,0));

	Percent=bytes_read * 100.0 / DocSize;

	if (! (Flags & FLAG_QUIET)) 
	{
		if (bytes_read > 0)
		{
		ETAsecs=(DocSize-bytes_read) / Bps;
		ETAStr=FormatStr(ETAStr,"%d:%02d",(int) ETAsecs/60, (int) ETAsecs % 60);
		}
		else ETAStr=CopyStr(ETAStr,"??:??");

		fprintf(stderr,"	Progress: %0.2f%%  %s of %s  %s  ETA: %s         \r",Percent,ToMetric(bytes_read,0),HUDocSize,BpsStr,ETAStr);
		
	}


	sprintf(CmdLine,"%s %0.2f%% %s          \0",ProgName,Percent,Title);

}
else
{
	if (! (Flags & FLAG_QUIET)) fprintf(stderr,"	Progress: %s %s     \r",ToMetric((double) bytes_read,0),BpsStr);
	sprintf(CmdLine,"%s %s              \0",ProgName,Title);
}

if ((DocSize == 0) || (Percent > Settings.PlayerLaunchPercent)) LaunchPlayer();

fflush(NULL);
if (Now - SpeedStart > 5) 
{
	SpeedStart=Now;
	PrevBytesRead=bytes_read;
}
LastDisplay=Now;
}

DestroyString(HUDocSize);
DestroyString(BpsStr);
DestroyString(Title);
}

