#ifndef BTREE_HPP
#define BTREE_HPP

#include "FileManager.hpp"
#include "Cache.hpp"

#define DEFAULT_BTREE_ORDER 2;
#define NO_ROOT 0
#define INVALID_NODE 0

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

    void Search(size_t key);
    void Add(RecordData rd);
    void Delete(RecordIndex ri);
    void Diplay();
    // search
    // add
    // delete
    // display
    // count reads and writes
private:
    void SearchRecursive(size_t currNodeNum, size_t key);

private:
    BTree();
    ~BTree();

private:
    size_t rootNodeNum = 1;
    unsigned int height = 0;                  // by default
    unsigned int order = DEFAULT_BTREE_ORDER; // by default
};

#endif
