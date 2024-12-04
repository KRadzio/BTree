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
    BTree::GetInstance().Init(2);
    RecordData rd;
    rd.index = 46;
    rd.value = "a";

    BTree::GetInstance().Add(rd);
    rd.index = 6;
    BTree::GetInstance().Add(rd);
    rd.index = 32;
    BTree::GetInstance().Add(rd);
    rd.index = 10;
    BTree::GetInstance().Add(rd);
    rd.index = 15;
    BTree::GetInstance().Add(rd);
    rd.index = 12;
    BTree::GetInstance().Add(rd);
    rd.index = 14;
    BTree::GetInstance().Add(rd);
    rd.index = 50;
    BTree::GetInstance().Add(rd);
    rd.index = 13;
    BTree::GetInstance().Add(rd);

    // BTree::GetInstance().Add(rd);
    // rd.index = 0;
    //  BTree::GetInstance().Add(rd);
    // rd.index = 17;
    // rd.value = EMPTY_RECORD;
    // BTree::GetInstance().Add(rd);
    // rd.value = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    // BTree::GetInstance().Add(rd);

    // BTree::GetInstance().Search(0);
    //    std::cout <<  BTree::GetInstance().Search(10) << std::endl;

    // Node d = FileManager::GetInstance().GetNode(10);
    // d.usedIndexes = 7667;
    // d.parentNodeNum = 1020;
    // d.childrenNodesNumbers[0] = 89;
    // d.indexes[0].index = 5610;
    // d.indexes[0].pageNumber = 84321;
    // // FileManager::GetInstance().InsertNewNode(d);
    // DataPage dp = FileManager::GetInstance().GetDataPage(1);
    // // FileManager::GetInstance().UpdateDataPage(2,dp);
    // RecordData rd;
    // rd.index = 42;
    // rd.value = "abcd";
    // FileManager::GetInstance().InsertNewRecord(rd);
    // // FileManager::GetInstance().InsertNewNode(d);
    return 0;
}