#ifndef TREE_HPP
#define TREE_HPP

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
    ~Tree();
    void insert(T value);
    void remove(T value);
private:
    void clear(TreeNode<T> *node);
};

#include "tree.tcc"
#endif
