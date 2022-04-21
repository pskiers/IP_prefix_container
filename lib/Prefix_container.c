#include <stdio.h>
#include <stdlib.h>
#include "Prefix_container.h"
#include "Ip_v4_prefix.h"

int max(int a, int b)
{
    return (a > b) ? a : b;
}


void init_prefix_container(Prefix_container* container)
{
    container->root = NULL;
}


int init_node(Node* node, unsigned int base, char mask)
{
    Ip_v4_prefix* new_prefix = (Ip_v4_prefix*) malloc(sizeof(Ip_v4_prefix));
    int err = init_prefix(new_prefix, base, mask);
    if (err)
        return err;
    node->height = 0;
    node->left_son = NULL;
    node->right_son = NULL;
    node->parent = NULL;
    node->prefix = new_prefix;
    return 0;
}


void destroy_node(Node* node)
{
    free(node->prefix);
    free(node);
}


int get_height(Node* node)
{
    if (node == NULL)
        return 0;
    return 1 + max(get_height(node->left_son), get_height(node->right_son));
}


int get_balance(Node* node)
{
    if (node == NULL)
        return 0;
    return get_height(node->left_son) - get_height(node->right_son);
}


Node* find_palace_for_node(Prefix_container* container, Node* node_to_add)
{
    Node* current_node = container->root;
    Node* previous_node = container->root;
    while (current_node)
    {
        int cmp = compare_prefixes(*current_node->prefix, *node_to_add->prefix);
        if (cmp == 0)
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
{
    Node* current_node = added_node;
    while (current_node)
    {
        int balance = get_balance(current_node);
        if (balance < -1 || balance > 1)
            return current_node;
        current_node->height = get_height(current_node);
        current_node = current_node->parent;
    }
    return NULL;

}


Node* rotate_right(Node* node)
{
    Node* left_tree = node->left_son;
    Node* left_right_tree = left_tree->right_son;
    Node* parent = node->parent;

    if (parent)
    {
        if (parent->left_son == node)
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

    node->height = get_height(node);
    left_tree->height = get_height(left_tree);

    return left_tree; // new root after rotation
}


Node* rotate_left(Node* node)
{
    Node* right_tree = node->right_son;
    Node* right_left_tree = right_tree->left_son;
    Node* parent = node->parent;

    if (parent)
    {
        if (parent->left_son == node)
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

    node->height = get_height(node);
    right_tree->height = get_height(right_tree);

    return right_tree; // new root after rotation
}


Node* fix_one_subtree(Node* unbalanced_node)
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
        return -3; // prefix already in the tree
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
        if (container->root == first_unbalanced)
            container->root = new_root;
    }
    return 0;
}


Node* get_min_node(Node* node)
{
    Node* current = node;
    while (current->left_son)
        current = current->left_son;
    return current;
}


int del_prefix(Prefix_container* container, unsigned int base, char mask)
{
    Ip_v4_prefix prefix_to_del;
    int err = init_prefix(&prefix_to_del, base, mask);
    if (err)
        return err;
    Node node_to_del = {.height=0, .left_son=NULL, .right_son=NULL, .parent=NULL, .prefix=&prefix_to_del};

    if (!container->root)
        return -3; // empty tree - prefix not in the tree
    // find the prefix
    Node* found_node = find_palace_for_node(container, &node_to_del);
    if (compare_prefixes(*found_node->prefix, prefix_to_del))
    {
        return -3; // prefix not in the tree
    }
    // standard BST delete
    Node* del_place = found_node;
    if(!found_node->left_son || !found_node->right_son)
        {
            Node* only_son = found_node->left_son ? found_node->left_son : found_node->right_son;
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
                destroy_node(del_place);
                return 0;
            }
            if (parent->left_son == found_node)
                parent->left_son = only_son;
            else
                parent->right_son = only_son;
            if (!only_son)
            {
                del_place = parent;
            }
            else
            {
                only_son->parent = parent;
                del_place = only_son;
            }
            destroy_node(found_node);
        }
    else
    {
        Node* min_node = get_min_node(found_node);
        found_node->prefix = min_node->prefix;
        Node* only_son = min_node->right_son;
        Node* parent = min_node->parent;
        del_place = parent;
        if (only_son)
        {
            only_son->parent = min_node->parent;
            parent->left_son = only_son; // must be a left son because min_node was found by 'going left' only
        }
        else
            parent->left_son = NULL; // must be a left son because min_node was found by 'going left' only
        destroy_node(min_node);
    }

    // fix tree (the AVL part)
    Node* unbalanced = get_first_unbalanced(del_place);
    while (unbalanced)
    {
        Node* temp = unbalanced;
        unbalanced = fix_one_subtree(unbalanced);
        if (container->root == temp)
            container->root = unbalanced;
        unbalanced = get_first_unbalanced(unbalanced);
    }
    return 0;
}

char check_for_prefix(Prefix_container* container, unsigned int ip)
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