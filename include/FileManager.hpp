#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

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
#define EMPTY_NODE 0
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
    void ResetReadsAndWrites();
    // we need to know the node size to read the index file
    // after calling it the tree will be basicly reseted
    void SetNodeSize(unsigned int nodeSize); 

    // getting stats
    inline size_t GetDataReads() { return dataReads; }
    inline size_t GetDataWrites() { return dataWrites; }
    inline size_t GetIndexReads() { return indexReads; }
    inline size_t GetIndexWrites() { return indexWrites; }

    // Index file operations
    Node GetNode(size_t nodeNumber); // get node that has a number
    // if any space can be reused then reuse it else create new
    // REMEMBER TO FILL THE NODE CORRECTLY
    size_t InsertNewNode(Node &node);
    void UpdateNode(Node &node, size_t nodeNumber); // update node in file

    // Data file operations
    void UpdateDataPage(size_t pageNum, DataPage &dataPage); // for deleting
    size_t InsertNewRecord(RecordData &newRecord);           // for inserting
    DataPage GetDataPage(size_t pageNum);                    // for reading

    // helper function
private:
    void CreateNewNode(Node &node); // use when inserting
    void CreateNewDataPage(RecordData &newRecord);
    void WriteNode(Node &node, std::fstream &file);
    void WriteDataPage(DataPage &dp, std::fstream &file);
    void FormatAndWriteNumber(size_t number, std::fstream &file, int length); // so that records have fixed number
    void FormatValue(std::string value, std::fstream &file);

private:
    FileManager();
    ~FileManager();

private:
    unsigned int nodeSize = 0; // it is zero by default we have to set it
    size_t dataWrites = 0;
    size_t dataReads = 0;
    size_t indexWrites = 0;
    size_t indexReads = 0;
};
#endif
