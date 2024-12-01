#include "FileManager.hpp"

FileManager::FileManager() {}
FileManager::~FileManager() {}

FileManager &FileManager::GetInstance()
{

    static FileManager *instance = new FileManager;
    return *instance;
}

void FileManager::ClearBothFiles()
{
    // by default ofstream has the trunc flag
    std::ofstream file;
    file.open(INDEX_FILE);
    file.close();
    file.open(DATA_FILE);
    file.close();
}

Node FileManager::GetNode(size_t nodeNumber)
{
    std::string line;
    std::ifstream file;
    Node n;
    n.childrenNodesNumbers = std::vector<size_t>(nodeSize + 1);
    n.indexes = std::vector<RecordIndex>(nodeSize);
    file.open(INDEX_FILE);
    for (size_t i = 1; i < nodeNumber; i++)
    {
        getline(file, line);                            // header
        getline(file, line);                            // first child node
        for (unsigned int j = 0; j < nodeSize * 2; j++) // n child nodes and n records
            getline(file, line);
    }

    getline(file, line); // header
    std::stringstream ss(line);
    getline(ss, line, DELIMITER);
    n.parentNodeNum = std::stoul(line);
    getline(ss, line);
    n.usedIndexes = std::stoi(line);
    getline(file, line); // first child
    n.childrenNodesNumbers[0] = std::stoul(line);
    for (unsigned int i = 0; i < nodeSize; i++)
    {
        // record
        getline(file,line);
        ss = std::stringstream(line);
        RecordIndex ri;
        getline(ss, line, DELIMITER);
        ri.index = std::stoul(line);
        getline(ss, line);
        ri.pageNumber = std::stoul(line);
        n.indexes[i] = ri;
        //child node
        getline(file, line);
         n.childrenNodesNumbers[i+1] = std::stoul(line);
    }
    file.close();
    return n;
}

void FileManager::InsertNewNode(Node &node) {}
void FileManager::UpdateNode(Node &node, size_t nodeNumber) {}
void FileManager::UpdateDataPage(size_t pageNum, RecordData &newRecord) {}
void FileManager::InsertNewRecord(RecordData &newRecord) {}
std::vector<RecordData> FileManager::GetDataPage(size_t pageNum)
{
    std::string line;
    std::ifstream file;
    std::vector<RecordData> v = std::vector<RecordData>(DATA_PAGE_SIZE);
    file.open(DATA_FILE);
    for (size_t i = 1; i < pageNum; i++)
    {
        getline(file, line); // header
        for (size_t j = 0; j < DATA_PAGE_SIZE; j++)
            getline(file, line); // records
    }
    if (file.eof())
    {
        std::cout << "Page out of bounds" << std::endl;
        return v;
    }
    getline(file, line); // skip header
    for (size_t i = 0; i < v.size(); i++)
    {
        RecordData rd;
        getline(file, line);
        std::stringstream ss(line);
        getline(ss, line, DELIMITER);
        rd.index = std::stoul(line);
        getline(ss, line);
        rd.value = line;
        v[i] = rd;
    }
    file.close();
    return v;
}

void FileManager::CreateNewNode(Node &node) {}