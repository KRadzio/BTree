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

class FileManager
{
public:
    static FileManager &GetInstance();

    // settings
    void ClearBothFiles(); // clear index file and data file
    void ResetReadsAndWrites();
    void ResetDataReadsAndWrites();
    void ResetTotalIndexReadsAndWrites();
    // we need to know the node size to read the index file
    // after calling it the tree will be basicly reseted
    void SetNodeSize(unsigned int nodeSize); 

    // getting stats
    inline size_t GetDataReads() { return dataReads; }
    inline size_t GetDataWrites() { return dataWrites; }
    inline size_t GetIndexReads() { return indexReads; }
    inline size_t GetIndexWrites() { return indexWrites; }
    inline size_t GetTotalIndexReads() { return totalIndexReads; }
    inline size_t GetTotalIndexWrites() { return totalIndexWrites; }

    // Index file operations
    Node GetNode(size_t nodeNumber); // get node that has a number
    // if any space can be reused then reuse it else create new
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
    size_t totalIndexReads = 0;
    size_t totalIndexWrites = 0;
};
#endif
