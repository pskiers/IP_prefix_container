#ifndef IP_PREFIX
#define IP_PREFIX

typedef struct
{
    unsigned int base;
    char mask;
    unsigned int min_address;
    unsigned int max_address;
} Ip_v4_prefix;

int init_prefix(Ip_v4_prefix* prefix, unsigned int base, char mask);
unsigned int min_address(Ip_v4_prefix* prefix);
unsigned int max_address(Ip_v4_prefix* prefix);

#endif