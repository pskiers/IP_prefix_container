#include <stdio.h>
#include "Prefix_container.h"


void init_prefix_container(Prefix_container* container)
{
    container->root = NULL;
}


int get_height(Node* node)
{
    if (node == NULL)
        return 0;
    return 1+max(get_height(node->left_son), get_height(node->right_son));
}


int get_balance(Node* node)
{
    if (node == NULL)
        return 0;
    return get_height(node->left_son->height) - get_height(node->right_son->height);
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
        int balance = get_balance(&current_node);
        if (balance < -1 || balance > 1)
            return current_node;
        current_node->height = get_height(&current_node);
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
    right_left_tree->parent = node;

    node->height = get_height(node);
    right_tree->height = get_height(right_tree);

    return right_tree; // new root after rotation
}

int add_prefix(Prefix_container* container, unsigned int base, char mask)
{
    Ip_v4_prefix new_prefix;
    int err = init_prefix(&new_prefix, base, mask);
    if (err)
        return err;
    Node new_node = {.height=0, .left_son=NULL, .right_son=NULL, .parent=NULL, .prefix=&new_prefix};
    if (!container->root)
        container->root = &new_node;
        return 0;

    // find place for the node in the tree
    Node* found_Node = find_palace_for_node(&container, &new_node);
    // add node to tree
    int cmp = compare_prefixes(*found_Node->prefix, new_prefix);
    if (cmp == 0)
        return -3;
    if (cmp == -1)
        *found_Node->left_son = &new_node;
    if (cmp == 1)
        *found_Node->right_son = &new_node;
        new_node.parent = found_Node;
    // update heights
    Node* first_unbalanced = get_first_unbalanced(&new_node);
    // fix tree if necesery
    if (first_unbalanced)
    {
        int balance = get_balance(first_unbalanced);
        if (balance > 1) // left unbalance
        {
            int left_balance = get_balance(first_unbalanced->left_son);
            if (left_balance = 1) // left left unbalance
                rotate_right(first_unbalanced);
            if (left_balance = -1) // left right unbalance
            {
                rotate_left(first_unbalanced->left_son);
                rotate_right(first_unbalanced);
            }
        }

        // right unbalance
        if (balance < -1)
        {
            int right_balance = get_balance(first_unbalanced->right_son);
            if (right_balance = 1) // right right unbalance
                rotate_left(first_unbalanced);
            if (right_balance = -1) // right left unbalance
            {
                rotate_right(first_unbalanced->right_son);
                rotate_left(first_unbalanced);
            }
        }
    }

