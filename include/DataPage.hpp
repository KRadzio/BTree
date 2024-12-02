#ifndef DATA_PAGE_HPP
#define DATA_PAGE_HPP

#include <vector>

#include "Records.hpp"

struct DataPage
{
    unsigned int filledRecords;
    std::vector<RecordData> records;
};


#endif
