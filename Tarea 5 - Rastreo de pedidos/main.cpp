#include "b-tree.hpp"

#include <iostream>

void printBNode(BNode *node);

void printBTree(BTree &tree){
    printBNode(tree.root);
}

static int IIII = 0;

void printBNode(BNode *node){
    if(node == nullptr)return;
    for (int i = 0; i < node->inserted; i++){
        printBNode(node->children[i]);
        std::cout<< IIII++ << ":" << node->keys[i] << std::endl;
    }
    printBNode(node->children[node->inserted]);
}


int main(){
    BTree tree;

    for (int i = 0; i < 50; i++){
        tree.insert(i);
    }
    try{
        for (int i = 0; i < 50; i++){
            findBKey(i, tree.root);
        }
    }catch(int ex){
        std::cout << ex << std::endl;
    }

    // printBTree(tree);

    std::cout << "Hello world!" << std::endl;

    return 0; 
}