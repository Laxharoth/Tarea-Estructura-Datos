#include "tree.hpp"

template <class T>
TreeNode<T>::TreeNode(T data) : data(data), left(nullptr), right(nullptr) {}

template <class T>
Tree<T>::Tree():root(nullptr) { }
template <class T>
Tree<T>::~Tree() {
    clear(root);
}
template <class T>
void Tree<T>::clear(TreeNode<T> *node){
    if(node == nullptr) return;
    this->clear(node->left);
    this->clear(node->right);
    delete node;
}

template <class T>
void Tree<T>::insert(T value){
    if(root == nullptr){
        this->root = new TreeNode<T>(value);
        return;
    }
    TreeNode<T> *node = this->root;
    while ( (node->data <  value && node->left != nullptr) || 
            (node->data >= value && node->left != nullptr) ){
        if(node->data <  value) node = node->left;
        else node = node->right;
    }
    if(node->data <  value) node->left = new TreeNode<T>(value);
    else node->right = new TreeNode<T>(value);
}
template <class T>
void Tree<T>::remove(T value){
    if(root == nullptr) return;
    TreeNode<T> *node = root;
    TreeNode<T> *prev = nullptr;
    while(node != nullptr && node->data != value){
        prev = node;
        if(node->data <  value) node = node->left;
        else node = node->right;
    }
    if(node == nullptr) return;
    // si no tiene hijos solo desacopla el nodo
    if(node->left == nullptr && node->right == nullptr){
        if(node == root){
            root = nullptr;
            delete node;
            return;
        } 
        if(value < prev->data) prev->left = nullptr;
        else prev->right = nullptr;
        delete node;
        return;
    }
    // buscar el nodo para reemplazar y desacoplarlo del arbol
    TreeNode<T> *leaf = node;
    TreeNode<T> *prevLeaf = prev;
    if(leaf->left != nullptr){
        prevLeaf = leaf;
        leaf = leaf->left;
        while(leaf->right != nullptr){
            prevLeaf = leaf;
            leaf = leaf->right;
        }
        prevLeaf->right = nullptr;
    }
    else if(leaf->right != nullptr){
        prevLeaf = leaf;
        leaf = leaf->right;
        while(leaf->left != nullptr){
            prevLeaf = leaf;
            leaf = leaf->left;
        }
        prevLeaf->left = nullptr;
    }
    leaf->left = node->left;
    leaf->right= node->right;
    if(prev == nullptr){
        root = leaf;
        delete node;
        return
    }
    if(value < prev->data) prev->left = leaf;
    else prev->right = leaf;
    delete node;
}
