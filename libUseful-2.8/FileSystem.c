#include "FileSystem.h"
#include <glob.h>
//#include <sys/ioctl.h>
//#include <sys/resource.h>
#include <sys/mount.h>

#ifdef linux
#include <sys/xattr.h>
#endif

const char *GetBasename(const char *Path)
{
const char *ptr;
int len;

len=StrLen(Path);
if (len==0) return("");
if (len==1) return(Path);

ptr=Path+len-1;
while (ptr > Path)
{
  if ((*ptr=='/') && (*(ptr+1) != '\0')) break;
  ptr--;
}

if ((*ptr=='/') && (*(ptr+1) != '\0')) ptr++;

return(ptr);
}


char *SlashTerminateDirectoryPath(char *DirPath)
{
char *ptr, *RetStr=NULL;

if (! StrValid(DirPath)) return(CopyStr(DirPath,"/"));
RetStr=DirPath;
ptr=RetStr+StrLen(RetStr)-1;
if (*ptr != '/') RetStr=AddCharToStr(RetStr,'/');

return(RetStr);
}


char *StripDirectorySlash(char *DirPath)
{
char *ptr;

//don't strip '/' (root dir)
if (! StrValid(DirPath)) return(DirPath);
if (strcmp(DirPath,"/")==0) return(DirPath);
ptr=DirPath+StrLen(DirPath)-1;

if (*ptr == '/') *ptr='\0';

return(DirPath);
}


int MakeDirPath(const char *Path, int DirMask)
{
 const char *ptr;
 char *Tempstr=NULL;
 int result=-1;

 ptr=Path;
 if (*ptr=='/') ptr++;
 ptr=strchr(ptr, '/');
 while (ptr)
 {
   Tempstr=CopyStrLen(Tempstr,Path,ptr-Path);
   result=mkdir(Tempstr, DirMask);
   if ((result==-1) && (errno != EEXIST)) break;
   ptr=strchr(++ptr, '/');
 }
 DestroyString(Tempstr);
 if (result==0) return(TRUE);
 return(FALSE);
}



int FileChangeExtension(const char *FilePath, const char *NewExt)
{
char *ptr;
char *Tempstr=NULL;
int result;

Tempstr=CopyStr(Tempstr,FilePath);
ptr=strrchr(Tempstr,'/');
if (!ptr) ptr=Tempstr;
ptr=strrchr(ptr,'.');
if (! ptr) ptr=Tempstr+StrLen(Tempstr);
*ptr='\0';

if (*NewExt=='.') Tempstr=CatStr(Tempstr,NewExt);
else Tempstr=MCatStr(Tempstr,".",NewExt,NULL);
result=rename(FilePath,Tempstr);

DestroyString(Tempstr);
if (result==0) return(TRUE);
else return(FALSE);
}


int FindFilesInPath(const char *File, const char *Path, ListNode *Files)
{
char *Tempstr=NULL, *CurrPath=NULL, *ptr;
int i;
glob_t Glob;

if (*File=='/')
{
	CurrPath=CopyStr(CurrPath,"");
	ptr=""; //so we execute once below
}
else ptr=GetToken(Path,":",&CurrPath,0);
while (ptr)
{
CurrPath=SlashTerminateDirectoryPath(CurrPath);
Tempstr=MCopyStr(Tempstr,CurrPath,File,NULL);

glob(Tempstr,0,0,&Glob);
for (i=0; i < Glob.gl_pathc; i++) ListAddItem(Files,CopyStr(NULL,Glob.gl_pathv[i]));
globfree(&Glob);

ptr=GetToken(ptr,":",&CurrPath,0);
}

DestroyString(Tempstr);
DestroyString(CurrPath);

return(ListSize(Files));
}



char *FindFileInPath(char *InBuff, const char *File, const char *Path)
{
char *Tempstr=NULL, *CurrPath=NULL, *RetStr=NULL, *ptr;

RetStr=CopyStr(InBuff,"");

if (*File=='/')
{
	CurrPath=CopyStr(CurrPath,"");
	ptr=""; //so we execute once below
}
else ptr=GetToken(Path,":",&CurrPath,0);

while (ptr)
{
CurrPath=SlashTerminateDirectoryPath(CurrPath);
Tempstr=MCopyStr(Tempstr,CurrPath,File,NULL);
if (access(Tempstr,F_OK)==0) 
{
RetStr=CopyStr(RetStr,Tempstr);
break;
}

ptr=GetToken(ptr,":",&CurrPath,0);
}

DestroyString(Tempstr);
DestroyString(CurrPath);

return(RetStr);
}


