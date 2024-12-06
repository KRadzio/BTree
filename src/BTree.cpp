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
    nodePassedUp = false;
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
        RecordIndex ri;
        ri.index = rd.index;
        ri.pageNumber = FileManager::GetInstance().InsertNewRecord(rd);
        AddRecursive(ri);
        Cache::GetInstance().ClearCache();
    }
}

void BTree::Delete(size_t key)
{
    if (key == INVALID_INDEX)
        return;
    if (!Search(key, false))
        Cache::GetInstance().ClearCache();
    else
    {
        RecordIndex ri;
        ri.index = key;
        auto node = Cache::GetInstance().GetLast();
        for (size_t i = 0; i < node.first.indexes.size(); i++)
            if (node.first.indexes[i].index == key)
            {
                ri.pageNumber = node.first.indexes[i].pageNumber;
                break;
            }
        DeleteRecursive(ri);
        Cache::GetInstance().ClearCache();
    }
}

void BTree::Diplay() {}

void BTree::Update(RecordData &rd)
{
    if (rd.index == INVALID_INDEX)
        return;
    if (!Search(rd.index, false))
        return;
    else
    {
        auto node = Cache::GetInstance().GetLast();
        size_t pos = 0;
        for (size_t i = 0; i < node.first.usedIndexes; i++)
            if (rd.index == node.first.indexes[i].index)
            {
                pos = i;
                break;
            }
        auto dataPage = FileManager::GetInstance().GetDataPage(node.first.indexes[pos].pageNumber);
        for (size_t i = 0; i < DATA_PAGE_SIZE; i++)
            if (dataPage.records[i].index == rd.index)
            {
                dataPage.records[i].value = rd.value;
                break;
            }
        FileManager::GetInstance().UpdateDataPage(node.first.indexes[pos].pageNumber, dataPage);
        Cache::GetInstance().ClearCache();
    }
}

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
    return false;
}

void BTree::AddRecursive(RecordIndex &ri)
{
    std::pair<Node, size_t> currNodePair;
    if (nodePassedUp)
    {
        auto nodePassed = Cache::GetInstance().Pop();
        currNodePair = Cache::GetInstance().Pop();
        Cache::GetInstance().Push(nodePassed.first, nodePassed.second); // push it back
    }
    else
        currNodePair = Cache::GetInstance().Pop();
    if (currNodePair.first.usedIndexes < 2 * order)
    {
        AddToNode(currNodePair.first, currNodePair.second, ri);
        return;
    }
    // try compensate
    bool compensationPossible = TryCompensate(currNodePair.first, currNodePair.second, ri);
    if (!compensationPossible)
    {
        if (currNodePair.first.parentNodeNum == NO_PARENT) // in root
            SplitRoot(currNodePair.first, ri);
        else
        {
            Split(currNodePair.first, currNodePair.second, ri);
            AddRecursive(ri);
        }
    }
}

void BTree::DeleteRecursive(RecordIndex &ri)
{
}

void BTree::AddToNode(Node &node, size_t nodeNumber, RecordIndex &ri)
{
    std::pair<Node, size_t> nodePassed;
    if (nodePassedUp) // if node is passed up
        nodePassed = Cache::GetInstance().Pop();
    node.usedIndexes++; // incremented at the begining
                        // the first empty place is indicated by usedIndexes
    for (size_t i = node.usedIndexes - 1; i >= 1; i--)
    {
        if (node.indexes[i - 1].index > ri.index)
        {
            node.indexes[i] = node.indexes[i - 1];
            node.indexes[i - 1] = ri;
            if (nodePassedUp)
            {
                node.childrenNodesNumbers[i + 1] = node.childrenNodesNumbers[i];
                node.childrenNodesNumbers[i] = nodePassed.second;
            }
        }
        else // place found
        {
            node.indexes[i] = ri;
            if (nodePassedUp)
                node.childrenNodesNumbers[i + 1] = nodePassed.second;
            break;
        }
    }
    if (nodePassedUp)
        nodePassedUp = false;
    FileManager::GetInstance().UpdateNode(node, nodeNumber);
}

void BTree::CreateRootNode(RecordData &rd)
{
    height++;
    Cache::GetInstance().SetSize(height + 1);
    Node n;
    InitNode(n, NO_PARENT);
    n.usedIndexes = 1;
    n.indexes[0].index = rd.index;
    n.indexes[0].pageNumber = FileManager::GetInstance().InsertNewRecord(rd);
    rootNodeNum = FileManager::GetInstance().InsertNewNode(n);
}

