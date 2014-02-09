#ifndef MOVGRAB_DISPLAY_H
#define MOVGRAB_DISPLAY_H

#include "common.h"

extern char *Player;

int DisplayAvailableFormats(ListNode *Vars, char *Formats, int ShowSize);
void DisplayProgress(char *FullTitle, char *Format, double bytes_read, double DocSize, int PrintName);

#endif

