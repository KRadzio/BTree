#ifndef DISPLAYER_HPP
#define DISPLAYER_HPP

#include <ncurses.h>

#include "BTree.hpp"

// d - order
// N - number of keys
// logd(N)


// log2d+1 (N+1) <= h <= logd+1 ((N+1)/2) + 1

// N / (2d) <= SIN  <= (N-1)/d + 1
// and the maximum number of disk access needed is T E = SIN + N. 

class Displayer
{
public:
    static Displayer& GetInstance();  

    void DiplayTree();
    void DiplayData();

private:
    void DiplayRecursive(size_t currHeight);
    void DisplayDataRecursive();

private:
    Displayer();
    ~Displayer();
};

#endif
