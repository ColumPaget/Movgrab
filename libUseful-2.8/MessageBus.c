#include "MessageBus.h"


ListNode *MBusConnections=NULL;

STREAM *MBusHandleConnectRequest(const char *URL)
{
STREAM *S=NULL;

if (! URL) return(NULL);
switch (*URL)
{
case 't':
if (strncmp(URL,"tcp:",4)==0) S=STREAMOpen(URL,"");
break;

}

if (S)
{
	if (! MBusConnections) MBusConnections=ListCreate();
	ListAddNamedItem(MBusConnections, URL, S);
}

return(S);
}


typedef struct
{
int Type;
int ConID;
char *URL;
int DataLen;
char *Data;
void *UserData;
STREAM *Broker;
} TMBusMsg


ListNode *MBusFindConnection(int ConID)
{
ListNode *Curr;
TMBusMsg *Item;

Curr=ListGetNext(MBusConnections);
while (Curr)
{
Item=(TMBusMsg *) Curr->Item;
if (Item->ConID==ConID) return(Item);
Curr=ListGetNext(Curr);
}
return(NULL);
}


int MBusBrokerRecv(STREAM *S, TMBusMsg *Msg)
{
int Type, result;
uint32_t ConID;
STREAM *Con;
ListNode *Node;

Msg->Type=STREAMReadChar(S);
if (Type==STREAM_CLOSED) return(MBUS_FAIL);
STREAMReadBytes(S, &Msg->ConID, sizeof(uint32_t));
Node=MBusFindConnection(Msg->ConID);
if (Node) 
{
	Msg->URL=CopyStr(Msg->URL, Node->Tag);
	Msg->UserData=Node->Item;
}
else
{
	Msg->URL=CopyStr(Msg->URL, "");
	Msg->UserData=NULL;
}

switch(Type)
{
case MBUS_CONNECT_RESULT:
	result=STREAMReadChar(S);
	if (result < 0) Msg->Result=FALSE;
	else Msg->Result=TRUE;
break;

case MBUS_SEND:
break;

case MBUS_CLOSE:
break;
}


return(TRUE);
}

int MBusClientRecv(STREAM *S, TMBusMsg *Msg)
{
int Type, result;
TMBusMsg *ConDetails;
uint32_t ConID;
STREAM *Con;

Msg->Type=STREAMReadChar(S);
if (Type==STREAM_CLOSED) return(MBUS_FAIL);
STREAMReadBytes(S, &Msg->ConID, sizeof(uint32_t));
ConDetails=MBusFindConnection(Msg->ConID);

switch(Type)
{
case MBUS_CONNECT:
	URL=STREAMReadLine(URL, S);
	Con=MBusHandleConnectRequest(URL);
	STREAMWriteChar(S, MBUS_CONNECT_RESULT);
	STREAMWriteBytes(S, &ConID, sizeof(uint32_t));
	if (Con) STREAMWriteChar(S, TRUE);
	else STREAMWriteChar(S, FALSE);
	STREAMFlush(S);
break;

case MBUS_SEND:
	if (ConDetails) 
	{

	}
break;

case MBUS_CLOSE:
break;
}


return(TRUE);
}

STREAM *MBusFindBroker(const char *URL)
{
ListNode *Curr;
char *Token=NULL;
const char *ptr;

Curr=GetNextListItem(MBusConnections);
while (Curr)
{
	if (Curr->ItemType==MBUS_BROKER)
	{
		ptr=GetToken(Curr->Tag,",",&Token,0);
		while (ptr)
		{
		if (fnmatch(Token,Curr->Tag,0)==0)
		{
			DestroyString(Token);
			return((STREAM *) Curr->Item);
		}
		ptr=GetToken(ptr,",",&Token,0);
		}
	}
Curr=GetNextListItem(Curr);
}

DestroyString(Token);
return(NULL);
}



int MBusConnect(const char *URL, void *UserData)
{
STREAM *Broker;
static uint32_t ConCount=0;
ListNode *Node;

Broker=MBusFindBroker(URL);
if (Broker)
{
	STREAMWriteChar(Broker, MBUS_CONNECT);
	ConCount++;
	STREAMWriteBytes(Broker, &ConCount, sizeof(uint32_t));
	STREAMWriteString(URL, Broker);
	STREAMWriteChar(Broker, '\n');
	STREAMFlush(Broker);
	if (! MBusConnections) MBusConnections=ListCreate();
	Node=ListAddNamedItem(MBusConnections, URL, UserData);
	Node->Hits=ConCount;
	return(TRUE);
}

return(FALSE);
}



