#include <iostream>
#include <string>

#include <ncurses.h>

#include "FileManager.hpp"

// Let h >= 0, d >= 1. B-tree with height h and order d is an ordered tree that is either empty (h = 0),
// or satisfies the following conditions:
// 1. All leaves are at the same level equal to h;
// 2. Each page contains at most 2d keys;
// 3. Each page except the root page contains at least d keys (the root may contain 1 key);
// 4. If a non-leaf page has m keys, then it has m+1 child pages.

// 20 digits

int main()
{
    unsigned int n = 0;
    size_t i = 0;
    std::cout << i - 1 << " " << n - 1 << std::endl;
    std::cout << std::stoi("00000000010") << std::endl;

    Node d = FileManager::GetInstance().GetNode(0);
    std::cout << d.parentNodeNum << std::endl;
    return 0;
}