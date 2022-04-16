#include "../lib/Ip_v4_prefix.h"
#include <stdio.h>

int main()
{
    Ip_v4_prefix pref1;
    init_prefix(&pref1, 102000, 16);
    printf("%u\n", pref1.base);
    printf("%d\n", pref1.mask);
    return 0;
}