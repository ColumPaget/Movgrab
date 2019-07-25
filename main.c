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
#include "settings.h"



int Type=TYPE_NONE;





main(int argc, char *argv[])
{
ListNode *Curr, *Next;
int OverrideType=TYPE_NONE;
char *Tempstr=NULL;
int result;

InitSettings();
HTTPSetFlags(HTTP_NOCOMPRESS);
StdIn=STREAMFromFD(0);
STREAMSetTimeout(StdIn,0);

DownloadQueue=ListCreate();
Tempstr=MCopyStr(Tempstr,GetCurrUserHomeDir(), "/.movgrab.conf", NULL);
if (! ParsePreferencesFile(Tempstr)) ParsePreferencesFile("/etc/movgrab.conf");
ParseEnvironmentVariables();

AddOutputFile("", TRUE);

ParseCommandLine(argc, argv, DownloadQueue, &OverrideType);
CheckSettings();
if (StrValid(Settings.Proxy)) 
{
//	if (strncmp(Settings.Proxy,"http:",5)==0) HTTPSetProxy(Settings.Proxy);
//	else if (strncmp(Settings.Proxy,"https:",6)==0) HTTPSetProxy(Settings.Proxy);
//	else 
	if (! SetGlobalConnectionChain(Settings.Proxy))
	{
		printf("ERROR: Failed to set proxy settings to '%s'\n",Settings.Proxy);
		exit(1);
	}
}

LibUsefulSetValue("HTTP:UserAgent", Settings.UserAgent);


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
			LibUsefulSetValue("Error:Silent", "Y");
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
