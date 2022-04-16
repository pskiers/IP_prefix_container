#include "../lib/Ip_v4_prefix.h"
#include <stdio.h>

int main()
{
    Ip_v4_prefix pref1;
    pref1.base = 1;
    printf("%d\n", pref1.base);
    return 0;
}