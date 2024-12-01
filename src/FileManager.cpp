#include "FileManager.hpp"

FileManager::FileManager() {}
FileManager::~FileManager() {}

FileManager &FileManager::GetInstance()
{

    static FileManager *instance = new FileManager;
    return *instance;
}

void FileManager::ClearBothFile()
{
}

Node FileManager::GetNode(size_t nodeNumber)
{
    Node n;
    n.parentNodeNum = 5;

    return n;
}

void FileManager::UpdateDataPage(size_t pageNum, RecordData &newRecord)
{
}