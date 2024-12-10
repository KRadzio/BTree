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
    while (!cachedNodes.empty())
        cachedNodes.pop();
}

void Cache::Push(Node &node, size_t nodeNumber)
{
    if (cachedNodes.size() < size)
        cachedNodes.push(std::make_pair(node, nodeNumber));
    else
        std::cout << "Cache is full" << std::endl;
}

void Cache::Push(std::pair<Node, size_t> &node)
{
    if (cachedNodes.size() < size)
        cachedNodes.push(node);
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

DataPage &Cache::GetDataPage(size_t pageNumber) {
    for(size_t i=0; i<dataPagePos; i++)
    {
        if(dataPagesCached[i].second == pageNumber)
            return dataPagesCached[i].first;
    }
    if(dataPagePos == MAX_DATAPAGES_CACHED)
        dataPagePos = 0;
    dataPagesCached[dataPagePos].first = FileManager::GetInstance().GetDataPage(pageNumber);
    dataPagesCached[dataPagePos].second = pageNumber;
    dataPagePos++; 
    return dataPagesCached[dataPagePos-1].first;
}
void Cache::ClearDataCache()
{
    dataPagesCached.clear();
    dataPagePos = 0;
}