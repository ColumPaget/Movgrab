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


void LibUsefulSetValue(const char *Name, const char *Value)
{
	if (! LibUsefulSettings) LibUsefulInitSettings();
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
