#ifndef NODE_HPP
#define NODE_HPP

#include <vector>

#include "Records.hpp"

struct Node
{
    size_t parentNodeNum = 0;
    int usedIndexes = 0;
    std::vector<size_t> childrenNodesNumbers;
    std::vector<RecordIndex> indexes;
};

#endif
