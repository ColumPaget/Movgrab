#ifndef MOVGRAB_CONTAINER_FILES
#define MOVGRAB_CONTAINER_FILES

#include "common.h"

typedef enum {CONT_M3U, CONT_M3U8, CONT_PLS, CONT_ASX} TContainerType;

extern const char *ContainerTypes[];

void M3UStreamVarName(const char *Config, char **VarName);
int M3UContainer(const char *URL, ListNode *Vars);
int GetContainerFileType(const char *URL);
int M3UStreamDownload(STREAM *ManifestCon, const char *URL, const char *Title);

#endif

