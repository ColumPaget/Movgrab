
#ifndef MOVGRAB_COMMON
#define MOVGRAB_COMMON

//This is doable through autoconf, but I'm sick of fighting with it
#define Version "3.1.1"

#include "libUseful-2.8/libUseful.h"
#include <string.h>
#include <glob.h>
#include "extract_text.h"

#define FLAG_QUIET 1
#define FLAG_BACKGROUND 2
#define FLAG_DEBUG1 4
#define FLAG_DEBUG2 8
#define FLAG_DEBUG3 16
#define FLAG_DEBUG (FLAG_DEBUG1 | FLAG_DEBUG2 | FLAG_DEBUG3)
#define FLAG_PORN 32
#define FLAG_PRINT_USAGE 64
#define FLAG_PRINT_VERSION 128
#define FLAG_TEST  256
#define FLAG_STDIN 512
#define FLAG_STDOUT 1024
#define FLAG_WAIT_INPUT 2048
#define FLAG_TEST_SITES 4096
#define FLAG_STREAM 8192
#define FLAG_STREAMCACHE 16384
#define FLAG_RETRY_DOWNLOAD 32768
#define FLAG_RESUME 65536
#define FLAG_HTTPS 131072
#define FLAG_POST 262144
#define FLAG_PLAYER_AUTO 524288
#define FLAG_NOOUT 1048576


extern int Type, Flags;
extern char *FileTypes[];
extern char *ItemSelectionArg;
extern char *NowPlayingFile;
extern char *FormatPreference;
extern char *Username, *Password;
extern char *Proxy;
extern char *ProgName, *CmdLine, *UserAgent;
extern int STREAMTimeout;
extern STREAM *StdIn;

char *FileTypeFromURL(char *URL);
char *BuildURL(char *RetStr, const char *Parent, const char *SubItem);
char *ItemCodeFromFileExtension(char *RetBuf, const char *Default, const char *URL);
void VarsAddDownloadItem(const char *ItemName, const char *URL, ListNode *Vars, int AddFlags);
int CheckForKeyboardInput();


#endif
