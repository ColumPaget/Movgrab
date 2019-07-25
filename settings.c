#include "settings.h"
#include "servicetypes.h"
#include "display.h"
#include "download.h"
#include "outputfiles.h"
#include "players.h"

TSettings Settings;

void InitSettings()
{
memset(&Settings,0,sizeof(Settings));
Settings.PlayerLaunchPercent=25;
Settings.UserAgent=MCopyStr(Settings.UserAgent,"Movgrab ",Version,NULL);
Settings.FormatPreference=CopyStr(Settings.FormatPreference,"mp4,flv,webm,m4v,mov,mpg,mpeg,wmv,avi,3gp,mp3,m4a,wma,m3u8,m3u8-stream,reference");
}

void PrintVersion()
{
fprintf(stdout,"\nMovgrab: version %s\n",Version);
}


void PrintUsage()
{
int i;

PrintVersion();
fprintf(stdout,"Author: Colum Paget\n");
fprintf(stdout,"Email: colums.projects@gmail.com\n");
fprintf(stdout,"\n");
fprintf(stdout,"Usage: movgrab [-t <type>] -a [<username>:<password>] [-p <http|socks4|socks5|sshtunnel>://<username>:<password>@<host>:<port> ] [-r] [-b] [-x] [-q] [-st <stream timeout>] [-f <format list>] [-v] [-P] [-Pp] [-U <user-agent>] [-o <output file>] [+o <extra output file>] url\n");
fprintf(stdout,"	movgrab -test-sites\n");
fprintf(stdout,"\n'-v'		increases verbosity/debug level\n");
fprintf(stdout,"'-v -v'		prints out all webpages encountered\n");
fprintf(stdout,"'-v -v -v'	maximum debugging\n");
fprintf(stdout,"'-version'		Program version\n");
fprintf(stdout,"'--version'		Program version\n");
fprintf(stdout,"'-T'		Test mode, don't do final download\n");
fprintf(stdout,"'-P <program>'		Player program (e.g. \"mplayer\"). If <program> is 'auto' then select it from players set up in config file.\n");
fprintf(stdout,"'-Pp'		Percent download to launch player at (default 25%)\n");
fprintf(stdout,"'-U'		User-agent string\n");
fprintf(stdout,"'-a'		Authentication info in Username:Password format.\n");
fprintf(stdout,"'-q'		QUIET. No progress/informative output.\n");
fprintf(stdout,"'-b'		Background. Fork into background and nohup\n");
fprintf(stdout,"'-p'		address of http/https/httpc/socks4/socks5 proxy server in URL format.\n");
fprintf(stdout,"'-proxy'		address of http/https/httpc/socks4/socks5 proxy server in URL format.\n");
fprintf(stdout,"'-w'		Wait for addresses to be entered on stdin.\n");
fprintf(stdout,"'-st'		Connection inactivity timeout in seconds. Set high for sites that 'throttle'\n");
fprintf(stdout,"'-tw <int>'		Set max width of item title in progress display (Default 50 chars)\n");
fprintf(stdout,"'-np <path>'	File to write current title to. Useful as 'now playing' for internet radio streams\n");
fprintf(stdout,"'-t'		specifies website type.\n");
fprintf(stdout,"'-r'		Resume download (only works when writing a single file, not with +o).\n");
fprintf(stdout,"'-f'		specifies preferred video/audio formats for sites that offer more than one\n");
fprintf(stdout,"			example: flv:640x480,flv,mp4,mp3\n");
fprintf(stdout,"			Use -T to get a list of formats the site offers\n");
fprintf(stdout,"			Use * to mean 'any format' (the default)\n");
fprintf(stdout,"			example: flv:640x480,mp4:640x480,*\n");
fprintf(stdout,"'-o'		specifies output file ( '-' for stdout, 'none' to suppress writing)\n");
fprintf(stdout,"'+o'		add an output file to list of output files ( '-' for stdout)\n");
fprintf(stdout,"'-x'		try to avoid 'family filter' on some sites\n");
fprintf(stdout,"'-n'		For pages with multiple movies (not movie formats, but movies) specifes item selection for download. Argument has the form:\n");
fprintf(stdout,"			-n all		Download all\n");
fprintf(stdout,"			-n 2		Download 2nd item\n");
fprintf(stdout,"			-n 2-5		Download 2nd to 5th item\n");
fprintf(stdout,"			-n 2-		Download from 2nd item onwards\n");
fprintf(stdout,"			-n -8		Download from 1st to 8th item\n");
fprintf(stdout,"-test-sites		Test downloading from each supported website");
fprintf(stdout,"\nThe '-t' argument is optional, Movgrab will try to guess the download type from the provided url.\n\n");

fprintf(stdout,"The url should be that of the page that the movie would normally appear on. Movgrab examines the page for embed tags and other information that would normally cause the movie to play on that page.\n");

fprintf(stdout,"\nDownload types are:\n");
for (i=1; DownloadTypes[i] !=NULL; i++) fprintf(stdout,"%-20s %s\n",DownloadTypes[i],DownloadNames[i]);

fprintf(stdout,"\nThe -proxy argument has the form <protocol>:<username>:<password>@<host>:<port>. So, for example socks4:192.168.1.1:8080 or socks5:user1:secret@192.168.1.1:5050\n");

fprintf(stdout,"\nAvailable proxy types are: 'http', 'https' (which is 'http' style proxy with port-443 style ssl), 'httpc' (which uses the http 1.1 'CONNECT' method), 'socks4' and 'socks5'. 'socks4' and 'socks5' can be used with the 'ssh -D' command to pipe all communications through an ssh tunnel.\n");

fprintf(stdout,"\nIf a website is not in the list, try 'movgrab -t generic <url>'\n");
fprintf(stdout,"\nMovgrab can also be used to stream from internet radio and pipe it into a player. E.g.'\n		movgrab -o - -q -proxy ssltunnel://guest:s3cr3t@sshserver:1022 http://schizoid.in/schizoid-psy.pls | mpg123 -\n");

fprintf(stdout,"\nMovgrab honors the following environment variables\n");
fprintf(stdout,"MOVGRAB_FORMATS    list of file formats in preference order\n");;
fprintf(stdout,"PROXY              proxy server for network comms (including server type, so e.g. socks4:192.168.5.1:1090)\n");;
fprintf(stdout,"proxy              proxy server for network comms (including server type, so e.g. socks4:192.168.5.1:1090)\n");;
fprintf(stdout,"socks4_proxy       socks4 proxy server\n");;
fprintf(stdout,"socks5_proxy       socks5 proxy server\n");;
fprintf(stdout,"http_proxy         http proxy server\n");;

fprintf(stdout,"\nMovgrab uses a preferences file either set globally in /etc/movgrab.conf or per user in ~/.movgrab.conf. Entries in this file are:\n");
fprintf(stdout,"mediafmt <formats>    list of file formats in preference order\n");;
fprintf(stdout,"proxy <url>           url of network proxy\n");;
fprintf(stdout,"useragent <string>    useragent string for http communications\n");;
fprintf(stdout,"player <content-type> <path>    path to player program for a particular content type. Used in combination with the '-P auto' command-line switch.\n");;
fprintf(stdout,"\nFeel free to email me and tell me if you've used this software!\n");

fprintf(stdout,"\nThanks for bug reports go to: 'Ant', Mark Gamar, Rich Kcsa, 'Rampant Badger', 'nibbles', 'deeice', Omair Eshkenazi, Matthias B, Ashish Disawal, Timo Juhani Lindfors, Abhisek Sanyal and others.\n");
fprintf(stdout,"\nSpecial thanks to:\n");
fprintf(stdout,"	'legatvs' for clive (http://clive.sourceforge.net) another downloader into whose code I had to look to figure out how to get youtube and daily motion working again.\n");
fprintf(stdout,"	Robert Crowley (http://oldcoder.org/) For all sorts of bug reports and advice.\n");
}


