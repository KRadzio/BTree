#ifndef BTREE_HPP
#define BTREE_HPP

#include <algorithm>

#include "FileManager.hpp"
#include "Cache.hpp"

#define DEFAULT_BTREE_ORDER 2
#define NO_ROOT 0
#define INVALID_NODE 0
#define NO_PARENT 0
#define NO_CHILDREN 0
#define LEFT 1
#define RIGHT 2

class BTree
{
public:
    static BTree &GetInstance();
    void Init(unsigned int order);
    void SetOrder(unsigned int order); // changes the order of the tree and resets the tree
    void Clear();

    bool Search(size_t key, bool clearCache = true, bool clearReadsAndWrites = true); // puts visited nodes in cache
    void Add(RecordData &rd, bool clearReadsAndWrites = true);
    void Delete(size_t key, bool clearReadsAndWrites = true);
    void Update(RecordData &rd, bool clearReadsAndWrites = true);

    inline size_t GetRootNum() { return rootNodeNum; }
    inline size_t GetKeysNumber() { return keysNumber; }
    inline unsigned int GetOrder() { return order; }
    inline unsigned int GetHeight() { return height; }
    inline size_t GetSearchReads() { return searchReads; }
    inline size_t GetAddReads() { return addReads; }
    inline size_t GetAddWrites() { return addWrites; }
    inline size_t GetDeleteReads() { return deleteReads; }
    inline size_t GetDeleteWrites() { return deleteWrites; }
    // helper functions
private:
    bool SearchRecursive(size_t currNodeNum, size_t key);
    void AddRecursive(RecordIndex &ri);
    void PostDeletionFix();
    void AddToNode(Node &node, size_t nodeNumber, RecordIndex &ri);
    void CreateRootNode(RecordData &rd);
    bool TryCompensate(Node &currNode, size_t currNodeNumber, RecordIndex &ri);
    void Compensate(Node &currNode, size_t pos, RecordIndex &ri, int direction);
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
    void ReplaceAndDelete(Node &currNode, size_t nodeNumber, size_t pos);
    RecordIndex FindReplacement(Node &currNode, size_t nodeNumber, int direction);
    void DeleteFromNode(Node &node, size_t nodeNumber, size_t pos);
    void ClearNode(std::pair<Node, size_t> &node);

private:
    BTree();
    ~BTree();

private:
    size_t keysNumber = 0;
    size_t rootNodeNum = 0;
    unsigned int height = 0;                  // by default
    unsigned int order = DEFAULT_BTREE_ORDER; // by default
    bool nodePassedUp = false;                // after split
    bool mergePerformed = false;              // after merge
    size_t searchReads = 0;
    size_t addReads = 0;
    size_t deleteReads = 0;
    size_t addWrites = 0;
    size_t deleteWrites = 0;
};

#endif
