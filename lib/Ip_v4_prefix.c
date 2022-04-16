#include "Ip_v4_prefix.h"


unsigned int min_address(Ip_v4_prefix* prefix)
{
    return prefix->max_address;
}