#include <stdio.h>

#include "Binary_Search_Tree.h"

Binary_Search_Tree::Binary_Search_Tree()
{
    root = NULL;
}

Binary_Search_Tree::~Binary_Search_Tree()
{
    destroy_tree();
}

void Binary_Search_Tree::insert( int key )
{
    if (root != NULL) insert( key, root );
    
    else
    {
        root = new BST_Node;
        root->key_value = key;
        root->left = NULL;
        root->right = NULL;
    }
}

void Binary_Search_Tree::insert( int key, BST_Node * leaf )
{
    if (key < leaf->key_value)
    {
        if (leaf->left!= NULL) insert( key, leaf->left );
        
        else
        {
            leaf->left = new BST_Node;
            leaf->left->key_value = key;
            leaf->left->left = NULL;
            leaf->left->right = NULL;
        }
    }
    
    else if (key >= leaf->key_value)
    {
        if (leaf->right!= NULL) insert( key, leaf->right );
        
        else
        {
            leaf->right = new BST_Node;
            leaf->right->key_value = key;
            leaf->right->left = NULL;
            leaf->right->right = NULL;
        }
    }
}

BST_Node * Binary_Search_Tree::search( int key )
{
    return search( key, root );
}

BST_Node * Binary_Search_Tree::search( int key, BST_Node * leaf )
{
    if (leaf != NULL)
    {
        if (key==leaf->key_value) return leaf;
        
        if (key < leaf->key_value) return search( key, leaf->left );
        
        else return search( key, leaf->right );
    }
    
    else return NULL;
}

void Binary_Search_Tree::destroy_tree()
{
    destroy_tree( root );
}

void Binary_Search_Tree::destroy_tree( BST_Node * leaf )
{
    if (leaf != NULL)
    {
        destroy_tree( leaf->left );
        destroy_tree( leaf->right );
        delete leaf;
    }
}
