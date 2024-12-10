#ifndef DISPLAYER_HPP
#define DISPLAYER_HPP

#include <ncurses.h>

#include "BTree.hpp"

#define NODE_WIDTH 35 // this will break when tree gets larger (the tree may be unreadable) 

// N / (2d) <= SIN  <= (N-1)/d + 1
// and the maximum number of disk access needed is T E = SIN + N. 

class Displayer
{
public:
    static Displayer& GetInstance();  

    void DiplayTree();
    void DiplayData();
    void SetWindowAndDimensions(WINDOW * window, int width, int height); 

private:
    void DisplayTreeRecursive(size_t currHeight, size_t currNodeNumber);
    void DisplayDataRecursive(size_t currNodeNumber);
    void DisplayNode(Node& node, size_t nodeNumber, size_t height);
    void DisplayDataFromNode(Node& node, size_t nodeNumber, size_t pos);

private:
    Displayer();
    ~Displayer();
private:
    WINDOW * window;
    int height;
    int width;
    std::vector<int> horizontalOffsets;


};

#endif
