#ifndef B_TREE_HPP
#define B_TREE_HPP
#include <vector>
#include <array>

using std::vector;

//TODO make it type specific on int then extend it to other types

#ifndef GRADE
#define GRADE 5
#endif

class BTree;
struct BNode;

struct BNode{
    std::array<int, GRADE - 1> keys{};
    std::array<BNode *, GRADE> children{nullptr};
    int inserted = 0;
    bool isLeaf{true};
    BNode *parent = nullptr;
    friend class BTree;
};

class BTree{
    void insertInNode(int key, BNode *lowerChild, BNode *node);
    BNode* divideNode(BNode *rightNode, BNode *newNode);
    public:
    BNode *root = nullptr;
    void insert(int key);
};

void orderInsert(int key, BNode *lowerChild, BNode *node);

#include "b-tree.tcc"
#endif