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
    rd.index = 10;
    rd.value = "a";
    BTree::GetInstance().Add(rd);
    rd.index = 0;
     BTree::GetInstance().Add(rd);
    rd.index = 17;
    rd.value = EMPTY_RECORD;
    BTree::GetInstance().Add(rd);
    rd.value = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    BTree::GetInstance().Add(rd);

    BTree::GetInstance().Search(0);
    BTree::GetInstance().Search(10);
    BTree::GetInstance().Search(20);
    BTree::GetInstance().Search(30);
    BTree::GetInstance().Search(40);
    BTree::GetInstance().Search(1);
    BTree::GetInstance().Search(2);
    BTree::GetInstance().Search(3);
    BTree::GetInstance().Search(4);
    BTree::GetInstance().Search(5);

    BTree::GetInstance().Search(7);

    BTree::GetInstance().Search(11);
    BTree::GetInstance().Search(12);
    BTree::GetInstance().Search(13);
    BTree::GetInstance().Search(14);

    BTree::GetInstance().Search(17);

    BTree::GetInstance().Search(22);
    BTree::GetInstance().Search(23);
    BTree::GetInstance().Search(24);
    BTree::GetInstance().Search(25);

    BTree::GetInstance().Search(27);

    BTree::GetInstance().Search(31);
    BTree::GetInstance().Search(32);
    BTree::GetInstance().Search(33);
    BTree::GetInstance().Search(34);

    BTree::GetInstance().Search(37);

    BTree::GetInstance().Search(41);
    BTree::GetInstance().Search(42);
    BTree::GetInstance().Search(43);
    BTree::GetInstance().Search(44);

    BTree::GetInstance().Search(50);

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