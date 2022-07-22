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
    while ( (value <  node->data && node->left != nullptr) || 
            (value >= node->data && node->right != nullptr) ){
        if(value <  node->data) node = node->left;
        else node = node->right;
    }
    if(value <  node->data) node->left = new TreeNode<T>(value);
    else node->right = new TreeNode<T>(value);
}
template <class T>
void Tree<T>::remove(const T value){
    if(root == nullptr) return;
    TreeNode<T> *node = root;
    TreeNode<T> *prev = nullptr;
    while(node != nullptr && node->data != value){
        prev = node;
        if(value <  node->data) node = node->left;
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
    auto replaceNode = [&prev,&value](TreeNode<T> *replace){
        if(value < prev->data) prev->left = replace;
        else prev->right = replace;
    };
    TreeNode<T>* leaf = nullptr;
    if(node->left != nullptr){
        leaf = node->left;
        if(leaf->right == nullptr){
            replaceNode(leaf);
            leaf->right = node->right;
            delete node;
            return;
        }
        TreeNode<T>* prevLeaf = nullptr;
        while( leaf->right != nullptr){
            prevLeaf = leaf;
            leaf = leaf->right;
        }
        prevLeaf->right = nullptr;
    }
    if(node->right != nullptr){
        leaf = node->right;
        if(leaf->left == nullptr){
            replaceNode(leaf);
            leaf->left = node->left;
            delete node;
            return;
        }
        TreeNode<T>* prevLeaf = nullptr;
        while( leaf->left != nullptr){
            prevLeaf = leaf;
            leaf = leaf->left;
        }
        prevLeaf->left = nullptr;
    }
    replaceNode(leaf);
    leaf->left = node->left;
    leaf->right= node->right;
    delete node;
}
