#ifndef LIBUSEFUL_MESSAGEBUS_H
#define LIBUSEFUL_MESSAGEBUS_H

#include "includes.h"
#include "defines.h"
#include "file.h"

#define MBUS_CONNECTION 0
#define MBUS_BROKER 1

#define MBUS_FAIL 0
#define MBUS_CONNECT 1
#define MBUS_CONNECT_RESULT 2
#define MBUS_SEND 3
#define MBUS_CLOSE 4


typedef struct
{
int Type;
int ConID;
int Result;
char *URL;
int DataLen;
char *Data;
void *UserData;
} TMBusMsg

#endif
