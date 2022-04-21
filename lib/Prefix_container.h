#ifndef PREFIX_CONTAINER_H
#define PREFIX_CONTAINER_H

#include "Ip_v4_prefix.h"


typedef struct Node
/*  Node of an AVL binary search tree for ip prefixes*/
{
    Ip_v4_prefix* prefix;
    struct Node* parent;
    struct Node* left_son;
    struct Node* right_son;
    int height; // counted form leaves not from root
} Node;



typedef struct
/*  Prefixes are stored in a data structure that is an AVL binary search tree */
{
    Node* root; // root of the tree
} Prefix_container;

int add_prefix(Prefix_container* container, unsigned int base, char mask);
int del_prefix(Prefix_container* container, unsigned int base, char mask);
char check_for_prefix(Prefix_container* container, unsigned int ip); // check if there is a prefix that the address
void destroy_container(Prefix_container* container); // basically a destructor

#endif