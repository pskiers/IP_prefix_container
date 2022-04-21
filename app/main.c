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
    assert(container.root->prefix->base == 0x00025000);
    assert(container.root->left_son->prefix->base == 0x00020000);
    assert(container.root->left_son->left_son->prefix->base == 0x00010000);
    assert(container.root->right_son->prefix->base == 0x00030000);
    assert(container.root->right_son->left_son->prefix->base == 0x00027000);
    assert(container.root->right_son->right_son->prefix->base == 0x00040000);
    add_prefix(&container, 0x00050000, 29);
    del_prefix(&container, 0x00020000, 29);
    assert(container.root->prefix->base == 0x00030000);
    assert(container.root->left_son->prefix->base == 0x00025000);
    assert(container.root->left_son->left_son->prefix->base == 0x00010000);
    assert(container.root->left_son->right_son->prefix->base == 0x00027000);
    assert(container.root->right_son->prefix->base == 0x00040000);
    assert(container.root->right_son->right_son->prefix->base == 0x00050000);
    del_prefix(&container, 0x00025000, 29);
    assert(container.root->prefix->base == 0x00030000);
    assert(container.root->left_son->prefix->base == 0x00027000);
    assert(container.root->left_son->left_son->prefix->base == 0x00010000);
    assert(container.root->right_son->prefix->base == 0x00040000);
    assert(container.root->right_son->right_son->prefix->base == 0x00050000);
    add_prefix(&container, 0x00050000, 30);
    add_prefix(&container, 0x00050000, 28);
    add_prefix(&container, 0x00050000, 27);
    char mask = check_for_prefix(&container, 0x00050001);
    assert(mask == 30);
    mask = check_for_prefix(&container, 0x00040003);
    assert(mask == 29);
    return 0;
}