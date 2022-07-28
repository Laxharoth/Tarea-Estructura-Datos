#ifndef TREE_HPP
#define TREE_HPP

#include <queue>

template <class T>
struct TreeNode{
    T data;
    TreeNode<T> *left;
    TreeNode<T> *right;
    TreeNode(T data);
};

template <class T>
struct Tree{
    TreeNode<T> *root;
    Tree();
    Tree(const Tree<T> &copy);
    ~Tree();
    void insert(T value);
    void remove(T value);
    void preorder( void (*callback)(TreeNode<T> *node) );
    void inorder( void (*callback)(TreeNode<T> *node) );
    void postorder( void (*callback)(TreeNode<T> *node) );
    void levelorder( void (*callback)(TreeNode<T> *node) );
private:
    void clear(TreeNode<T> *node);
};

#include "tree.tcc"
#endif