/* This checks if a certain file exists (not if we can open it etc, just if */
/* we can stat it, this is useful for checking pid files etc).              */
int FileExists(const char *FileName)
{
struct stat StatData;

if (stat(FileName,&StatData) == 0) return(1);
else return(0);
}


int FileChOwner(const char *FileName, const char *Owner)
{
int uid, result;

uid=LookupUID(Owner);
if (uid > -1) 
{
	result=chown(FileName, uid, -1);
	if (result==0) return(TRUE);
}
return(FALSE);
}



int FileChGroup(const char *FileName, const char *Group)
{
int gid, result;

gid=LookupGID(Group);
if (gid > -1) 
{
	result=chown(FileName, -1, gid);
	if (result==0) return(TRUE);
}
return(FALSE);
}


int FileCopyWithProgress(const char *SrcPath, const char *DestPath, DATA_PROGRESS_CALLBACK Callback)
{
STREAM *Src;
int result;

Src=STREAMOpen(SrcPath,"r");
if (! Src) return(FALSE);
if (Callback) STREAMAddProgressCallback(Src,Callback);
result=STREAMCopy(Src, DestPath);
STREAMClose(Src);
return(result);
}


char *FileGetXAttribute(char *RetStr, const char *Path, const char *Name)
{
int len;

#ifdef linux
len=getxattr(Path, Name, NULL, 0);
if (len > 0)
{
	RetStr=SetStrLen(RetStr,len);
	getxattr(Path, Name, RetStr, len);
}
else RetStr=CopyStr(RetStr, "");
#endif

return(RetStr);
}


int FileSetXAttribute(const char *Path, const char *Name, const char *Value, int Len)
{
#ifdef linux
if (Len==0) Len=StrLen(Value);
return(setxattr(Path, Name, Value, Len, 0));
#endif

return(-1);
}




int FileSystemMount(const char *Dev, const char *MountPoint, const char *Type, const char *Args)
{
const char *ptr, *p_Type, *p_MountPoint;
char *Token=NULL;
int Flags=0, result, Perms=700;

p_Type=Type;
if (! StrValid(MountPoint)) 
{
	p_MountPoint=Dev;
	if (*p_MountPoint) p_MountPoint++;
}
else p_MountPoint=MountPoint;

if (! StrValid(p_MountPoint)) return(FALSE);

#ifdef MS_BIND
if (strcmp(Type,"bind")==0) 
{
	p_Type="";
	Flags=MS_BIND;
}
#endif


ptr=GetToken(Args, " |,", &Token, GETTOKEN_MULTI_SEP);
while (ptr)
{
	#ifdef MS_RDONLY
	if (strcmp(Token,"ro")==0) Flags |= MS_RDONLY;
	#endif

	#ifdef MS_NOEXEC
	if (strcmp(Token,"noexec")==0) Flags |= MS_NOEXEC;
	#endif

	#ifdef MS_NOSUID
	if (strcmp(Token,"nosuid")==0) Flags |= MS_NOSUID;
	#endif

	#ifdef MS_NODEV
	if (strcmp(Token,"nodev")==0) Flags |= MS_NODEV;
	#endif

	if (strncmp(Token,"perms=",6)==0) Perms=strtol(Token+6,NULL,8);
ptr=GetToken(ptr, " |,", &Token, GETTOKEN_MULTI_SEP);
}

Token=MCopyStr(Token,p_MountPoint,"/",NULL);
MakeDirPath(Token,Perms);

//must do a little dance for readonly bind mounts. We must first mount, then remount readonly
#ifdef MS_BIND
if ((Flags & MS_BIND) && (Flags & MS_RDONLY)) 
{
	mount(Dev,p_MountPoint,"",MS_BIND,NULL);
	Flags |= MS_REMOUNT;
}
#endif

#ifdef linux
result=mount(Dev,p_MountPoint,p_Type,Flags,NULL);
#else
//assume BSD if not linux
result=mount(p_Type,p_MountPoint,Flags,Dev);
#endif

DestroyString(Token);
return(result);
}



