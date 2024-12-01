#ifndef BTREE_HPP
#define BTREE_HPP

#include "FileManager.hpp"
#include "Cache.hpp"

#define BTREE_ORDER 2;

// nodes may not be needed as separate class
// they are stored in text file
// data is also stored in another file

// cache for height + 1 pages

class BTree
{
public:
    static BTree &GetInstance();
    void SetOrder(unsigned int order); // changes the order of the tree and resets the tree

    // search
    // add
    // delete
    // display
    // count reads and writes

private:
    BTree();
    ~BTree();

private:
    size_t rootNodeNum = 0;
    unsigned int height = 0; // by default
    unsigned int order = BTREE_ORDER;         // by default
};

#endif
