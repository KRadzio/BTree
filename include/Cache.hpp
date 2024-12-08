#ifndef CACHE_HPP
#define CACHE_HPP

#include <iostream>
#include <stack>

#include "Node.hpp"

class Cache
{

public:
    static Cache &GetInstance();
    void SetSize(unsigned int size);          // changes size and resets cache
    void Push(Node &node, size_t nodeNumber); // node number is needed to save back to file if the node is modified
    void Push(std::pair<Node, size_t> &node);
    std::pair<Node, size_t> Pop();                                         // get last node and pop
    inline std::pair<Node, size_t> GetLast() { return cachedNodes.top(); } // get last saved node without poping
    void ClearCache();

private:
    Cache();
    ~Cache();

private:
    unsigned int size = 1;
    std::stack<std::pair<Node, size_t>> cachedNodes;
};

#endif