//if the system doesn't have these flags then define empty values for them
#ifndef UMOUNT_NOFOLLOW
#define UMOUNT_NOFOLLOW 0
#endif

#ifndef MNT_DETACH
#define MNT_DETACH 0
#endif


#define UMOUNT_RECURSE 1
#define UMOUNT_RMDIR   2

int FileSystemUnMount(const char *MountPoint, const char *Args)
{
int Flags=UMOUNT_NOFOLLOW;
int ExtraFlags=0;
char *Token=NULL;
const char *ptr;
struct stat FStat;
int i, result;
glob_t Glob;

ptr=GetToken(Args, " |,", &Token, GETTOKEN_MULTI_SEP);
while (ptr)
{
	if (strcmp(Token,"follow")==0) Flags &= ~UMOUNT_NOFOLLOW;
	if (strcmp(Token,"lazy")==0) Flags |= MNT_DETACH;
	if (strcmp(Token,"detach")==0) Flags |= MNT_DETACH;
	if (strcmp(Token,"recurse")==0) ExtraFlags |= UMOUNT_RECURSE;
	if (strcmp(Token,"rmdir")==0) ExtraFlags |= UMOUNT_RMDIR;

ptr=GetToken(ptr, " |,", &Token, GETTOKEN_MULTI_SEP);
}

if (ExtraFlags & UMOUNT_RECURSE)
{
	Token=MCopyStr(Token,MountPoint,"/*",NULL);
	glob(Token, 0, 0, &Glob);
	for (i=0; i < Glob.gl_pathc; i++)
	{
		stat(Glob.gl_pathv[i],&FStat);
		if (S_ISDIR(FStat.st_mode))
		{
			FileSystemUnMount(Glob.gl_pathv[i], Args);	
		}
	}
	globfree(&Glob);
}



#ifdef HAVE_UMOUNT2
result=umount2(MountPoint, Flags);
#elif HAVE_UMOUNT
result=umount(MountPoint);
#elif HAVE_UNMOUNT
result=unmount(MountPoint,0);
#else 
result=-1
#endif

if (ExtraFlags & UMOUNT_RMDIR) rmdir(MountPoint);
DestroyString(Token);

return(result);
}


#ifdef HAVE_FANOTIFY

#include <linux/fanotify.h>
#include <sys/fcntl.h>
#include <sys/stat.h>


/*
+  fd = fanotify_init (0, 0);
+  if (fd < 0 && 0)
+    {
+      if (errno == ENOSYS)
+	{
+	  puts ("SKIP: missing support for fanotify (check CONFIG_FANOTIFY=y)");
+	  return 0;
+	}
+
+      perror ("fanotify_init (0, 0) failed");
+      return 1;
+    }
+
+  ret = fanotify_mark (fd, FAN_MARK_ADD | FAN_MARK_MOUNT, FAN_ACCESS
+		       | FAN_MODIFY | FAN_OPEN | FAN_CLOSE | FAN_ONDIR
+		       | FAN_EVENT_ON_CHILD, AT_FDCWD, ".");
+  if (ret)
+    {
+      perror ("fanotify_mark (...) failed");
+      return 1;
+    }
+
+  puts ("All OK");
+  return 0;
+}
*/


int FileNotifyInit(const char *Path, int Flags)
{
char *Token=NULL, *ptr;
int fd;

fd=fanotify_init(Flags, O_RDWR);
if (fd==-1) return(fd);

ptr=GetToken(Path,":",&Token,0);
while (ptr)
{
	fanotify_mark(fd, FAN_MARK_ADD, FAN_CLOSE_WRITE, -1, NULL);

	ptr=GetToken(ptr,":",&Token,0);
}

DestroyString(Token);

return(fd);
}


int FileNotifyGetNext(int fd, char **Path)
{
struct fanotify_event_metadata metadata;
char *Tempstr=NULL;
int result;

result=read(fd, &metadata, sizeof(struct fanotify_event_metadata));
if (result < sizeof(struct fanotify_event_metadata)) return(-1);

if (Path)
{
	Tempstr=FormatStr(Tempstr, "/proc/self/fd/%d", metadata.fd);
	*Path=SetStrLen(*Path,PATH_MAX +1);
	readlink(Tempstr,*Path,PATH_MAX +1);
}

DestroyString(Tempstr);
return(metadata.fd);
}



#endif
