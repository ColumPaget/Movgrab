#include "servicetypes.h"
#include "containerfiles.h"

/*
This file and it's header (servicetypes.h) holds all the functions and data
related to individual services/sites. When adding a site you need to add to
the arrays 'DownloadTypes', 'DownloadNames' and 'TestLinks' and to the 
enumerated type in servicetypes.h tht matches to 'DownloadTypes'.

Then site specific 
*/



//Site type names used at the command line etc
char *DownloadTypes[]={"none","generic","youtube","metacafe","dailymotion","break","ehow","vimeo","vbox7","blip.tv","ted","myvideo","mytopclip","redbalcony","mobango","yale","princeton","reuters","liveleak","academicearth","photobucket","aljazeera","mefeedia","iviewtube","washingtonpost","cbsnews","france24","euronews","metatube","motionfeeds","escapist","guardian","redorbit","scivee","izlese","uctv.tv","royalsociety.tv","britishacademy","kitp","dotsub","astronomy.com","teachertube.com","discovery","bloomberg","nationalgeographic","videobash","ibtimes","smh","videojug","animehere","funnyordie",NULL};

//Longer names used in display
char *DownloadNames[]={"none",
"Generic: Search in page for http://*.flv, http://*.mp3, http//*.mp4 etc, etc, etc",
"YouTube: http://www.youtube.com",
"Metacafe: http://www.metacafe.com",
"Daily Motion: http://www.dailymotion.com",
"www.break.com",
"www.ehow.com",
"www.vimeo.com",
"www.vbox7.com",
"www.blip.tv",
"www.ted.com",
"www.myvideo.de",
"www.mytopclip.com",
"www.redbalcony.com",
"www.mobango.com",
"Yale University: http://oyc.yale.edu",
"Princeton University: http://www.princeton.edu/WebMedia/",
"Reuters: http://www.reuters.com/",
"Liveleak: http://www.liveleak.com",
"Academic Earth: http://www.academicearth.org",
"Photobucket: http://www.photobucket.com",
"Aljazeera: english.aljazeera.net",
"mefeedia.com",
"iViewTube: www.iviewtube.com",
"Washington Post: www.washingtonpost.com",
"CBS News: www.cbsnews.com",
"France24: www.france24.com",
"Euronews: www.euronews.net",
"www.metatube.com",
"www.motionfeeds.com",
"www.escapistmagazine.com",
"www.guardian.co.uk",
"www.redorbit.com",
"www.scivee.tv",
"www.izlese.org",
"University of California Television: http://www.uctv.tv/",
"http://royalsociety.org/",
"http://britac.studyserve.com",
"KAVLI INSTITUTE: http://online.itp.ucsb.edu/plecture/",
"dotsub.com",
"astronomy.com",
"teachertube.com",
"dsc.discovery.com",
"www.bloomberg.com (not bloomberg.tv)",
"National Geographic (http://video.nationalgeographic.com)",
"videobash",
"International Business Times",
"Sidney Morning Herald",
"www.videojug.com",
"www.animehere.com",
"Funny or Die (http://www.funnyordie.com)",
NULL};

//"http://vimeo.com/33204284",
//links used by the -test-sites feature to test if a download site still
//works with movgrab
char *TestLinks[]={"", "",
"http://www.youtube.com/watch?v=Vxp3seoRNgY",
"http://www.metacafe.com/watch/6063075/how_to_use_chopsticks/",
"http://www.dailymotion.com/video/x5790e_hubblecast-16-galaxies-gone-wild_tech",
"http://www.break.com/index/ninja-cat.html",
"http://www.ehow.com/video_6819748_creamy-thyme-scrambled-eggs-recipe.html",
"broken",
"http://www.vbox7.com/play:1417ad5a",
"http://blip.tv/greshamcollege/whengalaxiescollide_carolincrawford-6575570",
"http://www.ted.com/talks/janine_benyus_shares_nature_s_designs.html",
"http://www.myvideo.de/watch/9949/tornados",
"http://www.mytopclip.com/videos/32501/flip-over-card-trick-revealed",
"http://www.redbalcony.com/?vid=29433",
"http://www.mobango.com/media_details/struck_in_tsunami/%21tKpzdHIo5E%3D/",
"http://oyc.yale.edu/economics/game-theory/contents/sessions/session-1-introduction-five-first-lessons",
"http://www.princeton.edu/WebMedia/flash/lectures/20100428_publect_taibbi_tett.shtml",
"http://www.reuters.com/news/video/story?videoId=193471398&videoChannel=4",
"http://www.liveleak.com/view?i=a7b_1299633723",
"http://www.academicearth.org/lectures/interaction-with-physical-environment",
"http://gs147.photobucket.com/groups/r299/QM25Y4IJEP/?action=view&current=BlackSwan1.mp4",
"http://english.aljazeera.net/programmes/countingthecost/2011/02/2011219142816937101.html",
"http://www.mefeedia.com/video/36135458",
"http://www.iviewtube.com/v/152128/insane-hail-storm-oklahoma-city",
"http://www.washingtonpost.com/business/on-leadership-modern-day-machiavellis-/2011/02/18/ABYgckH_video.html",
"http://www.cbsnews.com/video/watch/?id=7357739n",
"http://www.france24.com/en/20110219-beyond-business-cybercriminality-iphone-mobile-security",
"http://www.euronews.com/news/bulletin/",
"http://www.metatube.com/en/videos/cid2/Funny-Videos/53210/Rail-Jump-Fail/",
"http://www.motionfeeds.com/10401/helsinki-travel-guide.html",
"http://www.escapistmagazine.com/videos/view/zero-punctuation/1776-Red-Dead-Redemption",
"http://www.guardian.co.uk/world/video/2011/may/13/fukushima-radiation-dairy-farmers-video",
"http://www.redorbit.com/news/video/science_2/2598565/unlocking_mysteries_of_sharks/index.html",
"http://www.scivee.tv/node/5300",
"http://www.izlese.org/hot-girl-hot-cars-911-turbo-vs-mercedes-s550-vs-rally-car.html",
"http://www.uctv.tv/search-details.aspx?showID=20888",
"http://royalsociety.tv/rsPlayer.aspx?presentationid=474",
"broken",
"http://online.itp.ucsb.edu/plecture/bmonreal11/",
"http://dotsub.com/view/5d90ef11-d5e5-42fb-8263-a4c128fb64df",
"http://www.astronomy.com/News-Observing/Liz%20and%20Bills%20Cosmic%20Adventures/2011/02/Episode%202.aspx",
"http://www.teachertube.com/viewVideo.php?video_id=114089&title=Marco_Polo",
"http://dsc.discovery.com/videos/how-the-universe-works-birth-of-a-black-hole.html",
"http://www.bloomberg.com/video/72477250/",
"http://video.nationalgeographic.com/video/environment/environment-natural-disasters/earthquakes/earthquake-101/",
"http://www.videobash.com/video_show/wing-suit-amazing-footage-6086",
"http://tv.ibtimes.com/woolly-mammoth-skeleton-discovered-near-paris-nicknamed-helmut-7190",
"http://www.smh.com.au/technology/sci-tech/newly-discovered-planets-include-superearth-20110913-1k7tl.html",
"http://www.videojug.com/film/how-to-do-the-best-card-trick-in-the-world",
"http://www.animehere.com/accel-world-episode-1.html",
"http://www.funnyordie.com/videos/032785be3a/genie-on-hard-times-with-parker-posey?playlist=featured_videos",
NULL};


int SelectDownloadFormat(ListNode *Vars, int WebsiteType, int DisplaySize);


