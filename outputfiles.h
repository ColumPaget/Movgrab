
#ifndef MOVGRAB_OUTPUT_FILES
#define MOVGRAB_OUTPUT_FILES

#include "common.h"

char *OutputFilesGetFilePath();
void OpenOutputFiles(char *Title, char *URL, double *FileSize);
void WriteOutputFiles(char *Data, int Len);
void AddOutputFile(char *Path, int SingleOutput);
char *GuessExtn(char *ContentType, char *Format, char *ID);


#endif