bool BTree::TryCompensate(Node &currNode, size_t currNodeNumber, RecordIndex &ri)
{
    // compensate only in leafs for now
    if (currNode.parentNodeNum == NO_PARENT) // root
        return false;

    std::pair<Node, size_t> parentNodePair;
    if (nodePassedUp)
    {
        auto nodePassed = Cache::GetInstance().Pop();
        parentNodePair = Cache::GetInstance().GetLast();
        Cache::GetInstance().Push(nodePassed.first, nodePassed.second); // push it back
    }
    else
        parentNodePair = Cache::GetInstance().GetLast();

    size_t pos;
    Node leftSibling;
    Node rightSibling;
    for (size_t i = 0; i < parentNodePair.first.childrenNodesNumbers.size(); i++)
        if (currNodeNumber == parentNodePair.first.childrenNodesNumbers[i])
        {
            pos = i;
            break;
        }
    // left most
    if (pos == 0)
    {
        rightSibling = FileManager::GetInstance().GetNode(parentNodePair.first.childrenNodesNumbers[pos + 1]);
        if (rightSibling.usedIndexes == order * 2)
            return false;
        else
        {
            Cache::GetInstance().Push(rightSibling, parentNodePair.first.childrenNodesNumbers[pos + 1]);
            Compensate(currNode, currNodeNumber, pos, ri, RIGHT);
            return true;
        }
    }
    // right most
    if (pos == parentNodePair.first.usedIndexes)
    {
        leftSibling = FileManager::GetInstance().GetNode(parentNodePair.first.childrenNodesNumbers[pos - 1]);
        if (leftSibling.usedIndexes == order * 2)
            return false;
        else
        {
            Cache::GetInstance().Push(leftSibling, parentNodePair.first.childrenNodesNumbers[pos - 1]);
            Compensate(currNode, currNodeNumber, pos, ri, LEFT);
            return true;
        }
    }
    // in between
    leftSibling = FileManager::GetInstance().GetNode(parentNodePair.first.childrenNodesNumbers[pos - 1]);
    rightSibling = FileManager::GetInstance().GetNode(parentNodePair.first.childrenNodesNumbers[pos + 1]);
    if (leftSibling.usedIndexes == order * 2 && rightSibling.usedIndexes == order * 2)
        return false;
    else
    {
        if (leftSibling.usedIndexes < order * 2)
        {
            Cache::GetInstance().Push(leftSibling, parentNodePair.first.childrenNodesNumbers[pos - 1]);
            Compensate(currNode, currNodeNumber, pos, ri, LEFT);
        }
        if (rightSibling.usedIndexes < order * 2)
        {
            Cache::GetInstance().Push(rightSibling, parentNodePair.first.childrenNodesNumbers[pos + 1]);
            Compensate(currNode, currNodeNumber, pos, ri, RIGHT);
        }
        return true;
    }
}

