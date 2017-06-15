#include "Terminal.h"
#include "pty.h"
#include <sys/ioctl.h>

const char *ANSIColorStrings[]={"none","black","red","green","yellow","blue","magenta","cyan","white",NULL};


char *ANSICode(int Color, int BgColor, int Flags)
{
static char *ANSI=NULL;
int FgVal, BgVal;

if ((! Color) && (! Flags)) return("");

if ( (Color > 0) && (BgColor > 0) )
{	
	if (Color >= ANSI_DARKGREY) FgVal=90+Color - ANSI_DARKGREY;
	else FgVal=30+Color-1;
	
		if (BgColor >= ANSI_DARKGREY) BgVal=100+BgColor - ANSI_DARKGREY;
	else BgVal=40+BgColor-1;
	
	ANSI=FormatStr(ANSI,"\x1b[%d;%d",FgVal,BgVal);
	if (Flags) ANSI=CatStr(ANSI,";");
}
else if (Color > 0) 
{
	if (Color >= ANSI_DARKGREY) FgVal=90+Color - ANSI_DARKGREY;
	else FgVal=30+Color-1;
	
	ANSI=FormatStr(ANSI,"\x1b[%d",FgVal);
	if (Flags) ANSI=CatStr(ANSI,";");
}
else ANSI=CopyStr(ANSI,"\x1b[");

if (Flags)
{
	if (Flags & ANSI_BOLD) ANSI=CatStr(ANSI,"01");
	if (Flags & ANSI_FAINT) ANSI=CatStr(ANSI,"02");
	if (Flags & ANSI_UNDER) ANSI=CatStr(ANSI,"04");
	if (Flags & ANSI_BLINK) ANSI=CatStr(ANSI,"05");
	if (Flags & ANSI_INVERSE) ANSI=CatStr(ANSI,"07");
}
ANSI=CatStr(ANSI,"m");

return(ANSI);
}





int ANSIParseColor(const char *Str)
{
int val;

if (! Str) return(ANSI_NONE);
val=MatchTokenFromList(Str, ANSIColorStrings, 0);
if (val==-1) val=ANSI_NONE;

return(val);
}


void TerminalGeometry(STREAM *S, int *wid, int *len)
{
    struct winsize w;

    ioctl(S->out_fd, TIOCGWINSZ, &w);

    *wid=w.ws_col;
    *len=w.ws_row;
}




char *UnicodeStr(char *RetStr, int Code)
{	
	char *Tempstr=NULL;

	if (Code > 0x7FF) Tempstr=FormatStr(Tempstr,"%c%c%c",128 + 64 + 32 + ((Code & 61440) >> 12), 128 + ((Code & 4032) >>6), 128 + (Code & 63));
	else Tempstr=FormatStr(Tempstr,"%c%c",128+64+((Code & 1984) >> 6), 128 + (Code & 63));
	RetStr=CatStr(RetStr,Tempstr);
	DestroyString(Tempstr);

	return(RetStr);
}



int TermStrLen(const char *Str)
{
const char *ptr;
int len=0;

for (ptr=Str; *ptr != '\0'; ptr++)
{
switch (*ptr)
{
  case '~':
    ptr++;
    ptr++;
  break;

  default:
    len++;
  break;
}
}

return(len);
}



