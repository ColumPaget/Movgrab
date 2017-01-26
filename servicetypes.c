#include "servicetypes.h"
#include "containerfiles.h"
#include "selectformat.h"

/*
This file and it's header (servicetypes.h) holds all the functions and data
related to individual services/sites. When adding a site you need to add to
the arrays 'DownloadTypes', 'DownloadNames' and 'TestLinks' and to the 
enumerated type in servicetypes.h tht matches to 'DownloadTypes'.

Then site specific 
*/



//Site type names used at the command line etc
char *DownloadTypes[]={"none","generic","youtube","youtu.be","metacafe","dailymotion","break","ehow","vimeo","ted","reuters","liveleak","photobucket","washingtonpost","cbsnews","france24","euronews","metatube","guardian","redorbit","uctv.tv","royalsociety.tv","dotsub","astronomy.com","discovery","bloomberg","nationalgeographic","videobash","smh","funnyordie","ign","ebaumsworld","gamestar","imdb","charlierose","stanfordoc",NULL};

//Longer names used in display
char *DownloadNames[]={"none",
"Generic: Search in page for http://*.flv, http://*.mp3, http//*.mp4 etc, etc, etc",
"YouTube: http://www.youtube.com",
"youtu.be: http://www.youtu.be",
"Metacafe: http://www.metacafe.com",
"Daily Motion: http://www.dailymotion.com",
"www.break.com",
"www.ehow.com",
"www.vimeo.com",
"www.ted.com",
"Reuters: http://www.reuters.com/",
"Liveleak: http://www.liveleak.com",
"Photobucket: http://www.photobucket.com",
"mefeedia.com",
"Washington Post: www.washingtonpost.com",
"CBS News: www.cbsnews.com",
"France24: www.france24.com",
"Euronews: www.euronews.net",
"www.metatube.com",
"www.guardian.co.uk",
"www.redorbit.com",
"University of California Television: http://www.uctv.tv/",
"http://royalsociety.org/",
"dotsub.com",
"astronomy.com",
"dsc.discovery.com",
"www.bloomberg.com (not bloomberg.tv)",
"National Geographic (http://video.nationalgeographic.com)",
"videobash",
"International Business Times",
"Sidney Morning Herald",
"Funny or Die (http://www.funnyordie.com)",
"IGN",
"Ebaums World",
"www.gamestar.de",
"www.imdb.com",
"Charlie Rose",
"Stanford Open Classroom",
NULL};

//"http://vimeo.com/33204284",
//links used by the -test-sites feature to test if a download site still
//works with movgrab
char *TestLinks[]={"", "",
"http://www.youtube.com/watch?v=Vxp3seoRNgY",
"http://youtu.be/OdrEId7YI1k",
"http://www.metacafe.com/watch/6063075/how_to_use_chopsticks/",
"http://www.dailymotion.com/video/x5790e_hubblecast-16-galaxies-gone-wild_tech",
"http://www.break.com/video/break-compilations-2591623/cats-vs-the-world-iii-breaking-videos-3075295",
"http://www.ehow.com/video_6819748_creamy-thyme-scrambled-eggs-recipe.html",
"broken",
"http://www.ted.com/talks/janine_benyus_shares_nature_s_designs.html",
"http://www.reuters.com/video/2016/05/02/foam-swords-drawn-in-mass-play-fight-in?videoId=368328211",
"http://www.liveleak.com/view?i=e28_1462299205",
"http://gs147.photobucket.com/groups/r299/QM25Y4IJEP/?action=view&current=BlackSwan1.mp4",
"http://www.washingtonpost.com/video/politics/tom-prices-tense-senate-finance-hearing/2017/01/24/f0c35346-e282-11e6-a419-eefe8eff0835_video.html",
"http://www.cbsnews.com/video/watch/?id=7357739n",
"http://www.france24.com/en/20160430-down-earth-fast-fashion-pollution-environment-ethical-consumption",
"http://www.euronews.com/news/bulletin/",
"http://www.metatube.com/en/videos/cid2/Funny-Videos/53210/Rail-Jump-Fail/",
"http://www.guardian.co.uk/world/video/2011/may/13/fukushima-radiation-dairy-farmers-video",
"http://www.redorbit.com/video/using-f1-technology-to-transform-healthcare-012016/",
"http://www.uctv.tv/search-details.aspx?showID=20888",
"http://royalsociety.tv/rsPlayer.aspx?presentationid=474",
"http://dotsub.com/view/5d90ef11-d5e5-42fb-8263-a4c128fb64df",
"http://www.astronomy.com/News-Observing/Liz%20and%20Bills%20Cosmic%20Adventures/2011/02/Episode%202.aspx",
"http://dsc.discovery.com/videos/how-the-universe-works-birth-of-a-black-hole.html",
"http://www.bloomberg.com/video/72477250/",
"http://video.nationalgeographic.com/video/environment/environment-natural-disasters/earthquakes/earthquake-101/",
"http://www.videobash.com/video_show/wing-suit-amazing-footage-6086",
"http://www.smh.com.au/technology/sci-tech/newly-discovered-planets-include-superearth-20110913-1k7tl.html",
"http://www.funnyordie.com/videos/032785be3a/genie-on-hard-times-with-parker-posey?playlist=featured_videos",
"http://www.ign.com/videos/2013/06/05/the-last-of-us-review",
"http://www.ebaumsworld.com/videos/a-giant-python-opens-the-door/83367677/",
"http://www.gamestar.de/videos/trailer,3/hobbit-3-die-schlacht-der-fuenf-heere,76110.html",
"http://www.imdb.com/video/imdb/vi3832131865",
"https://charlierose.com/videos/27996",
"http://openclassroom.stanford.edu/MainFolder/VideoPage.php?course=PracticalUnix&video=wget&speed=100",
NULL};



//Guess service type from servername in URL
int IdentifyServiceType(const char *URL)
{
int Type=TYPE_NONE;
char *Proto=NULL, *Server=NULL, *Tempstr=NULL;

if (! URL) return(TYPE_NONE);

Type=GetContainerFileType(URL);
if (Type != TYPE_NONE) return(Type);

ParseURL(URL,&Proto,&Server,&Tempstr,NULL,NULL,NULL,NULL);
if (! StrValid(Server))
{
DestroyString(Proto);
DestroyString(Server);
DestroyString(Tempstr);
return(TYPE_NONE);
}

if (
	(strstr(Server,"youtube")) 
   ) Type=TYPE_YOUTUBE;
else if (
	(strcmp(Server,"youtu.be")==0) 
   ) Type=TYPE_YOUTUBE_SHORT;
else if (strcmp(Server,"www.metacafe.com")==0)
{
 Type=TYPE_METACAFE;
}
else if (strcmp(Server,"www.break.com")==0)
{
 Type=TYPE_BREAK_COM;
}
else if (strstr(Server,".ehow."))
{
 Type=TYPE_EHOW;
}
else if (strcmp(Server,"www.dailymotion.com")==0)
{
 Type=TYPE_DAILYMOTION;
}
else if (strcmp(Server,"www.ted.com")==0)
{
 Type=TYPE_TED;
}
else if (strstr(Server,"photobucket.com"))
{
 Type=TYPE_PHOTOBUCKET;
}
else if (strstr(Server,"liveleak"))
{
 Type=TYPE_LIVELEAK;
}
else if (strstr(Server,"smh.com.au"))
{
 Type=TYPE_SMH;
}
else if (strstr(Server,"vimeo.com"))
{
 Type=TYPE_VIMEO;
}
else if (strstr(Server,"reuters"))
{
 Type=TYPE_REUTERS;
}
else if (strstr(Server,"ucsd.tv"))
{
 Type=TYPE_UCTV;
}
else if (strstr(Server,"uctv.tv"))
{
 Type=TYPE_UCTV;
}
else if (strstr(Server,"washingtonpost"))
{
 Type=TYPE_WASHINGTONPOST;
}
else if (strstr(Server,"cbsnews"))
{
 Type=TYPE_CBSNEWS;
}
else if (strstr(Server,"france24"))
{
 Type=TYPE_FRANCE24;
}
else if (strstr(Server,"euronews"))
{
 Type=TYPE_EURONEWS;
}
else if (strstr(Server,"metatube"))
{
 Type=TYPE_METATUBE;
}
else if (strstr(Server,"guardian"))
{
 Type=TYPE_GUARDIAN;
}
else if (strstr(Server,"redorbit"))
{
 Type=TYPE_REDORBIT;
}
else if (strcmp(Server,"royalsociety.tv")==0)
{
 Type=TYPE_ROYALSOCIETY_STAGE2;
}
else if (strcmp(Server,"royalsociety.org")==0)
{
 Type=TYPE_ROYALSOCIETY;
}
else if (strcmp(Server,"dotsub.com")==0)
{
 Type=TYPE_DOTSUB;
}
else if (strstr(Server,"astronomy.com"))
{
 Type=TYPE_ASTRONOMYCOM;
}
else if (strstr(Server,"discovery.com") || strstr(Server,"sciencechannel.com"))
{
 Type=TYPE_DISCOVERY;
}
else if (strstr(Server,"nationalgeographic.com"))
{
 Type=TYPE_NATGEO;
}
else if (strstr(Server,"bloomberg.com"))
{
 Type=TYPE_BLOOMBERG;
}
else if (strstr(Server,"www.videobash.com"))
{
 Type=TYPE_VIDEOBASH;
}
else if (strstr(Server,"funnyordie.com"))
{
 Type=TYPE_FUNNYORDIE;
}
else if (strstr(Server,".ign."))
{
 Type=TYPE_IGN;
}
else if (strstr(Server,".imdb.com"))
{
 Type=TYPE_IMDB;
}
else if (strstr(Server,".ebaumsworld.com"))
{
 Type=TYPE_EBAUMSWORLD;
}
else if (strstr(Server,".gamestar.de"))
{
 Type=TYPE_GAMESTAR;
}
else if (strstr(Server,"charlierose.com"))
{
 Type=TYPE_CHARLIEROSE;
}
else if (strcmp(Server,"openclassroom.stanford.edu")==0)
{
 Type=TYPE_STANFORD_OPENCLASS;
}
else if (strstr(Server,".google."))
{
 Type=TYPE_GOOGLE_URL;
}


DestroyString(Server);
DestroyString(Proto);
DestroyString(Tempstr);

return(Type);
}




