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
    Cache::GetInstance().SetSize(height + 1);
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

bool BTree::Search(size_t key, bool clearCache)
{
    if (rootNodeNum == NO_ROOT) // BTree is empty
        return false;
    if (key == INVALID_INDEX) // invalid input
        return false;
    size_t currNodeNum = rootNodeNum;
    bool found = SearchRecursive(currNodeNum, key);
    if (clearCache) // in insert we do not want this
        Cache::GetInstance().ClearCache();
    return found;
}
void BTree::Add(RecordData &rd)
{
    // invalid input will not be alowed
    if (rd.index == INVALID_INDEX || rd.value == EMPTY_RECORD || rd.value.length() > VALUE_MAX_LENGTH)
        return;
    if (Search(rd.index, false))
        Cache::GetInstance().ClearCache();
    else
    {
        if (rootNodeNum == NO_ROOT) // the btree is empty
        {
            CreateRootNode(rd);
            Cache::GetInstance().ClearCache();
            return;
        }

        auto currNodePair = Cache::GetInstance().Pop();
        // node number is needed for saving back to file
        if (currNodePair.first.usedIndexes < 2 * order)
            AddToNode(currNodePair.first, currNodePair.second, rd);
        // try compensate
        // try split
        Cache::GetInstance().ClearCache();
        // use the cache to not read the pages twice
    }
}
void BTree::Delete(RecordIndex ri) {}
void BTree::Diplay() {}

bool BTree::SearchRecursive(size_t currNodeNum, size_t key)
{
    if (currNodeNum == INVALID_NODE) // end of tree (leafs do not have children)
        return false;
    Node currNode = FileManager::GetInstance().GetNode(currNodeNum);
    Cache::GetInstance().Push(currNode, currNodeNum);
    if (key < currNode.indexes[0].index) // smaller than first
        return SearchRecursive(currNode.childrenNodesNumbers[0], key);
    for (size_t i = 0; i < currNode.indexes.size() - 1; i++)
    {
        if (currNode.indexes[i].index == key)
            return true;
        if (currNode.indexes[i].index < key && (currNode.indexes[i + 1].index > key || currNode.indexes[i + 1].index == INVALID_INDEX)) //  x< key < x+1
            return SearchRecursive(currNode.childrenNodesNumbers[i + 1], key);
    }
    if (key == currNode.indexes[currNode.indexes.size() - 1].index) // the biggest one is equal
        return true;
    if (key > currNode.indexes[currNode.indexes.size() - 1].index) // larger than biggest
        return SearchRecursive(currNode.childrenNodesNumbers[currNode.childrenNodesNumbers.size() - 1], key);
    // we can remove the last if since all other condicions are already checked
    // but for now the return at the end can stay
    // to remove warning, the key will fall to one of the categories above
    return false;
}

void BTree::AddToNode(Node &node, size_t nodeNumber, RecordData &rd)
{
    node.usedIndexes++; // incremented at the begining
    RecordIndex ri;
    ri.index = rd.index;
    ri.pageNumber = FileManager::GetInstance().InsertNewRecord(rd);
    // the first empty place is indicated by usedIndexes
    for (size_t i = node.usedIndexes - 1; i >= 1; i--)
    {
        if (node.indexes[i - 1].index > ri.index)
        {
            node.indexes[i] = node.indexes[i - 1];
            node.indexes[i - 1] = ri;
        }
        else // place found
        {
            node.indexes[i] = ri;
            break;
        }
    }
    FileManager::GetInstance().UpdateNode(node, nodeNumber);
}

void BTree::CreateRootNode(RecordData &rd)
{
    height++;
    Cache::GetInstance().SetSize(height + 1);
    Node n;
    n.parentNodeNum = NO_PARENT;
    n.usedIndexes = 1;
    n.childrenNodesNumbers = std::vector<size_t>(order * 2 + 1);
    for (size_t i = 0; i < n.childrenNodesNumbers.size(); i++)
        n.childrenNodesNumbers[i] = NO_CHILDREN;
    n.indexes = std::vector<RecordIndex>(order * 2);
    n.indexes[0].index = rd.index;
    n.indexes[0].pageNumber = FileManager::GetInstance().InsertNewRecord(rd);
    for (size_t i = 1; i < n.indexes.size(); i++)
    {
        n.indexes[i].index = INVALID_INDEX;
        n.indexes[i].pageNumber = INVALID_PAGE;
    }
    rootNodeNum = FileManager::GetInstance().InsertNewNode(n);
}

void BTree::Compensate() {}
void BTree::Split() {}