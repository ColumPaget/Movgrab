
#ifndef LIBUSEFUL_ANSI_H
#define LIBUSEFUL_ANSI_H

#include "includes.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {ANSI_NONE, ANSI_BLACK, ANSI_RED, ANSI_GREEN, ANSI_YELLOW, ANSI_BLUE, ANSI_MAGENTA, ANSI_CYAN, ANSI_WHITE, ANSI_RESET, ANSI_RESET2, ANSI_DARKGREY, ANSI_LIGHTRED, ANSI_LIGHTGREEN, ANSI_LIGHTYELLOW, ANSI_LIGHTBLUE, ANSI_LIGHTMAGENTA, ANSI_LIGHTCYAN, ANSI_LIGHTWHITE} T_ANSI_COLORS;


#define ANSI_HIDE			65536
#define ANSI_BOLD			131072
#define ANSI_FAINT		262144
#define ANSI_UNDER		524288
#define ANSI_BLINK		1048576
#define ANSI_INVERSE  2097152
#define ANSI_NORM "\x1b[0m"
#define ANSI_BACKSPACE 0x08

#define TERM_SHOWTEXT  1
#define TERM_SHOWSTARS 2
#define TERM_SHOWTEXTSTARS 4

#define TERMBAR_UPPER 1
#define TERMBAR_LOWER 2
#define TERMBAR_CENTER 4

typedef enum {TERM_NORM, TERM_TEXT, TERM_COLOR, TERM_CLEAR_SCREEN, TERM_CLEAR_ENDLINE, TERM_CLEAR_STARTLINE, TERM_CLEAR_LINE, TERM_CURSOR_HOME, TERM_CURSOR_MOVE, TERM_CURSOR_SAVE, TERM_CURSOR_UNSAVE, TERM_CURSOR_HIDE, TERM_CURSOR_SHOW, TERM_SCROLL, TERM_SCROLL_REGION, TERM_UNICODE} ETerminalCommands; 


#define TerminalClear(S) ( TerminalCommand(TERM_CLEAR_SCREEN, 0, 0, S))
#define TerminalEraseLine(S) ( TerminalCommand(TERM_CLEAR_ENDLINE, 0, 0, S))
#define TerminalCursorHide(S) ( TerminalCommand(TERM_CURSOR_HIDE, 0, 0, S))
#define TerminalCursorShow(S) ( TerminalCommand(TERM_CURSOR_SHOW, 0, 0, S))
#define TerminalCursorSave(S) ( TerminalCommand(TERM_CURSOR_SAVE, 0, 0, S))
#define TerminalCursorRestore(S) ( TerminalCommand(TERM_CURSOR_UNSAVE, 0, 0, S))
#define TerminalCursorMove(S, x, y) ( TerminalCommand(TERM_CURSOR_MOVE, x, y, S))
#define TerminalScroll(S, x, y) ( TerminalCommand(TERM_SCROLL, y, x, S))
#define TerminalScrollUp(S) ( TerminalCommand(TERM_SCROLL, 1, 0, S))
#define TerminalScrollDown(S) ( TerminalCommand(TERM_SCROLL, -1, 0, S))

typedef struct
{
int Flags;
char *ForeColor;
char *BackColor;
int TextLen;
char *Text;
STREAM *Term;
} TERMBAR;


char *ANSICode(int Color, int BgColor, int Flags);
int ANSIParseColor(const char *Str);
int TermStrLen(const char *Str);
int TerminalCommand(int Cmd, int Arg1, int Arg2, STREAM *S);
char *TerminalFormatStr(char *RetStr, const char *Str);
void TerminalPutStr(const char *Str, STREAM *S);
char *TerminalReadText(char *RetStr, int Flags, STREAM *S);
char *TerminalReadPrompt(char *RetStr, const char *Prompt, int Flags, STREAM *S);
void TerminalGeometry(STREAM *S, int *wid, int *len);
TERMBAR *TerminalBarCreate(STREAM *Term, const char *Config, const char *Text);
void TerminalBarUpdate(TERMBAR *TB, const char *Text);
char *TerminalBarReadText(char *RetStr, TERMBAR *TB, const char *Prompt);
int TerminalInit(STREAM *S);

#ifdef __cplusplus
}
#endif



#endif
