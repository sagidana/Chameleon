#include "utils.h"

int change_page_permissions_of_address(void *addr, int permissions) 
{
    int page_size = getpagesize();
    addr -= (unsigned long)addr % page_size; // Align addr.

    if(mprotect(addr, page_size, permissions) == -1)
        return -1;
    return 0;
}