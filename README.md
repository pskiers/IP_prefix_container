# CONTAINER FOR IPv4 PREFIXES

## Overview
Main goal of the project was to create management system for IPv4 prefixes.


## Content summary
The project contains the following:
- **library** - a C library containing implementation of the container and functions allowing for interactions with the container, as well as structure for IPv4 prefixes
- **demo programme** - a simple interactive programme showcasing how the library can be used
- **tests** - pretty self explanatory, tests for the library


## Building the project

### Linux
To build the project navigate to the project folder then do the following:
```
mkdir build
cd build
cmake ../
make
```

## Running the demo programme
To run the demo programme navigate to the project directory and do the following:
```
cd build
./app/Main

```


## Runnong the test
To run the test navigate to the project directory and do the following:
```
cd build
make test

```


## Project structure
The project is divided into 3 directories: **app**, **lib** and **test**. The role of those is quickly described bellow.
 - app - A foder for the demo programme
 - lib - Contains the library
 - test - folder for tests


## Library
The library contains mainly 2 things: a structure representing an IPv4 prefix and a structure representing a container for those prefixes.

### IPv4 prefix
```
typedef struct
{
    unsigned int base;
    char mask;
    unsigned int bitmask;
} Ip_v4_prefix;
```
A simple struct containing base, mask of the prefix, as well as calculated for the prefix bit mask. It results in bigger size of the structure, but also quicker operations of comparing prefix with IP adress, which is a common operation when checking if address is in the data structure. Available functions for the structure:
```
int init_prefix(Ip_v4_prefix* prefix, unsigned int base, char mask); // use to initialize a prefix
unsigned int max_address(Ip_v4_prefix* prefix);
unsigned int get_bitmask(char mask);
int compare_prefixes(Ip_v4_prefix prefix1, Ip_v4_prefix prefix2); // compare 2 prefixes
int compare_ip_address(Ip_v4_prefix prefix, unsigned int ip_address); // compare address and prefix address range
```
### Container for prefixes
To ensure good speed for operation of checking if address is in the prefix set, the container is implemented as AVL binary search tree.
```
typedef struct Node
{
    Ip_v4_prefix* prefix;
    struct Node* parent;
    struct Node* left_son;
    struct Node* right_son;
    int height; // counted form leaves not from root
} Node;

typedef struct
{
    Node* root;
} Prefix_container;
```
Available operations on prefix container:
```
int add_prefix(Prefix_container* container, unsigned int base, char mask);
int del_prefix(Prefix_container* container, unsigned int base, char mask);
char check_for_prefix(Prefix_container* container, unsigned int ip); // check if there is a prefix that the address
void destroy_container(Prefix_container* container); // basically a destructor

```
Addition and deletion of prefix is implemented like a standard AVL insertion and deletion. It is important to note that the **container allocates memory dynamically** so in order to avoid memory leaks, one should **use the destructor** provided for the container.

### Single container
If one container is all you need then an easier alternative to creating prefix container and using functions decalred in Prefix_container.h is using this module. This is basically a little simpler interface with some additionall limitations. Following are equivalents for the functions from Prefix_container.h, declared and defined in this module:
```
int add(unsigned int base, char mask);
int del(unsigned int base, char mask);
char check(unsigned int ip);
void destroy();
```


## Computational complexity
For adding and deleting prefix to the container, computational complexities are equal to computational complexity of AVL insertion and deletion, respectively, as they follow the same algorithm (and as comparing two prefixes is done in constant time). Hence time complexity for both operations at worst O(log n) and on average O(log n). Operation of checking, on the other hand, is a little different from AVL search. To do check need to do standard AVL search, however we don't stop once we find a good prefix. We always have to go all the way down to one of the leaves of the tree to make sure we got the smallest prefix. Consequently, every check will have complexity equall to that of worst case AVL search. Check has time complexity of O(log n).


## Memory usage
The container has a standard linear memory usage, as when it comes to memory it is a normal bianry search tree. Sizes of created structures:
- Ip_v4_prefix = 12 bytes
- Node = 40 bytes