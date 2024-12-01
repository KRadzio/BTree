#include <iostream>
#include <string>

#include <ncurses.h>

#include "FileManager.hpp"
#include "BTree.hpp"

// Let h >= 0, d >= 1. B-tree with height h and order d is an ordered tree that is either empty (h = 0),
// or satisfies the following conditions:
// 1. All leaves are at the same level equal to h;
// 2. Each page contains at most 2d keys;
// 3. Each page except the root page contains at least d keys (the root may contain 1 key);
// 4. If a non-leaf page has m keys, then it has m+1 child pages.

// 20 digits

int main()
{
    Node newNode;
    BTree::GetInstance();
    Node d = FileManager::GetInstance().GetNode(2);
    std::cout << d.parentNodeNum << std::endl;
    std::cout << d.usedIndexes << std::endl;
    d.usedIndexes = 20;
    d.parentNodeNum = 235;
    d.childrenNodesNumbers[0] = 25;
    d.indexes[0].index = 42;
    d.indexes[0].pageNumber = 84;
    FileManager::GetInstance().UpdateNode(d,1);
    return 0;
}