#include "Single_container.h"
#include <stdlib.h>


Prefix_container CONTAINER = {.root = NULL};


int add(unsigned int base, char mask)
{
    return add_prefix(&CONTAINER, base, mask);
}


int del(unsigned int base, char mask)
{
    return del_prefix(&CONTAINER, base, mask);
}


char check(unsigned int ip)
{
    return check_for_prefix(&CONTAINER, ip);
}


void destroy()
{
    destroy_container(&CONTAINER);
}
