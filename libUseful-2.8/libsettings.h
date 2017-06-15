#ifndef LIBUSEFUL_SETTINGS
#define LIBUSEFUL_SETTINGS

#include "Vars.h"

/* These functions provide an interface for setting variables that */
/* are used by libUseful itself */

#define  LU_ATEXIT_REGISTERED 1
#define  LU_CONTAINER         2

extern int LibUsefulFlags;

#ifdef __cplusplus
extern "C" {
#endif


ListNode *LibUsefulValuesGetHead();
void LibUsefulSetValue(const char *Name, const char *Value);
const char *LibUsefulGetValue(const char *Name);
void LibUsefulAtExit();

#ifdef __cplusplus
};
#endif


#endif
