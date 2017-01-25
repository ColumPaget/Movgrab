#include "selectformat.h"
#include "servicetypes.h"

char *GatherMatchingFormats(char *Buffer, char *Type, ListNode *Vars)
{
ListNode *Curr;
char *Tempstr=NULL;

Tempstr=CopyStr(Buffer,"");
Curr=ListGetNext(Vars);
while (Curr)
{
if (strncmp(Curr->Tag,"item:",5)==0)
{
if ((StrLen(Type)==0) || (strncmp(Curr->Tag,Type,StrLen(Type))==0)) Tempstr=MCatStr(Tempstr,Curr->Tag+5," ",NULL);
}

Curr=ListGetNext(Curr);
}

return(Tempstr);
}

int FmtIDMatches(const char *FmtID, const char *CurrItem, const char *ItemData)
{
int len;

len=StrLen(FmtID);

if (len==0) return(TRUE);
if (strcmp(FmtID,"item:*")==0) return(TRUE);
if (strncmp(CurrItem,"item:",5) !=0) return(FALSE);

if ((strncmp(CurrItem,FmtID,StrLen(FmtID))==0) && StrValid(ItemData)) return(TRUE);
return(FALSE);
}



//this function compares the video formats found on the page to the list of
//preferences expressed by the user with the '-f' flag, and contained in the
//global variable 'FormatPreference'
int SelectDownloadFormat(ListNode *Vars, int WebsiteType, int DisplaySize)
{
ListNode *Curr;
char *ptr, *Tempstr=NULL, *Fmt=NULL, *FmtID=NULL, *Selected=NULL, *p_ItemFormat;
int RetVal=-1, FoundMatch=FALSE, i;

Tempstr=GatherMatchingFormats(Tempstr,"",Vars);
	if (! (Flags & FLAG_QUIET))
	{
	for (i=0; i < 3; i++)
	{
 		if (DisplayAvailableFormats(Vars, Tempstr, DisplaySize)) break;
		//printf("Connection Refused, sleeping for 20 secs before retry\n");
		//sleep(10);
		break;
	}
	}

	ptr=GetToken(FormatPreference,",",&Fmt,0);
	while (ptr)
	{
	if (StrLen(Fmt)) FmtID=MCopyStr(FmtID,"item:",Fmt,NULL);
	else FmtID=CopyStr(FmtID,"");

	if (Flags & FLAG_DEBUG) fprintf(stderr,"  %s ",Fmt);

		FoundMatch=FALSE;
		Curr=ListGetNext(Vars);
		while (Curr)
		{
			if (FmtIDMatches(FmtID,Curr->Tag, (char *) Curr->Item))
			{
					if (Flags & (FLAG_DEBUG)) 
					{
						Tempstr=GatherMatchingFormats(Tempstr,FmtID,Vars);
						fprintf(stderr,"... YES! %s\n",Tempstr);
					}

					if (! StrValid(Selected)) 
					{
					Selected=CopyStr(Selected,Curr->Tag);
					SetVar(Vars,"ID",(char *) Curr->Item);
					}

					FoundMatch=TRUE;
					break;
				}
				Curr=ListGetNext(Curr);
			}

			if  ((! FoundMatch) && (Flags & FLAG_DEBUG)) fprintf(stderr,"... no\n",Fmt);

			
			ptr=GetToken(ptr,",",&Fmt,0);
	}


if (StrValid(Selected))
{
	if (strcmp(Selected,"item:reference")==0) RetVal=TYPE_REFERENCE;
	else if (strncmp(Selected,"item:m3u8-stream",16)==0) RetVal=TYPE_CONTAINERFILE_M3U8;
	else RetVal=WebsiteType;
}

if (! (Flags & FLAG_TEST_SITES))
{
	if (RetVal==-1) fprintf(stderr,"No suitable download format found from '%s'\n\n",FormatPreference);
	else if (RetVal==TYPE_REFERENCE) fprintf(stderr,"Reference to another site: %s\n",GetVar(Vars,"ID"));
	else fprintf(stderr,"Selected format %s\n",Selected);
}


//+5 to get past leading 'item:' in variable name
if (StrLen(Selected)) SetVar(Vars,"DownloadFormat",Selected+5);

DestroyString(Selected);
DestroyString(Tempstr);
DestroyString(Fmt);
return(RetVal);
}

