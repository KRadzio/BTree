#include "Cache.hpp"

Cache::Cache() {}
Cache::~Cache() { cachedNodes.clear(); }

Cache &Cache::GetInstance()
{
    static Cache *instance = new Cache;
    return *instance;
}
void Cache::SetSize(unsigned int size)
{
    this->size = size;
    auto tmp = cachedNodes;
    cachedNodes = std::vector<Node>(size);
    for (size_t i = 0; i < tmp.size(); i++)
        cachedNodes[i] = tmp[i];
}
void Cache::InsertNewNode(Node &node)
{
    if (index < size)
    {
        cachedNodes[index] = node;
        index++;
    }
    else
        std::cout << "Cache is full" << std::endl;
}
Node &Cache::GetNode(unsigned int n)
{
    return cachedNodes[n];
}

void Cache::ClearCache()
{
    index = 0; // we reset the cache index
}