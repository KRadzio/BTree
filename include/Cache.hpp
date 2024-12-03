#ifndef CACHE_HPP
#define CACHE_HPP

#include <iostream>
#include <stack>

#include "Node.hpp"

class Cache
{

public:
    static Cache &GetInstance();
    void SetSize(unsigned int size); // changes size and resets cache
    void Push(Node& node);
    Node Pop();
    void ClearCache();

private:
    Cache();
    ~Cache();

private:
    unsigned int size = 1;
    std::stack<Node> cachedNodes;
};

#endif
