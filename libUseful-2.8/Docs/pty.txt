#ifndef LIBUSEFUL_PTY_H
#define LIBUSEFUL_PTY_H

#include "defines.h"

#define TTYFLAG_PTY 1
#define TTYFLAG_CANON 4096
#define TTYFLAG_HARDWARE_FLOW 8192
#define TTYFLAG_SOFTWARE_FLOW 16324
#define TTYFLAG_CRLF_KEEP 32768
#define TTYFLAG_IGNSIG 65536
#define TTYFLAG_ECHO 131072
#define TTYFLAG_CRLF 262144
#define TTYFLAG_LFCR 524288
#define TTYFLAG_NONBLOCK 1048576

#define STREAMConfigTTY(S,speed,flags) ((S && istty(S->in_fd)) ? TTYConfig(S->in_fd,speed,flags))
#define STREAMResetTTY(S) ((S && istty(S->in_fd)) ? TTYReset(S->in_fd))
#define STREAMHangUpTTY(S) ((S && istty(S->in_fd)) ? TTYHangUp(S->in_fd))

#ifdef __cplusplus
extern "C" {
#endif

int TTYReset(int tty);
int TTYHangUp(int tty);
int TTYOpen(const char *devname, int LineSpeed, int Flags);
void TTYConfig(int tty, int LineSpeed, int Flags);
int TTYConfigOpen(const char *Dev, const char *Config);
int TTYParseConfig(const char *Config, int *Speed);
int PseudoTTYGrab(int *pty, int *tty, int Flags);

#ifdef __cplusplus
}
#endif


#endif
