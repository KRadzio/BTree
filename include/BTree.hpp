#ifndef BTREE_HPP
#define BTREE_HPP

#include <algorithm>

#include "FileManager.hpp"
#include "Cache.hpp"

#define DEFAULT_BTREE_ORDER 2;
#define NO_ROOT 0
#define INVALID_NODE 0
#define NO_PARENT 0
#define NO_CHILDREN 0
#define LEFT 1
#define RIGHT 2

// nodes may not be needed as separate class
// they are stored in text file
// data is also stored in another file

// cache for height + 1 pages

class BTree
{
public:
    static BTree &GetInstance();
    void Init(unsigned int order);
    void SetOrder(unsigned int order); // changes the order of the tree and resets the tree

    bool Search(size_t key, bool clearCache = true); // puts visited nodes in cache
    void Add(RecordData &rd);
    void Delete(size_t key);
    void Update(RecordData &rd);

    inline size_t GetRootNum() { return rootNodeNum; }

    // helper functions
private:
    bool SearchRecursive(size_t currNodeNum, size_t key);
    void AddRecursive(RecordIndex &ri);
    void PostDeletionFix();
    void AddToNode(Node &node, size_t nodeNumber, RecordIndex &ri);
    void CreateRootNode(RecordData &rd);
    bool TryCompensate(Node &currNode, size_t currNodeNumber, RecordIndex &ri);
    void Compensate(Node &currNode, size_t currNodeNumber, size_t pos, RecordIndex &ri, int direction);
    bool TryCompensateDeletion(std::pair<Node, size_t> &currNode);
    void CompensateDeletion(std::pair<Node, size_t> &currNode, size_t pos, int direction);
    void Split(Node &currNode, size_t currNodeNumber, RecordIndex &ri);
    void SplitRoot(Node &currNode, RecordIndex &ri);
    void Merge(std::pair<Node, size_t> &currNode);
    void MergeRoot(std::pair<Node, size_t> &currNode, std::pair<Node, size_t> &sibling);
    void InitNode(Node &node, size_t parentNum);
    void ChangeParents(Node &child, size_t newParentNumber);
    void SetChildNodesIndexes(std::vector<size_t> &childNodesNumber, Node &dst1, Node &dst2, size_t mid);
    void FindNodePos(size_t &nodePos, std::pair<Node, size_t> &nodePassed, std::vector<RecordIndex> &indexes);
    size_t FindChildNodePos(std::pair<Node, size_t> &parent, size_t childNodeNumber);
    void ReplaceAndDelete(Node &currNode, size_t nodeNumber, size_t pos, RecordIndex &ri);
    RecordIndex FindReplacement(Node &currNode, size_t nodeNumber, int direction);
    void DeleteFromNode(Node &node, size_t nodeNumber, size_t pos, RecordIndex &ri);
    void ClearNode(std::pair<Node, size_t> &node);

private:
    BTree();
    ~BTree();

private:
    size_t rootNodeNum = 0;
    unsigned int height = 0;                  // by default
    unsigned int order = DEFAULT_BTREE_ORDER; // by default
    bool nodePassedUp = false;                // after split
    bool mergePerformed = false;              // after merge
};

#endif