int ParseType(char *Type)
{
int i, result=TYPE_NONE;

for (i=0; DownloadTypes[i] !=NULL; i++)
{
	if (strcasecmp(Type,DownloadTypes[i])==0) result=i;
}
return(result);
}


int ParsePreferencesFile(const char *Path)
{
STREAM *S;
char *Tempstr=NULL, *Token=NULL, *ptr;

S=STREAMOpen(Path, "r");
if (! S) return(FALSE);
Tempstr=STREAMReadLine(Tempstr, S);
while (Tempstr)
{
StripTrailingWhitespace(Tempstr);
StripLeadingWhitespace(Tempstr);
ptr=GetToken(Tempstr, "\\S", &Token, 0);

if (strcasecmp(Token, "mediafmt")==0) Settings.FormatPreference=CopyStr(Settings.FormatPreference,ptr);
else if (strcasecmp(Token, "sslciphers")==0) LibUsefulSetValue("SSL-Permitted-Ciphers", ptr);
else if (strcasecmp(Token, "ssllevel")==0) LibUsefulSetValue("SSL-Level", ptr);
else if (strcasecmp(Token, "proxy")==0) Settings.Proxy=CopyStr(Settings.Proxy, ptr);
else if (strcasecmp(Token, "useragent")==0) Settings.UserAgent=CopyStr(Settings.UserAgent, ptr);
else if (strcasecmp(Token, "player")==0) ParsePlayer(ptr);

Tempstr=STREAMReadLine(Tempstr, S);
}

STREAMClose(S);

Destroy(Tempstr);
Destroy(Token);

return(TRUE);
}


