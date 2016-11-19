#ifndef MOVGRAB_DOWNLOAD
#define MOVGRAB_DOWNLOAD

#include "common.h"

int DownloadItem(const char *URL, const char *Format, const char *Path, int Flags);
int DownloadPage(const char *Path, int Type, const char *Title, int Flags);

int TransferItem(STREAM *Con, const char *Title, const char *URL, const char *Format, double SegmentSize, double DocSize, double *BytesRead, int PrintName);

STREAM *ConnectAndRetryUntilDownload(const char *URL, int Flags, double BytesRead);

extern char *Proxy;
extern int PlayerLaunchPercent;

#endif
