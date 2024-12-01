#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include <fstream>
#include <vector>

#include "Node.hpp"

#define DATA_PAGE_SIZE 10;
// data is stored in pages
// pages have their number
// key -> value of each of the elements
// if empty then use some special value (0 / NULL or something)
// index file contains pages of BTree (nodes)
// pointers to child pages
// keys and page number in data file
// maybe a page num in index file

// Index file page structure
// header (parent number, number of free places)
// pointer to child (0 for null)
// key - page number in data
// the higher the d the longer the page will be

// Data file page structure
// header (is full)
// key value
// page size ~ 100 records may be good

// UpdatePage - Load the data page to memory , update record then save back to disk

class FileManager
{
public:
    static FileManager &GetInstance();
    void ClearBothFile();
    inline void SetNodeSize(unsigned int nodeSize) { this->nodeSize = nodeSize; }

    Node GetNode(size_t nodeNumber);
    // get data page


    // return page number
    void UpdateDataPage(size_t pageNum, RecordData &newRecord);

    // update index page
    // crate index page (when there is no empty page)
    // create new data page (new recprd can be inserted to page than still have free space)


private:
    FileManager();
    ~FileManager();

private:
    unsigned int nodeSize = 0;
    // maybe something to store free pages?
    // it may be a file
};
#endif
