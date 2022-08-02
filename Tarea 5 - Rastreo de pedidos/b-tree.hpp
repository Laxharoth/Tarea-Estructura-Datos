#ifndef B_TREE_HPP
#define B_TREE_HPP
#include <vector>
#include <array>

using std::vector;

//TODO make it type specific on int then extend it to other types

#ifndef GRADE
#define GRADE 5
#endif

template <class T>
class BTree;

template <class T>
struct BNode{
    std::array<T, GRADE - 1> keys{};
    std::array<BNode<T> *, GRADE> children{nullptr};
    int inserted = 0;
    bool isLeaf{true};
    BNode<T> *parent = nullptr;
    friend class BTree<T>;
};

template <class T>
class BTree{
    void insertInNode(int key, BNode<T> *lowerChild, BNode<T> *node);
    public:
    BNode<T> *root = nullptr;
    void insert(int key);
    int find(int key);
};

template <class T>
void orderInsert(int key, BNode<T> *lowerChild, BNode<T> *node);

#include "b-tree.tcc"
#endif