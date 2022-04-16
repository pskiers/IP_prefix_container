#include "../lib/Ip_v4_prefix.h"
#include <stdio.h>

int main()
{
    Ip_v4_prefix pref1;
    int ret = init_prefix(&pref1, 4293079744, 26);
    if (ret == -1 || ret == -2)
        printf("Bad stuff\n");
    else
    {
        printf("%x\n", pref1.base);
        printf("%d\n", pref1.mask);
        printf("%x\n", pref1.bitmask);
        printf("%x\n", pref1.max_address);
    }
    return 0;
}