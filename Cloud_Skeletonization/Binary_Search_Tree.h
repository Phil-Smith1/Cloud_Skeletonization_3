#pragma once

class BST_Node
{
    public:
    
    int key_value;
    BST_Node * left;
    BST_Node * right;
};

class Binary_Search_Tree
{
    public:
    
    Binary_Search_Tree();
    ~Binary_Search_Tree();
    
    void insert( int key );
    void insert( int key, BST_Node * leaf );
    
    BST_Node * search( int key );
    BST_Node * search( int key, BST_Node * leaf );
    
    void destroy_tree();
    void destroy_tree( BST_Node * leaf );
    
    BST_Node * root;
};
