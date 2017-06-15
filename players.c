#include "players.h"

ListNode *Players=NULL;
char *Player=NULL;
pid_t PlayerPid=0;

void ParsePlayer(const char *Config)
{
char *ContentType=NULL;
const char *ptr;

ptr=GetToken(Config,"\\S",&ContentType,GETTOKEN_QUOTES);
if (! Players) Players=ListCreate();
SetVar(Players,ContentType,ptr);

DestroyString(ContentType);
}



char *SelectPlayer(const char *ContentType)
{
ListNode *Curr;

Curr=ListGetNext(Players);
while (Curr)
{
if (fnmatch(Curr->Tag, ContentType, 0)==0) 
{
	printf("PLAYER: [%s] %s\n",ContentType,Curr->Item);
	Player=CopyStr(Player, (char *) Curr->Item);
	return((char *) Curr->Item);
}
Curr=ListGetNext(Curr);
}

return(NULL);
}

void SetPlayer(const char *Config)
{
if (strcmp(Config, "auto")==0) Flags |= FLAG_PLAYER_AUTO;
else Player=CopyStr(Player, Config);
}


void LaunchPlayer()
{
char *Tempstr=NULL;

if (PlayerPid > 0) return;
if (! StrValid(Player)) return;

Tempstr=MCopyStr(Tempstr,Player," ",OutputFilesGetFilePath(),NULL);
PlayerPid=Spawn(Tempstr,"");

DestroyString(Tempstr);
}


