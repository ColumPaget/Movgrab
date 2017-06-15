#ifndef MOVGRAB_SETTINGS
#define MOVGRAB_SETTINGS

#include "common.h"

typedef struct
{
int Flags;
int DebugLevel;
char *UserAgent;
char *Proxy;
char *Username;
char *Password;
char *FormatPreference;
char *ItemSelectArg;
int DisplayTitleWidth;
char *NowPlayingFile;
int STREAMTimeout;
int PlayerLaunchPercent;
} TSettings;

extern TSettings Settings;

void InitSettings();
void PrintVersion();
void PrintUsage();
void CheckSettings();
int ParseType(char *Type);
void ParseEnvironmentVariables();
int ParsePreferencesFile(const char *Path);
void ParseCommandLine(int argc, char *argv[], ListNode *DL_List, int *OverrideType);

#endif

