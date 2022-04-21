#include <stdio.h>
#include <stdlib.h>
#include "Prefix_container.h"


int max(int a, int b)
/*  returns bigger value */
{
    return (a > b) ? a : b;
}


int init_node(Node* node, unsigned int base, char mask)
/*  Initializes node with malloced prefix. Used to prepare node for adding to the container.
    Should be used on mallocked node. If used on mallocked node then this finction is complementary
    to destroy_node(). Returns 0 if initialization successfull, returns -1 otherwise. */
{
    Ip_v4_prefix* new_prefix = (Ip_v4_prefix*) malloc(sizeof(Ip_v4_prefix));
    int err = init_prefix(new_prefix, base, mask);
    if (err)
        return err; // initialization unsuccessful
    node->height = 0;
    node->left_son = NULL;
    node->right_son = NULL;
    node->parent = NULL;
    node->prefix = new_prefix;
    return 0;
}


void destroy_node(Node* node)
/*  Frees memory allocated for node. Comlemetary to init_node(). Both node and its prefix must be
    allocated */
{
    free(node->prefix);
    free(node);
}


void destroy_node_recursive(Node* node)
/*  Destroys node and all of its descendants */
{
    if (node->left_son)
        destroy_node_recursive(node->left_son);
    if (node->right_son)
        destroy_node_recursive(node->right_son);
    destroy_node(node);
}


void destroy_container(Prefix_container* container)
/*  Destructor for container. Must be used to avoid memory leaks. */
{
    if (container->root)
        destroy_node_recursive(container->root);
}


int get_height(Node* node)
/*  Calculate height of the node in the tree (container). Height counted from the leaves, NOT from the root*/
{
    if (node == NULL)
        return 0;
    return 1 + max(get_height(node->left_son), get_height(node->right_son));
}


int get_balance(Node* node)
/*  Calculate balance of the node */
{
    if (node == NULL)
        return 0;
    return get_height(node->left_son) - get_height(node->right_son);
}


Node* find_palace_for_node(Prefix_container* container, Node* node_to_add)
/*  Finds the given node or a place for a given node. Return pointer to node which can be parent to
    the given node or pointer to node that is equal to the qiven node. */
{
    Node* current_node = container->root;
    Node* previous_node = container->root;
    while (current_node) // binary search done iteratively
    {
        int cmp = compare_prefixes(*current_node->prefix, *node_to_add->prefix);
        if (cmp == 0) // found equal node
            return current_node;
        if (cmp == -1)
        {
            previous_node = current_node;
            current_node = current_node->left_son;
        }
        if (cmp == 1)
        {
            previous_node = current_node;
            current_node = current_node->right_son;
        }
    }
    return previous_node;
}


Node* get_first_unbalanced(Node* added_node)
/*  Returns pointer to the first unbalanced node found while going from the given
    node to root. If no unbalanced node found returns NULL */
{
    Node* current_node = added_node;
    while (current_node) // going up to the root iteratively
    {
        int balance = get_balance(current_node);
        if (balance < -1 || balance > 1)
            return current_node;
        current_node->height = get_height(current_node); // update balance
        current_node = current_node->parent;
    }
    return NULL; // no unbalanced nodes found

}


Node* rotate_right(Node* node)
/*  AVL right rotation. Returns new root after rotation */
{
    Node* left_tree = node->left_son;
    Node* left_right_tree = left_tree->right_son;
    Node* parent = node->parent;

    if (parent)
    {
        if (parent->left_son == node) // check if it is a left or right son
            parent->left_son = left_tree;
        else
            parent->right_son = left_tree;
    }
    left_tree->parent = node->parent;

    left_tree->right_son = node;
    node->parent = left_tree;

    node->left_son = left_right_tree;
    if (left_right_tree)
        left_right_tree->parent = node;

    node->height = get_height(node); // update height
    left_tree->height = get_height(left_tree); // update height

    return left_tree; // new root after rotation
}


Node* rotate_left(Node* node)
/*  AVL left rotation. Returns new root after rotation */
{
    Node* right_tree = node->right_son;
    Node* right_left_tree = right_tree->left_son;
    Node* parent = node->parent;

    if (parent)
    {
        if (parent->left_son == node) // check if it is a left or right son
            parent->left_son = right_tree;
        else
            parent->right_son = right_tree;
    }
    right_tree->parent = node->parent;

    right_tree->left_son = node;
    node->parent = right_tree;

    node->right_son = right_left_tree;
    if (right_left_tree)
        right_left_tree->parent = node;

    node->height = get_height(node); // update height
    right_tree->height = get_height(right_tree); // update height

    return right_tree; // new root after rotation
}


Node* fix_one_subtree(Node* unbalanced_node)
/*  Fixes balance of tree unbalanced in the given node. Standard AVL operation. Return new
    root after rotation(s).*/
{
    int balance = get_balance(unbalanced_node);
    Node* new_root;
    if (balance > 1) // left unbalance
    {
        int left_balance = get_balance(unbalanced_node->left_son);
        if (left_balance == 1) // left left unbalance
        {
            new_root = rotate_right(unbalanced_node);
            return new_root;
        }
        else // left right unbalance
        {
            rotate_left(unbalanced_node->left_son);
            new_root = rotate_right(unbalanced_node);
            return new_root;
        }
    }

    else // right unbalance
    {
        int right_balance = get_balance(unbalanced_node->right_son);
        if (right_balance == -1) // right right unbalance
        {
            new_root = rotate_left(unbalanced_node);
            return new_root;
        }
        else // right left unbalance
        {
            rotate_right(unbalanced_node->right_son);
            new_root = rotate_left(unbalanced_node);
            return new_root;
        }
    }
}


