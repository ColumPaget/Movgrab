#ifndef LIBUSEFUL_FILEPATH_H
#define LIBUSEFUL_FILEPATH_H

#include "includes.h"
#include "DataProcessing.h"

#ifdef __cplusplus
extern "C" {
#endif

#define FileCopy(SrcPath, DestPath) (FileCopyWithProgress(SrcPath, DestPath, NULL))

const char *GetBasename(const char *Path);
char *SlashTerminateDirectoryPath(char *DirPath);
char *StripDirectorySlash(char *DirPath);
int FileExists(const char *);
int MakeDirPath(const char *Path, int DirMask);
int FindFilesInPath(const char *File, const char *Path, ListNode *Files);
char *FindFileInPath(char *InBuff, const char *File, const char *Path);
int FileChangeExtension(const char *FilePath, const char *NewExt);
int FindFilesInPath(const char *File, const char *Path, ListNode *Files);
int FileChOwner(const char *Path, const char *Owner);
int FileChGroup(const char *Path, const char *Group);

char *FileGetXAttribute(char *RetStr, const char *Path, const char *Name);
int FileSetXAttribute(const char *Path, const char *Name, const char *Value, int Len);

int FileCopyWithProgress(const char *SrcPath, const char *DestPath, DATA_PROGRESS_CALLBACK Callback);

int FileSystemMount(const char *Dev, const char *MountPoint, const char *Type, const char *Args);
int FileSystemUnMount(const char *MountPoint, const char *Args);

int FileNotifyInit(const char *Path, int Flags);
int FileNotifyGetNext(int fd, char **Path);


#ifdef __cplusplus
}
#endif



#endif
