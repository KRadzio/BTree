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
    rd.value = "abc";

    BTree::GetInstance().Add(rd);
    BTree::GetInstance().Delete(46);

    rd.index = 6;
    BTree::GetInstance().Add(rd);
    rd.index = 32;
    BTree::GetInstance().Add(rd);
    rd.index = 10;
    BTree::GetInstance().Add(rd);
    rd.index = 15;
    BTree::GetInstance().Add(rd);

    BTree::GetInstance().Delete(15);

    rd.index = 12;
    BTree::GetInstance().Add(rd);
    rd.index = 14;
    BTree::GetInstance().Add(rd);

    rd.index = 50;
    BTree::GetInstance().Add(rd);
    rd.index = 13;
    BTree::GetInstance().Add(rd);
    rd.index = 3;
    BTree::GetInstance().Add(rd);
    rd.index = 7;
    BTree::GetInstance().Add(rd);
    rd.index = 8;
    BTree::GetInstance().Add(rd);
    rd.index = 9;
    BTree::GetInstance().Add(rd);
    rd.index = 40;
    BTree::GetInstance().Add(rd);
    rd.index = 41;
    BTree::GetInstance().Add(rd);
    rd.index = 44;
    BTree::GetInstance().Add(rd);
    rd.index = 45;
    BTree::GetInstance().Add(rd);
    rd.index = 42;
    BTree::GetInstance().Add(rd);
    rd.index = 43;
    BTree::GetInstance().Add(rd);
    rd.index = 17;
    BTree::GetInstance().Add(rd);
    rd.index = 22;
    BTree::GetInstance().Add(rd);
    rd.index = 31;
    BTree::GetInstance().Add(rd);
    rd.index = 51;
    BTree::GetInstance().Add(rd);
    rd.index = 52;
    BTree::GetInstance().Add(rd);
    rd.index = 18;
    BTree::GetInstance().Add(rd);
    rd.index = 19;
    BTree::GetInstance().Add(rd);
    rd.index = 20;
    BTree::GetInstance().Add(rd);
    rd.index = 21;
    BTree::GetInstance().Add(rd);
    rd.index = 16;
    BTree::GetInstance().Add(rd);
    rd.index = 11;
    BTree::GetInstance().Add(rd);
    rd.index = 23;
    BTree::GetInstance().Add(rd);
    rd.index = 24;
    BTree::GetInstance().Add(rd);
    rd.index = 35;
    BTree::GetInstance().Add(rd);
    rd.index = 25;
    BTree::GetInstance().Add(rd);
    rd.index = 26;
    BTree::GetInstance().Add(rd);
    rd.index = 34;
    BTree::GetInstance().Add(rd);
    rd.index = 36;
    BTree::GetInstance().Add(rd);
    rd.index = 47;
    BTree::GetInstance().Add(rd);
    rd.index = 48;
    BTree::GetInstance().Add(rd);
    rd.index = 49;
    BTree::GetInstance().Add(rd);
    rd.index = 53;
    BTree::GetInstance().Add(rd);
    rd.index = 54;
    BTree::GetInstance().Add(rd);
    rd.index = 37;
    BTree::GetInstance().Add(rd);
    rd.index = 55;
    BTree::GetInstance().Add(rd);

    rd.value = "hrtjki";
    BTree::GetInstance().Update(rd);
    rd.index = 7;
    BTree::GetInstance().Update(rd);
    rd.index = 100;
    BTree::GetInstance().Update(rd);
    BTree::GetInstance().Delete(43);
    BTree::GetInstance().Delete(40);
    BTree::GetInstance().Delete(50);
    BTree::GetInstance().Delete(51);
    BTree::GetInstance().Delete(21);
    BTree::GetInstance().Delete(20);
    BTree::GetInstance().Delete(19);
    BTree::GetInstance().Delete(52);
    BTree::GetInstance().Delete(53);
    BTree::GetInstance().Delete(42);
    BTree::GetInstance().Delete(54);
    BTree::GetInstance().Delete(55);
    BTree::GetInstance().Delete(49);
    BTree::GetInstance().Delete(48);
    BTree::GetInstance().Delete(44);
    BTree::GetInstance().Delete(36);
    BTree::GetInstance().Delete(37);
    BTree::GetInstance().Delete(41);
    BTree::GetInstance().Delete(35);
    BTree::GetInstance().Delete(34);
    BTree::GetInstance().Delete(31);
    BTree::GetInstance().Delete(32);
    BTree::GetInstance().Delete(12);
    BTree::GetInstance().Delete(11);
    BTree::GetInstance().Delete(7);
    BTree::GetInstance().Delete(26);
    BTree::GetInstance().Delete(45);
    BTree::GetInstance().Delete(47);
    BTree::GetInstance().Delete(23);
    BTree::GetInstance().Delete(25);
    BTree::GetInstance().Delete(18);
    BTree::GetInstance().Delete(3);
    BTree::GetInstance().Delete(14);
    BTree::GetInstance().Delete(16);
    BTree::GetInstance().Delete(24);
    BTree::GetInstance().Delete(10);
    BTree::GetInstance().Delete(22);
    BTree::GetInstance().Delete(17);
    BTree::GetInstance().Delete(13);
    BTree::GetInstance().Delete(9);
    BTree::GetInstance().Delete(8);
    BTree::GetInstance().Delete(6);

    // rd.index = 43;
    // BTree::GetInstance().Add(rd);

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