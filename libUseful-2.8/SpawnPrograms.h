#ifndef LIBUSEFUL_SPAWN_H
#define LIBUSEFUL_SPAWN_H

#include "includes.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SHELLSAFE_BLANK 1

char *MakeShellSafeString(char *RetStr, const char *String, int SafeLevel);
void SwitchProgram(const char *CommandLine, const char *Config);
int xfork(const char *Config);
int xforkio(int StdIn, int StdOut, int StdErr);
int SpawnWithIO(const char *CommandLine, const char *Config, int StdIn, int StdOut, int StdErr);
int Spawn(const char *ProgName, const char *Config);
/* This creates a child process that we can talk to using a couple of pipes*/
pid_t PipeSpawnFunction(int *infd,int  *outfd,int  *errfd, BASIC_FUNC Func, void *Data, const char *Config);
pid_t PipeSpawn(int *infd,int  *outfd,int  *errfd, const char *Command, const char *Config);
pid_t PseudoTTYSpawnFunction(int *ret_pty, BASIC_FUNC Func, void *Data, int Flags, const char *Config);
pid_t PseudoTTYSpawn(int *pty, const char *Command, const char *Config);
STREAM *STREAMSpawnCommand(const char *Command, const char *Config);
STREAM *STREAMSpawnFunction(BASIC_FUNC Func, void *Data, const char *Config);

#ifdef __cplusplus
}
#endif


#endif
