#include "Ip_v4_prefix.h"


int init_prefix(Ip_v4_prefix* prefix, unsigned int base, char mask)
{
    prefix->base = base;
    prefix->mask = mask;
    return 0;
}

unsigned int min_address(Ip_v4_prefix* prefix)
{
    return prefix->max_address;
}