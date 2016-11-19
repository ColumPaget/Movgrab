#ifndef LIBUSEFUL_SPAWN_H
#define LIBUSEFUL_SPAWN_H

#include "includes.h"

#ifdef __cplusplus
extern "C" {
#endif

#define COMMS_BY_PIPE 0
#define COMMS_BY_PTY 1
#define SPAWN_TRUST_COMMAND 2
#define COMMS_COMBINE_STDERR 4
#define SPAWN_DAEMON 8
#define SPAWN_SETSID 16
#define SPAWN_CTRL_TTY 32
#define SPAWN_CHROOT 64
#define SPAWN_JAIL 128
#define SPAWN_SIGDEF 256

//up to 2048, beyond that is TTYFLAG_

#define SHELLSAFE_BLANK 1

char *MakeShellSafeString(char *RetStr, const char *String, int SafeLevel);
void SwitchProgram(const char *CommandLine, int Flags, const char *Config);
int ForkWithContext();
/* This function turns our process into a demon */
int demonize();
int ForkWithIO(int StdIn, int StdOut, int StdErr);
int SpawnWithIO(const char *CommandLine, int Flags, const char *Config, int StdIn, int StdOut, int StdErr);
int Spawn(const char *ProgName, int Flags, const char *Config);
/* This creates a child process that we can talk to using a couple of pipes*/
int PipeSpawnFunction(int *infd,int  *outfd,int  *errfd, BASIC_FUNC Func, void *Data, int Flags, const char *Config);
int PipeSpawn(int *infd,int  *outfd,int  *errfd, const char *Command, int Flags, const char *Config);
int PseudoTTYSpawn(int *pty, const char *Command, int Flags, const char *Config);
STREAM *STREAMSpawnCommand(const char *Command, int Flags, const char *Config);
STREAM *STREAMSpawnFunction(BASIC_FUNC Func, void *Data, int Flags, const char *Config);

#ifdef __cplusplus
}
#endif


#endif