char *TerminalCommandStr(char *RetStr, int Cmd, int Arg1, int Arg2)
{
int i;
char *Tempstr=NULL;

switch (Cmd)
{
case TERM_CLEAR_SCREEN:
RetStr=CatStr(RetStr, "\x1b[2J");
break;

case TERM_CLEAR_ENDLINE:
RetStr=CatStr(RetStr,"\x1b[K");
break;

case TERM_CLEAR_STARTLINE:
RetStr=CatStr(RetStr,"\x1b[1K");
break;

case TERM_CLEAR_LINE:
RetStr=CatStr(RetStr,"\x1b[K");
break;

case TERM_CURSOR_HOME:
RetStr=CatStr(RetStr,"\x1b[H");
break;

case TERM_CURSOR_MOVE:
Tempstr=FormatStr(Tempstr,"\x1b[%d;%dH",Arg2+1,Arg1+1);
RetStr=CatStr(RetStr,Tempstr);
break;

case TERM_CURSOR_SAVE:
RetStr=CatStr(RetStr,"\x1b[s");
break;

case TERM_CURSOR_UNSAVE:
RetStr=CatStr(RetStr,"\x1b[u");
break;

case TERM_CURSOR_HIDE:
RetStr=CatStr(RetStr,"\x1b[?25l");
break;

case TERM_CURSOR_SHOW:
RetStr=CatStr(RetStr,"\x1b[?25h");
break; 

case TERM_SCROLL:
if (Arg1 < 0) Tempstr=FormatStr(Tempstr,"\x1b[%dT",0-Arg1);
else Tempstr=FormatStr(Tempstr,"\x1b[%dS",Arg1);
RetStr=CatStr(RetStr,Tempstr);
break;

case TERM_SCROLL_REGION:
Tempstr=FormatStr(Tempstr,"\x1b[%d;%dr",Arg1, Arg2);
RetStr=CatStr(RetStr,Tempstr);
break;

case TERM_COLOR:
RetStr=CatStr(RetStr,ANSICode(Arg1, Arg2, 0));
break;

case TERM_TEXT:
RetStr=CatStr(RetStr,ANSICode(0, 0, Arg1));
break;

case TERM_NORM:
RetStr=CatStr(RetStr,ANSI_NORM);
break;

case TERM_UNICODE:
switch (Arg1)
{
	//non-breaking space
	case 0x00a0:
		RetStr=AddCharToStr(RetStr,' '); break; 
	break;

	//left and right double quote. We simplify down to just double quote
	case 0x201c:
	case 0x201d:
		RetStr=AddCharToStr(RetStr,'"'); break; 
	break;
	
	//en-dash and em-dash
	case 0x2013:
	case 0x2014: RetStr=AddCharToStr(RetStr,'-'); break; 

	//2019 is apostrophe in unicode. presumably it gives you as special, pretty apostrophe, but it causes hell with
	//straight ansi terminals, so we remap it here
	case 0x2019: RetStr=AddCharToStr(RetStr,'\''); break; 

	case 0x2026: RetStr=CatStr(RetStr,"..."); break; 

	default:
		RetStr=UnicodeStr(RetStr, Arg1);
	break;
}
break;
}

DestroyString(Tempstr);
return(RetStr);
}


char *TerminalFormatStr(char *RetStr, const char *Str)
{
const char *ptr, *end;
long len, val;

for (ptr=Str; *ptr !='\0'; ptr++)
{
	if (*ptr=='~')
	{
		ptr++;
		if (*ptr=='\0') break;
		switch (*ptr)
		{
			case '~': RetStr=AddCharToStr(RetStr, *ptr); break;
			case 'r': RetStr=TerminalCommandStr(RetStr, TERM_COLOR, ANSI_RED, 0); break;
			case 'R': RetStr=TerminalCommandStr(RetStr, TERM_COLOR, 0, ANSI_RED); break;
			case 'g': RetStr=TerminalCommandStr(RetStr, TERM_COLOR, ANSI_GREEN, 0); break;
			case 'G': RetStr=TerminalCommandStr(RetStr, TERM_COLOR, 0, ANSI_GREEN); break;
			case 'b': RetStr=TerminalCommandStr(RetStr, TERM_COLOR, ANSI_BLUE, 0); break;
			case 'B': RetStr=TerminalCommandStr(RetStr, TERM_COLOR, 0, ANSI_BLUE); break;
			case 'y': RetStr=TerminalCommandStr(RetStr, TERM_COLOR, ANSI_YELLOW, 0); break;
			case 'Y': RetStr=TerminalCommandStr(RetStr, TERM_COLOR, 0, ANSI_YELLOW); break;
			case 'm': RetStr=TerminalCommandStr(RetStr, TERM_COLOR, ANSI_MAGENTA, 0); break;
			case 'M': RetStr=TerminalCommandStr(RetStr, TERM_COLOR, 0, ANSI_MAGENTA); break;
			case 'c': RetStr=TerminalCommandStr(RetStr, TERM_COLOR, ANSI_CYAN, 0); break;
			case 'e': RetStr=TerminalCommandStr(RetStr, TERM_TEXT, ANSI_BOLD, 0); break;
			case 'i': RetStr=TerminalCommandStr(RetStr, TERM_TEXT, ANSI_INVERSE, 0); break;
			case 'u': RetStr=TerminalCommandStr(RetStr, TERM_TEXT, ANSI_UNDER, 0); break;
			case 'I': RetStr=TerminalCommandStr(RetStr, TERM_TEXT, ANSI_INVERSE, 0); break;
			case '<': RetStr=TerminalCommandStr(RetStr, TERM_CLEAR_STARTLINE, 0, 0); break;
			case '>': RetStr=TerminalCommandStr(RetStr, TERM_CLEAR_ENDLINE, 0, 0); break;
			case 'U':
				ptr++;
				if (! strntol(&ptr, 4, 16, &val)) break;
				ptr--; //because of ptr++ on next loop
				RetStr=TerminalCommandStr(RetStr, TERM_UNICODE, val, 0);
			break;
			case '0': RetStr=TerminalCommandStr(RetStr, TERM_NORM, 0, 0); break;
		}
	}
	else if (*ptr=='\\')
	{
		ptr++;
		if (*ptr=='u')
		{
			ptr++;
			if (! strntol(&ptr, 4, 16, &val)) break;
			ptr--; //because of ptr++ on next loop
			RetStr=TerminalCommandStr(RetStr, TERM_UNICODE, val, 0);
		}
		else RetStr=AddCharToStr(RetStr, *ptr);
	}
	else RetStr=AddCharToStr(RetStr, *ptr);
}

return(RetStr);
}



