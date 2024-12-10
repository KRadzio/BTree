#ifndef CACHE_HPP
#define CACHE_HPP

#include <iostream>
#include <stack>
#include <vector>

#include "Node.hpp"
#include "DataPage.hpp"
#include "FileManager.hpp"

#define MAX_DATAPAGES_CACHED 4

class Cache
{

public:
    static Cache &GetInstance();
    void SetSize(unsigned int size);          // changes size and resets cache
    void Push(Node &node, size_t nodeNumber); // node number is needed to save back to file if the node is modified
    void Push(std::pair<Node, size_t> &node);
    std::pair<Node, size_t> Pop();                                         // get last node and pop
    inline std::pair<Node, size_t> GetLast() { return cachedNodes.top(); } // get last saved node without poping
    void ClearCache();                                                     // to clear cached nodes

    // data pages
    DataPage &GetDataPage(size_t pageNumber);
    void ClearDataCache(); // to clear cached data pages

private:
    Cache();
    ~Cache();

private:
    unsigned int size = 1;
    size_t dataPagePos = 0;
    std::stack<std::pair<Node, size_t>> cachedNodes;
    std::vector<std::pair<DataPage,size_t>> dataPagesCached = std::vector<std::pair<DataPage,size_t>>(MAX_DATAPAGES_CACHED);
};

#endif
