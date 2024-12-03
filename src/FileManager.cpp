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
        getline(file, line);
        ss = std::stringstream(line);
        RecordIndex ri;
        getline(ss, line, DELIMITER);
        ri.index = std::stoul(line);
        getline(ss, line);
        ri.pageNumber = std::stoul(line);
        n.indexes[i] = ri;
        // child node
        getline(file, line);
        n.childrenNodesNumbers[i + 1] = std::stoul(line);
    }
    file.close();
    return n;
}

size_t FileManager::InsertNewNode(Node &node)
{
    std::string line;
    std::fstream file;
    file.open(INDEX_FILE, std::ios_base::out | std::ios_base::in);
    size_t nodeNumber = 1;
    while (!file.eof())
    {
        // break loop faster
        getline(file, line); // header
        if(file.eof())
            break;
        std::stringstream ss(line);
        getline(ss, line, DELIMITER); // parent number
        getline(ss, line); // used indexed
        if (std::stoi(line) == EMPTY_NODE)
            break;
        getline(file, line);                            // first child node
        for (unsigned int j = 0; j < nodeSize * 2; j++) // n child nodes and n records
            getline(file, line);
        nodeNumber++;
    }
    if (file.eof())
    {
        file.close();
        CreateNewNode(node);
        return nodeNumber;
    }
    file.close();
    UpdateNode(node,nodeNumber);
    return nodeNumber; // we need to return the node number
} // check if there are empty then either update the empty one or create new one

void FileManager::UpdateNode(Node &node, size_t nodeNumber)
{
    // remember to push elements to queue
    std::string line;
    std::fstream file;
    file.open(INDEX_FILE, std::ios_base::out | std::ios_base::in);
    for (size_t i = 1; i < nodeNumber; i++)
    {
        getline(file, line);                            // header
        getline(file, line);                            // first child node
        for (unsigned int j = 0; j < nodeSize * 2; j++) // n child nodes and n records
            getline(file, line);
    }
    WriteNode(node, file);
    file.close();
}

void FileManager::UpdateDataPage(size_t pageNum, DataPage &dataPage)
{
    std::string line;
    std::fstream file;
    file.open(DATA_FILE, std::ios_base::out | std::ios_base::in);
    for (size_t i = 1; i < pageNum; i++)
    {
        getline(file, line); // header
        for (int j = 0; j < DATA_PAGE_SIZE; j++)
            getline(file, line);
    }
    WriteDataPage(dataPage, file);
    file.close();
}

size_t FileManager::InsertNewRecord(RecordData &newRecord)
{
    std::string line;
    std::fstream file;
    file.open(DATA_FILE, std::ios_base::out | std::ios_base::in);
    size_t pageNumber = 1;
    while (!file.eof())
    {
        getline(file, line); // header
        if (std::stoi(line) < DATA_PAGE_SIZE)
            break;
        for (int i = 0; i < DATA_PAGE_SIZE; i++)
            getline(file, line); // records
        pageNumber++;
    }
    if (file.eof())
    {
        CreateNewDataPage(newRecord);
        file.close();
        return pageNumber;
    }
    DataPage dp;
    dp.filledRecords = std::stoi(line) + 1;
    dp.records = std::vector<RecordData>(DATA_PAGE_SIZE);
    bool found = false;
    for (size_t i = 0; i < DATA_PAGE_SIZE; i++)
    {
        RecordData rd;
        getline(file, line);
        std::stringstream ss(line);
        getline(ss, line, DELIMITER);
        rd.index = std::stoul(line);
        getline(ss, line);
        rd.value = line;
        dp.records[i] = rd;
        if (!found && dp.records[i].index == INVALID_INDEX)
        {
            dp.records[i] = newRecord;
            found = true;
        } // we still have to load the entire page
    }
    file.close();
    // one read to find empty place
    // then one save to write it
    UpdateDataPage(pageNumber, dp);
    return pageNumber;
} // insert at the first empty page

DataPage FileManager::GetDataPage(size_t pageNum)
{
    std::string line;
    std::ifstream file;
    DataPage dp;
    dp.records = std::vector<RecordData>(DATA_PAGE_SIZE);
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
        return dp;
    }
    getline(file, line); // header
    dp.filledRecords = std::stoi(line);
    for (size_t i = 0; i < dp.records.size(); i++)
    {
        RecordData rd;
        getline(file, line);
        std::stringstream ss(line);
        getline(ss, line, DELIMITER);
        rd.index = std::stoul(line);
        getline(ss, line, UNUSEDBYTE);
        rd.value = line;
        dp.records[i] = rd;
    }
    file.close();
    return dp;
}

void FileManager::CreateNewNode(Node &node)
{
    std::fstream file;
    file.open(INDEX_FILE, std::ios_base::app | std::ios_base::out);
    WriteNode(node, file);
    file.close();
}

void FileManager::CreateNewDataPage(RecordData &newRecord)
{
    std::fstream file;
    file.open(DATA_FILE, std::ios_base::out | std::ios_base::app);
    FormatAndWriteNumber(1, file, INT32_MAX_LENGTH);
    file << std::endl;
    FormatAndWriteNumber(newRecord.index, file, INT64_MAX_LENGTH);
    file << " ";
    FormatValue(newRecord.value, file);
    file << std::endl;
    for (int i = 0; i < DATA_PAGE_SIZE - 1; i++)
    {
        FormatAndWriteNumber(0, file, INT64_MAX_LENGTH);
        file << " ";
        FormatValue(EMPTY_RECORD, file);
        file << std::endl;
    }
    file.close();
}

void FileManager::WriteNode(Node &node, std::fstream &file)
{
    FormatAndWriteNumber(node.parentNodeNum, file, INT64_MAX_LENGTH);
    file << " ";
    FormatAndWriteNumber(node.usedIndexes, file, INT32_MAX_LENGTH);
    file << std::endl;
    FormatAndWriteNumber(node.childrenNodesNumbers[0], file, INT64_MAX_LENGTH);
    file << std::endl;
    for (size_t i = 0; i < nodeSize; i++)
    {
        FormatAndWriteNumber(node.indexes[i].index, file, INT64_MAX_LENGTH);
        file << " ";
        FormatAndWriteNumber(node.indexes[i].pageNumber, file, INT64_MAX_LENGTH);
        file << std::endl;
        FormatAndWriteNumber(node.childrenNodesNumbers[i + 1], file, INT64_MAX_LENGTH);
        file << std::endl;
    }
}

void FileManager::WriteDataPage(DataPage &dp, std::fstream &file)
{
    FormatAndWriteNumber(dp.filledRecords, file, INT32_MAX_LENGTH);
    file << std::endl;
    for (size_t i = 0; i < DATA_PAGE_SIZE; i++)
    {
        FormatAndWriteNumber(dp.records[i].index, file, INT64_MAX_LENGTH);
        file << " ";
        FormatValue(dp.records[i].value, file);
        file << std::endl;
    }
}

void FileManager::FormatAndWriteNumber(size_t number, std::fstream &file, int length)
{
    int counter = 0;
    size_t tmp = number;
    while (tmp > 0)
    {
        tmp /= 10;
        counter++;
    }
    for (int i = 0; i < length - counter; i++)
        file << '0';
    if (counter > 0)
        file << number;
}

void FileManager::FormatValue(std::string value, std::fstream &file)
{
    size_t len = VALUE_MAX_LENGTH - value.size();
    if (value.size() > 0)
        file << value;
    for (size_t i = 0; i < len; i++)
        file << UNUSEDBYTE;
}