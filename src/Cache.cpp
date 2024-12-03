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

void Cache::Push(Node &node)
{
    if (cachedNodes.size() < size)
        cachedNodes.push(node);
    else
        std::cout << "Cache is full" << std::endl;
}

Node Cache::Pop()
{
    Node tmp = cachedNodes.top();
    cachedNodes.pop();
    return tmp;
}

void Cache::ClearCache()
{
    while (!cachedNodes.empty())
        cachedNodes.pop();
}