void ParseCommandLine(int argc, char *argv[], ListNode *DL_List, int *OverrideType)
{
int i,j, DebugLevel=0;
char *ptr;

ProgName=CopyStr(ProgName,argv[0]);
CmdLine=argv[0];


for (i=1; i < argc; i++)
{
	if (strcmp(argv[i],"-p")==0) Settings.Proxy=CopyStr(Settings.Proxy,argv[++i]);
	else if (strcmp(argv[i],"-proxy")==0) Settings.Proxy=CopyStr(Settings.Proxy,argv[++i]);
	else if (strcmp(argv[i],"-a")==0)
	{
			ptr=GetToken(argv[++i],":",&Username,0);
			ptr=GetToken(ptr,":",&Password,0);
	}
	else if (strcmp(argv[i],"-v")==0)
	{
		DebugLevel++;
	}
	else if (strcmp(argv[i],"-o")==0)
	{
		i++;
		if (strcmp(argv[i],"none")==0) Flags |= FLAG_NOOUT;
		else if (strcmp(argv[i],"-")==0) 
		{
			Flags |= FLAG_STDOUT;
			AddOutputFile(argv[i], TRUE);
		}
		else AddOutputFile(argv[i], TRUE);
	}
	else if (strcmp(argv[i],"+o")==0)
	{
		i++;
		AddOutputFile(argv[i], FALSE);
		if (strcmp(argv[i],"-")==0) Flags |= FLAG_STDOUT;
	}
	else if (strcmp(argv[i],"-n")==0)
	{
		Settings.ItemSelectArg=CopyStr(Settings.ItemSelectArg,argv[++i]);
	}
	else if (strcmp(argv[i],"-t")==0) *OverrideType=ParseType(argv[++i]);
	else if (strcmp(argv[i],"-f")==0) Settings.FormatPreference=CopyStr(Settings.FormatPreference,argv[++i]);
	else if (strcmp(argv[i],"-q")==0) Flags |= FLAG_QUIET;
	else if (strcmp(argv[i],"-b")==0) Flags |= FLAG_BACKGROUND;
	else if (strcmp(argv[i],"-r")==0) Flags |= FLAG_RESUME;
	else if (strcmp(argv[i],"-x")==0) Flags |= FLAG_PORN;
	else if (strcmp(argv[i],"-T")==0) Flags |= FLAG_TEST;
	else if (strcmp(argv[i],"-w")==0) Flags |= FLAG_STDIN;
	else if (strcmp(argv[i],"-dt")==0) DisplayTitleWidth=atoi(argv[++i]);
	else if (strcmp(argv[i],"-np")==0) Settings.NowPlayingFile=CopyStr(Settings.NowPlayingFile, argv[++i]);
	else if (strcmp(argv[i],"-st")==0) Settings.STREAMTimeout=atoi(argv[++i]);
	else if (strcmp(argv[i],"-P")==0) SetPlayer(argv[++i]);
	else if (strcmp(argv[i],"-Pp")==0) Settings.PlayerLaunchPercent=atoi(argv[++i]);
	else if (strcmp(argv[i],"-U")==0) Settings.UserAgent=CopyStr(Settings.UserAgent, argv[++i]);
	else if (strcmp(argv[i],"-?")==0) Flags |= FLAG_PRINT_USAGE;
	else if (strcmp(argv[i],"-h")==0) Flags |= FLAG_PRINT_USAGE;
	else if (strcmp(argv[i],"-help")==0) Flags |= FLAG_PRINT_USAGE;
	else if (strcmp(argv[i],"--help")==0) Flags |= FLAG_PRINT_USAGE;
	else if (strcmp(argv[i],"-version")==0) Flags |= FLAG_PRINT_VERSION;
	else if (strcmp(argv[i],"--version")==0) Flags |= FLAG_PRINT_VERSION;
	else if (strcmp(argv[i],"-test-sites")==0) 
	{
		Flags |= FLAG_TEST_SITES | FLAG_QUIET;
		for (j=1; TestLinks[j] !=NULL; j++)
		{
		if (StrLen(TestLinks[j])) ListAddNamedItem(DL_List,DownloadTypes[j],CopyStr(NULL,TestLinks[j]));
			
		}
		Settings.ItemSelectArg=CopyStr(Settings.ItemSelectArg,"0");
	}
	else
	{
		ListAddItem(DL_List, CopyStr(NULL,argv[i]));
	}	

}


if (Flags & FLAG_BACKGROUND) 
{
Flags |= FLAG_QUIET;
demonize();
}

if (Flags & FLAG_QUIET) DebugLevel=0;

if (DebugLevel==1) Flags |= FLAG_DEBUG1;
if (DebugLevel==2) Flags |= FLAG_DEBUG2;
if (DebugLevel > 2) Flags |= FLAG_DEBUG3;
}

