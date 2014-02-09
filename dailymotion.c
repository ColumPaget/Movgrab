#include "dailymotion.h"


void DecodeDailyMotionFormats(char *Format, ListNode *Vars)
{
	if (strstr(Format,"FLV-320x240")) 
	{
		SetVar(Vars,"item:flv:320x240",Format);
	}
	else if (strstr(Format,"FLV-80x60")) 
	{
		SetVar(Vars,"item:flv:80x60",Format);
	}
	else if (strstr(Format,"ON2-848x480"))
	{
			SetVar(Vars,"item:on2:848x480",Format);
	}
	else if (strstr(Format,"ON2-320x240")) 
	{
			SetVar(Vars,"item:on2:320x240",Format);
	}
	else if (strstr(Format,"H264-848x480")) 
	{
		SetVar(Vars,"item:mp4-h264:848x480",Format);
	}
	else if (strstr(Format,"H264-512x384")) 
	{
			SetVar(Vars,"item:mp4-h264:512x384",Format);
	}
	else if (strstr(Format,"H264-320x240")) 
	{
			SetVar(Vars,"item:mp4-h264:320x240",Format);
	}
	else if (strstr(Format,"H264-1280x720")) 
	{
			SetVar(Vars,"item:mp4-h264:1280x720",Format);
	}
	else if (StrLen(Format)) fprintf(stderr,"Unknown DailyMotion Format: [%s]\n",Format);

}