char *ExtractMetacafeMediaURL(char *RetStr, char *Data, char *Start, char *End)
{
char *Tempstr=NULL, *Token=NULL, *ptr;


ptr=strstr(Data,Start);
ptr+=StrLen(Start);
ptr=GetToken(ptr,End,&Token,0);
Tempstr=HTTPUnQuote(Tempstr,Token);
RetStr=MCopyStr(RetStr,Tempstr,"?__gda__=",NULL);
ptr=GetToken(Data,"gdaKey=",&Token,0);
ptr=GetToken(ptr,"&",&Token,0);
RetStr=CatStr(RetStr,Token);
	
DestroyString(Tempstr);
DestroyString(Token);


return(RetStr);
}




//This function is called before we even pull the first page from a site
//it is a good place to do any site-specific stuff like rewriting the
//site URL to a form that's better for movgrab
char *SiteSpecificPreprocessing(char *RetBuff, char *Path, char *Proto, char *Server, int Port, char *Doc, int *Type, char **Title, int *Flags)
{
char *Tempstr=NULL;
char *NextPath=NULL;
char *ptr, *Token=NULL;

NextPath=CopyStr(RetBuff,Path);

switch (*Type)
{
case TYPE_YOUTUBE_SHORT:
	//something like	https://youtu.be/OdrEId7YI1k
	ptr=Doc;
	while (*ptr=='/') ptr++;
	NextPath=MCopyStr(NextPath,Proto,"://www.youtube.com/get_video_info?&video_id=",ptr,"&el=detailpage&ps=default&eurl=&gl=US&hl=enB",NULL);
	*Type=TYPE_YOUTUBE;
break;

case TYPE_YOUTUBE:
	//hmm.. have we been given the http://www.youtube.com/v/ or https://www.youtube.com/embed/ format?

	if (strncmp(Doc,"/v/",3)==0) Token=CopyStr(Token,Doc+3);
	else if (strncmp(Doc,"/embed/",7)==0) Token=CopyStr(Token,Doc+7);
	else if (strncmp(Doc,"/watch?v=",9)==0) Token=CopyStr(Token,Doc+9);
	else 
	{
		*Type=TYPE_YOUTUBE_PLAYLIST;
		NextPath=MCopyStr(NextPath,Proto,"://",Server,"/",Doc,NULL);
	}

	if (*Type == TYPE_YOUTUBE) 
	{
	//strip any http arguments 
	ptr=strrchr(Token,'?');
	if (ptr) *ptr='\0';

	NextPath=MCopyStr(NextPath,Proto,"://www.youtube.com/get_video_info?&video_id=",Token,"&el=detailpage&ps=default&eurl=&gl=US&hl=enB",NULL);
	}

	//Do we have authentication info?
	//if (StrLen(Username) && StrLen(Password)) YoutubeLogin(Username,Password);

break;


case TYPE_METACAFE:
	ptr=GetToken(Doc,"watch/",&Token,0);
	ptr=GetToken(ptr,"/",&Token,0);
	if (strchr(Token,'-'))
	{
		//Movie is embedded from elsewhere
		if (strncmp(Token,"yt",2)==0) 
		{
			ptr=strrchr(Token,'-');
			if (ptr) 
			{
				ptr++;
	//			*Type=TYPE_NONE;
	//			Tempstr=MCopyStr(Tempstr,"http://www.youtube.com/watch?v=",ptr,NULL);
	//			GrabMovie(Tempstr);

				*Type=TYPE_YOUTUBE;
				NextPath=MCopyStr(NextPath,"http://www.youtube.com/watch?v=",ptr,NULL);
	
			}
		}
		else if (! (*Flags & FLAG_QUIET)) fprintf(stderr,"Movie is not genuinely stored on metacafe, it is embedded from elsewhere, but it's not youtube, so I don't know how to download it. Sorry.\n");
	}
	else 
	{
		STREAM *S;

		if (*Flags & FLAG_PORN)
		{
		//Initial 'turn off family filter'
		Tempstr=FormatStr(Tempstr,"%s://%s:%d/f/index.php?inputType=filter&controllerGroup=user&filters=0&submit=Continue+-+I%27m+over+18",Proto,Server,Port);
		S=HTTPMethod("POST",Tempstr,"","","","",0);
		STREAMClose(S);

		//But we have to do it twice, probably something to do with cookies
		NextPath=FormatStr(NextPath,"http://%s:%d/f/index.php?inputType=filter&controllerGroup=user&filters=0&Continue=Continue+-+I%27m+over+18&prevURL=%s",Server,Port,Path);
		}
		else NextPath=CopyStr(NextPath,Path);
	}
break;

case TYPE_DAILYMOTION:
	if (*Flags & FLAG_PORN)
	{
		Tempstr=HTTPQuote(Tempstr,Doc);
		NextPath=FormatStr(NextPath,"http://%s:%d/family_filter?urlback=/%s&enable=false",Server,Port,Tempstr);
	}
	else NextPath=CopyStr(NextPath,Path);
break;

case TYPE_VIMEO:
 	NextPath=MCopyStr(NextPath,"http://player.vimeo.com/video/",Doc,NULL);
break;

case TYPE_GOOGLE_URL:

	ptr=strchr(Path, '?');
	if (ptr)
	{
		ptr++;
 		ptr=GetToken(ptr,"&",&Token,0);
		while (ptr)
		{
		if (strncmp(Token, "url=", 4)==0) NextPath=HTTPUnQuote(NextPath,Token+4);
		if (strncmp(Token, "q=", 2)==0) NextPath=HTTPUnQuote(NextPath,Token+2);
 		ptr=GetToken(ptr,"&",&Token,0);
		}
		*Type=IdentifyServiceType(NextPath);
	}
break;

case TYPE_CHARLIEROSE:
	NextPath=MCopyStr(NextPath,"https://charlierose.com/video/player/",GetBasename(Path),NULL);
break;

default:
 NextPath=CopyStr(NextPath,Path);
break;

}

DestroyString(Tempstr);
DestroyString(Token);

return(NextPath);
}




