#include "libUseful.h"

main()
{
char *ptr;

CredsStoreAdd("test1", "user1", "pass1");
CredsStoreAdd("test2", "user2", "pass2");
CredsStoreAdd("test3", "user3", "pass3");
CredsStoreAdd("test4", "user4", "pass4");
ptr=CredsStoreGetSecret("test3", "user3");

printf("%s\n",ptr);
}
