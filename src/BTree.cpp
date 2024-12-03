#include "BTree.hpp"

BTree::BTree() {}
BTree::~BTree() {}

BTree &BTree::GetInstance()
{
    static BTree *instance = new BTree;
    return *instance;
}

void BTree::Init(unsigned int order)
{
    this->order = order;
    FileManager::GetInstance().SetNodeSize(order * 2);
}

void BTree::SetOrder(unsigned int order)
{
    // change order, node size and clear files
    this->order = order;
    FileManager::GetInstance().SetNodeSize(order * 2);
    height = 0;
    rootNodeNum = 0;
    FileManager::GetInstance().ClearBothFiles();
}

void BTree::Search(size_t key)
{
    // maybe clear cache by default after search
    // also this needs to return something
    if (rootNodeNum == NO_ROOT)
    {
        std::cout << "The BTree is empty \n";
        return;
    }
    if (key == INVALID_INDEX)
    {
        std::cout << "Not found, invalid index \n";
        return;
    }
    size_t currNodeNum = rootNodeNum;
    SearchRecursive(currNodeNum, key);
    return;
}
void BTree::Add(RecordData rd) {}
void BTree::Delete(RecordIndex ri) {}
void BTree::Diplay() {}

void BTree::SearchRecursive(size_t currNodeNum, size_t key)
{
    if (currNodeNum == INVALID_NODE)
    {
        std::cout << "Not found " << key << " page empty\n";
        return;
    }
    Node currNode = FileManager::GetInstance().GetNode(currNodeNum);
    if (key < currNode.indexes[0].index) // smaller than first
    {
        SearchRecursive(currNode.childrenNodesNumbers[0], key);
        return;
    }
    for (size_t i = 0; i < currNode.indexes.size() - 1; i++)
    {
        if (currNode.indexes[i].index == key)
        {
            std::cout << "Found: " << key << std::endl;
            return;
        }
        if (currNode.indexes[i].index < key && currNode.indexes[i + 1].index > key) //  x< key < x+1
        {
            SearchRecursive(currNode.childrenNodesNumbers[i + 1], key);
            return;
        }
    }
    if (key == currNode.indexes[currNode.indexes.size() - 1].index) // the biggest one is equal
    {
        std::cout << "Found: " << key << std::endl;
        return;
    }
    if (key > currNode.indexes[currNode.indexes.size() - 1].index) // larger than biggest
    {
        SearchRecursive(currNode.childrenNodesNumbers[currNode.childrenNodesNumbers.size() - 1], key);
        return;
    }
}