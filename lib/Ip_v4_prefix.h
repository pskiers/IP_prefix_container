#ifndef IP_PREFIX
#define IP_PREFIX

typedef struct
{
    unsigned int base;  // base of the prefix
    unsigned int bitmask; // binary mask
    char mask; // basically number of ones in the mask ex. bitmask 255.255.0.0 -> mask 16
} Ip_v4_prefix;

int init_prefix(Ip_v4_prefix* prefix, unsigned int base, char mask); // use to initialize a prefix
unsigned int max_address(Ip_v4_prefix* prefix);
unsigned int get_bitmask(char mask); // calculate bitmask
int compare_prefixes(Ip_v4_prefix prefix1, Ip_v4_prefix prefix2); // compare 2 prefixes
int compare_ip_address(Ip_v4_prefix prefix, unsigned int ip_address); // compare address and prefix address range

#endif