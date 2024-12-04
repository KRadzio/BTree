#include "Cache.hpp"

Cache::Cache() {}
Cache::~Cache() {}

Cache &Cache::GetInstance()
{
    static Cache *instance = new Cache;
    return *instance;
}

void Cache::SetSize(unsigned int size)
{
    this->size = size;
    auto tmp = cachedNodes;
    while (!cachedNodes.empty())
        tmp.pop();
}

void Cache::Push(Node &node, size_t nodeNumber)
{
    if (cachedNodes.size() < size)
        cachedNodes.push(std::make_pair(node, nodeNumber));
    else
        std::cout << "Cache is full" << std::endl;
}

std::pair<Node, size_t> Cache::Pop()
{
    auto tmp = cachedNodes.top();
    cachedNodes.pop();
    return tmp;
}

void Cache::ClearCache()
{
    while (!cachedNodes.empty())
        cachedNodes.pop();
}