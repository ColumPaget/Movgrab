#ifndef LIBUSEFUL_LOG_H
#define LIBUSEFUL_LOG_H

#include "includes.h"
#include "defines.h"
#include "file.h"

#define LOGFILE_DEFAULTS 0
#define LOGFILE_FLUSH 1
#define LOGFILE_SYSLOG 2
#define LOGFILE_LOGPID 4
#define LOGFILE_LOGUSER 8
#define LOGFILE_LOCK 16
#define LOGFILE_TIMESTAMP 32
#define LOGFILE_MILLISECS 64
#define LOGFILE_ROTATE_NUMBERS 128
#define LOGFILE_ROTATE_MINUS 256
#define LOGFILE_HARDEN 512
#define LOGFILE_MARK   1024
#define LOGFILE_FMARK  2048
#define LOGFILE_REPEATS  4096
#define LOGFILE_PLAIN 536870912

#define LOGFLUSH_FORCE 1
#define LOGFLUSH_REOPEN 2

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
  char *Path;
  int Flags;
  uint64_t MaxSize;
  int MaxRotate;
  int LogFacility;
  time_t LastMessageTime;
  time_t LastFlushTime;
  time_t FlushInterval;
  time_t NextMarkTime;
  time_t MarkInterval;
	char *LastMessage;
	int RepeatMessage;
  STREAM *S;
} TLogFile;

ListNode *LogFilesGetList();
TLogFile *LogFileCreate(const char *FileName, int Flags);
TLogFile *LogFileGetEntry(const char *FileName);
int LogFileSetDefaults(int Flags, int MaxSize, int MaxRotate, int FlushInterval);
void LogFileSetValues(TLogFile *LogFile, int Flags, int MaxSize, int MaxRotate, int FlushInterval);
int LogFileFindSetValues(const char *FileName, int Flags, int MaxSize, int MaxRotate, int FlushInterval);
void LogFileFlushAll(int Force);
void LogFileClose(const char *Path);
int LogFileAppendTempLog(const char *LogPath, const char *TmpLogPath);
void LogFileCheckRotate(const char *FileName);


int LogToSTREAM(STREAM *S, int Flags, const char *Str);
int LogWrite(TLogFile *Log, const char *Str);
int LogToFile(const char *FileName, const char *fmt, ...);

#ifdef __cplusplus
}
#endif


#endif
