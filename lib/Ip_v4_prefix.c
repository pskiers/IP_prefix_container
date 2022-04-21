#include "Ip_v4_prefix.h"


int init_prefix(Ip_v4_prefix* prefix, unsigned int base, char mask)
/*  A function to initialize ip prefix. Recomended way of initializing this struct.
    returns 0 if initialization succesful, otherwise returns -1 */
{
    unsigned int bitmask = get_bitmask(mask);
    if (bitmask == 0xffffffff)
        return -1;  // bad mask value
    if ((~bitmask & base) != 0) // significant part (with ones) of the base is longer than the mask - probably a mistake so better fail as soon as possible
        return -1;  // bad base
    prefix->base = base;
    prefix->bitmask = bitmask;
    prefix->mask = mask;
    return 0;
}


unsigned int get_bitmask(char mask)
/*  Calculate binary version of the bitmask from mask aka number of ones in the mask */
{
    if (mask < 0 || mask > 31)
        return 0xffffffff; // mask 0xffffffff used as an error value as it is not a valid mask anyway
    return ((1 << mask) - 1) << (32 - mask); // cool math trick, basically return 32 bits - first <mask> bits set to 1, rest to 0
}


unsigned int max_address(Ip_v4_prefix* prefix)
/*  Calculate the biggest address for the prefix */
{
    return prefix->base | (~prefix->bitmask);
}


int compare_prefixes(Ip_v4_prefix prefix1, Ip_v4_prefix prefix2)
/*  Compares two prefixes, returns -1 if prefix1 is bigger, 0 if prefixes equal, 1 if prefix2 is bigger */
{
    if (prefix1.base == prefix2.base && prefix1.mask == prefix2.mask)
        return 0;
    if (prefix1.base > prefix2.base ||
        (prefix1.base == prefix2.base && prefix1.mask > prefix2.mask ))
        return -1;
    return 1;
}


int compare_ip_address(Ip_v4_prefix prefix, unsigned int ip_address)
/*  Checks if prefix contains given address. Returns 0 if prefix contains address, returns -1 if
    address is smaller than the smallest address of the prefix, return 1 otherwise */
{
    unsigned int address_base = ip_address & prefix.bitmask; // get 'base' of the address
    if (address_base < prefix.base)
        return -1;
    if (address_base > prefix.base)
        return 1;
    return 0;
}
