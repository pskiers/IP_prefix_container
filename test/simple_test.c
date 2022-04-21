#include "../lib/Ip_v4_prefix.h"
#include "../lib/Prefix_container.h"
#include "Single_container.h"
#include <stdio.h>
#include <assert.h>


extern Prefix_container CONTAINER;


int main()
{
    add(0x00010000, 29);
    add(0x00020000, 29);
    add(0x00030000, 29);
    add(0x00040000, 29);
    add(0x00025000, 29);
    add(0x00027000, 29);
    assert(CONTAINER.root->prefix->base == 0x00025000);
    assert(CONTAINER.root->left_son->prefix->base == 0x00020000);
    assert(CONTAINER.root->left_son->left_son->prefix->base == 0x00010000);
    assert(CONTAINER.root->right_son->prefix->base == 0x00030000);
    assert(CONTAINER.root->right_son->left_son->prefix->base == 0x00027000);
    assert(CONTAINER.root->right_son->right_son->prefix->base == 0x00040000);
    add(0x00050000, 29);
    del(0x00020000, 29);
    assert(CONTAINER.root->prefix->base == 0x00030000);
    assert(CONTAINER.root->left_son->prefix->base == 0x00025000);
    assert(CONTAINER.root->left_son->left_son->prefix->base == 0x00010000);
    assert(CONTAINER.root->left_son->right_son->prefix->base == 0x00027000);
    assert(CONTAINER.root->right_son->prefix->base == 0x00040000);
    assert(CONTAINER.root->right_son->right_son->prefix->base == 0x00050000);
    del(0x00025000, 29);
    assert(CONTAINER.root->prefix->base == 0x00030000);
    assert(CONTAINER.root->left_son->prefix->base == 0x00027000);
    assert(CONTAINER.root->left_son->left_son->prefix->base == 0x00010000);
    assert(CONTAINER.root->right_son->prefix->base == 0x00040000);
    assert(CONTAINER.root->right_son->right_son->prefix->base == 0x00050000);
    add(0x00050000, 30);
    add(0x00050000, 28);
    add(0x00050000, 27);
    char mask = check(0x00050001);
    assert(mask == 30);
    mask = check(0x00040003);
    assert(mask == 29);
    destroy();
    return 0;
}