//For websites with multiple videos on a page (not multiple formats of the
//same video, but actual different videos) decide which one to get
void HandleMultipleMedia(int Type,char *Server,int Flags,ListNode *Vars,int MediaCount)
{ 
char *Tempstr=NULL, *ptr;
int i, startpos, endpos;

startpos=0;
endpos=MediaCount;

		if (MediaCount==1) endpos=1;
		else if (StrLen(ItemSelectionArg)==0)
		{
			if (! (Flags & FLAG_QUIET))
			{
 			fprintf(stderr,"\nMultiple downloads exist on this page.\n");
			fprintf(stderr,"Please select by using the command-line argument -n <num>\n");
 			fprintf(stderr,"	e.g. -n all\n");
 			fprintf(stderr,"	     -n 0-4\n");
 			fprintf(stderr,"	     -n 3-\n\n");
			for (i=0; i < MediaCount; i++)
			{
			Tempstr=FormatStr(Tempstr,"ID:%d",i);
			ptr=GetVar(Vars,Tempstr);
			if (ptr) ptr=strrchr(ptr,'.');
			if (! ptr) ptr="?";

			Tempstr=FormatStr(Tempstr,"Title:%d",i);
			fprintf(stderr,"	% 4d: %4s  %s\n",i,ptr,GetVar(Vars,Tempstr));
			}
			fprintf(stderr,"\n");
			}
			endpos=startpos;
		}
		else if (strcmp(ItemSelectionArg,"all")==0)
		{
			//do nothing
		}
		else if (strchr(ItemSelectionArg,'-'))
		{
		ptr=GetToken(ItemSelectionArg,"-",&Tempstr,0);
		if (StrLen(Tempstr)) startpos=atoi(Tempstr);
		else startpos=0;
		if (StrLen(ptr)) endpos=atoi(ptr);
		else endpos=MediaCount;
		}
		else
		{
			startpos=atoi(ItemSelectionArg);
			endpos=startpos+1;
		}

		for (i=startpos; i < endpos; i++)
		{
		Tempstr=FormatStr(Tempstr,"ID:%d",i);
		ptr=GetVar(Vars,Tempstr);
		SetVar(Vars,"ID",ptr);
		GrabMovie(ptr, TYPE_YOUTUBE);
		}

DestroyString(Tempstr);
}





//Called after the first page has been downloaded from the site
//Decides what to do next (Download another page, download the actual 
//media item, give up, etc.

int GetNextURL(int Type, char *Server, int Flags, ListNode *Vars)
{
char *Tempstr=NULL, *Title=NULL, *Fmt=NULL, *ptr;
int RetVal=FALSE;
STREAM *Con;

Title=CopyStr(Title,GetVar(Vars,"Title"));
Fmt=CopyStr(Fmt,GetVar(Vars,"DownloadFormat"));

switch (Type)
{
case TYPE_M3U8_STREAM:
	Tempstr=CopyStr(Tempstr,GetVar(Vars,"ID"));
	Con=ConnectAndRetryUntilDownload(Tempstr, 0, 0);
	if (Con)
	{
	M3UStreamDownload(Con, Tempstr, Title);
	STREAMClose(Con);
	}
break;

case TYPE_REFERENCE:
case TYPE_GOOGLE_URL:
	Tempstr=CopyStr(Tempstr,GetVar(Vars,"ID"));
	RetVal=GrabMovie(Tempstr,TYPE_NONE);
break;

case TYPE_YOUTUBE:
		Tempstr=CopyStr(Tempstr,GetVar(Vars,"ID"));
  	RetVal=DownloadItem(Tempstr, Title, Fmt, Flags);
break;

case TYPE_YOUTUBE_PLAYLIST:
		Tempstr=CopyStr(Tempstr,GetVar(Vars,"ID"));
  	RetVal=DownloadPage(Tempstr,TYPE_YOUTUBE, Title, Flags);
break;

case TYPE_METACAFE:
#define METACAFE_OVER_18 "allowAdultContent=1&submit=Continue+-+I%27m+over+18"
 Tempstr=SubstituteVarsInString(Tempstr,"$(ID)&$(METACAFE_OVER_18)",Vars,0);
 	RetVal=DownloadItem(Tempstr, Title, Fmt, Flags);
break;



case TYPE_BREAK_COM:
		Tempstr=SubstituteVarsInString(Tempstr,"http://www.break.com/$(ID)",Vars,0);
 		RetVal=DownloadPage(Tempstr,TYPE_BREAK_STAGE2,Title,Flags);
break;

case TYPE_VIMEO:
 	RetVal=DownloadPage(GetVar(Vars,"ID"),TYPE_VIMEO_STAGE2,Title,Flags);
break;

case TYPE_VIMEO_STAGE2:
		Tempstr=SubstituteVarsInString(Tempstr,"$(BASE)/$(ID)",Vars,0);
  	RetVal=DownloadItem(Tempstr, Title, Fmt, Flags);
break;


case TYPE_ROYALSOCIETY:
		ptr=GetVar(Vars,"ID");
		if (ptr && (strncmp(ptr,"http:",5)==0)) RetVal=DownloadItem(ptr,Title, Fmt, Flags);
		else
		{
 		Tempstr=SubstituteVarsInString(Tempstr,"http://royalsociety.tv/rsPlayer.aspx?presentationid=$(ID)",Vars,0);
  	RetVal=DownloadPage(Tempstr,TYPE_ROYALSOCIETY_STAGE2, Title,Flags);
		}
break;

case TYPE_ROYALSOCIETY_STAGE2:
 		Tempstr=SubstituteVarsInString(Tempstr,"$(ID)",Vars,0);
  	//RetVal=DownloadM3U(Tempstr, Title, Flags);
break;


case TYPE_ASTRONOMYCOM:
 	Tempstr=SubstituteVarsInString(Tempstr,"$(ID)",Vars,0);
  RetVal=DownloadPage(Tempstr,TYPE_ASTRONOMYCOM_STAGE2, Title,Flags);
break;

case TYPE_BLOOMBERG:
 	Tempstr=SubstituteVarsInString(Tempstr,"http://videos.bloomberg.com/$(ID).flv",Vars,0);
 	RetVal=DownloadItem(Tempstr, Title, Fmt, Flags);
break;

case TYPE_IGN:
 	Tempstr=SubstituteVarsInString(Tempstr,"http://apis.ign.com/video/v3/videos/$(ID)",Vars,0);
  RetVal=DownloadPage(Tempstr,TYPE_IGN_STAGE2, Title,Flags);
break;

case TYPE_IMDB:
 	Tempstr=SubstituteVarsInString(Tempstr,"http://www.imdb.com/video/imdb/vi$(ID)/imdb/single",Vars,0);
  RetVal=DownloadPage(Tempstr,TYPE_IMDB_STAGE2, Title,Flags);
break;

case TYPE_GAMESTAR:
 	Tempstr=SubstituteVarsInString(Tempstr,"http://gamestar.de/_misc/videos/portal/getVideoUrl.cfm?premium=0&videoId=$(ID)",Vars,0);
 	RetVal=DownloadItem(Tempstr, Title, Fmt, Flags);
break;


case TYPE_STANFORD_OPENCLASS:
 	Tempstr=SubstituteVarsInString(Tempstr,"http://openclassroom.stanford.edu/MainFolder/courses/$(course)/videos/$(ID).xml",Vars,0);
 	Title=SubstituteVarsInString(Title,"$(course)-$(ID)",Vars,0);

  RetVal=DownloadPage(Tempstr,TYPE_STANFORD_STAGE2, Title,Flags);
break;


case TYPE_DOTSUB:
case TYPE_GENERIC:
case TYPE_TED:
case TYPE_NATGEO:
case TYPE_UCTV:
case TYPE_REUTERS:
case TYPE_LIVELEAK:
case TYPE_EURONEWS:
case TYPE_SMH:
case TYPE_REDORBIT:
case TYPE_PHOTOBUCKET:
case TYPE_WASHINGTONPOST:
case TYPE_CBSNEWS:
case TYPE_FRANCE24:
case TYPE_METATUBE:
case TYPE_GUARDIAN:
case TYPE_DISCOVERY:
case TYPE_REDORBIT_STAGE2:
case TYPE_ASTRONOMYCOM_STAGE2:
case TYPE_BREAK_STAGE2:
case TYPE_IGN_STAGE2:
case TYPE_IMDB_STAGE2:
case TYPE_STANFORD_STAGE2:
case TYPE_FUNNYORDIE:
case TYPE_EBAUMSWORLD:
case TYPE_DAILYMOTION:
case TYPE_VIDEOBASH:
case TYPE_EHOW:
case TYPE_CHARLIEROSE:
case TYPE_CONTAINERFILE_PLS:
case TYPE_CONTAINERFILE_ASX:
case TYPE_CONTAINERFILE_M3U8:
  Tempstr=CopyStr(Tempstr, GetVar(Vars,"ID"));
	if ((strncmp(Tempstr,"http:",5)!=0) && (strncmp(Tempstr,"https:",6)!=0)) Tempstr=MCopyStr(Tempstr,"http:",GetVar(Vars,"ID"),NULL);
 	RetVal=DownloadItem(Tempstr, Title, Fmt, Flags);
break;
}


DestroyString(Tempstr);
DestroyString(Title);
DestroyString(Fmt);

return(RetVal);
}


