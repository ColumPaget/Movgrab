#ifndef MOVGRAB_CONTAINER_FILES
#define MOVGRAB_CONTAINER_FILES

#include "common.h"

typedef enum {CONT_M3U, CONT_M3U8, CONT_PLS, CONT_ASX} TContainerType;

extern char *ContainerTypes[];

int DownloadContainer(char *Path, char *Title, int Flags);
int GetContainerFileType(char *URL);

#endif

