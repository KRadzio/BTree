#ifndef RECORD_HPP
#define RECORD_HPP

#include <string>

#define EMPTY_RECORD ""
#define INVALID_INDEX 0
#define INVALID_PAGE 0

struct RecordData
{
    size_t index = INVALID_INDEX;
    std::string value = EMPTY_RECORD;
};

struct RecordIndex
{
    size_t index = INVALID_INDEX;
    size_t pageNumber = INVALID_PAGE;
};

#endif
