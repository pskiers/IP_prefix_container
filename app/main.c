#include "../lib/Ip_v4_prefix.h"
#include "../lib/Prefix_container.h"
#include <stdio.h>

int main()
{
    Prefix_container container;
    init_prefix_container(&container);
    add_prefix(&container, 0xffff0000, 16);
    add_prefix(&container, 0xfffff000, 20);
    add_prefix(&container, 0xffffff00, 24);
    add_prefix(&container, 0xfffffff0, 28);
    del_prefix(&container, 0xffff0000, 16);
    return 0;
}