int add_prefix(Prefix_container* container, unsigned int base, char mask)
/*  Performs standard AVL insert. Returns 0 if prefix created and added successfully,
    returns -1 otherwise (ex. if prefix is already in the container) */
{
    Node* new_node = (Node*) malloc(sizeof(Node));
    int err = init_node(new_node, base, mask);
    if (err)
        return err;
    if (!container->root)
    {
        container->root = new_node;
        return 0;
    }
    // find place for the node in the tree
    Node* found_Node = find_palace_for_node(container, new_node);
    // add node to tree
    int cmp = compare_prefixes(*found_Node->prefix, *new_node->prefix);
    if (cmp == 0)
        return -1; // prefix already in the tree
    if (cmp == -1)
        found_Node->left_son = new_node;
    if (cmp == 1)
        found_Node->right_son = new_node;
    new_node->parent = found_Node;
    // update heights
    Node* first_unbalanced = get_first_unbalanced(new_node);
    // fix tree if necesery
    if (first_unbalanced)
    {
        Node* new_root = fix_one_subtree(first_unbalanced);
        if (container->root == first_unbalanced) // if rotation changed the root of the whole tree
            container->root = new_root;
    }
    return 0;
}


Node* get_min_node(Node* node)
/*  Returns pointer to a node that is a descendant of the given node, with the smallest prefix*/
{
    Node* current = node;
    while (current->left_son)
        current = current->left_son;
    return current;
}


int del_prefix(Prefix_container* container, unsigned int base, char mask)
/*  Performs standard AVL deletion. Returns 0 if prefix deleted successfully,
    returns -1 otherwise (ex. if prefix is not in the container)*/
{
    Ip_v4_prefix prefix_to_del;
    int err = init_prefix(&prefix_to_del, base, mask);
    if (err)
        return err;
    Node node_to_del = {.height=0, .left_son=NULL, .right_son=NULL, .parent=NULL, .prefix=&prefix_to_del};

    if (!container->root)
        return -1; // empty tree - prefix not in the tree
    // find the prefix
    Node* found_node = find_palace_for_node(container, &node_to_del);
    if (compare_prefixes(*found_node->prefix, prefix_to_del))
    {
        return -1; // prefix not in the tree
    }
    // standard BST delete
    Node* del_place = found_node;
    if(!found_node->left_son || !found_node->right_son) // if found node has one or no kids
        {
            Node* only_son = found_node->left_son ? found_node->left_son : found_node->right_son; // get the only kid
            Node* parent = found_node->parent;
            if (!parent) // if found node is the root with not more than one son
            {
                if (only_son) // it is an AVL BST so it means the tree has exactly 2 nodes
                {
                    only_son->parent = NULL;
                    container->root = only_son; // change the root
                    only_son->height = 1;
                }
                else
                    container->root = NULL;
                destroy_node(del_place); // free deleted node
                return 0;
            }
            if (parent->left_son == found_node)
                parent->left_son = only_son;
            else
                parent->right_son = only_son;
            if (!only_son)
            {
                del_place = parent; // remeber deletion place for balancing
            }
            else
            {
                only_son->parent = parent;
                del_place = only_son; // remeber deletion place for balancing
            }
            destroy_node(found_node); // free deleted node
        }
    else // found node has 2 kids
    {
        Node* min_node = get_min_node(found_node->right_son); // find ths smallest bigger node later delete him instead
        // swap prefixes
        Ip_v4_prefix* temp = found_node->prefix;
        found_node->prefix = min_node->prefix;
        min_node->prefix = temp;
        // do an easier deletion on a node with one or less kids
        Node* only_son = min_node->right_son; // can only have right son cause it is ths smallest bigger node
        Node* parent = min_node->parent;
        del_place = parent; // remeber deletion place for balancing
        if (only_son)
        {
            only_son->parent = min_node->parent;
            if (parent->left_son == only_son)
                parent->left_son = only_son;
            else
                parent->right_son = only_son;
        }
        else
        {
            if (parent->left_son == only_son)
                parent->left_son = NULL;
            else
                parent->right_son = NULL;

        }
        destroy_node(min_node); // free deleted node
    }

    // fix tree (the AVL part)
    Node* unbalanced = get_first_unbalanced(del_place);
    while (unbalanced) // must go all the way up to the root
    {
        Node* temp = unbalanced;
        unbalanced = fix_one_subtree(unbalanced);
        if (container->root == temp) // see if rotation changed the root of the tree
            container->root = unbalanced;
        unbalanced = get_first_unbalanced(unbalanced);
    }
    return 0;
}

char check_for_prefix(Prefix_container* container, unsigned int ip)
/*  Checks if given address is contained by any prefix from the container. If it is, then return
    the smallest prefix (prefix with the biggest mask), otherwise return -1 */
{
    Node* current_node = container->root;
    char found_mask = -1;
    while (current_node)
    {
        int cmp = compare_ip_address(*current_node->prefix, ip);
        if (cmp == 0)
        {
            found_mask = current_node->prefix->mask;
            current_node = current_node->right_son;
        }
        if (cmp == -1)
        {
            current_node = current_node->left_son;
        }
        if (cmp == 1)
        {
            current_node = current_node->right_son;
        }
    }
    return found_mask;
}