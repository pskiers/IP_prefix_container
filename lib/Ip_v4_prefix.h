#ifndef IP_PREFIX
#define IP_PREFIX

typedef struct
{
    unsigned int base;
    char mask;
    unsigned int bitmask;
    unsigned int max_address;
} Ip_v4_prefix;

int init_prefix(Ip_v4_prefix* prefix, unsigned int base, char mask);
unsigned int max_address(Ip_v4_prefix* prefix);
unsigned int get_bitmask(char mask);
int compare_prefixes(Ip_v4_prefix prefix1, Ip_v4_prefix prefix2);

#endif