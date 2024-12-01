#ifndef CACHE_HPP
#define CACHE_HPP

#include <iostream>
#include <vector>

#include "Node.hpp"

class Cache
{

public:
    static Cache &GetInstance();
    void SetSize(unsigned int size);
    void InsertNewNode(Node& node);
    Node& GetNode(unsigned int n);
    void ClearCache();

private:
    Cache();
    ~Cache();

private:
    unsigned int index = 0;
    unsigned int size = 1;
    std::vector<Node> cachedNodes;
};

#endif