int TerminalCommand(int Cmd, int Arg1, int Arg2, STREAM *S)
{
char *Tempstr=NULL;

Tempstr=TerminalCommandStr(Tempstr, Cmd, Arg1, Arg2);
STREAMWriteString(Tempstr, S);

DestroyString(Tempstr);
}



void TerminalPutStr(const char *Str, STREAM *S)
{
char *Tempstr=NULL;

Tempstr=TerminalFormatStr(Tempstr, Str);
if (S) STREAMWriteLine(Tempstr, S);
else write(1,Tempstr,StrLen(Tempstr));

DestroyString(Tempstr);
}


char *TerminalReadText(char *RetStr, int Flags, STREAM *S)
{
int inchar, len=0;
char outchar;

if (isatty(S->in_fd)) TTYConfig(S->in_fd, 0, TTYFLAG_CRLF);
inchar=STREAMReadChar(S);
while (inchar != EOF)
{
	outchar=inchar & 0xFF;

	switch (inchar)
	{
		case '\n':
		case '\r':
		break;

		case 0x08: //this is backspace
		len--;
		break;

		default:
		if (Flags & TERM_SHOWSTARS) outchar='*';
		else if ((Flags & TERM_SHOWTEXTSTARS) && (len > 0)) 
		{
			//backspace over previous character and replace with star
			STREAMWriteString("\x08*",S);
		}
		RetStr=AddCharToBuffer(RetStr,len++, inchar & 0xFF);
		break;
	}


	STREAMWriteBytes(S, &outchar,1);
	STREAMFlush(S);
	if (inchar == '\n') break;
	if (inchar == '\r') break;

	inchar=STREAMReadChar(S);
}

if (isatty(S->in_fd)) TTYReset(S->in_fd);

return(RetStr);
}


char *TerminalReadPrompt(char *RetStr, const char *Prompt, int Flags, STREAM *S)
{
TerminalPutStr("\r~>",S);
TerminalPutStr(Prompt, S);
STREAMFlush(S);
return(TerminalReadText(RetStr, Flags, S));
}

int TerminalBarConfig(const char *Config, char **ForeColor, char **BackColor)
{
char *Name=NULL, *Value=NULL;
const char *ptr;
int Flags=TERMBAR_LOWER;

ptr=GetNameValuePair(Config, " ","=",&Name,&Value);
while (ptr)
{
switch (*Name)
{
	case 'f':
	case 'F':
	if (
			(strcasecmp(Name,"forecolor")==0) ||
			(strcasecmp(Name,"fcolor")==0)
		)
	{
		if (ForeColor) *ForeColor=CopyStr(*ForeColor, Value);
	}
	break;

	case 'b':
	case 'B':
	if (
			(strcasecmp(Name,"backcolor") ==0) ||
			(strcasecmp(Name,"bcolor") ==0)
		)
	{
		if (BackColor) *BackColor=CopyStr(*BackColor, Value);
	}
	else if (strcasecmp(Name, "bottom") ==0) Flags |= TERMBAR_LOWER;
	break;

	case 'c':
	case 'C':
	if (strcasecmp(Name, "center") ==0) Flags |= TERMBAR_CENTER;
	break;

	case 't':
	case 'T':
	if (strcasecmp(Name, "top") ==0) Flags |= TERMBAR_UPPER;
	break;
}

ptr=GetNameValuePair(ptr, " ","=",&Name,&Value);
}

DestroyString(Name);
DestroyString(Value);
return(Flags);
}