void CheckSettings()
{
char *Token=NULL, *ptr;
int i;

if ((! isatty(1)) && (! (Flags & FLAG_STDOUT)))
{
fprintf(stderr,"\nWARNING: Stdout does not seem to be a terminal, so it could be a pipe to another program.	But you've not used '-o -' or '+o -' to redirect output into a pipe. Hence output will be written to a file. If you're piping into a player app, and there's no sound/video, then you need to add '-o -'\n\n");
}

Destroy(Token);
}




void ParseEnvironmentProxy()
{
const char *ptr;

ptr=getenv("proxy");
if (! StrValid(ptr)) ptr=getenv("PROXY");
if (StrValid(ptr)) 
{
	Settings.Proxy=CopyStr(Settings.Proxy, ptr);
	return;
}


ptr=getenv("socks4_proxy");
if (StrValid(ptr)) 
{
	Settings.Proxy=MCopyStr(Settings.Proxy, "socks4:", ptr, NULL);
	return;
}

ptr=getenv("socks5_proxy");
if (StrValid(ptr)) 
{
	Settings.Proxy=MCopyStr(Settings.Proxy, "socks5:", ptr, NULL);
	return;
}

ptr=getenv("http_proxy");
if (StrValid(ptr)) 
{
	if (
			(strncasecmp(ptr,"http:",5) !=0) &&
			(strncasecmp(ptr,"https:",6) !=0)
		) Settings.Proxy=MCopyStr(Settings.Proxy,"http:",ptr,NULL);
	else Settings.Proxy=CopyStr(Settings.Proxy,ptr);
	return;
}

ptr=getenv("ssh_tunnel");
if (StrValid(ptr)) 
{
	if (strncasecmp(ptr,"sshtunnel:",10)==0) Settings.Proxy=CopyStr(Settings.Proxy,ptr);
	else if (strncasecmp(ptr,"ssh:",4)==0) Settings.Proxy=MCopyStr(Settings.Proxy,"sshtunnel:",ptr+4,NULL);
	else Settings.Proxy=MCopyStr(Settings.Proxy,"sshtunnel:",ptr,NULL);
}

}

void ParseEnvironmentVariables()
{
const char *ptr;

ParseEnvironmentProxy();

ptr=getenv("SSL_CIPHERS");
if (StrValid(ptr)) LibUsefulSetValue("SSL-Permitted-Ciphers", ptr);

ptr=getenv("SSL_LEVEL");
if (StrValid(ptr)) LibUsefulSetValue("SSL-Level", ptr);

ptr=getenv("MOVGRAB_FORMATS");
if (StrValid(ptr)) Settings.FormatPreference=CopyStr(Settings.FormatPreference,ptr);
}

