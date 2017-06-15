#include "DataParser.h"


//Gets recursively called
const char *ParserParseItems(PARSER *P, const char *Doc, ListNode *Parent, int IndentLevel);

int ParserType(const char *Type)
{
const char *Types[]={"json","soap","yaml","config","ini",NULL};
return(MatchTokenFromList(Type,Types,0));
}

PARSER *ParserCreate(int Type)
{
PARSER *P=NULL;

if (Type > -1)
{
P=(PARSER *) calloc(1,sizeof(PARSER));
P->Items=ListCreate();
P->Type=Type;
}
return(P);
}


void ParserItemsDestroy(ListNode *Items)
{
ListNode *Curr;

Curr=ListGetNext(Items);
while (Curr)
{
if (Curr->ItemType==ITEM_ARRAY) ParserItemsDestroy((ListNode *) Curr->Item);
else if (Curr->ItemType==ITEM_ENTITY) ParserItemsDestroy((ListNode *) Curr->Item);
else DestroyString(Curr->Item);
Curr=ListGetNext(Curr);
}
ListDestroy(Items, NULL);
}

void ParserDestroy(void *p_PARSER)
{
PARSER *P;

P=(PARSER *) p_PARSER;
if (P->Type != PARSER_FORK) ParserItemsDestroy(P->Items);
DestroyString(P->Path);
DestroyString(P->Document);
free(P);
}

void ParserAddString(PARSER *P, const char *Str)
{

}


const char *ParserAddNewStructure(PARSER *P, const char *Data, ListNode *Parent, int Type, const char *Name, int IndentLevel)
{
ListNode *Item, *Node;
const char *ptr;

	Item=ListCreate();
//	Item->Tag=CopyStr(Item->Tag,Name);
	Node=ListAddNamedItem(Parent, Name, Item);
	Node->ItemType=Type;
	ptr=ParserParseItems(P, Data, Item, IndentLevel);
	return(ptr);
}


const char *ParserJSONItems(PARSER *P, const char *Doc, ListNode *Parent, int IndentLevel)
{
const char *ptr;
char *Token=NULL, *PrevToken=NULL, *Name=NULL;
ListNode *Node;

ptr=GetToken(Doc, ",|[|]|{|}|:",&Token,GETTOKEN_MULTI_SEP|GETTOKEN_INCLUDE_SEP|GETTOKEN_HONOR_QUOTES);
while (ptr)
{
	StripQuotes(Token);
	if (strcmp(Token, "[") ==0) 
	{
		ptr=ParserAddNewStructure(P, ptr, Parent, ITEM_ARRAY, Name, IndentLevel+1);
	}
	else if (strcmp(Token, "]") ==0)
	{
		if (ptr && (*ptr==',')) ptr++;
		break;
	}
	else if (strcmp(Token, "{") ==0) ptr=ParserAddNewStructure(P, ptr, Parent, ITEM_ENTITY, Name, IndentLevel+1);
	else if (strcmp(Token, "}") ==0) 
	{
		//we can have an item right before a '}' that doesn't terminate with a ',' becasue the '}' terminates it
		if (StrValid(Name) && StrValid(PrevToken))
		{
			Node=ListAddNamedItem(Parent, Name, CopyStr(NULL, PrevToken));
			Node->ItemType=ITEM_VALUE;
		}
		if (ptr && (*ptr==',')) ptr++;
		break;
	}
	else if (strcmp(Token, ":") ==0) Name=CopyStr(Name, PrevToken);
	else if (strcmp(Token, ",") ==0)
	{
	Node=ListAddNamedItem(Parent, Name, CopyStr(NULL, PrevToken));
	Node->ItemType=ITEM_VALUE;
	}

	PrevToken=CopyStr(PrevToken, Token);
	ptr=GetToken(ptr, ",|[|]|{|}|:",&Token,GETTOKEN_MULTI_SEP|GETTOKEN_INCLUDE_SEP|GETTOKEN_HONOR_QUOTES);
}

DestroyString(PrevToken);
DestroyString(Token);
DestroyString(Name);
return(ptr);
}


const char *ParserYAMLItems(PARSER *P, const char *Doc, ListNode *Parent, int IndentLevel)
{
const char *ptr, *tptr;
char *Token=NULL, *PrevToken=NULL, *Name=NULL;
int count=0, BreakOut=FALSE;
ListNode *Node;

ptr=GetToken(Doc, "\n|#[|]|{|}|:",&Token,GETTOKEN_MULTI_SEP|GETTOKEN_INCLUDE_SEP|GETTOKEN_HONOR_QUOTES);
while (ptr)
{
	switch(*Token)
	{
	case ':': 
		Name=CopyStr(Name, PrevToken);
		PrevToken=CopyStr(PrevToken,"");
	break;

	case '#':
		while ((*ptr != '\0') && (*ptr != '\n')) ptr++;
	break;

	case '\n':
	if (StrValid(PrevToken))
	{
	StripTrailingWhitespace(PrevToken);
	StripLeadingWhitespace(PrevToken);
	Node=ListAddNamedItem(Parent, Name, CopyStr(NULL, PrevToken));
	Node->ItemType=ITEM_VALUE;
	}

	count=0;
	for (tptr=ptr; *tptr==' '; tptr++) count++;
	if (count > IndentLevel) ptr=ParserAddNewStructure(P, tptr, Parent, ITEM_ENTITY, Name, count);
	else if (count < IndentLevel) BreakOut=TRUE;
	PrevToken=CopyStr(PrevToken,"");
	break;

	default:
	PrevToken=CopyStr(PrevToken, Token);
	break;
	}

	if (BreakOut) 
	{
		break;
	}

	ptr=GetToken(ptr, "\n|#[|]|{|}|:",&Token,GETTOKEN_MULTI_SEP|GETTOKEN_INCLUDE_SEP|GETTOKEN_HONOR_QUOTES);
}

DestroyString(PrevToken);
DestroyString(Token);
DestroyString(Name);

return(ptr);
}




