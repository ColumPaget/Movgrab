#ifndef MOVGRAB_PLAYERS_H
#define MOVGRAB_PLAYERS_H

#include "common.h"

extern int DisplayTitleWidth;

void ParsePlayer(const char *Config);
char *SelectPlayer(const char *ContentType);
void SetPlayer(const char *Config);
void LaunchPlayer();

#endif
