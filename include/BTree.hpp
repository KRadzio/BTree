#ifndef BTREE_HPP
#define BTREE_HPP

#include <algorithm>

#include "FileManager.hpp"
#include "Cache.hpp"

#define DEFAULT_BTREE_ORDER 2;
#define NO_ROOT 0
#define INVALID_NODE 0
#define NO_PARENT 0
#define NO_CHILDREN 0
#define LEFT 1
#define RIGHT 2

// nodes may not be needed as separate class
// they are stored in text file
// data is also stored in another file

// cache for height + 1 pages

class BTree
{
public:
    static BTree &GetInstance();
    void Init(unsigned int order);
    void SetOrder(unsigned int order); // changes the order of the tree and resets the tree

    bool Search(size_t key, bool clearCache = true);
    void Add(RecordData &rd);
    void Delete(RecordIndex ri);
    void Diplay();
    // search
    // add
    // delete
    // display
    // count reads and writes
private:
    bool SearchRecursive(size_t currNodeNum, size_t key);
    void AddRecursive(RecordData& rd);
    void AddToNode(Node &node, size_t nodeNumber, RecordData &rd);
    void CreateRootNode(RecordData &rd);
    bool TryCompensate(Node &currNode, size_t currNodeNumber, RecordData& rd);
    void Compensate(Node& currNode, size_t pos, RecordData& rd, int direction);
    void Split();

private:
    BTree();
    ~BTree();

private:
    size_t rootNodeNum = 1;
    unsigned int height = 2;                  // by default
    unsigned int order = DEFAULT_BTREE_ORDER; // by default
};

#endif