//Guess service type from servername in URL
int IdentifyServiceType(char *Server)
{
int Type=0;

if (
	(strstr(Server,"youtube")) 
   ) Type=TYPE_YOUTUBE;

if (strcmp(Server,"www.metacafe.com")==0)
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
else if (strcmp(Server,"oyc.yale.edu")==0)
{
 Type=TYPE_YALE;
}
else if (strcmp(Server,"www.princeton.edu")==0)
{
 Type=TYPE_PRINCETON;
}
else if (strcmp(Server,"www.academicearth.org")==0)
{
 Type=TYPE_ACADEMIC_EARTH;
}
else if (strstr(Server,"photobucket.com"))
{
 Type=TYPE_PHOTOBUCKET;
}
else if (strstr(Server,"vbox7.com"))
{
 Type=TYPE_VBOX7;
}
else if (strstr(Server,"myvideo"))
{
 Type=TYPE_MYVIDEO;
}
else if (strstr(Server,"redbalcony.com"))
{
 Type=TYPE_REDBALCONY;
}
else if (strstr(Server,"mobango.com"))
{
 Type=TYPE_MOBANGO;
}
else if (strstr(Server,"izlese.org"))
{
 Type=TYPE_IZLESE;
}
else if (strstr(Server,"mytopclip.com"))
{
 Type=TYPE_MYTOPCLIP;
}
else if (strstr(Server,"liveleak"))
{
 Type=TYPE_LIVELEAK;
}
else if (strstr(Server,"ibtimes"))
{
 Type=TYPE_IBTIMES;
}
else if (strstr(Server,"smh.com.au"))
{
 Type=TYPE_SMH;
}
else if (strstr(Server,"blip.tv"))
{
 Type=TYPE_BLIPTV;
}
else if (strstr(Server,"vimeo.com"))
{
 Type=TYPE_VIMEO;
}
else if (strstr(Server,"reuters"))
{
 Type=TYPE_REUTERS;
}
else if (strstr(Server,"mefeedia.com"))
{
 Type=TYPE_MEFEEDIA;
}
else if (strstr(Server,"ucsd.tv"))
{
 Type=TYPE_UCTV;
}
else if (strstr(Server,"uctv.tv"))
{
 Type=TYPE_UCTV;
}
else if (strstr(Server,"aljazeera.net"))
{
 Type=TYPE_ALJAZEERA;
}
else if (strstr(Server,"iviewtube.com"))
{
 Type=TYPE_IVIEWTUBE;
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
else if (strstr(Server,"motionfeeds"))
{
 Type=TYPE_MOTIONFEEDS;
}
else if (strstr(Server,"guardian"))
{
 Type=TYPE_GUARDIAN;
}
else if (strstr(Server,"redorbit"))
{
 Type=TYPE_REDORBIT;
}
else if (strstr(Server,"scivee"))
{
 Type=TYPE_SCIVEE;
}
else if (strstr(Server,"escapistmagazine.com"))
{
 Type=TYPE_ESCAPIST;
}
else if (strcmp(Server,"royalsociety.tv")==0)
{
 Type=TYPE_ROYALSOCIETY_STAGE2;
}
else if (strcmp(Server,"royalsociety.org")==0)
{
 Type=TYPE_ROYALSOCIETY;
}
else if (strcmp(Server,"britac.studyserve.com")==0)
{
 Type=TYPE_BRITISHACADEMY;
}
else if (strcmp(Server,"online.itp.ucsb.edu")==0)
{
 Type=TYPE_KAVLIINSTITUTE;
}
else if (strcmp(Server,"dotsub.com")==0)
{
 Type=TYPE_DOTSUB;
}
else if (strstr(Server,"astronomy.com"))
{
 Type=TYPE_ASTRONOMYCOM;
}
else if (strstr(Server,"teachertube.com"))
{
 Type=TYPE_TEACHERTUBE;
}
else if (strstr(Server,"discovery.com"))
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
else if (strstr(Server,"www.videojug.com"))
{
 Type=TYPE_VIDEOJUG;
}
else if (strstr(Server,"animehere.com"))
{
 Type=TYPE_ANIMEHERE;
}
else if (strstr(Server,"funnyordie.com"))
{
 Type=TYPE_FUNNYORDIE;
}
else if (strstr(Server,".google."))
{
 Type=TYPE_GOOGLE_URL;
}

return(Type);
}



//A couple of old functions related to specific sites. As these sites no longer
//work it is likely that these functions will be removed some day
int DoVBOX7(char *ID, char *Title)
{
char *Dir=NULL, *Tempstr=NULL;
int i, RetVal=FALSE;

Dir=CopyStrLen(Dir,ID,2);

for (i=1; i < 50; i++)
{
	if (i==0) Tempstr=FormatStr(Tempstr,"http://media.vbox7.com/s/%s/%s.flv",Dir,ID);
  else Tempstr=FormatStr(Tempstr,"http://media%02d.vbox7.com/s/%s/%s.flv",i,Dir,ID);
  if (DownloadItem(Tempstr, Title, Flags))
	{
		RetVal=TRUE;
		 break;
	}
}

DestroyString(Dir);
DestroyString(Tempstr);

return(RetVal);
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


// These functions used by escapist magazine, but the method might be more 
// generic than just that one side
void ParseFlashPlaylistItem(char *Data,ListNode *Vars)
{
char *Name=NULL, *Value=NULL, *URL=NULL, *Type=NULL, *ptr;

strrep(Data,'\'',' ');
ptr=GetNameValuePair(Data,",",":",&Name,&Value);
while (ptr)
{
StripTrailingWhitespace(Name);
StripLeadingWhitespace(Name);
StripQuotes(Name);

StripTrailingWhitespace(Value);
StripLeadingWhitespace(Value);
StripQuotes(Value);


if (StrLen(Name))
{
  if (strcmp(Name,"eventCategory")==0) Type=CopyStr(Type,Value);
  if (strcmp(Name,"url")==0) URL=CopyStr(URL,Value);
}

ptr=GetNameValuePair(ptr,",",":",&Name,&Value);
}

if (StrLen(Type) && (strcmp(Type,"Video")==0)) SetVar(Vars,"item:mp4",URL);

DestroyString(Name);
DestroyString(Value);
DestroyString(URL);
DestroyString(Type);

}


void ParseFlashPlaylist(char *Data, ListNode *Vars)
{
char *Tempstr=NULL, *Item=NULL,  *ptr;

//This clips the playlist structure out into Tempstr
ptr=GetToken(Data,"{'playlist':[",&Tempstr,0);
ptr=GetToken(ptr,"]",&Tempstr,0);

ptr=GetToken(Tempstr,"{",&Item,0);
while (ptr)
{
//'Item' no contains one playlist item
ptr=GetToken(ptr,"}",&Item,0);
ParseFlashPlaylistItem(Item,Vars);

ptr=GetToken(ptr,"{",&Item,0);
}

DestroyString(Tempstr);
DestroyString(Item);
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

if (*Type==TYPE_YOUTUBE)
{

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

}
else if (*Type==TYPE_METACAFE)
{
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
		S=HTTPMethod("POST",Tempstr,"","");
		STREAMClose(S);

		//But we have to do it twice, probably something to do with cookies
		NextPath=FormatStr(NextPath,"http://%s:%d/f/index.php?inputType=filter&controllerGroup=user&filters=0&Continue=Continue+-+I%27m+over+18&prevURL=%s",Server,Port,Path);
		}
		else NextPath=CopyStr(NextPath,Path);
	}
}
else if (*Type==TYPE_DAILYMOTION)
{
	if (*Flags & FLAG_PORN)
	{
		Tempstr=HTTPQuote(Tempstr,Doc);
		NextPath=FormatStr(NextPath,"http://%s:%d/family_filter?urlback=/%s&enable=false",Server,Port,Tempstr);
	}
	else NextPath=CopyStr(NextPath,Path);
}
else if (*Type==TYPE_PRINCETON)
{
	ptr=strrchr(Doc,'/');
	if (ptr)
	{
		ptr++;
		*Title=CopyStr(*Title,ptr);
		ptr=strrchr(*Title,'.');
		if (ptr) *ptr='\0';
	}
 	NextPath=CopyStr(NextPath,Path);
}
else if (*Type==TYPE_VIMEO)
{
 	NextPath=MCopyStr(NextPath,"http://player.vimeo.com/video/",Doc,NULL);
}
else if (*Type==TYPE_GOOGLE_URL)
{
	ptr=strstr(Path,"url?q=");
	if (ptr)
	{
		ptr+=6;
 		ptr=GetToken(ptr,"&",&Token,NULL);
 		NextPath=HTTPUnQuote(NextPath,Token);
		*Type==TYPE_REFERENCE;
	}
}
else
{
 NextPath=CopyStr(NextPath,Path);
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
		//GetNextURL(Type, Server, Flags, Vars);
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

Title=CopyStr(Title,GetVar(Vars,"Title"));
Fmt=CopyStr(Fmt,GetVar(Vars,"DownloadFormat"));

switch (Type)
{
case TYPE_REFERENCE:
	Tempstr=CopyStr(Tempstr,GetVar(Vars,"ID"));
  if (GetContainerFileType(Tempstr) != -1)	RetVal=DownloadContainer(Tempstr, Title, Flags);
	else RetVal=GrabMovie(Tempstr,TYPE_NONE);
break;

case TYPE_YOUTUBE:
		Tempstr=CopyStr(Tempstr,GetVar(Vars,"ID"));
  	RetVal=DownloadItem(Tempstr, Title, Fmt, Flags);
break;

case TYPE_YOUTUBE_PLAYLIST:
		Tempstr=CopyStr(Tempstr,GetVar(Vars,"ID"));
  	RetVal=DownloadPage(Tempstr,TYPE_YOUTUBE, Title, Flags);
break;


case TYPE_BREAK_COM:
		Tempstr=CopyStr(Tempstr,GetVar(Vars,"ID"));
  	RetVal=DownloadItem(Tempstr, Title, Fmt, Flags);
break;

case TYPE_EHOW:
	ptr=GetVar(Vars,"ID");
	if (strncmp(ptr,"http:",5)==0) RetVal=DownloadItem(ptr,Title, Fmt, Flags);
	else
	{
		Tempstr=SubstituteVarsInString(Tempstr,"http://$(Server):$(Port)/embedvars.aspx?isEhow=true&show_related=true&id=$(ID)",Vars,0);
  	RetVal=DownloadPage(Tempstr,TYPE_EHOW_STAGE2, Title,Flags);
	}
break;

case TYPE_EHOW_STAGE2:
  	RetVal=DownloadItem(GetVar(Vars,"ID"), Title, Fmt, Flags);
break;


case TYPE_METACAFE:
#define METACAFE_OVER_18 "allowAdultContent=1&submit=Continue+-+I%27m+over+18"
 Tempstr=SubstituteVarsInString(Tempstr,"$(ID)&$(METACAFE_OVER_18)",Vars,0);
 	RetVal=DownloadItem(Tempstr, Title, Fmt, Flags);
break;


case TYPE_DAILYMOTION:
  Tempstr=SubstituteVarsInString(Tempstr,"http://www.dailymotion.com/services/oembed?url=$(ID)&format=xml",Vars,0);
  RetVal=DownloadPage(Tempstr,TYPE_DAILYMOTION_STAGE2,Title,Flags);
break;

case TYPE_DAILYMOTION_STAGE2:
  Tempstr=SubstituteVarsInString(Tempstr,"$(ID)",Vars,0);
  RetVal=DownloadPage(Tempstr,TYPE_DAILYMOTION_STAGE3,Title,Flags);
break;

case TYPE_DAILYMOTION_STAGE3:
  Tempstr=SubstituteVarsInString(Tempstr,"$(ID)",Vars,0);
  RetVal=DownloadItem(Tempstr, Title, Fmt, Flags);
break;

case TYPE_VIDEOJUG:
  Tempstr=SubstituteVarsInString(Tempstr,"$(ID)",Vars,0);
  RetVal=DownloadPage(Tempstr,TYPE_VIDEOJUG_STAGE2,Title,Flags);
break;

case TYPE_VIDEOJUG_STAGE2:
  Tempstr=SubstituteVarsInString(Tempstr,"$(ID)",Vars,0);
  RetVal=DownloadPage(Tempstr,TYPE_VIDEOJUG_STAGE3,Title,Flags);
break;

case TYPE_VIDEOJUG_STAGE3:
  Tempstr=SubstituteVarsInString(Tempstr,"$(ID)",Vars,0);
  RetVal=DownloadItem(Tempstr, Title, Fmt, Flags);
break;



case TYPE_MOBANGO:
 //Tempstr=SubstituteVarsInString(Tempstr,"http://www.mobango.com/$(ID)",Vars,0);
 RetVal=DownloadItem(GetVar(Vars,"ID"), Title, Fmt, Flags);
break;

case TYPE_WASHINGTONPOST_JSON:
 	RetVal=DownloadPage(GetVar(Vars,"ID"),TYPE_WASHINGTONPOST_STAGE2,Title,Flags);
break;

case TYPE_WASHINGTONPOST_STAGE2:
	Tempstr=SubstituteVarsInString(Tempstr,"$(server)$(flvurl)",Vars,0);
 	RetVal=DownloadItem(Tempstr,Title, Fmt, Flags);
break;


case TYPE_MYVIDEO:
		Tempstr=SubstituteVarsInString(Tempstr,"$(MyVidURL)/$(ID).flv",Vars,0);
  	RetVal=DownloadItem(Tempstr, Title, Fmt, Flags);
break;

case TYPE_VBOX7:
	RetVal=DoVBOX7(GetVar(Vars,"ID"), Title);
break;

case TYPE_VIMEO:
 	RetVal=DownloadPage(GetVar(Vars,"ID"),TYPE_VIMEO_STAGE2,Title,Flags);
break;

case TYPE_VIMEO_STAGE2:
		Tempstr=SubstituteVarsInString(Tempstr,"$(BASE)/$(ID)",Vars,0);
  	RetVal=DownloadItem(Tempstr, Title, Fmt, Flags);
break;


case TYPE_YALE:
 Tempstr=SubstituteVarsInString(Tempstr,"$(ID)",Vars,0);
 	RetVal=DownloadItem(Tempstr,Title, Fmt, Flags);
break;

case TYPE_BLIPTV:
 		Tempstr=FormatStr(Tempstr,"http://%s/%s",Server,GetVar(Vars,"ID"));
  	RetVal=DownloadPage(Tempstr,TYPE_BLIPTV_STAGE2, Title,Flags);
break;

case TYPE_ESCAPIST:
 		Tempstr=SubstituteVarsInString(Tempstr,"$(ID)",Vars,0);
  	RetVal=DownloadPage(Tempstr,TYPE_ESCAPIST_STAGE2, Title,Flags);
break;

case TYPE_REDBALCONY:
 		Tempstr=SubstituteVarsInString(Tempstr,"$(ID)",Vars,0);
  	RetVal=DownloadPage(Tempstr,TYPE_REDBALCONY_STAGE2, Title,Flags);
break;


case TYPE_REDORBIT:
 		Tempstr=SubstituteVarsInString(Tempstr,"$(ID)",Vars,0);
  	RetVal=DownloadPage(Tempstr,TYPE_REDORBIT_STAGE2, Title,Flags);
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
  	RetVal=DownloadM3U(Tempstr, Title, Flags);
break;


case TYPE_BRITISHACADEMY:
 		Tempstr=SubstituteVarsInString(Tempstr,"http://britac.studyserve.com/home/$(ID)",Vars,0);
  	RetVal=DownloadPage(Tempstr,TYPE_BRITISHACADEMY_STAGE2, Title,Flags);
break;

case TYPE_BRITISHACADEMY_STAGE2:
 		Tempstr=SubstituteVarsInString(Tempstr,"http://britac.studyserve.com/home/lectures/$(ID)",Vars,0);
  	RetVal=DownloadASX(Tempstr, Title,Flags);
break;

case TYPE_KAVLIINSTITUTE:
 		Tempstr=SubstituteVarsInString(Tempstr,"$(ID)",Vars,0);
  	RetVal=DownloadPage(Tempstr,TYPE_KAVLIINSTITUTE_STAGE2, Title,Flags);
break;

case TYPE_EURONEWS:
 Tempstr=SubstituteVarsInString(Tempstr,"http://video.euronews.net/$(ID).flv",Vars,0);
 RetVal=DownloadItem(Tempstr, Title, Fmt, Flags);
break;

case TYPE_DOTSUB:
 Tempstr=SubstituteVarsInString(Tempstr,"$(SERV)$(ID)",Vars,0);
 RetVal=DownloadItem(Tempstr, Title, Fmt, Flags);
break;

case TYPE_ASTRONOMYCOM:
 	Tempstr=SubstituteVarsInString(Tempstr,"$(ID)",Vars,0);
  RetVal=DownloadPage(Tempstr,TYPE_ASTRONOMYCOM_STAGE2, Title,Flags);
break;

case TYPE_TEACHERTUBE:
 	Tempstr=SubstituteVarsInString(Tempstr,"$(ID)",Vars,0);
 	RetVal=DownloadItem(Tempstr, Title, Fmt, Flags);
break;

case TYPE_BLOOMBERG:
 	Tempstr=SubstituteVarsInString(Tempstr,"http://videos.bloomberg.com/$(ID).flv",Vars,0);
 	RetVal=DownloadItem(Tempstr, Title, Fmt, Flags);
break;

case TYPE_VIDEOBASH:
 	Tempstr=SubstituteVarsInString(Tempstr,"http://$(ID)",Vars,0);
 	RetVal=DownloadItem(Tempstr, Title, Fmt, Flags);
break;

case TYPE_ANIMEHERE:
 	Tempstr=SubstituteVarsInString(Tempstr,"$(ID)",Vars,0);
  RetVal=DownloadPage(Tempstr,TYPE_ANIMEHERE_STAGE2, Title,Flags);
break;

case TYPE_KAVLIINSTITUTE_STAGE2:
case TYPE_SCIVEE:
case TYPE_BLIPTV_STAGE2:
case TYPE_GENERIC:
case TYPE_MYTOPCLIP:
case TYPE_PRINCETON:
case TYPE_TED:
case TYPE_NATGEO:
case TYPE_UCTV:
case TYPE_IZLESE:
case TYPE_REUTERS:
case TYPE_LIVELEAK:
case TYPE_IBTIMES:
case TYPE_SMH:
case TYPE_ACADEMIC_EARTH:
case TYPE_PHOTOBUCKET:
case TYPE_ALJAZEERA:
case TYPE_IVIEWTUBE:
case TYPE_WASHINGTONPOST:
case TYPE_CBSNEWS:
case TYPE_FRANCE24:
case TYPE_METATUBE:
case TYPE_MOTIONFEEDS:
case TYPE_GUARDIAN:
case TYPE_ESCAPIST_STAGE2:
case TYPE_REDORBIT_STAGE2:
case TYPE_REDBALCONY_STAGE2:
case TYPE_ASTRONOMYCOM_STAGE2:
case TYPE_ANIMEHERE_STAGE2:
 Tempstr=SubstituteVarsInString(Tempstr,"$(ID)",Vars,0);

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



// This is the main function that 'screen scrapes' a webpage looking for 
// information that it can use to get a video
int ExtractItemInfo(STREAM *S, int Type, char *URL, char *Title, int Flags)
{
char *Tempstr=NULL, *Token=NULL, *VarName=NULL, *Server=NULL;
ListNode *Vars=NULL;
char *ptr, *ptr2;
int MediaCount=0, i, Port;
int RetVal=FALSE, State=0;

#define GENERIC_TITLE_START "<title>"
#define GENERIC_TITLE_END "</title>"

ParseURL(URL,NULL,&Server,&Token,NULL,NULL,NULL,NULL);
Port=atoi(Token);

Vars=ListCreate();
SetVar(Vars,"Server",Server);


Tempstr=FormatStr(Tempstr,"%d",Port);
SetVar(Vars,"Port",Tempstr);
SetVar(Vars,"Title",Title);

	if (Flags & (FLAG_DEBUG2 | FLAG_DEBUG3)) fprintf(stderr,"\n------- DOWNLOADING DOCUMENT ------\n");
Tempstr=STREAMReadLine(Tempstr, S);
while (Tempstr)
{
	StripTrailingWhitespace(Tempstr);
	StripLeadingWhitespace(Tempstr);
	
	if (Flags & (FLAG_DEBUG2 | FLAG_DEBUG3)) fprintf(stderr,"%s\n",Tempstr);
switch (Type)
{

case TYPE_YOUTUBE:
//#define YOUTUBE_PTR "new SWFObject(\"/player2.swf?"

//#define YOUTUBE_PTR "var swfArgs = {"
#define YOUTUBE_DIV "url_encoded_fmt_stream_map="
#define YOUTUBE_TITLE_START "&title="
#define YOUTUBE_TITLE_END "&"

	if (strstr(Tempstr,YOUTUBE_TITLE_START))
	{
		GenericExtractFromLine(Tempstr, "Title",YOUTUBE_TITLE_START, YOUTUBE_TITLE_END, Vars,EXTRACT_DEQUOTE);
	}


	if (strstr(Tempstr,YOUTUBE_DIV))
	{
		if (StrLen(GetVar(Vars,"item:flv"))==0) 
		{
			GenericExtractFromLine(Tempstr, "yt:url_fmt",YOUTUBE_DIV, "&", Vars,EXTRACT_DEQUOTE);
			Tempstr=CopyStr(Tempstr,GetVar(Vars,"yt:url_fmt"));

			DecodeYouTubeFormats(Tempstr,Vars);
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
printf("PL! %s\n",Tempstr);
}
break;


case TYPE_METACAFE:
#define METACAFE_ITEM "&mediaData="
#define METACAFE_MEDIA_URL ",\"mediaURL\":\""
	if (strstr(Tempstr,GENERIC_TITLE_START))
	{
		GenericExtractFromLine(Tempstr, "Title",GENERIC_TITLE_START,GENERIC_TITLE_END, Vars,EXTRACT_DEQUOTE);
	}


	if (strstr(Tempstr,METACAFE_ITEM))
	{
		GenericExtractFromLine(Tempstr, "metacafe:mediaData",METACAFE_ITEM,"&", Vars, EXTRACT_DEQUOTE);
		ptr=GetVar(Vars,"metacafe:mediaData");
		GenericExtractFromLine(ptr, "item:mp4",METACAFE_MEDIA_URL,"\"", Vars, EXTRACT_DESLASHQUOTE|EXTRACT_GUESSTYPE);
	}
break;


case TYPE_BLIPTV:
#define BLIPTV_LINE "<link rel=\"alternate\" type=\"application/rss+xml\""
#define BLIPTV_ITEM_START "href=\""
#define BLIPTV_ITEM_END "\""
	ptr=strstr(Tempstr,BLIPTV_LINE);
	if (ptr)
	{
		GenericExtractFromLine(Tempstr, "ID",BLIPTV_ITEM_START,BLIPTV_ITEM_END,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
	}
break;

case TYPE_BLIPTV_STAGE2:
#define BLIP_SOURCE_LINE "blip:role=\"Source\""
#define BLIP_LD_LINE "blip:role=\"Blip LD\""
#define BLIP_SD_LINE "blip:role=\"Blip SD\""
#define BLIP_HD_LINE "blip:role=\"Blip HD"

		if (strstr(Tempstr,BLIP_SOURCE_LINE)) BlipTVExtractFromLine(Tempstr,Vars);
		if (strstr(Tempstr,BLIP_LD_LINE)) BlipTVExtractFromLine(Tempstr,Vars);
		if (strstr(Tempstr,BLIP_SD_LINE)) BlipTVExtractFromLine(Tempstr,Vars);
		if (strstr(Tempstr,BLIP_HD_LINE)) BlipTVExtractFromLine(Tempstr,Vars);
break;


case TYPE_BREAK_COM:
#define BREAK_ITEM_START "videoPath: '"
#define BREAK_EXTRA_START "icon: '"
#define BREAK_END "'"
#define BREAK_TITLE "sVidTitle: '"


	ptr=strstr(Tempstr,BREAK_ITEM_START);
	if (ptr) GenericExtractFromLine(Tempstr, "item:flv",BREAK_ITEM_START,BREAK_END,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);

	ptr=strstr(Tempstr,BREAK_EXTRA_START);
	if (ptr) 
	{
		GenericExtractFromLine(Tempstr, "Extra",BREAK_EXTRA_START,BREAK_END,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
		ptr=GetVar(Vars,"item:flv");
		Tempstr=MCopyStr(Tempstr,ptr,"?",GetVar(Vars,"Extra"),NULL);
		SetVar(Vars,"item:flv",Tempstr);
	}
	
	ptr=strstr(Tempstr,BREAK_TITLE);
	if (ptr) GenericExtractFromLine(Tempstr, "Title",BREAK_TITLE,BREAK_END,Vars,0);


break;



case TYPE_EHOW:
#define EHOW_ITEM "\"source\":\""
#define EHOW_ITEM_END "\""
#define EHOW_HD_ITEM "\"sourcehd\":\""
#define EHOW_HD_ITEM_END "\""
#define EHOW_TITLE "<h1 class=\"Heading1a\">"
#define EHOW_TITLE_END "</h1>"
#define EHOW_ITEM2 "showPlayer({"

	if (strstr(Tempstr,EHOW_ITEM))
	{
		GenericExtractFromLine(Tempstr, "item:flv",EHOW_ITEM,EHOW_ITEM_END,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
	}

	if (strstr(Tempstr,EHOW_HD_ITEM))
	{
		GenericExtractFromLine(Tempstr, "item:flv:hd",EHOW_HD_ITEM,EHOW_HD_ITEM_END,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
	}


	ptr=strstr(Tempstr,EHOW_ITEM2);
	if (ptr)
	{
		EhowExtractShowPlayer(S,ptr,Vars);
	}


	ptr=strstr(Tempstr,EHOW_TITLE);
	if (ptr)
	{
		GenericExtractFromLine(Tempstr, "Title",EHOW_TITLE,EHOW_TITLE_END,Vars,EXTRACT_DEQUOTE);
	}
break;

case TYPE_EHOW_STAGE2:
#define EHOW_STAGE2_ITEM "source="
#define EHOW_STAGE2_ITEM_END "&"

	ptr=strstr(Tempstr,EHOW_STAGE2_ITEM);
	if (ptr)
	{
		GenericExtractFromLine(Tempstr, "item:flv",EHOW_STAGE2_ITEM,EHOW_STAGE2_ITEM_END,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
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


case TYPE_VIDEOJUG:
#define VIDEOJUG_ITEM "type=\"application/xml+oembed\" href=\""
#define VIDEOJUG_ITEM_END "\""
#define VIDEOJUG_TITLE "<meta property=\"og:title\" content=\""
#define VIDEOJUG_TITLE_END "\""

	ptr=strstr(Tempstr,VIDEOJUG_ITEM);
	if (ptr)
	{
		GenericExtractFromLine(Tempstr, "ID",VIDEOJUG_ITEM,VIDEOJUG_ITEM_END,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
	}

	ptr=strstr(Tempstr,VIDEOJUG_TITLE);
	if (ptr)
	{
		GenericExtractFromLine(Tempstr, "Title",VIDEOJUG_TITLE,VIDEOJUG_TITLE_END,Vars,EXTRACT_DEQUOTE);
	}
break;

case TYPE_VIDEOJUG_STAGE2:
#define VIDEOJUG_S2_LINE "<html>&lt;iframe"
#define VIDEOJUG_S2_ITEM "src=\""
#define VIDEOJUG_S2_ITEM_END "\""

  if (strstr(Tempstr,VIDEOJUG_S2_LINE))
  {
    GenericExtractFromLine(Tempstr, "ID",VIDEOJUG_S2_ITEM,VIDEOJUG_S2_ITEM_END,Vars,EXTRACT_NOSPACES);
  }
break;

case TYPE_VIDEOJUG_STAGE3:
#define VIDEOJUG_S3_LINE "var html5Embed ="
#define VIDEOJUG_S3_ITEM "src=\""
#define VIDEOJUG_S3_ITEM_END "\""

  if (strstr(Tempstr,VIDEOJUG_S3_LINE))
  {
    GenericExtractFromLine(Tempstr, "ID",VIDEOJUG_S3_ITEM,VIDEOJUG_S3_ITEM_END,Vars,EXTRACT_NOSPACES);
  }
break;



case TYPE_DAILYMOTION:
#define DAILYMOTION_ITEM "oembed?url="
#define DAILYMOTION_ITEM_END "&format=xml"
#define DAILYMOTION_TITLE_START "<meta property=\"og:title\" content=\""
#define DAILYMOTION_TITLE_END "\""


  if (strstr(Tempstr,DAILYMOTION_TITLE_START))
  {
    GenericExtractFromLine(Tempstr, "Title",DAILYMOTION_TITLE_START,DAILYMOTION_TITLE_END,Vars, EXTRACT_DEQUOTE | EXTRACT_DEHTMLQUOTE);
  }


  if (strstr(Tempstr,DAILYMOTION_ITEM))
  {
    GenericExtractFromLine(Tempstr, "ID",DAILYMOTION_ITEM,DAILYMOTION_ITEM_END,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
  }
break;


case TYPE_DAILYMOTION_STAGE2:
#define DAILYMOTION_S2_ITEM "iframe src=\""
#define DAILYMOTION_S2_ITEM_END "\""

  if (strstr(Tempstr,DAILYMOTION_S2_ITEM))
  {
    GenericExtractFromLine(Tempstr, "ID",DAILYMOTION_S2_ITEM,DAILYMOTION_S2_ITEM_END,Vars,EXTRACT_NOSPACES);
  }
break;

case TYPE_DAILYMOTION_STAGE3:
#define DAILYMOTION_S3_ITEM "stream_h264_url\":\""
#define DAILYMOTION_S3_LD_ITEM "stream_h264_ld_url\":\""
#define DAILYMOTION_S3_HD_ITEM "stream_h264_hd_url\":\""
#define DAILYMOTION_S3_ITEM_END "\""

  if (strstr(Tempstr,DAILYMOTION_S3_ITEM))
  {
    GenericExtractFromLine(Tempstr, "dailymotion:tmp",DAILYMOTION_S3_ITEM,DAILYMOTION_S3_ITEM_END,Vars,EXTRACT_NOSPACES| EXTRACT_DESLASHQUOTE);
		DecodeDailyMotionFormats(GetVar(Vars,"dailymotion:tmp"), Vars);
  }

  if (strstr(Tempstr,DAILYMOTION_S3_LD_ITEM))
  {
    GenericExtractFromLine(Tempstr, "dailymotion:tmp",DAILYMOTION_S3_LD_ITEM,DAILYMOTION_S3_ITEM_END,Vars,EXTRACT_NOSPACES| EXTRACT_DESLASHQUOTE);
		DecodeDailyMotionFormats(GetVar(Vars,"dailymotion:tmp"), Vars);
  }

  if (strstr(Tempstr,DAILYMOTION_S3_HD_ITEM))
  {
    GenericExtractFromLine(Tempstr, "dailymotion:tmp",DAILYMOTION_S3_HD_ITEM,DAILYMOTION_S3_ITEM_END,Vars,EXTRACT_NOSPACES| EXTRACT_DESLASHQUOTE);
		DecodeDailyMotionFormats(GetVar(Vars,"dailymotion:tmp"), Vars);
  }
break;


case TYPE_VBOX7:
#define VBOX7_ITEM "so.addVariable(\"vid\", \""
#define VBOX7_ITEM_END "\");"

if (strstr(Tempstr,VBOX7_ITEM))
{
		GenericExtractFromLine(Tempstr, "item:flv",VBOX7_ITEM,VBOX7_ITEM_END,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
}

if (strstr(Tempstr,GENERIC_TITLE_START))
{
		GenericExtractFromLine(Tempstr, "Title",GENERIC_TITLE_START,GENERIC_TITLE_END,Vars,EXTRACT_DEQUOTE);
}
break;


case TYPE_TED:
#define TED_ITEM_LINE "<a id=\"no-flash-video-download\""
#define TED_ITEM_START "<a id=\"no-flash-video-download\" href=\""
#define TED_ITEM_END "\""

#define TED2_ITEM_LINE "name=&quot;flashvars&quot; value=&quot;vu="
#define TED2_ITEM_START "name=&quot;flashvars&quot; value=&quot;vu="
#define TED2_ITEM_END "&amp;"


if (strstr(Tempstr,TED_ITEM_LINE))
{
	GenericExtractFromLine(Tempstr, "item:mp4",TED_ITEM_START,TED_ITEM_END,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
}


if (strstr(Tempstr,TED2_ITEM_LINE))
{
	GenericExtractFromLine(Tempstr, "item:mp4:alt",TED2_ITEM_START,TED2_ITEM_END,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
}


if (strstr(Tempstr,GENERIC_TITLE_START))
{
		GenericExtractFromLine(Tempstr, "Title",GENERIC_TITLE_START,GENERIC_TITLE_END,Vars,EXTRACT_DEQUOTE);
}
break;


case TYPE_MYVIDEO:
#define MYVIDEO_URL_START "link rel='image_src' href='"
#define MYVIDEO_URL_END "/thumbs"
#define MYVIDEO_VIDID_END "_"

if (strstr(Tempstr,MYVIDEO_URL_START))
{
		ptr=GenericExtractFromLine(Tempstr, "MyVidURL",MYVIDEO_URL_START,MYVIDEO_URL_END,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
		ptr=GenericExtractFromLine(ptr, "item:flv","/",MYVIDEO_VIDID_END,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
}


if (strstr(Tempstr,GENERIC_TITLE_START))
{
		GenericExtractFromLine(Tempstr, "Title",GENERIC_TITLE_START,GENERIC_TITLE_END,Vars,EXTRACT_DEQUOTE);
}
break;



case TYPE_YALE:

#define YALE_ITEM_LINE "<a href=\"http://openmedia.yale.edu/cgi-bin/open_yale/media_downloader.cgi?file="
#define YALE_ITEM_START "a href=\""
#define YALE_ITEM_END "\""

#define YALE_TYPE_START "id=\""

if (strstr(Tempstr,YALE_ITEM_LINE))
{
		GenericExtractFromLine(Tempstr, "YI_TYPE",YALE_TYPE_START,YALE_ITEM_END,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);

		Token=CopyStr(Token,"");
		ptr=GetVar(Vars,"YI_TYPE");
		if (ptr)
		{
			if (strcmp(ptr,"course_media_audio")==0) Token=CopyStr(Token,"item:mp3");
			if (strcmp(ptr,"course_media_high")==0) Token=CopyStr(Token,"item:mov:HD");
			if (strcmp(ptr,"course_media_low")==0) Token=CopyStr(Token,"item:mov:LD");
		}
		GenericExtractFromLine(Tempstr, Token,YALE_ITEM_START,YALE_ITEM_END,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
		printf("%s %s\n",Token,GetVar(Vars,Token));
}


if (strstr(Tempstr,GENERIC_TITLE_START))
{
		GenericExtractFromLine(Tempstr, "Title",GENERIC_TITLE_START,GENERIC_TITLE_END,Vars,EXTRACT_DEQUOTE);
}

break;

case TYPE_REDBALCONY:
#define REDBALCONY_ITEM_START "playlist\":\""
#define REDBALCONY_ITEM_END "\""

if (strstr(Tempstr,REDBALCONY_ITEM_START))
{
		GenericExtractFromLine(Tempstr, "ID",REDBALCONY_ITEM_START,REDBALCONY_ITEM_END,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES | EXTRACT_GUESSTYPE);
}


if (strstr(Tempstr,GENERIC_TITLE_START))
{
		GenericExtractFromLine(Tempstr, "Title",GENERIC_TITLE_START,GENERIC_TITLE_END,Vars,EXTRACT_DEQUOTE);
}

break;

case TYPE_REDBALCONY_STAGE2:
#define REDBALCONY_S2_VID_LINE "medium=\"video\""
#define REDBALCONY_S2_ITEM_START " url=\""
#define REDBALCONY_S2_ITEM_END "\""

if (strstr(Tempstr,REDBALCONY_S2_VID_LINE))
{
		GenericExtractFromLine(Tempstr, "item:flv",REDBALCONY_S2_ITEM_START,REDBALCONY_S2_ITEM_END,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES );

}

break;



case TYPE_MEFEEDIA:
#define MEFEEDIA_FIND  "<li class=\"videosource\">"
#define MEFEEDIA_ITEM_START "href=\""
#define MEFEEDIA_ITEM_END "\""

ptr=strstr(Tempstr,MEFEEDIA_FIND);
if (ptr)
{
		GenericExtractFromLine(ptr, "item:reference",MEFEEDIA_ITEM_START,MEFEEDIA_ITEM_END,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
}


if (strstr(Tempstr,GENERIC_TITLE_START))
{
		GenericExtractFromLine(Tempstr, "Title",GENERIC_TITLE_START,GENERIC_TITLE_END,Vars,EXTRACT_DEQUOTE);
}

break;

case TYPE_IVIEWTUBE:
//#define IVIEWTUBE_ITEM_START "('ltas.mediaid','"
//#define IVIEWTUBE_ITEM_END "'"

#define IVIEWTUBE_TITLE_START "name=\"flname\" value=\""
#define IVIEWTUBE_TITLE_END "\""

#define IVIEWTUBE_ITEM_START "http://www.iviewtube.com/player/player.swf?file="
#define IVIEWTUBE_ITEM_END "&"

if (strstr(Tempstr,IVIEWTUBE_ITEM_START))
{
		GenericExtractFromLine(Tempstr, "item:flv",IVIEWTUBE_ITEM_START,IVIEWTUBE_ITEM_END,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES | EXTRACT_GUESSTYPE);
}


if (strstr(Tempstr,GENERIC_TITLE_START))
{
		GenericExtractFromLine(Tempstr, "Title",GENERIC_TITLE_START,GENERIC_TITLE_END,Vars,EXTRACT_DEQUOTE);
}

break;



case TYPE_MOBANGO:
#define MOBANGO_EXT_START "extension="
#define MOBANGO_EXT_END "&"
#define MOBANGO_ITEM_START "href=\""
#define MOBANGO_ITEM_END "\""

if (strstr(Tempstr,MOBANGO_EXT_START))
{
		GenericExtractFromLine(Tempstr, "extension",MOBANGO_EXT_START,MOBANGO_EXT_END,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
		ptr=GetVar(Vars,"extension");

		Token=MCopyStr(Token,"item:",ptr,NULL);
		GenericExtractFromLine(Tempstr, Token,MOBANGO_ITEM_START,MOBANGO_ITEM_END,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);

		ptr=GetVar(Vars,Token);
		ptr=strstr(ptr,"title=");
		if (ptr)
		{
			ptr+=6;
			GetToken(ptr,"&",&Tempstr,0);
			SetVar(Vars,"Title",Tempstr);
		}
	
		ptr=GetVar(Vars,Token);
		ptr=strstr(ptr,"sendtomobile=");
		if (ptr) *ptr='\0';


		
}

break;


#define IZLESE_ITEM_START "file=http"
#define IZLESE_ITEM_END "&"
#define IZLESE_TITLE_START "<h1>"
#define IZLESE_TITLE_END "</h1>"
#define IZLESE_TITLE2_START "<title>"
#define IZLESE_TITLE2_END "</title>"

case TYPE_IZLESE:
if (strstr(Tempstr,IZLESE_ITEM_START) && strstr(Tempstr,IZLESE_ITEM_END))
{
		GenericExtractFromLine(Tempstr, "tmp",IZLESE_ITEM_START,IZLESE_ITEM_END,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
		ptr=GetVar(Vars,"tmp");
		if (ptr)
		{
			//put 'http' back on
			Tempstr=MCopyStr(Tempstr,"http",ptr,NULL);
			
		}

	if (strstr(ptr,"youtube"))
	{
		SetVar(Vars,"item:reference",Tempstr);
	}
	else 
	{
		SetVar(Vars,"item:flv",Tempstr);
	}

}


if (strstr(Tempstr,IZLESE_TITLE_START))
{
		GenericExtractFromLine(Tempstr, "Title",IZLESE_TITLE_START,IZLESE_TITLE_END,Vars,EXTRACT_DEQUOTE);
}

if (strstr(Tempstr,IZLESE_TITLE2_START))
{
		GenericExtractFromLine(Tempstr, "Title",IZLESE_TITLE2_START,IZLESE_TITLE2_END,Vars,EXTRACT_DEQUOTE);
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


#define AE_YT_ITEM1_START "href=\"http://www.youtube.com/watch?v="
#define AE_YT_ITEM1_END "\""

case TYPE_ACADEMIC_EARTH:
	ptr=strstr(Tempstr,AE_YT_ITEM1_START);
	if (ptr)
	{
		GenericExtractFromLine(Tempstr, "item:reference",AE_YT_ITEM1_START,AE_YT_ITEM1_END,Vars, EXTRACT_NOSPACES);

		Tempstr=MCopyStr(Tempstr,"http://youtube.com/watch?v=",GetVar(Vars,"item:reference"),NULL);
		SetVar(Vars,"item:reference",Tempstr);
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


#define LIVELEAK_ITEM_START "file: \""
#define LIVELEAK_ITEM_END "'\""
case TYPE_LIVELEAK:
ptr=strstr(Tempstr,LIVELEAK_ITEM_START);
if (ptr)
{
	GenericExtractFromLine(Tempstr, "item:flv",LIVELEAK_ITEM_START,LIVELEAK_ITEM_END,Vars,EXTRACT_WITHIN_QUOTES | EXTRACT_NOSPACES | EXTRACT_GUESSTYPE);
}

if (strstr(Tempstr,GENERIC_TITLE_START))
{
		GenericExtractFromLine(Tempstr, "Title",GENERIC_TITLE_START,GENERIC_TITLE_END,Vars,EXTRACT_DEQUOTE);
}
break;



//#define IBTIMES_ITEM_START "<meta itemprop=\"contentURL\" content=\""
#define IBTIMES_ITEM_START "file: \""
#define IBTIMES_ITEM_END "\""
#define IBTIMES_ITEM2_START "{type:\"html5\",config:{file:\""
#define IBTIMES_ITEM3_START "{type:\"download\",config:{file:\""

case TYPE_IBTIMES:
ptr=strstr(Tempstr,IBTIMES_ITEM_START);
if (ptr) GenericExtractFromLine(Tempstr, "ID",IBTIMES_ITEM_START,IBTIMES_ITEM_END,Vars, EXTRACT_GUESSTYPE);
ptr=strstr(Tempstr,IBTIMES_ITEM2_START);
if (ptr) GenericExtractFromLine(Tempstr, "ID",IBTIMES_ITEM2_START,IBTIMES_ITEM_END,Vars, EXTRACT_GUESSTYPE);
ptr=strstr(Tempstr,IBTIMES_ITEM3_START);
if (ptr) GenericExtractFromLine(Tempstr, "ID",IBTIMES_ITEM3_START,IBTIMES_ITEM_END,Vars, EXTRACT_GUESSTYPE);



if (strstr(Tempstr,GENERIC_TITLE_START))
{
	GenericExtractFromLine(Tempstr, "Title",GENERIC_TITLE_START,GENERIC_TITLE_END,Vars,EXTRACT_DEQUOTE);
}
break;


#define SMH_ITEM_START "file\": \""
#define SMH_ITEM_END "\""
#define SMH_TRIGGER "\"playlist\": ["

case TYPE_SMH:

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

if (strstr(Tempstr,GENERIC_TITLE_START))
{
	GenericExtractFromLine(Tempstr, "Title",GENERIC_TITLE_START,GENERIC_TITLE_END,Vars,EXTRACT_DEQUOTE);
}
break;



case TYPE_WASHINGTONPOST:
#define WASHINGTONPOST_ITEM_LINE "mediaQueryString"
#define WASHINGTONPOST_ITEM_START "flvURL="
#define WASHINGTONPOST_ITEM_END "&"

#define WASHINGTONPOST_JSON_START "jsonURL=\""
#define WASHINGTONPOST_JSON_END "\""

#define WASHINGTONPOST_JSONP_START "name=\"jsonpURL\" value=\""
#define WASHINGTONPOST_JSONP_END "\""


if (strstr(Tempstr,WASHINGTONPOST_ITEM_LINE) && (StrLen(GetVar(Vars,"item:flv"))==0))
{
		GenericExtractFromLine(Tempstr, "item:flv",WASHINGTONPOST_ITEM_START,WASHINGTONPOST_ITEM_END,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
		Tempstr=MCopyStr(Tempstr,"http://",Server,GetVar(Vars,"item:flv"),NULL);
		SetVar(Vars,"item:flv",Tempstr);
}

if (strstr(Tempstr,WASHINGTONPOST_JSON_START))
{
		GenericExtractFromLine(Tempstr, "ID",WASHINGTONPOST_JSON_START,WASHINGTONPOST_JSON_END,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
		Type=TYPE_WASHINGTONPOST_JSON;

		ptr=GetVar(Vars,"ID");
		if (*ptr=='/')
		{
		Tempstr=MCopyStr(Tempstr,"http://",Server,GetVar(Vars,"ID"),NULL);
		SetVar(Vars,"ID",Tempstr);
		}
}

if (strstr(Tempstr,WASHINGTONPOST_JSONP_START))
{
		GenericExtractFromLine(Tempstr, "ID",WASHINGTONPOST_JSONP_START,WASHINGTONPOST_JSONP_END,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
		Type=TYPE_WASHINGTONPOST_JSON;
		Tempstr=MCopyStr(Tempstr,"http://",Server,GetVar(Vars,"ID"),NULL);
		SetVar(Vars,"ID",Tempstr);
}


if (strstr(Tempstr,GENERIC_TITLE_START))
{
		GenericExtractFromLine(Tempstr, "Title",GENERIC_TITLE_START,GENERIC_TITLE_END,Vars,EXTRACT_DEQUOTE);
}

break;

case TYPE_WASHINGTONPOST_STAGE2:
#define WASHINGTONPOST_SERVER_START "staticServer\":\""
#define WASHINGTONPOST_SERVER_END "\""
#define WASHINGTONPOST_ITEM2_START "flvURL\": \""
#define WASHINGTONPOST_ITEM2_END "\""

if (strstr(Tempstr,WASHINGTONPOST_SERVER_START))
{
		GenericExtractFromLine(Tempstr, "server",WASHINGTONPOST_SERVER_START,WASHINGTONPOST_SERVER_END,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
}

if (strstr(Tempstr,WASHINGTONPOST_ITEM2_START))
{
		GenericExtractFromLine(Tempstr, "flvurl",WASHINGTONPOST_ITEM2_START,WASHINGTONPOST_ITEM2_END,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
}
		Tempstr=MCopyStr(Tempstr,"http://",Server,GetVar(Vars,"item:flv"),NULL);
		SetVar(Vars,"item:flv",Tempstr);

break;



case TYPE_CBSNEWS:
ExtractCBSNews(Vars, Tempstr);
if (strstr(Tempstr,GENERIC_TITLE_START))
{
		GenericExtractFromLine(Tempstr, "Title",GENERIC_TITLE_START,GENERIC_TITLE_END,Vars,EXTRACT_DEQUOTE);
}

break;


case TYPE_FRANCE24:
#define FRANCE24_ITEM_START "meta property=\"og:video\" content=\""
#define FRANCE24_ITEM_END "\""
#define FRANCE24_ITEM2_START "file="
#define FRANCE24_ITEM2_END "&"

if (strstr(Tempstr,FRANCE24_ITEM_START) )
{
		GenericExtractFromLine(Tempstr, "item:flv",FRANCE24_ITEM_START,FRANCE24_ITEM_END,Vars,EXTRACT_GUESSTYPE);
}

if (strstr(Tempstr,FRANCE24_ITEM2_START) )
{
		GenericExtractFromLine(Tempstr, "item:flv",FRANCE24_ITEM2_START,FRANCE24_ITEM2_END,Vars,EXTRACT_GUESSTYPE);
}



if (strstr(Tempstr,GENERIC_TITLE_START))
{
		GenericExtractFromLine(Tempstr, "Title",GENERIC_TITLE_START,GENERIC_TITLE_END,Vars,0);
}

break;


case TYPE_EURONEWS:
#define EURONEWS_ITEM_START "videofile:\""
#define EURONEWS_BULLETIN_START "vid0:\""
#define EURONEWS_ITEM_END "\""

if (strstr(Tempstr,EURONEWS_ITEM_START) )
{
		//don't try using 'guesstype' here, as we stick .flv on later, and need
		//to be able to find 'ID', not 'item:guessed'
		GenericExtractFromLine(Tempstr, "ID",EURONEWS_ITEM_START,EURONEWS_ITEM_END,Vars,0);
}

if (strstr(Tempstr,EURONEWS_BULLETIN_START) )
{
		//don't try using 'guesstype' here, as we stick .flv on later, and need
		//to be able to find 'ID', not 'item:guessed'
		GenericExtractFromLine(Tempstr, "ID",EURONEWS_BULLETIN_START,EURONEWS_ITEM_END,Vars,0);
}

if (strstr(Tempstr,GENERIC_TITLE_START))
{
		GenericExtractFromLine(Tempstr, "Title",GENERIC_TITLE_START,GENERIC_TITLE_END,Vars,0);
}

break;



case TYPE_METATUBE:
#define METATUBE_ITEM_START "flashvars.src = \""
#define METATUBE_ITEM_END "\";"
#define METATUBE_ITEM2_START "<video src=\""
#define METATUBE_ITEM2_END "\""

if (strstr(Tempstr,METATUBE_ITEM_START) )
{
		GenericExtractFromLine(Tempstr, "item:flv",METATUBE_ITEM_START,METATUBE_ITEM_END,Vars,EXTRACT_GUESSTYPE);
}

if (strstr(Tempstr,METATUBE_ITEM2_START) )
{
		GenericExtractFromLine(Tempstr, "item:flv",METATUBE_ITEM2_START,METATUBE_ITEM2_END,Vars,EXTRACT_GUESSTYPE);
}

if (strstr(Tempstr,GENERIC_TITLE_START))
{
		GenericExtractFromLine(Tempstr, "Title",GENERIC_TITLE_START,GENERIC_TITLE_END,Vars,0);
}

break;

case TYPE_MOTIONFEEDS:
#define MOTIONFEEDS_ITEM_LINE "param name=\"movie\" "
#define MOTIONFEEDS_ITEM_START1 "file="
#define MOTIONFEEDS_ITEM_START2 "value="
#define MOTIONFEEDS_ITEM_START3 "http://www.youtube.com/watch?v="
#define MOTIONFEEDS_ITEM_END "&"

if (strstr(Tempstr,MOTIONFEEDS_ITEM_LINE) )
{
if (strstr(Tempstr,MOTIONFEEDS_ITEM_START1) ) GenericExtractFromLine(Tempstr, "item:flv",MOTIONFEEDS_ITEM_START1,MOTIONFEEDS_ITEM_END,Vars,0);
else if (strstr(Tempstr,MOTIONFEEDS_ITEM_START2) ) GenericExtractFromLine(Tempstr, "item:reference",MOTIONFEEDS_ITEM_START2,MOTIONFEEDS_ITEM_END,Vars,0);
}


if (strstr(Tempstr,GENERIC_TITLE_START))
{
		GenericExtractFromLine(Tempstr, "Title",GENERIC_TITLE_START,GENERIC_TITLE_END,Vars,0);
}

if (strstr(Tempstr,MOTIONFEEDS_ITEM_START3) ) 
{
GenericExtractFromLine(Tempstr, "item:reference",MOTIONFEEDS_ITEM_START3,MOTIONFEEDS_ITEM_END,Vars,0);
Tempstr=MCopyStr(Tempstr,MOTIONFEEDS_ITEM_START3,GetVar(Vars,"item:reference"),NULL);
SetVar(Vars,"item:reference",Tempstr);
}

break;



case TYPE_ESCAPIST:
#define ESCAPIST_ITEM_START "swf?config="
#define ESCAPIST_ITEM_END "&"
#define ESCAPIST_TITLE_START "<meta property=\"og:title\" content=\""
#define ESCAPIST_TITLE_END "\""

if (strstr(Tempstr,ESCAPIST_ITEM_START) )
{
 GenericExtractFromLine(Tempstr, "ID",ESCAPIST_ITEM_START,ESCAPIST_ITEM_END,Vars,EXTRACT_DEQUOTE);
}

if (strstr(Tempstr,ESCAPIST_TITLE_START) ) 
{
GenericExtractFromLine(Tempstr, "Title",ESCAPIST_TITLE_START,ESCAPIST_TITLE_END,Vars,0);
}
break;

case TYPE_ESCAPIST_STAGE2:
/*
#define ESCAPIST_STAGE2_ITEM_START "'},{'url':'"
#define ESCAPIST_STAGE2_ITEM_END "'"
if (strstr(Tempstr,ESCAPIST_STAGE2_ITEM_START) ) GenericExtractFromLine(Tempstr, "item:mp4",ESCAPIST_STAGE2_ITEM_START,ESCAPIST_STAGE2_ITEM_END,Vars,0);

*/

ParseFlashPlaylist(Tempstr, Vars);
break;


case TYPE_GUARDIAN:
#define GUARDIAN_ITEM1_START "'src': '"
#define GUARDIAN_ITEM1_END "'"
#define GUARDIAN_ITEM2_START "file: \""
#define GUARDIAN_ITEM2_END "\""


if (strstr(Tempstr,GUARDIAN_ITEM1_START) )
{
		GenericExtractFromLine(Tempstr, "item:mp4",GUARDIAN_ITEM1_START,GUARDIAN_ITEM1_END,Vars,EXTRACT_GUESSTYPE);
}

if (strstr(Tempstr,GUARDIAN_ITEM2_START) )
{
		GenericExtractFromLine(Tempstr, "item:mp4",GUARDIAN_ITEM2_START,GUARDIAN_ITEM2_END,Vars,EXTRACT_GUESSTYPE);
}



if (strstr(Tempstr,GENERIC_TITLE_START))
{
		GenericExtractFromLine(Tempstr, "Title",GENERIC_TITLE_START,GENERIC_TITLE_END,Vars,0);
}


break;

case TYPE_REDORBIT:
#define REDORBIT_ITEM_START "playlist="
#define REDORBIT_ITEM_END "'"

if (strstr(Tempstr,REDORBIT_ITEM_START) )
{
		GenericExtractFromLine(Tempstr, "ID",REDORBIT_ITEM_START,REDORBIT_ITEM_END,Vars,EXTRACT_DEQUOTE);
}


if (strstr(Tempstr,GENERIC_TITLE_START))
{
		GenericExtractFromLine(Tempstr, "Title",GENERIC_TITLE_START,GENERIC_TITLE_END,Vars,0);
}


break;

case TYPE_REDORBIT_STAGE2:
#define REDORBIT2_ITEM_START "<media:content url=\""
#define REDORBIT2_ITEM_END "\""

if (strstr(Tempstr,REDORBIT2_ITEM_START) )
{
		GenericExtractFromLine(Tempstr, "item:flv",REDORBIT2_ITEM_START,REDORBIT2_ITEM_END,Vars,EXTRACT_GUESSTYPE);
}
break;

case TYPE_SCIVEE:
#define SCIVEE_ITEM_START "<param name=\"flashvars\" value=\"id="
#define SCIVEE_ITEM_END "&"
if (strstr(Tempstr,SCIVEE_ITEM_START) )
{
		GenericExtractFromLine(Tempstr, "ID",SCIVEE_ITEM_START,SCIVEE_ITEM_END,Vars,0);
	 Tempstr=MCopyStr(Tempstr,"http://www.scivee.tv/assets/video/",GetVar(Vars,"ID"),NULL);
	SetVar(Vars,"item:flv",Tempstr);
	SetVar(Vars,"ID","");

}
else if (strstr(Tempstr,GENERIC_TITLE_START))
{
		GenericExtractFromLine(Tempstr, "Title",GENERIC_TITLE_START,GENERIC_TITLE_END,Vars,0);
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

case TYPE_BRITISHACADEMY:
#define BRITISHACADEMY_LINEDETECT "HearLecturePicture.gif"
#define BRITISHACADEMY_ITEMSTART "javascript:launch('"
#define BRITISHACADEMY_ITEMEND "'"

		if (strstr(Tempstr,BRITISHACADEMY_LINEDETECT)) GenericExtractFromLine(Tempstr, "ID",BRITISHACADEMY_ITEMSTART,BRITISHACADEMY_ITEMEND,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
break;

case TYPE_BRITISHACADEMY_STAGE2:
#define BRITISHACADEMY_S2_ITEMSTART "<param name=\"FileName\" value=\""
#define BRITISHACADEMY_S2_ITEMEND "\""

		if (strstr(Tempstr,BRITISHACADEMY_S2_ITEMSTART)) GenericExtractFromLine(Tempstr, "ID",BRITISHACADEMY_S2_ITEMSTART,BRITISHACADEMY_S2_ITEMEND,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
break;

case TYPE_KAVLIINSTITUTE:
 if (strstr(Tempstr,"rm/flashtv.html")) 
 {
		Tempstr=MCopyStr(Tempstr,URL,"/rm/flashtv.html",NULL);
		SetVar(Vars,"ID",Tempstr);
 }
 else if (strstr(Tempstr,"rm/flash.html")) 
 {
		Tempstr=MCopyStr(Tempstr,URL,"/rm/flash.html",NULL);
		SetVar(Vars,"ID",Tempstr);
 }
break;


case TYPE_KAVLIINSTITUTE_STAGE2:
#define KAVLI_ITEMSTART "file="
#define KAVLI_ITEMEND "&"

		if (strstr(Tempstr,KAVLI_ITEMSTART)) GenericExtractFromLine(Tempstr, "ID",KAVLI_ITEMSTART,KAVLI_ITEMEND,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
break;

case TYPE_DOTSUB:
#define DOTSUB_ITEMSTART "mediaUri = '"
#define DOTSUB_ITEMEND "'"
#define DOTSUB_SERVSTART "webAppUrl = '"
#define DOTSUB_TITLESTART "og:title\" content=\""
#define DOTSUB_TITLEEND "\""

		if (strstr(Tempstr,DOTSUB_ITEMSTART)) GenericExtractFromLine(Tempstr, "ID",DOTSUB_ITEMSTART,DOTSUB_ITEMEND,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
		if (strstr(Tempstr,DOTSUB_SERVSTART)) GenericExtractFromLine(Tempstr, "SERV",DOTSUB_SERVSTART,DOTSUB_ITEMEND,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
		if (strstr(Tempstr,DOTSUB_TITLESTART))
		{
		GenericExtractFromLine(Tempstr, "Title",DOTSUB_TITLESTART,DOTSUB_TITLEEND,Vars,0);
		}
break;

case TYPE_ASTRONOMYCOM:
#define ASTRONOMYCOM_ITEMSTART "http://kws.astronomy.com/generator.aspx?key="
#define ASTRONOMYCOM_ITEMEND "\""
#define ASTRONOMYCOM_TITLESTART "<span class=\"currentItem\">"
#define ASTRONOMYCOM_TITLEEND "</span>"

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
#define ASTRONOMYCOM_S2_ITEMSTART "so.addVariable(\"file\", \""
#define ASTRONOMYCOM_S2_ITEMEND "\""

		if (strstr(Tempstr,ASTRONOMYCOM_S2_ITEMSTART))
		{
			 GenericExtractFromLine(Tempstr, "ID",ASTRONOMYCOM_S2_ITEMSTART,ASTRONOMYCOM_ITEMEND,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
		}
	
break;

case TYPE_TEACHERTUBE:
#define TEACHERTUBE_ITEMSTART "'file': '"
#define TEACHERTUBE_ITEMEND "'"

	if (strstr(Tempstr,GENERIC_TITLE_START))
	{
		GenericExtractFromLine(Tempstr, "Title",GENERIC_TITLE_START,GENERIC_TITLE_END,Vars,EXTRACT_DEQUOTE);
	}

		if (strstr(Tempstr,TEACHERTUBE_ITEMSTART))
		{
			 GenericExtractFromLine(Tempstr, "ID",TEACHERTUBE_ITEMSTART,TEACHERTUBE_ITEMEND,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
		}
break;


case TYPE_DISCOVERY:
#define DISCOVERY_ITEMSTART "\"m3u8\": \""
#define DISCOVERY_ITEMEND "\""
#define DISCOVERY_TITLE_START "<meta property=\"og:title\" content=\""
#define DISCOVERY_TITLE_END "\""

	if (strstr(Tempstr,DISCOVERY_TITLE_START))
	{
		GenericExtractFromLine(Tempstr, "Title",DISCOVERY_TITLE_START,DISCOVERY_TITLE_END,Vars,EXTRACT_DEQUOTE);
	}

		if (strstr(Tempstr,DISCOVERY_ITEMSTART))
		{
			//Only get the first item
			if (StrLen(GetVar(Vars,"item:reference"))==0) GenericExtractFromLine(Tempstr, "item:reference",DISCOVERY_ITEMSTART,DISCOVERY_ITEMEND,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
		}
break;

case TYPE_BLOOMBERG:
#define BLOOMBERG_ITEMSTART "BLOOMBERG._fvid_id = \""
#define BLOOMBERG_ITEMEND "\""

	if (strstr(Tempstr,BLOOMBERG_ITEMSTART))
	{
		GenericExtractFromLine(Tempstr, "item:flv",BLOOMBERG_ITEMSTART,BLOOMBERG_ITEMEND,Vars,EXTRACT_DESLASHQUOTE | EXTRACT_NOSPACES);
	}

	if (strstr(Tempstr,GENERIC_TITLE_START))
	{
		GenericExtractFromLine(Tempstr, "Title",GENERIC_TITLE_START,GENERIC_TITLE_END,Vars,0);
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

case TYPE_ANIMEHERE:
//<p><iframe src="http://www.video44.net/gogo/?w=600&amp;h=438&amp;file=robotics_notes_-_01.flv&amp;sv=1" 
#define ANIMEHERE_ITEMHINT ".flv"
#define ANIMEHERE_ITEMSTART "<p><iframe src=\""
#define ANIMEHERE_ITEMEND "\""
#define ANIMEHERE_TITLE_START "<meta property=\"og:title\" content=\""
#define ANIMEHERE_TITLE_END "\""

	if (strstr(Tempstr,ANIMEHERE_ITEMHINT))
	{
		GenericExtractFromLine(Tempstr, "ID",ANIMEHERE_ITEMSTART,ANIMEHERE_ITEMEND,Vars,EXTRACT_DEHTMLQUOTE | EXTRACT_NOSPACES);
	}

	if (strstr(Tempstr,ANIMEHERE_TITLE_START))
	{
		GenericExtractFromLine(Tempstr, "Title",ANIMEHERE_TITLE_START,ANIMEHERE_TITLE_END,Vars,0);
	}

break;


case TYPE_ANIMEHERE_STAGE2:
#define ANIMEHERE_S2_ITEMSTART "file="
#define ANIMEHERE_S2_ITEMEND "&amp;"

	if (strstr(Tempstr,ANIMEHERE_S2_ITEMSTART))
	{
		GenericExtractFromLine(Tempstr, "item:flv",ANIMEHERE_S2_ITEMSTART,ANIMEHERE_S2_ITEMEND,Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
	}
break;

case TYPE_FUNNYORDIE:
#define FOD_ITEMSTART "<source src=\""
#define FOD_ITEMEND ".m3u8"
#define FOD_TITLE_START "title: \""
#define FOD_TITLE_END "\""

	if (strstr(Tempstr,FOD_ITEMSTART))
	{
		GenericExtractFromLine(Tempstr, "item:reference",FOD_ITEMSTART,FOD_ITEMEND,Vars,EXTRACT_DESLASHQUOTE | EXTRACT_NOSPACES);
		ptr=GetVar(Vars,"item:reference");
		if (ptr)
		{
			Tempstr=MCopyStr(Tempstr,ptr,".m3u8",NULL);
			SetVar(Vars,"item:reference",Tempstr);
		}
	}

	if (strstr(Tempstr,FOD_TITLE_START))
	{
		GenericExtractFromLine(Tempstr, "Title",FOD_TITLE_START,FOD_TITLE_END,Vars,0);
	}

break;


case TYPE_GOOGLE_URL:
		SetVar(Vars,"item:reference",URL);
break;



case TYPE_MYTOPCLIP:
case TYPE_PRINCETON:
case TYPE_UCTV:
case TYPE_GENERIC:
case TYPE_ALJAZEERA:

//some sites are actually just frontends to youtube
#define YOUTUBE_REFERENCE1 "http://www.youtube.com/watch?v="
#define YOUTUBE_REFERENCE2 "http://www.youtube.com/v/"

if (strstr(Tempstr,YOUTUBE_REFERENCE1))
{
		GenericExtractFromLine(Tempstr, "yt-tmp",YOUTUBE_REFERENCE1,"\"",Vars,EXTRACT_DEQUOTE | EXTRACT_NOSPACES);
		ptr=GetVar(Vars,"yt-tmp");
		if (StrLen(ptr)) Token=MCopyStr(Token,YOUTUBE_REFERENCE1,ptr,NULL);
		SetVar(Vars,"item:reference",Token);
		Token=CopyStr(Token,""); //So as later stages of this process don't
														 //pick up on it

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

for (i=0; i < ContainerTypes[i]; i++)
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


if (strstr(Tempstr,GENERIC_TITLE_START))
{
		GenericExtractFromLine(Tempstr, "Title",GENERIC_TITLE_START,GENERIC_TITLE_END,Vars,EXTRACT_DEQUOTE);
}

break;


}

  Tempstr=STREAMReadLine(Tempstr,S);
}

if (Flags & (FLAG_DEBUG2 | FLAG_DEBUG3)) fprintf(stderr,"\n------- END DOCUMENT ------\n\n");


if (MediaCount > 0) HandleMultipleMedia(Type,Server,Flags,Vars,MediaCount);
else
{
	if (StrLen(GetVar(Vars,"ID"))==0)
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

