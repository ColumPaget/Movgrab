#ifndef MOVGRAB_SETTINGS
#define MOVGRAB_SETTINGS

#include "common.h"

void PrintVersion();
void PrintUsage();
int ParseType(char *Type);
void ParseCommandLine(int argc, char *argv[], ListNode *DL_List, int *OverrideType);
void CheckSettings();
void ParseEnvironmentVariables();

#endif