void BTree::Compensate(Node &currNode, size_t currNodeNumber, size_t pos, RecordIndex &ri, int direction)
{
    auto sibling = Cache::GetInstance().Pop();

    std::pair<Node, size_t> parent;
    std::pair<Node, size_t> nodePassed;
    if (nodePassedUp)
    {
        nodePassed = Cache::GetInstance().Pop();
        parent = Cache::GetInstance().GetLast();
    }
    else
        parent = Cache::GetInstance().GetLast();

    // put all indexed to one vector
    std::vector<RecordIndex> indexes = currNode.indexes;
    indexes.push_back(ri);
    if (direction == LEFT)
        indexes.push_back(parent.first.indexes[pos - 1]);
    else
        indexes.push_back(parent.first.indexes[pos]);
    for (size_t i = 0; i < sibling.first.usedIndexes; i++)
        indexes.push_back(sibling.first.indexes[i]);

    std::sort(indexes.begin(), indexes.end(), [](const RecordIndex &ri1, const RecordIndex &ri2)
              { return ri1.index < ri2.index; });

    size_t mid = indexes.size() / 2;

    if (direction == LEFT) // rotate left
    {
        // move indexes
        if (indexes.size() % 2 == 0)
            mid--;
        for (size_t i = mid + 1; i < indexes.size(); i++)
            currNode.indexes[i - mid - 1] = indexes[i];
        parent.first.indexes[pos - 1] = indexes[mid];
        for (size_t i = 0; i < mid; i++)
            sibling.first.indexes[i] = indexes[i];
        // move child node indexes
        if (nodePassedUp)
        {
            // first move to sibling then move children in currNode
            sibling.first.childrenNodesNumbers[sibling.first.usedIndexes + 1] = currNode.childrenNodesNumbers[0];
            auto node = FileManager::GetInstance().GetNode(currNode.childrenNodesNumbers[0]);
            node.parentNodeNum = sibling.second;
            FileManager::GetInstance().UpdateNode(node, currNode.childrenNodesNumbers[0]);
            size_t newNodePos;
            for (size_t i = 0; i < currNode.indexes.size(); i++)
                if (currNode.indexes[i].index > nodePassed.first.indexes[0].index)
                {
                    newNodePos = i;
                    break;
                }
            for (size_t i = 0; i < newNodePos; i++)
                currNode.childrenNodesNumbers[i] = currNode.childrenNodesNumbers[i + 1];
            currNode.childrenNodesNumbers[newNodePos] = nodePassed.second;
        }
    }
    else // rotate right
    {
        // move indexes
        for (size_t i = 0; i < mid; i++)
            currNode.indexes[i] = indexes[i];
        parent.first.indexes[pos] = indexes[mid];
        for (size_t i = mid + 1; i < indexes.size(); i++)
            sibling.first.indexes[i - mid - 1] = indexes[i];
        // move child node indexes
        if (nodePassedUp)
        {
            // first move children in sibling then add node passed
            for (size_t i = sibling.first.usedIndexes + 1; i > 0; i--)
                sibling.first.childrenNodesNumbers[i] = sibling.first.childrenNodesNumbers[i - 1];

            sibling.first.childrenNodesNumbers[0] = nodePassed.second;
            nodePassed.first.parentNodeNum = sibling.second;
            FileManager::GetInstance().UpdateNode(nodePassed.first, nodePassed.second);
        }
    }
    sibling.first.usedIndexes++;
    if (nodePassedUp)
        nodePassedUp = false;
    FileManager::GetInstance().UpdateNode(currNode, parent.first.childrenNodesNumbers[pos]);
    FileManager::GetInstance().UpdateNode(parent.first, parent.second);
    FileManager::GetInstance().UpdateNode(sibling.first, sibling.second);
}

void BTree::Split(Node &currNode, size_t currNodeNumber, RecordIndex &ri)
{
    std::pair<Node, size_t> parent;
    std::pair<Node, size_t> nodePassed;
    if (nodePassedUp)
    {
        nodePassed = Cache::GetInstance().Pop();
        parent = Cache::GetInstance().GetLast();
    }
    else
        parent = Cache::GetInstance().GetLast();
    std::vector<RecordIndex> indexes = currNode.indexes;
    indexes.push_back(ri);
    std::sort(indexes.begin(), indexes.end(), [](const RecordIndex &ri1, const RecordIndex &ri2)
              { return ri1.index < ri2.index; });
    size_t mid = indexes.size() / 2;
    Node newNode;
    InitNode(newNode, parent.second);
    currNode.usedIndexes = newNode.usedIndexes = order;

    if (nodePassedUp)
    {
        size_t nodePos = 0;
        FindNodePos(nodePos, nodePassed, indexes);
        std::vector<size_t> childNodesNumber = currNode.childrenNodesNumbers;
        childNodesNumber.emplace(childNodesNumber.begin() + nodePos, nodePassed.second);
        // split child pages between nodes
        SetChildNodesIndexes(childNodesNumber, currNode, newNode, mid);
    }
    // setIndexes
    for (size_t i = 0; i < order; i++)
        currNode.indexes[i] = indexes[i];
    for (size_t i = 0; i < order; i++)
        newNode.indexes[i] = indexes[i + mid + 1];
    for (size_t i = order; i < currNode.indexes.size(); i++)
    {
        currNode.indexes[i].index = INVALID_INDEX;
        currNode.indexes[i].pageNumber = INVALID_PAGE;
        if (nodePassedUp)
            currNode.childrenNodesNumbers[i + 1] = NO_CHILDREN;
    }

    FileManager::GetInstance().UpdateNode(currNode, currNodeNumber);

    ri = indexes[mid];                                                     // ri changed
    size_t nodeNumber = FileManager::GetInstance().InsertNewNode(newNode); // save new node to disk

    // update children only in new node
    if (nodePassedUp)
        ChangeParents(newNode, nodeNumber);

    Cache::GetInstance().Push(newNode, nodeNumber); // insert new node to cache
    nodePassedUp = true;                            // set the flag
}

