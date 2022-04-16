#include "Ip_v4_prefix.h"


int init_prefix(Ip_v4_prefix* prefix, unsigned int base, char mask)
{
    unsigned int bitmask = get_bitmask(mask);
    if (bitmask == 0xffffffff)
        return -1;
    if ((~bitmask & base) != 0)
        return -2;
    prefix->base = base;
    prefix->bitmask = bitmask;
    prefix->mask = mask;
    prefix->max_address = max_address(prefix);
    return 0;
}


unsigned int get_bitmask(char mask)
{
    if (mask < 0 || mask > 31)
        return 0xffffffff;
    return ((1 << mask) - 1) << (32 - mask);
}


unsigned int max_address(Ip_v4_prefix* prefix)
{
    return prefix->base | (~prefix->bitmask);
}