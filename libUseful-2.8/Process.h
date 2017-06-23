#ifndef LIBUSEFUL_PROCESS_H
#define LIBUSEFUL_PROCESS_H


#define COMMS_COMBINE_STDERR 4
#define PROC_DAEMON 8
#define PROC_SETSID 16
#define PROC_CTRL_TTY 32
#define PROC_CHROOT 64
#define PROC_JAIL 128
#define PROC_SIGDEF 256
#define PROC_CONTAINER 512
#define PROC_CONTAINER_NET  1024

//these must be compatible with PROC_ defines
#define SPAWN_NOSHELL 8192
#define SPAWN_TRUST_COMMAND 16384


void CloseOpenFiles();
int SwitchUID(int uid);
int SwitchGID(int gid);
int SwitchUser(const char *User);
int SwitchGroup(const char *Group);
char *GetCurrUserHomeDir();
int WritePidFile(char *ProgName);
int CreateLockFile(char *FilePath,int Timeout);
void ProcessTitleCaptureBuffer(char **argv);
void ProcessSetTitle(char *FmtStr, ...);
void ColLibDefaultSignalHandler(int sig);
int ProcessApplyConfig(const char *Config);
int demonize();

#endif
