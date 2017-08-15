#ifndef __UTILS_H
#define __UTILS_H

#include <sys/mman.h>
#include <unistd.h>


/*
 * Given address, change the permisions of the relevant page to the desired permissions.
 */
int change_page_permissions_of_address(void *addr, int permissions);

#endif