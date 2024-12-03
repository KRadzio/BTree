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

void BTree::Search() {}
void BTree::Add() {}
void BTree::Delete() {}
void BTree::Diplay() {}