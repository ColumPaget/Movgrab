#include "ehow.h"

void EhowExtractShowPlayer(STREAM *S, char *Data, ListNode *Vars)
{
char *Tempstr=NULL, *PlayerData=NULL, *ItemType=NULL, *ptr;
int wide=0, high=0;

PlayerData=CopyStr(PlayerData,Data);
while (! strstr(PlayerData,"});"))
{
	Tempstr=STREAMReadLine(Tempstr,S);
	PlayerData=MCatStr(PlayerData,Tempstr,",",NULL);
}

ptr=GetToken(PlayerData,"width: ",&Tempstr,0);
if (ptr) ptr=GetToken(PlayerData,",",&Tempstr,0);
wide=atoi(Tempstr);

ptr=GetToken(PlayerData,"height: ",&Tempstr,0);
if (ptr) ptr=GetToken(PlayerData,",",&Tempstr,0);
high=atoi(Tempstr);

ptr=GetToken(PlayerData,"id: ",&Tempstr,0);
if (ptr) ptr=GetToken(PlayerData,",",&Tempstr,0);
ptr=strrchr(Tempstr,'.');
if (ptr) ptr++;
else ptr="flv";

if ((wide==0) || (high==0)) ItemType=MCopyStr(ItemType,"item:",ptr,NULL);
else ItemType=FormatStr(ItemType,"item:%s:%dx%d",ptr,wide,high);

SetVar(Vars,ItemType,Tempstr);


DestroyString(PlayerData);
DestroyString(ItemType);
DestroyString(Tempstr);
}

