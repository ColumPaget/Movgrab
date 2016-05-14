#include "libUseful.h"

main()
{
STREAM *S;
char *Tempstr=NULL;

S=STREAMOpenFile("/etc/services",STREAM_RDONLY | STREAM_MMAP);
Tempstr=STREAMReadLine(Tempstr, S);
while (Tempstr)
{
printf("%s",Tempstr);
Tempstr=STREAMReadLine(Tempstr, S);
}

DestroyString(Tempstr);
}