void BTree::SplitRoot(Node &currNode, RecordIndex &ri)
{
    height++;
    std::pair<Node, size_t> nodePassed;
    if (nodePassedUp)
        nodePassed = Cache::GetInstance().Pop();
    std::vector<RecordIndex> indexes = currNode.indexes;
    indexes.push_back(ri);
    std::sort(indexes.begin(), indexes.end(), [](const RecordIndex &ri1, const RecordIndex &ri2)
              { return ri1.index < ri2.index; });
    size_t mid = indexes.size() / 2;

    // root can have only one record and when it split it will only have one
    Node leftChild;
    Node rightChild;
    InitNode(leftChild, rootNodeNum);
    InitNode(rightChild, rootNodeNum);

    // set child nodes
    if (nodePassedUp)
    {
        size_t nodePos = 0;
        FindNodePos(nodePos, nodePassed, indexes);
        std::vector<size_t> childNodesNumber = currNode.childrenNodesNumbers;
        childNodesNumber.emplace(childNodesNumber.begin() + nodePos, nodePassed.second);
        SetChildNodesIndexes(childNodesNumber, leftChild, rightChild, mid);
    }

    for (size_t i = 0; i < mid; i++)
        leftChild.indexes[i] = indexes[i];
    for (size_t i = mid + 1; i < indexes.size(); i++)
        rightChild.indexes[i - mid - 1] = indexes[i];

    leftChild.usedIndexes = rightChild.usedIndexes = order;

    // reset root
    InitNode(currNode, NO_PARENT);
    currNode.usedIndexes++;
    currNode.indexes[0] = indexes[mid];
    currNode.childrenNodesNumbers[0] = FileManager::GetInstance().InsertNewNode(leftChild);
    currNode.childrenNodesNumbers[1] = FileManager::GetInstance().InsertNewNode(rightChild);

    // change parent of nodes since two new nodes are added
    if (nodePassedUp)
    {
        ChangeParents(leftChild, currNode.childrenNodesNumbers[0]);
        ChangeParents(rightChild, currNode.childrenNodesNumbers[1]);
        nodePassedUp = false;
    }

    FileManager::GetInstance().UpdateNode(currNode, rootNodeNum);

    Cache::GetInstance().SetSize(height + 1);
}

void BTree::InitNode(Node &node, size_t parentNum)
{
    node.parentNodeNum = parentNum;
    node.usedIndexes = 0;
    node.indexes = std::vector<RecordIndex>(order * 2);
    node.childrenNodesNumbers = std::vector<size_t>(order * 2 + 1);
    for (size_t i = 0; i < node.indexes.size(); i++)
    {
        node.indexes[i].index = INVALID_INDEX;
        node.indexes[i].pageNumber = INVALID_PAGE;
    }
    for (size_t i = 0; i < node.childrenNodesNumbers.size(); i++)
        node.childrenNodesNumbers[i] = NO_CHILDREN;
}

void BTree::ChangeParents(Node &child, size_t newParentNumber)
{
    for (size_t i = 0; i <= order; i++)
    {
        auto node = FileManager::GetInstance().GetNode(child.childrenNodesNumbers[i]);
        node.parentNodeNum = newParentNumber;
        FileManager::GetInstance().UpdateNode(node, child.childrenNodesNumbers[i]);
    }
}

void BTree::SetChildNodesIndexes(std::vector<size_t> &childNodesNumber, Node &dst1, Node &dst2, size_t mid)
{
    for (size_t i = 0; i < childNodesNumber.size(); i++)
    {
        if (i <= mid)
            dst1.childrenNodesNumbers[i] = childNodesNumber[i];
        else
            dst2.childrenNodesNumbers[i - mid - 1] = childNodesNumber[i];
    }
}

void BTree::FindNodePos(size_t &nodePos, std::pair<Node, size_t> &nodePassed, std::vector<RecordIndex> &indexes)
{
    for (size_t i = 0; i < indexes.size(); i++)
        if (indexes[i].index > nodePassed.first.indexes[0].index)
        {
            nodePos = i;
            break;
        }
    if (nodePos == 0) // imposible to be placed there
        nodePos = indexes.size();
}