const char *ParserConfigItems(PARSER *P, const char *Doc, ListNode *Parent, int IndentLevel)
{
const char *ptr;
char *Token=NULL, *PrevToken=NULL, *Name=NULL;
ListNode *Node;

ptr=Doc;
while (ptr)
{
	while (isspace(*ptr)) ptr++;
	ptr=GetToken(ptr, " |#|=|:|\n",&Name,GETTOKEN_MULTI_SEP|GETTOKEN_INCLUDE_SEP|GETTOKEN_HONOR_QUOTES);
	switch (*Name)
	{
		case '#': ptr=GetToken(ptr,"\n",&Token,0); break;
		case '\0': break;

		default: 
		while (isspace(*ptr)) ptr++;
		if ((*ptr=='=') || (*ptr==':')) ptr++;
		ptr=GetToken(ptr,"\n",&Token,0); 
		StripLeadingWhitespace(Token);
		StripTrailingWhitespace(Token);
		Node=ListAddNamedItem(Parent, Name, CopyStr(NULL, Token));
		Node->ItemType=ITEM_VALUE;
		break;
	}
//	else if (strcmp(Token, "{") ==0) ptr=ParserAddNewStructure(P, ptr, Parent, ITEM_ENTITY, Name);
//	else if (strcmp(Token, "}") ==0) break;
}

DestroyString(PrevToken);
DestroyString(Token);
DestroyString(Name);
return(ptr);
}



const char *ParserParseItems(PARSER *P, const char *Doc, ListNode *Parent, int IndentLevel)
{
switch (P->Type)
{
case PARSER_JSON: return(ParserJSONItems(P, Doc, Parent, IndentLevel)); break;
case PARSER_YAML: return(ParserYAMLItems(P, Doc, Parent, IndentLevel)); break;
case PARSER_CONFIG: return(ParserConfigItems(P, Doc, Parent, IndentLevel)); break;
}

}



void ParserParseDocument(PARSER *P, const char *Doc)
{
ListNode *Node;
const char *ptr;

if (! P) return;
if (! Doc) return;
if (! P->Items) P->Items=ListCreate();
ptr=Doc;
while (isspace(*ptr)) ptr++;
if (*ptr=='{') ptr++;
ParserParseItems(P, ptr, P->Items, 0);
ParserOpenItem(P,"/");
}



ListNode *ParserGetNext(PARSER *P) 
{
P->Curr=ListGetNext(P->Curr); 
return(P->Curr);
}

ListNode *ParserGetPrev(PARSER *P) 
{
P->Curr=ListGetPrev(P->Curr); 
return(P->Curr);
}


ListNode *ParserFindItem(PARSER *P, const char *Name)
{
ListNode *Node;
char *Token=NULL;
const char *ptr;


ptr=Name;
if (*ptr=='/') 
{
	Node=P->Items;
	ptr++;
}
else if (! P->Curr) Node=P->Items;
else if (P->Curr->ItemType != ITEM_VALUE)
{
	Node=(ListNode *) P->Curr->Item;
}

if (StrValid(ptr))
{
ptr=GetToken(ptr,"/",&Token,0);
while (ptr)
{
	Node=(ListNode *) ListFindNamedItem(Node,Token);
	if (! Node) break;
	ptr=GetToken(ptr,"/",&Token,0);
}
}
else Node=ListGetNext(P->Items);

DestroyString(Token);
return(Node);
}



ListNode *ParserOpenItem(PARSER *P, const char *Name)
{
ListNode *Node;

Node=ParserFindItem(P, Name);
if (Node) 
{
	P->Curr=(ListNode *) Node->Item;
	return((ListNode *) Node->Item);
}
else return(NULL);
}

PARSER *ParserFork(PARSER *P, const char *Name)
{
PARSER *New;
ListNode *Node;

Node=ParserFindItem(P, Name);
if (Node && (Node->ItemType != ITEM_VALUE))
{
	New=ParserCreate(PARSER_FORK);
	New->Items=Node;
	New->Curr=Node;
	return(New);
}

return(NULL);
}


const char *ParserGetValue(PARSER *P, const char *Name)
{
ListNode *Node;

if (P->Curr)
{
Node=P->Curr;
if (Node->ItemType==ITEM_ENTITY) Node=(ListNode *) Node->Item;
if (Node) Node=ListFindNamedItem(Node, Name);
if (Node) return((const char *) Node->Item);
}

return(NULL);
}

