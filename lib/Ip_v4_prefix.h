#ifndef IP_PREFIX
#define IP_PREFIX

typedef struct
{
    unsigned int base;
    unsigned int bitmask;
    char mask;
} Ip_v4_prefix;

int init_prefix(Ip_v4_prefix* prefix, unsigned int base, char mask); // use to initialize a prefix
unsigned int max_address(Ip_v4_prefix* prefix);
unsigned int get_bitmask(char mask);
int compare_prefixes(Ip_v4_prefix prefix1, Ip_v4_prefix prefix2); // compare 2 prefixes
int compare_ip_address(Ip_v4_prefix prefix, unsigned int ip_address); // compare address and prefix address range

#endif