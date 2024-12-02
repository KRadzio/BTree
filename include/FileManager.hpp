#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>

#include "Node.hpp"
#include "DataPage.hpp"

#define DATA_PAGE_SIZE 10 // can be by default or it can be changed if we want to?
#define DELIMITER ' '
#define UNUSEDBYTE '\0'
#define VALUE_MAX_LENGTH 30
#define INDEX_FILE "./files/indexfile.txt"
#define DATA_FILE "./files/data.txt"
#define INT32_MAX_LENGTH 10 // max int32 length in digits
#define INT64_MAX_LENGTH 20 // max int64 length in digit
// data is stored in pages
// pages have their number
// key -> value of each of the elements
// if empty then use some special value (0 / NULL or something)
// index file contains pages of BTree (nodes)
// pointers to child nodes
// keys and page number in data file
// maybe a page num in index file

// Index file page structure
// header (parent number, number of free places)
// pointer to child (0 for null)
// key - page number in data
// the higher the d the longer the page will be

// Data file page structure
// header (number of indexes in page)
// key value
// page size ~ 100 records may be good

// pages are indexed from 1

class FileManager
{
public:
    static FileManager &GetInstance();

    // settings
    void ClearBothFiles(); // clear index file and data file
    inline void SetNodeSize(unsigned int nodeSize) { this->nodeSize = nodeSize; }

    // Index file operations
    Node GetNode(size_t nodeNumber);                // get node that has a number
    size_t InsertNewNode(Node &node);               // if any space can be reused then reuse it else create new
    void UpdateNode(Node &node, size_t nodeNumber); // update node in file

    // Data file operations
    // change to page
    void UpdateDataPage(size_t pageNum, DataPage &dataPage); // for deleting
    size_t InsertNewRecord(RecordData &newRecord);           // for inserting
    // change to dataPage
    DataPage GetDataPage(size_t pageNum); // for reading

    // helper function
private:
    void CreateNewNode(Node &node); // use when inserting
    void CreateNewDataPage(RecordData &newRecord);
    void WriteNode(Node &node, std::fstream &file);
    void WriteDataPage(DataPage &dp, std::fstream &file);
    // get/read Node/DataPage as helper functions maybe?
    void FormatAndWriteNumber(size_t number, std::fstream &file, int length); // so that records have fixed number
    void FormatValue(std::string value, std::fstream &file);

private:
    FileManager();
    ~FileManager();

private:
    unsigned int nodeSize = 0;
    std::queue<size_t> freePages; // for now
    size_t freePagesIndex = 0;
    // swap it to a file or something
};
#endif