TERMBAR *TerminalBarCreate(STREAM *Term, const char *Config, const char *Text)
{
TERMBAR *TB;
char *Tempstr=NULL;
const char *ptr;

TB=(TERMBAR *) calloc(1,sizeof(TERMBAR));
TB->Term=Term;

TB->Flags=TerminalBarConfig(Config, &(TB->ForeColor), &(TB->BackColor));
STREAMSetItem(Term, Tempstr, TB);

if (StrValid(Text)) TerminalBarUpdate(TB, Text);
DestroyString(Tempstr);

return(TB);
}


void TerminalBarUpdate(TERMBAR *TB, const char *Text)
{
int rows, cols, x=0, y=0, TextLen;
char *Str=NULL;

TextLen=TermStrLen(Text);
TerminalGeometry(TB->Term, &cols, &rows);
TerminalCommand(TERM_CURSOR_SAVE, 0, 0, TB->Term);

if (TB->Flags & TERMBAR_UPPER) y=0;
else y=rows-1;

TerminalCommand(TERM_CURSOR_MOVE, 0, y, TB->Term);

if (TB->Flags & TERMBAR_CENTER) 
{
	x=(cols / 2) - (TextLen / 2);
	Str=CopyStr(Str, "~i");
	Str=PadStr(Str,' ', x);
	Str=CatStr(Str, Text);
	Str=PadStr(Str,' ',cols-TextLen-x);
}
else 
{
	Str=MCopyStr(Str,"~i",Text,NULL);
	Str=PadStr(Str, ' ', cols-TextLen);
}

TerminalPutStr(Str, TB->Term);
TerminalCommand(TERM_CURSOR_UNSAVE, 0, 0, TB->Term);

DestroyString(Str);
}


char *TerminalBarReadText(char *RetStr, TERMBAR *TB, const char *Prompt)
{
int inchar;

RetStr=CopyStr(RetStr,"");
TerminalBarUpdate(TB, Prompt);

if (isatty(TB->Term->in_fd)) TTYConfig(TB->Term->in_fd, 0, TTYFLAG_CRLF);
inchar=STREAMReadChar(TB->Term);
while (inchar != EOF)
{
switch (inchar)
{
case STREAM_TIMEOUT:
return(RetStr);
break;

case '\n': 
	RetStr=CopyStrLen(RetStr, TB->Text, TB->TextLen);
	TB->TextLen=0;
	if (isatty(TB->Term->in_fd)) TTYReset(TB->Term->in_fd);
	return(RetStr);
break;

case '\b':
	TB->Text[TB->TextLen]='\0';
	if (TB->TextLen > 0) TB->TextLen--;
break;

default:
	TB->Text=AddCharToBuffer(TB->Text,TB->TextLen,inchar);
	TB->TextLen++;
break;
}

TerminalBarUpdate(TB, TB->Text);
inchar=STREAMReadChar(TB->Term);
}

if (isatty(TB->Term->in_fd)) TTYReset(TB->Term->in_fd);
DestroyString(RetStr);
return(NULL);
}


int TerminalInit(STREAM *S)
{
int cols, rows, offset;
char *Tempstr=NULL;
TERMBAR *TB;

offset=2;
TerminalGeometry(S, &cols, &rows);
Tempstr=FormatStr(Tempstr,"%d",cols);
STREAMSetValue(S, "Terminal:cols", Tempstr);
Tempstr=FormatStr(Tempstr,"%d",rows);
STREAMSetValue(S, "Terminal:rows", Tempstr);

TerminalCommand(TERM_SCROLL_REGION, offset, rows-offset+1, S);
TerminalCommand(TERM_CURSOR_MOVE, 0, offset, S);

DestroyString(Tempstr);
}
