#include "b-tree.hpp"

template <class T>
BNode<T>* divideNode(BNode<T> *rightNode){
    const int start = 0;
    const int half = rightNode->inserted / 2;
    const int end = rightNode->inserted;
    
    BNode<T> *leftNode = new BNode<T>();
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

template <class T>
void BTree<T>::insertInNode(T key, BNode<T> *lowerChild, BNode<T> *node){
    if(node->inserted < GRADE - 1){
        orderInsert(key, lowerChild, node);
        return;
    }
    BNode<T> *rightSibling = node;
    BNode<T> *leftSibling  = divideNode(rightSibling);

    BNode<T> *parent = node->parent;
    if(parent == nullptr){
        parent = new BNode<T>();
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

template <class T>
void BTree<T>::insert(T key){
    if(root == nullptr){
        root = new BNode<T>();
        root->isLeaf = true;
        root->inserted = 0;
        root->parent = nullptr;
    }
    BNode<T> *node = root;
    while(!(node->isLeaf)){
        size_t i;
        for(i = 0; i < node->inserted && key >= node->keys[i]; ++i){}
        node = node->children[i];
    }
    insertInNode(key,nullptr,node);
}

template <class T>
void orderInsert(int key, BNode<T> *lowerChild, BNode<T> *node){
    static int key_1 = 0;
    if(node->inserted == 0){
        node->children[1] = node->children[0];
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
    node->keys[position] = key;
    node->children[position] = lowerChild;
    node->inserted++;
}

template <class T>
int BTree<T>::find(T key){
    int i = 0;
    BNode<T> *node = root;
    while(node != nullptr){
        while( i < node->inserted && key >= node->keys[i] ){ 
            if(key == node->keys[i]) return node->keys[i];
            ++i; 
        }
        node = node->children[i];
        i = 0;
    }
    throw key;
}

template <class T>
void BTree<T>::breathFirst(void (*callback)(BNode<T> *node)){
    std::queue<BNode<T>*> queue;
    std::queue<BNode<T>*> aux;
    queue.push(root);
    while(!(queue.empty())){
        while(!(queue.empty())){
            BNode<T> *node = queue.front();
            queue.pop();
            if(node == nullptr) continue;
            int i;
            for(i = 0; i < node->inserted; ++i){
                aux.push(node->children[i]);
            }
            aux.push(node->children[i]);
            callback(node);
        }
        std::swap(queue, aux);
    }
}
template <class T>
BTree<T>::~BTree(){
    this->breathFirst( [](BNode<T> *node){ delete node;} );
}
