#include "BTree.hpp"

BTree::BTree() { FileManager::GetInstance().SetNodeSize(order * 2); }
BTree::~BTree() {}

BTree &BTree::GetInstance()
{
    static BTree *instance = new BTree;
    return *instance;
}

void BTree::SetOrder(unsigned int order)
{
    // change order, node size and clear files
    this->order = order;
    FileManager::GetInstance().SetNodeSize(order * 2);
    height = 0;
    rootNodeNum = 0;
    FileManager::GetInstance().ClearBothFile();
}