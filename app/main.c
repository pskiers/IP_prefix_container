#include "../lib/Ip_v4_prefix.h"
#include "../lib/Prefix_container.h"
#include <stdio.h>
#include <assert.h>


int main()
{
    Prefix_container container;
    init_prefix_container(&container);
    add_prefix(&container, 0x00010000, 29);
    add_prefix(&container, 0x00020000, 29);
    add_prefix(&container, 0x00030000, 29);
    add_prefix(&container, 0x00040000, 29);
    add_prefix(&container, 0x00025000, 29);
    add_prefix(&container, 0x00027000, 29);
    assert(1);
    add_prefix(&container, 0x00050000, 29);
    del_prefix(&container, 0x00020000, 29);
    assert(1);
    del_prefix(&container, 0x00025000, 29);
    assert(1);
    add_prefix(&container, 0x00050000, 30);
    char mask = check_for_prefix(&container, 0x00050001);
    assert(mask == 30);
    return 0;
}