#include "defines.h"
#include "includes.h"
#include "Vars.h"
#include "libUseful.h"

/* These functions provide an interface for setting variables that */
/* are used by libUseful itself */

int LibUsefulFlags=0;
ListNode *LibUsefulSettings=NULL;

ListNode *LibUsefulValuesGetHead()
{
return(LibUsefulSettings);
}

void LibUsefulInitSettings()
{
char *Tempstr=NULL;

		LibUsefulSettings=ListCreate();
		SetVar(LibUsefulSettings,"LibUsefulVersion",__LIBUSEFUL_VERSION__);
		Tempstr=MCopyStr(Tempstr,__LIBUSEFUL_BUILD_DATE__," ",__LIBUSEFUL_BUILD_TIME__,NULL);
		SetVar(LibUsefulSettings,"LibUsefulBuildTime",Tempstr);
		DestroyString(Tempstr);
}

void LibUsefulSetHTTPFlag(int Flag, const char *Value)
{
int Flags;

	if (strcasecmp(Value, "true")==0) Flags=HTTPGetFlags() | Flag;
	else Flags=HTTPGetFlags() & ~Flag;
	HTTPSetFlags(Flags);
}



void LibUsefulSetValue(const char *Name, const char *Value)
{
	if (! LibUsefulSettings) LibUsefulInitSettings();
	if (strcasecmp(Name,"HttpDebug")==0) LibUsefulSetHTTPFlag(HTTP_DEBUG, Value);
	if (strcasecmp(Name,"HttpNoCookies")==0) LibUsefulSetHTTPFlag(HTTP_NOCOOKIES, Value);
	if (strcasecmp(Name,"HttpNoCompress")==0) LibUsefulSetHTTPFlag(HTTP_NOCOMPRESS, Value);
	if (strcasecmp(Name,"HttpNoRedirect")==0) LibUsefulSetHTTPFlag(HTTP_NOREDIRECT, Value);
	if (strcasecmp(Name,"HttpNoCache")==0) LibUsefulSetHTTPFlag(HTTP_NOCACHE, Value);
	SetVar(LibUsefulSettings,Name,Value);
}

const char *LibUsefulGetValue(const char *Name)
{
if (! LibUsefulSettings) LibUsefulInitSettings();

if (!StrLen(Name)) return("");
return(GetVar(LibUsefulSettings,Name));
}

void LibUsefulAtExit()
{
if (LibUsefulFlags & LU_CONTAINER) FileSystemUnMount("/","lazy");
}
