#include <iostream>
#include <string>

#include <ncurses.h>

#include "FileManager.hpp"
#include "BTree.hpp"

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

    return 0;
}