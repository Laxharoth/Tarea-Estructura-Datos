#include "b-tree.hpp"

#include <iostream>
using std::cout;using std::endl;
static size_t III = 0;

void aquivoi(){
    std::cout << ++III << ":" << " aquivoi" << std::endl;
}
BNode* divideNode(BNode *rightNode);

void BTree::insertInNode(int key, BNode *lowerChild, BNode *node){
    if(node->inserted < GRADE - 1){
        orderInsert(key, lowerChild, node);
        return;
    }
    BNode *rightSibling = node;
    BNode *leftSibling  = divideNode(rightSibling);

    BNode *parent = node->parent;
    if(parent == nullptr){
        parent = new BNode();
        parent->isLeaf = false;
        root = parent;
        rightSibling->parent = parent;
        leftSibling->parent = parent;
        parent->children[0] = rightSibling;
    }
    //goes to the left side
    if( key < leftSibling->keys[ leftSibling->inserted - 1 ])
        for( int i = 0; i < leftSibling->inserted / 2; ++i)
            if( key < node->keys[ i ]) {
                std::swap( key, leftSibling->keys[i] );
                std::swap( lowerChild, leftSibling->children[i] );
            }
    //goes to the right side
    if( key > rightSibling->keys[0])
        for( int i = rightSibling->inserted-1; i >= 0;--i )
            if( key > node->keys[ i ]){
                std::swap( key, rightSibling->keys[i] );
                std::swap( lowerChild, rightSibling->children[i] );
            } 
    // is in the middle
    insertInNode(key, leftSibling, parent);
}
BNode* divideNode(BNode *rightNode){
    const int start = 0;
    const int half = rightNode->inserted / 2;
    const int end = rightNode->inserted;
    
    BNode *leftNode = new BNode();
    leftNode->inserted = 0;
    leftNode->parent = rightNode->parent;
    leftNode->children[half]  = rightNode->children[half];
    static int divide_i = 0; 
    for(size_t i = start; i < half ; ++i){
        leftNode->keys[i] = rightNode->keys[i];
        leftNode->children[i] = rightNode->children[i];
        leftNode->inserted++;
    }
    rightNode->inserted = 0;
    rightNode->children[end - half]  = rightNode->children[end];
    for(size_t i = half; i < end; ++i){
        rightNode->keys[i - half] = rightNode->keys[i];
        // comienza con el nodo del medio el mismo nodo final del lado izquierdo
        //   pero va a ser reemplazado por el nodo correcto
        rightNode->children[i - half] = rightNode->children[i];
        rightNode->inserted++;
    }
    return leftNode;
}
void BTree::insert(int key){
    if(root == nullptr){
        root = new BNode();
        root->isLeaf = true;
        root->inserted = 0;
        root->parent = nullptr;
    }
    BNode *node = root;
    while(!(node->isLeaf)){
        size_t i;
        for(i = 0; i < node->inserted && key >= node->keys[i]; ++i){}
        node = node->children[i];
    }
    insertInNode(key,nullptr,node);
}

void orderInsert(int key, BNode *lowerChild, BNode *node){
    
    static int key_1 = 0;
    if(node->inserted == 0){
        node->children[1] = node->children[0];
        cout << "inserting " << key_1++ << ": " << key << endl;
        node->keys[0] = key;
        node->children[0] = lowerChild;
        node->inserted++;
        return;
    }
    int position = 0;
    while(key >= node->keys[position]  && position < node->inserted)
    { ++position; }

    node->children[node->inserted + 1] = node->children[node->inserted];
    for (int i = node->inserted-1; i >= position; --i){
        node->keys[i + 1] = node->keys[i];
        node->children[i + 1] = node->children[i];
    }
    cout << "inserting " << key_1++ << ": " << key << endl;
    node->keys[position] = key;
    node->children[position] = lowerChild;
    node->inserted++;
}
