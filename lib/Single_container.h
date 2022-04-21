#ifndef SINGLE_CONTAINER_H
#define SINGLE_CONTAINER_H

#include "Prefix_container.h"


extern Prefix_container CONTAINER;

int add(unsigned int base, char mask); // add_prefix() for CONTAINER
int del(unsigned int base, char mask); // del_prefix() for CONTAINER
char check(unsigned int ip); // check_for_prefix() for CONTAINER
void destroy(); // destroy_container() for CONTAINER


#endif