void BlipTVExtractFromLine(char *Line, ListNode *Vars)
{
char *ptr, *Type=NULL, *Width=NULL, *Height=NULL, *Tempstr=NULL;

 GenericExtractFromLine(Line, "width","width=\"","\"",Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
 GenericExtractFromLine(Line, "height","height=\"","\"",Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
 GenericExtractFromLine(Line, "url","url=\"","\"",Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);

	ptr=GetVar(Vars,"url");
	if (StrLen(ptr))
	{
		ptr=strrchr(ptr,'.');
		if (ptr) Type=CopyStr(Type,ptr+1);
	}

	ptr=GetVar(Vars,"width");
	if (StrLen(ptr))
	{
		Width=CopyStr(Width,ptr);
		Height=CopyStr(Height,GetVar(Vars,"height"));
		Tempstr=MCopyStr(Tempstr,"item:",Type,":",Width,"x",Height,NULL);
		SetVar(Vars,Tempstr,GetVar(Vars,"url"));
	}

DestroyString(Type);
DestroyString(Width);
DestroyString(Height);
DestroyString(Tempstr);
}



void ExtractDailyMotion(const char *Line, const char *Start, const char *End, ListNode *Vars)
{
const char *ptr, *tptr, *eptr;;
char *Item=NULL, *Name=NULL, *Res=NULL;

    ptr=Line;
		while (ptr)
		{
			ptr=GenericExtractFromLine(ptr, "item", Start, End, Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
			Item=CopyStr(Item,GetVar(Vars,"item"));
			tptr=strstr(Item, "H264-");
			if (tptr)
			{
				tptr+=5;
				GetToken(tptr,"/",&Res,0);
				Name=MCopyStr(Name,"item:mp4:",Res,NULL);
				SetVar(Vars, Name, Item);
			}
		}

DestroyString(Item);
DestroyString(Name);
DestroyString(Res);
}





/*******************************************************************************************************
// This is the main function that 'screen scrapes' a webpage looking for 
// information that it can use to get a video
*******************************************************************************************************/

int ExtractItemInfo(STREAM *S, int Type, char *URL, char *Title, int Flags)
{
char *Tempstr=NULL, *Token=NULL, *VarName=NULL, *Server=NULL;
ListNode *Vars=NULL;
char *ptr, *ptr2;
int MediaCount=0, i, Port;
int RetVal=FALSE, State=0;

ParseURL(URL,NULL,&Server,&Token,NULL,NULL,NULL,NULL);
Port=atoi(Token);

Vars=ListCreate();
SetVar(Vars,"Server",Server);


Tempstr=FormatStr(Tempstr,"%d",Port);
SetVar(Vars,"Port",Tempstr);

if (Flags & (FLAG_DEBUG2 | FLAG_DEBUG3)) fprintf(stderr,"\n------- DOWNLOADING DOCUMENT ------\n");
Tempstr=STREAMReadLine(Tempstr, S);

while (Tempstr)
{
	StripTrailingWhitespace(Tempstr);
	StripLeadingWhitespace(Tempstr);
	
	if (Flags & (FLAG_DEBUG2 | FLAG_DEBUG3)) fprintf(stderr,"%s\n",Tempstr);


switch (Type)
{

case TYPE_CONTAINERFILE_PLS:
	ptr=GetToken(Tempstr,"=",&Token,0);
	if (strncmp(Token,"File",4)==0)
	{
		GenericExtractFromLine(Tempstr, "item:mp3","=", "", Vars, EXTRACT_DESLASHQUOTE|EXTRACT_GUESSTYPE);
	}
break;

case TYPE_CONTAINERFILE_ASX:
	#define ASX_ITEM_START "<ref href=\""


		if (strstr(Tempstr,ASX_ITEM_START)) 
		{
			GenericExtractFromLine(Tempstr, "item:mp3", ASX_ITEM_START, "\"", Vars, EXTRACT_DESLASHQUOTE|EXTRACT_GUESSTYPE);
		}
break;


case TYPE_CONTAINERFILE_M3U8:
if (strncmp(Tempstr,"#EXT-X-MEDIA-SEQUENCE",21)==0)
{
	//uh oh, this is an apple iphone download rather than a manifest of streams. Call downloader function
	M3UStreamDownload(S, URL, Title);
}
else if (strncmp(Tempstr,"#EXT-X-STREAM-INF:",18)==0)
{
/* example of apple iphone stream MANIFEST
#EXT-X-STREAM-INF:PROGRAM-ID=1, BANDWIDTH=898000, RESOLUTION=640x360, CODECS="avc1.42001e,mp4a.40.2" 
http://ipad-streaming.cbsnews.com/media/mpx/2016/04/17/667983939550/0417_60Min_Alfonsi_HackingYourPhoneKolbe_508208_800/0417_60Min_Alfonsi_HackingYourPhoneKolbe_508208_800.m3u8
*/


  M3UStreamVarName(Tempstr+18, &VarName);

  Tempstr=STREAMReadLine(Tempstr,S);
  StripTrailingWhitespace(Tempstr);
	if (strncasecmp(Tempstr,"http:",5)==0) SetVar(Vars, VarName, Tempstr);
	else if (strncasecmp(Tempstr,"https:",6)==0) SetVar(Vars, VarName, Tempstr);
	else 
	{
		ptr=strrchr(URL,'/');
		if (ptr)
		{
			Token=CopyStrLen(Token,URL,ptr-URL);
			Token=MCatStr(Token,"/",Tempstr,NULL);
  		SetVar(Vars, VarName, Token);
		}
	}
}
else if (*Tempstr !=0) VarsAddDownloadItem("item:mp3", Tempstr, Vars, EXTRACT_GUESSTYPE);
break;


case TYPE_YOUTUBE:
//#define YOUTUBE_PTR "new SWFObject(\"/player2.swf?"

//#define YOUTUBE_PTR "var swfArgs = {"
#define YOUTUBE_DIV "url_encoded_fmt_stream_map="
#define YOUTUBE_TITLE_START "&title="
#define YOUTUBE_END "&"

	if (strstr(Tempstr,YOUTUBE_TITLE_START))
	{
		GenericExtractFromLine(Tempstr, "Title",YOUTUBE_TITLE_START, YOUTUBE_END, Vars, EXTRACT_DEQUOTE);
	}

	if (strstr(Tempstr,YOUTUBE_DIV))
	{
		if (StrLen(GetVar(Vars,"item:flv"))==0) 
		{
			GenericExtractFromLine(Tempstr, "yt:url_fmt",YOUTUBE_DIV, YOUTUBE_END, Vars,EXTRACT_DEQUOTE);
			Token=CopyStr(Token,GetVar(Vars,"yt:url_fmt"));
			DecodeYouTubeFormats(Token,Vars);
		}
	}

break;


case TYPE_YOUTUBE_PLAYLIST:
#define YOUTUBE_PLAYLIST_ITEM "/watch?v="
#define YOUTUBE_PLAYLIST_ITEM_END "\""

if (strstr(Tempstr,YOUTUBE_PLAYLIST_ITEM)) 
{
	GenericExtractFromLine(Tempstr, "tmp",YOUTUBE_PLAYLIST_ITEM,YOUTUBE_PLAYLIST_ITEM_END,Vars,EXTRACT_DEHTMLQUOTE | EXTRACT_NOSPACES);
	Tempstr=FormatStr(Tempstr,"http://%s:%d/watch?v=%s",Server,Port,GetVar(Vars,"tmp"));
	VarName=FormatStr(VarName,"ID:%d",MediaCount);
	SetVar(Vars,VarName,Tempstr);
	MediaCount++;
}
break;


case TYPE_METACAFE:
#define METACAFE_ITEM "&mediaData="
#define METACAFE_MEDIA_URL ",\"mediaURL\":\""

GenericTitleExtract(Tempstr, Vars);

if (strstr(Tempstr,METACAFE_ITEM))
{
	GenericExtractFromLine(Tempstr, "metacafe:mediaData",METACAFE_ITEM,"&", Vars, EXTRACT_DEQUOTE);
	ptr=GetVar(Vars,"metacafe:mediaData");
	GenericExtractFromLine(ptr, "item:mp4",METACAFE_MEDIA_URL,"\"", Vars, EXTRACT_DESLASHQUOTE|EXTRACT_GUESSTYPE);
}
break;



case TYPE_BREAK_COM:
#define BREAK_ITEM_START "name=\"Break.com Video Player\" src=\""
#define BREAK_END "\""

	GenericTitleExtract(Tempstr, Vars);
	if (strstr(Tempstr,BREAK_ITEM_START)) GenericExtractFromLine(Tempstr, "ID",BREAK_ITEM_START,BREAK_END,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
break;


case TYPE_BREAK_STAGE2:
#define BREAK_STAGE2_REF "<param name=\"movie\" value=\""
#define BREAK_STAGE2_URI "\"uri\": \""
#define BREAK_STAGE2_END "\""
#define BREAK_STAGE2_HEIGHT "\"height\": "
#define BREAK_STAGE2_WIDTH "\"width\": "

	if (strstr(Tempstr,"<param name=")) 
	{
		Token=UnQuoteStr(Token,Tempstr);
		GenericExtractFromLine(Token, "item:reference",BREAK_STAGE2_REF,BREAK_STAGE2_END,Vars, EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
	}

	if (strstr(Tempstr,BREAK_STAGE2_URI)) 
	{
		//set previous item
		if (State > 0)
		{
		VarName=FormatStr(VarName,"width:%d",State);
		Token=MCopyStr(Token, "item:mp4:",GetVar(Vars,VarName),"x",NULL);
		VarName=FormatStr(VarName,"height:%d",State);
		Token=CatStr(Token, GetVar(Vars,VarName));
		VarName=FormatStr(VarName,"ID:%d",State);
		SetVar(Vars,Token,GetVar(Vars,VarName));
		}

		VarName=FormatStr(VarName,"ID:%d",++State);
		GenericExtractFromLine(Tempstr, VarName,BREAK_STAGE2_URI,BREAK_STAGE2_END,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
	}

	if (strstr(Tempstr,BREAK_STAGE2_WIDTH)) 
	{
		VarName=FormatStr(VarName,"width:%d",State);
		GenericExtractFromLine(Tempstr, VarName,BREAK_STAGE2_WIDTH,",",Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
	}

	if (strstr(Tempstr,BREAK_STAGE2_HEIGHT)) 
	{
		VarName=FormatStr(VarName,"height:%d",State);
		GenericExtractFromLine(Tempstr, VarName,BREAK_STAGE2_HEIGHT,",",Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
	}
break;

case TYPE_EHOW:
#define EHOW_LINE "property=\"og:video\""
#define EHOW_ITEM "source="
#define EHOW_ITEM_END "&"
#define EHOW_TITLE "<h1 class=\"Heading1a\">"
#define EHOW_TITLE_END "</h1>"

	if (strstr(Tempstr,EHOW_LINE))
	{
		GenericExtractFromLine(Tempstr, "item:flv",EHOW_ITEM,EHOW_ITEM_END,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
	}

	ptr=strstr(Tempstr,EHOW_TITLE);
	if (ptr)
	{
		GenericExtractFromLine(Tempstr, "Title",EHOW_TITLE,EHOW_TITLE_END,Vars,EXTRACT_DEQUOTE);
	}
break;



case TYPE_VIMEO:
//"smil":{"url":"http:\/\/player.vimeo.com\/config\/46727983.smil"
#define VIMEO1_ITEM "smil\":{\"url\":\""
#define VIMEO1_ITEM_END "\""

	ptr=strstr(Tempstr,VIMEO1_ITEM);
	if (ptr)
	{
		GenericExtractFromLine(Tempstr, "ID",VIMEO1_ITEM,VIMEO1_ITEM_END,Vars,EXTRACT_DESLASHQUOTE | EXTRACT_NOSPACES);
	}


break;


case TYPE_VIMEO_STAGE2:
#define VIMEO1_BASE "<meta name=\"httpBase\" content=\""
#define VIMEO1_BASE_END "\""
#define VIMEO1_ITEM "<video src=\""
#define VIMEO1_ITEM_END "\""


ptr=strstr(Tempstr,VIMEO1_BASE);
if (ptr)
{
	GenericExtractFromLine(Tempstr, "BASE",VIMEO1_BASE,VIMEO1_BASE_END,Vars,EXTRACT_NOSPACES);
}

ptr=strstr(Tempstr,VIMEO1_ITEM);
if (ptr)
{
	GenericExtractFromLine(Tempstr, "ID",VIMEO1_ITEM,VIMEO1_ITEM_END,Vars,EXTRACT_NOSPACES);
}

break;

case TYPE_VIMEO_STAGE3:
#define VIMEO3_ITEM "smil:{\"url\":\""
#define VIMEO3_ITEM_END "\""

	ptr=strstr(Tempstr,VIMEO3_ITEM);
	if (ptr)
	{
		GenericExtractFromLine(Tempstr, "ID",VIMEO3_ITEM,VIMEO3_ITEM_END,Vars,EXTRACT_NOSPACES);
	}

/*
	ptr=strstr(Tempstr,VIMEO2_ITEM);
	if (ptr)
	{
		GenericExtractFromLine(Tempstr, "ID",VIMEO2_ITEM,VIMEO2_ITEM_END,Vars,EXTRACT_NOSPACES);
	}
*/
break;



case TYPE_DAILYMOTION:
#define DAILYMOTION_ITEM "/mp4\",\"url\":\""
#define DAILYMOTION_ITEM_END "\"}"
#define DAILYMOTION_TITLE_START "<meta property=\"og:title\" content=\""
#define DAILYMOTION_TITLE_END "\""


  if (strstr(Tempstr,DAILYMOTION_TITLE_START))
  {
    GenericExtractFromLine(Tempstr, "Title",DAILYMOTION_TITLE_START,DAILYMOTION_TITLE_END,Vars, EXTRACT_DEQUOTE | EXTRACT_DEHTMLQUOTE);
  }


  if (strstr(Tempstr,DAILYMOTION_ITEM))
  {
		Token=UnQuoteStr(Token,Tempstr);
		ExtractDailyMotion(Token, DAILYMOTION_ITEM, DAILYMOTION_ITEM_END, Vars);
  }
break;


case TYPE_TED:
#define TED_ITEM_START "\"file\":\""
#define TED_ITEM_END "\""

Title=CopyStr(Title,GetBasename(URL));
if (strstr(Tempstr,TED_ITEM_START))
{
	ptr=Tempstr;
	while (ptr)
	{
	ptr=GenericExtractFromLine(ptr, "file",TED_ITEM_START,TED_ITEM_END,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
	ptr2=GetVar(Vars,"file");
	if (strncmp(ptr2,"http",4)==0) SetVar(Vars,"item:mp4",ptr2);
	}
}
break;




#define REUTERS_FLV_ITEM_START "'flv':"
#define REUTERS_MP4_ITEM_START "'mpeg':"
#define REUTERS_TITLE "'headline':"

case TYPE_REUTERS:
	ptr=strstr(Tempstr,REUTERS_FLV_ITEM_START);
	if (ptr)
	{
		GenericExtractFromLine(Tempstr, "item:flv",REUTERS_FLV_ITEM_START,",",Vars,EXTRACT_WITHIN_QUOTES | EXTRACT_NOSPACES);
	}

	ptr=strstr(Tempstr,REUTERS_MP4_ITEM_START);
	if (ptr)
	{
		GenericExtractFromLine(Tempstr, "item:mp4",REUTERS_MP4_ITEM_START,",",Vars,EXTRACT_WITHIN_QUOTES | EXTRACT_NOSPACES);
	}


	ptr=strstr(Tempstr,REUTERS_TITLE);
	if (ptr)
	{
		GenericExtractFromLine(Tempstr, "Title",REUTERS_TITLE,",",Vars,EXTRACT_WITHIN_QUOTES | EXTRACT_NOSPACES);
	}
break;


#define PHOTOBUCKET_START "\"fullsizeUrl\":\""
#define PHOTOBUCKET_END "\""

case TYPE_PHOTOBUCKET:
	ptr=strstr(Tempstr,PHOTOBUCKET_START);
	if (ptr)
	{
		GenericExtractFromLine(Tempstr, "item:mp4",PHOTOBUCKET_START,PHOTOBUCKET_END,Vars, EXTRACT_DESLASHQUOTE | EXTRACT_GUESSTYPE);
	}
break;




#define SMH_ITEM_START "file\": \""
#define SMH_ITEM_END "\""
#define SMH_TRIGGER "\"playlist\": ["

case TYPE_SMH:

GenericTitleExtract(Tempstr, Vars);
if (strstr(Tempstr,SMH_TRIGGER)) State++;

if (State==1)
{
ptr=strstr(Tempstr,SMH_ITEM_START);
if (ptr)
{
 GenericExtractFromLine(Tempstr, "tmp",SMH_ITEM_START,SMH_ITEM_END,Vars, EXTRACT_GUESSTYPE);
 ptr=GetVar(Vars,"tmp");
 if (strstr(ptr,"_high.mp4")) SetVar(Vars,"item:mp4:high",ptr);
 if (strstr(ptr,"_mid.mp4")) SetVar(Vars,"item:mp4:mid",ptr);
 if (strstr(ptr,"_low.mp4")) SetVar(Vars,"item:mp4:low",ptr);
}
}
break;



case TYPE_WASHINGTONPOST:
#define WASHINGTONPOST_ITEM_START "player.swf?file="
#define WASHINGTONPOST_ITEM_END "&"

GenericTitleExtract(Tempstr, Vars);
if (strstr(Tempstr,WASHINGTONPOST_ITEM_START))
{
		GenericExtractFromLine(Tempstr, "item:mp4",WASHINGTONPOST_ITEM_START,WASHINGTONPOST_ITEM_END,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES | EXTRACT_HTTP_ONLY);
}
break;




case TYPE_CBSNEWS:
#define CBS_ITEM_START "\"contentUrl\":\""
#define CBS_ITEM_END "\""

GenericTitleExtract(Tempstr, Vars);
if (strstr(Tempstr,CBS_ITEM_START) )
{
		ptr=Tempstr;
		while (ptr) ptr=GenericExtractFromLine(ptr, "item:flv",CBS_ITEM_START,CBS_ITEM_END,Vars,EXTRACT_GUESSTYPE|EXTRACT_DESLASHQUOTE);
}
break;


case TYPE_FRANCE24:
#define FRANCE24_ITEM_LINE "window.BSPlayer.items"
#define FRANCE24_ITEM_START "\"is_default\":0,\"source\":\""
#define FRANCE24_ITEM_END "\""
#define FRANCE24_ITEM2_START "file="
#define FRANCE24_ITEM2_END "&"

GenericTitleExtract(Tempstr, Vars);
if (strstr(Tempstr,FRANCE24_ITEM_LINE) )
{
		ptr=Tempstr;
		while (ptr) ptr=GenericExtractFromLine(ptr, "item:flv",FRANCE24_ITEM_START,FRANCE24_ITEM_END,Vars,EXTRACT_GUESSTYPE|EXTRACT_DESLASHQUOTE);
		
}
else if (strstr(Tempstr,FRANCE24_ITEM2_START) )
{
		GenericExtractFromLine(Tempstr, "item:flv",FRANCE24_ITEM2_START,FRANCE24_ITEM2_END,Vars,EXTRACT_GUESSTYPE);
}

break;




case TYPE_METATUBE:
#define METATUBE_ITEM_START "\"sources\":[\""
#define METATUBE_ITEM_END "\""
#define METATUBE_ITEM2_START "<video src=\""
#define METATUBE_ITEM2_END "\""

GenericTitleExtract(Tempstr, Vars);
if (strstr(Tempstr,METATUBE_ITEM_START) )
{
		GenericExtractFromLine(Tempstr, "item:flv",METATUBE_ITEM_START,METATUBE_ITEM_END,Vars,EXTRACT_GUESSTYPE | EXTRACT_DESLASHQUOTE);
}
break;




case TYPE_ROYALSOCIETY:
#define ROYALSOCIETY_ITEM_START "javascript:launchTV("
#define ROYALSOCIETY_ITEM_END ")"

		if (strstr(Tempstr,ROYALSOCIETY_ITEM_START)) 
		{
			GenericExtractFromLine(Tempstr, "ID",ROYALSOCIETY_ITEM_START,ROYALSOCIETY_ITEM_END,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
		}

#define ROYALSOCIETY_ITEM2_START "a id=\"RecordedURL-video\" href=\""
#define ROYALSOCIETY_ITEM2_END "\""

		if (strstr(Tempstr,ROYALSOCIETY_ITEM2_START)) 
		{
			GenericExtractFromLine(Tempstr, "item:mp4",ROYALSOCIETY_ITEM2_START,ROYALSOCIETY_ITEM2_END,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
		}

#define ROYALSOCIETY_TITLE_START	"<span id=\"ctl00_MainContentPlaceHolder_RS_EventTile1_EventTitle\">"
#define ROYALSOCIETY_TITLE_END "</span" 

		if (strstr(Tempstr,ROYALSOCIETY_TITLE_START)) 
		{
		GenericExtractFromLine(Tempstr, "Title",ROYALSOCIETY_TITLE_START,ROYALSOCIETY_TITLE_END,Vars,0);
		}
		
break;


case TYPE_ROYALSOCIETY_STAGE2:

#define ROYALSOCIETY_ITEM "ipadUrl: '"

		if (strstr(Tempstr,ROYALSOCIETY_ITEM)) 
		{
			GenericExtractFromLine(Tempstr, "ID",ROYALSOCIETY_ITEM,"\'",Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
		}
break;


/*
case TYPE_DOTSUB:
#define DOTSUB_ITEMSTART "<source src=\""
#define DOTSUB_ITEMEND "\""
#define DOTSUB_TITLESTART "og:title\" content=\""
#define DOTSUB_TITLEEND "\""

		if (strstr(Tempstr,DOTSUB_ITEMSTART)) GenericExtractFromLine(Tempstr, "ID",DOTSUB_ITEMSTART,DOTSUB_ITEMEND,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES | EXTRACT_GUESSTYPE);
		if (strstr(Tempstr,DOTSUB_TITLESTART)) GenericExtractFromLine(Tempstr, "Title",DOTSUB_TITLESTART,DOTSUB_TITLEEND,Vars,0);
break;
*/

case TYPE_ASTRONOMYCOM:
#define ASTRONOMYCOM_ITEMSTART "http://kws.kalmbach.com/generator2.aspx"
#define ASTRONOMYCOM_ITEMEND "\""
#define ASTRONOMYCOM_TITLESTART "<h1 class=\"headline\">"
#define ASTRONOMYCOM_TITLEEND "</h1>"

		if (strstr(Tempstr,ASTRONOMYCOM_TITLESTART))
		{
		GenericExtractFromLine(Tempstr, "Title",ASTRONOMYCOM_TITLESTART,ASTRONOMYCOM_TITLEEND,Vars,0);
		}

		if (strstr(Tempstr,ASTRONOMYCOM_ITEMSTART))
		{
			 GenericExtractFromLine(Tempstr, "ID",ASTRONOMYCOM_ITEMSTART,ASTRONOMYCOM_ITEMEND,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
			 Tempstr=MCopyStr(Tempstr,ASTRONOMYCOM_ITEMSTART,GetVar(Vars,"ID"),NULL);
			 SetVar(Vars,"ID",Tempstr);
		}
		

break;


case TYPE_ASTRONOMYCOM_STAGE2:
#define ASTRONOMYCOM_S2_ITEMSTART "file:\""
#define ASTRONOMYCOM_S2_ITEMEND "\""

		if (strstr(Tempstr,ASTRONOMYCOM_S2_ITEMSTART))
		{
			 GenericExtractFromLine(Tempstr, "ID",ASTRONOMYCOM_S2_ITEMSTART,ASTRONOMYCOM_ITEMEND,Vars,EXTRACT_GUESSTYPE);
		}
	
break;



case TYPE_BLOOMBERG:
#define BLOOMBERG_ITEMSTART "BLOOMBERG._fvid_id = \""
#define BLOOMBERG_ITEMEND "\""

	GenericTitleExtract(Tempstr, Vars);
	if (strstr(Tempstr,BLOOMBERG_ITEMSTART))
	{
		GenericExtractFromLine(Tempstr, "item:flv",BLOOMBERG_ITEMSTART,BLOOMBERG_ITEMEND,Vars,EXTRACT_DESLASHQUOTE | EXTRACT_NOSPACES);
	}
break;

case TYPE_NATGEO:
#define NATGEO_ITEM_START "HTML5src:'"
#define NATGEO_ITEM_END "\'"
#define NATGEO_FLV_START "class=\"ngs_video\" data-require=\"ngsPlayer\" data-options='{ \"slug\": \""
#define NATGEO_FLV_END "\""
#define NATGEO_TITLE_START "<meta property=\"og:title\" content=\""
#define NATGEO_TITLE_END "\""

	if (strstr(Tempstr,NATGEO_ITEM_START))
	{
		GenericExtractFromLine(Tempstr, "tmp",NATGEO_ITEM_START,NATGEO_ITEM_END,Vars,EXTRACT_DESLASHQUOTE | EXTRACT_NOSPACES);

		Tempstr=MCopyStr(Tempstr,"http://",Server,"/",GetVar(Vars,"tmp"),NULL);
		SetVar(Vars,"item:reference",Tempstr);
	}

	if (strstr(Tempstr,NATGEO_FLV_START))
	{
		GenericExtractFromLine(Tempstr, "item:flv",NATGEO_FLV_START,NATGEO_FLV_END,Vars,EXTRACT_NOSPACES);
	}

	if (strstr(Tempstr,NATGEO_TITLE_START))
	{
		GenericExtractFromLine(Tempstr, "Title",NATGEO_TITLE_START,NATGEO_TITLE_END,Vars,0);
	}

break;

case TYPE_VIDEOBASH:
#define VIDEOBASH_ITEMSTART "&amp;file=\" + 'http://' + '"
#define VIDEOBASH_ITEMEND "\'"
#define VIDEOBASH_TITLE_START "<meta property=\"og:title\" content=\""
#define VIDEOBASH_TITLE_END "\""

	if (strstr(Tempstr,VIDEOBASH_ITEMSTART))
	{
		GenericExtractFromLine(Tempstr, "item:mp4",VIDEOBASH_ITEMSTART,VIDEOBASH_ITEMEND,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
	}

	if (strstr(Tempstr,VIDEOBASH_TITLE_START))
	{
		GenericExtractFromLine(Tempstr, "Title",VIDEOBASH_TITLE_START,VIDEOBASH_TITLE_END,Vars,0);
	}

break;


case TYPE_IGN:
#define IGN_ITEMSTART "video_id\":\""
#define IGN_ITEMEND "\""

	GenericTitleExtract(Tempstr, Vars);
	if (strstr(Tempstr,IGN_ITEMSTART))
	{
		GenericExtractFromLine(Tempstr, "ID",IGN_ITEMSTART,IGN_ITEMEND,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
	}
break;

case TYPE_IGN_STAGE2:
	IGN_DecodeFormats(Tempstr, Vars);
break;

case TYPE_IMDB:
#define IMDB_ITEMSTART "://www.imdb.com/video/imdb/vi"
#define IMDB_ITEMEND "\""

	GenericTitleExtract(Tempstr, Vars);
if (strstr(Tempstr,IMDB_ITEMSTART))
{
	GenericExtractFromLine(Tempstr, "ID",IMDB_ITEMSTART,IMDB_ITEMEND,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);

	Token=CopyStr(Token,GetVar(Vars,"ID"));
	if (StrValid(Token))
	{
		ptr=strchr(Token,'?');
		if (ptr) *ptr='\0';
		ptr=strchr(Token,'/');
		if (ptr) *ptr='\0';
		SetVar(Vars,"ID",Token);
	}
}
break;

case TYPE_IMDB_STAGE2:
#define IMDB_STAGE2_ITEMSTART "\"videoUrl\":\""
#define IMDB_STAGE2_ITEMEND "\""

ptr=Tempstr;
while (ptr)
{
if (! strstr(ptr,IMDB_STAGE2_ITEMSTART)) break;
ptr=GenericExtractFromLine(ptr, "ID",IMDB_STAGE2_ITEMSTART,IMDB_STAGE2_ITEMEND,Vars,EXTRACT_GUESSTYPE);
}
break;


case TYPE_EBAUMSWORLD:
#define EBAUMSWORLD_ITEMSTART "params.file = '"
#define EBAUMSWORLD_ITEMEND "'"

	GenericTitleExtract(Tempstr, Vars);
	if (strstr(Tempstr,EBAUMSWORLD_ITEMSTART))
	{
		GenericExtractFromLine(Tempstr, "ID",EBAUMSWORLD_ITEMSTART,EBAUMSWORLD_ITEMEND,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
	}
break;

case TYPE_GAMESTAR:
#define GAMESTAR_ITEMSTART "var iVideoId ="
#define GAMESTAR_ITEMEND ";"
#define GAMESTAR2_ITEMSTART "ga('set', 'dimension4', '"
#define GAMESTAR2_ITEMEND "'"
	
	GenericTitleExtract(Tempstr, Vars);
	if (strstr(Tempstr,GAMESTAR_ITEMSTART))
	{
		GenericExtractFromLine(Tempstr, "ID",GAMESTAR_ITEMSTART,GAMESTAR_ITEMEND,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
	}
	if (strstr(Tempstr,GAMESTAR2_ITEMSTART))
	{
		GenericExtractFromLine(Tempstr, "ID",GAMESTAR2_ITEMSTART,GAMESTAR2_ITEMEND,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
	}
break;


case TYPE_STANFORD_OPENCLASS:
#define STANFORD_OPENCLASS_COURSE "var courseName = \""
#define STANFORD_OPENCLASS_VIDEO "var videoName = \""
#define STANFORD_OPENCLASS_END "\""
	
	GenericTitleExtract(Tempstr, Vars);
	if (strstr(Tempstr,STANFORD_OPENCLASS_COURSE))
	{
		GenericExtractFromLine(Tempstr, "course",STANFORD_OPENCLASS_COURSE,STANFORD_OPENCLASS_END,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
	}
	if (strstr(Tempstr,STANFORD_OPENCLASS_VIDEO))
	{
		GenericExtractFromLine(Tempstr, "ID",STANFORD_OPENCLASS_VIDEO,STANFORD_OPENCLASS_END,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
	}
break;


case TYPE_STANFORD_STAGE2:
#define STANFORD_STAGE2_ITEMSTART "<videoFile>"
#define STANFORD_STAGE2_ITEMEND "</"

	if (strstr(Tempstr,STANFORD_STAGE2_ITEMSTART))
	{
		GenericExtractFromLine(Tempstr, "ID",STANFORD_STAGE2_ITEMSTART,STANFORD_STAGE2_ITEMEND,Vars, 0);
		Token=CopyStr(Token,URL);
		ptr=strrchr(Token,'/');
		if (ptr)
		{
			*ptr='\0';
			Token=MCatStr(Token,"/",GetVar(Vars,"ID"),NULL);
			SetVar(Vars,"ID",Token);
		}
	}
break;

case TYPE_GOOGLE_URL:
		SetVar(Vars,"item:reference",URL);
		Type=TYPE_REFERENCE;
break;



case TYPE_UCTV:
case TYPE_GENERIC:

//some sites are actually just frontends to youtube
#define YOUTUBE_REFERENCE1 "http://www.youtube.com/watch?v="
#define YOUTUBE_REFERENCE2 "http://www.youtube.com/v/"

GenericTitleExtract(Tempstr, Vars);

if (strstr(Tempstr,YOUTUBE_REFERENCE1))
{
		GenericExtractFromLine(Tempstr, "yt-tmp",YOUTUBE_REFERENCE1,"\"",Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
		ptr=GetVar(Vars,"yt-tmp");
		if (StrLen(ptr)) Token=MCopyStr(Token,YOUTUBE_REFERENCE1,ptr,NULL);
		SetVar(Vars,"item:reference",Token);
		Token=CopyStr(Token,""); //So as later stages of this process don't
}

if (strstr(Tempstr,YOUTUBE_REFERENCE2))
{
		GenericExtractFromLine(Tempstr, "yt-tmp",YOUTUBE_REFERENCE2,"\"",Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
		ptr=GetVar(Vars,"yt-tmp");
		if (StrLen(ptr)) Token=MCopyStr(Token,YOUTUBE_REFERENCE2,ptr,NULL);
		SetVar(Vars,"item:reference",Token);
		Token=CopyStr(Token,""); //So as later stages of this process don't
														 //pick up on it
}

//Try looking for 'container' filees like .pls .m3u .asx
for (i=0; ContainerTypes[i] !=NULL; i++)
{
if (strstr(Tempstr,ContainerTypes[i]))
{
		GenericExtractFromLine(Tempstr, "tmp","http://",ContainerTypes[i],Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
		ptr=GetVar(Vars,"tmp");
		if (StrLen(ptr)) Token=MCopyStr(Token,"http://",ptr,ContainerTypes[i],NULL);
		SetVar(Vars,"item:reference",Token);
}
}


//This goes searching for urls starting with 'http://' and ending with likely media file extensions
for (i=0; FileTypes[i] !=NULL; i++)
{
	if (strstr(Tempstr,FileTypes[i]))
	{
		VarName=MCopyStr(VarName,"item:",FileTypes[i]+1,NULL);
		GenericExtractFromLine(Tempstr, VarName,"http://",FileTypes[i],Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
		ptr=GetVar(Vars,VarName);
		if (StrLen(ptr)) Token=MCopyStr(Token,"http://",ptr,NULL);
		else
		{
			GenericExtractFromLine(Tempstr, VarName,"href=",FileTypes[i],Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
			Token=CopyStr(Token,GetVar(Vars,VarName));
			if (StrLen(Token) && (strncasecmp(Token,"http://",7) !=0))
			{
				Token=MCopyStr(Token,"http://",GetVar(Vars,"Server"),"/",NULL);
				Token=CatStr(Token,GetVar(Vars,VarName));
			}
		}
		
		if (StrLen(Token)) 
		{
			Token=CatStr(Token,FileTypes[i]);
			SetVar(Vars,VarName,Token);
		}
	}
}
break;


//sites that user HTML5
#define HTML5_ITEM_START "<source "
#define HTML5_ITEM_END ">"
case TYPE_REDORBIT:
case TYPE_GUARDIAN:
case TYPE_LIVELEAK:
case TYPE_DOTSUB:
case TYPE_FUNNYORDIE:
case TYPE_CHARLIEROSE:
GenericTitleExtract(Tempstr, Vars);
ptr=strstr(Tempstr,HTML5_ITEM_START);
while (ptr)
{
	ptr=GenericExtractFromLine(ptr, "mediadef",HTML5_ITEM_START,HTML5_ITEM_END,Vars,EXTRACT_WITHIN_HTMLTAG);
	ptr2=GetVar(Vars,"mediadef");
	if (StrValid(ptr2)) 
	{
		ptr2=GetNameValuePair(ptr2," ","=",&VarName,&Token);
		while (ptr2)
		{
		StripQuotes(VarName);
		StripQuotes(Token);
		if (strcmp(VarName,"src")==0) SetVar(Vars,"url",Token);
		if (strcmp(VarName,"res")==0) SetVar(Vars,"resolution",Token);
		if (strcmp(VarName,"type")==0) SetVar(Vars,"type",Token);
		ptr2=GetNameValuePair(ptr2," ","=",&VarName,&Token);
		}
	}

	VarName=CopyStr(VarName,"");
	ptr2=GetVar(Vars,"type");

	if (strcmp(ptr2,"video/mp4")==0) VarName=MCopyStr(VarName, "item:mp4:",GetVar(Vars,"resolution"),NULL);
	else if (strcmp(ptr2,"video/webm")==0) VarName=MCopyStr(VarName, "item:webm:",GetVar(Vars,"resolution"),NULL);
	else if (strcmp(ptr2,"video/flv")==0) VarName=MCopyStr(VarName, "item:flv:",GetVar(Vars,"resolution"),NULL);
	else if (strcmp(ptr2,"video/m3u8")==0) VarName=MCopyStr(VarName, "item:m3u8:",GetVar(Vars,"resolution"),NULL);

	if (StrValid(VarName)) SetVar(Vars,VarName,GetVar(Vars,"url"));

	ptr=strstr(ptr,HTML5_ITEM_START);
}

break;


case TYPE_EURONEWS:
case TYPE_DISCOVERY:
#define OG_URL "<meta property=\"og:video:url\" content=\""
#define OG2_URL "<meta property=\"og:video\" content=\""
#define TWITTER_URL "<meta name=\"twitter:player:stream\" content=\""
#define OG_END "\""

	GenericTitleExtract(Tempstr, Vars);
	if (strstr(Tempstr, OG_URL)) GenericExtractFromLine(Tempstr, "ID",OG_URL,OG_END,Vars,EXTRACT_GUESSTYPE);
	if (strstr(Tempstr, OG2_URL)) GenericExtractFromLine(Tempstr, "ID",OG2_URL,OG_END,Vars,EXTRACT_GUESSTYPE);
	if (strstr(Tempstr, TWITTER_URL)) GenericExtractFromLine(Tempstr, "ID",TWITTER_URL,OG_END,Vars,EXTRACT_GUESSTYPE);
break;
}

  Tempstr=STREAMReadLine(Tempstr,S);
}

if (Flags & (FLAG_DEBUG2 | FLAG_DEBUG3)) fprintf(stderr,"\n------- END DOCUMENT ------\n\n");

//ptr=GetVar(Vars,"item:m3u8");
//if (StrValid(ptr)) M3UContainer(ptr, Vars);

ptr=GetVar(Vars,"Title");
if (! StrValid(ptr)) ptr=GetVar(Vars,"Title:meta");
if (! StrValid(ptr)) ptr=GetVar(Vars,"Title:html");
if (! StrValid(ptr)) ptr=Title;
SetVar(Vars,"Title",ptr);


if (MediaCount > 0) HandleMultipleMedia(Type,Server,Flags,Vars,MediaCount);
else
{
	if (! StrValid(GetVar(Vars,"ID")))
	{
 		Type=SelectDownloadFormat(Vars,Type,TRUE);
	}	

	ptr=GetVar(Vars,"ID");

	if (ptr) RetVal=GetNextURL(Type, Server, Flags, Vars);
	else if (! (Flags & FLAG_QUIET))
	{
		fprintf(stderr,"FAILED TO GET DOCUMENT REFERENCE!\n");
		fprintf(stderr,"Maybe you need to change the format preferences, or else the url you supplied is wrong\n");
	}
}

ListDestroy(Vars,DestroyString);

DestroyString(VarName);
DestroyString(Token);
DestroyString(Tempstr);

return(RetVal);
}

