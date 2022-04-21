#ifndef SINGLE_CONTAINER_H
#define SINGLE_CONTAINER_H

#include "Prefix_container.h"


extern Prefix_container CONTAINER;

int add(unsigned int base, char mask);
int del(unsigned int base, char mask);
char check(unsigned int ip);
void destroy();


#endif
