#include "Displayer.hpp"

Displayer::Displayer() {}
Displayer::~Displayer() {}

Displayer &Displayer::GetInstance()
{
    static Displayer *instance = new Displayer;
    return *instance;
}

void Displayer::DiplayTree()
{
    wclear(window);
    wrefresh(window);
    FileManager::GetInstance().ResetDataReadsAndWrites();
    horizontalOffsets = std::vector<int>(BTree::GetInstance().GetHeight());
    for (size_t i = 0; i < horizontalOffsets.size(); i++)
        horizontalOffsets[i] = 0;
    if (BTree::GetInstance().GetRootNum() != NO_ROOT)
        DisplayTreeRecursive(1, BTree::GetInstance().GetRootNum());
    mvwprintw(window, BTree::GetInstance().GetHeight() * 2 + 2, 0, "\nReads: %lu\n", FileManager::GetInstance().GetIndexReads());
    wprintw(window, "Press any key to continue\n");
    wrefresh(window);
    wgetch(window);
    wclear(window);
    FileManager::GetInstance().ResetReadsAndWrites();
    Cache::GetInstance().ClearCache();
}
void Displayer::DiplayData()
{
    FileManager::GetInstance().ResetReadsAndWrites();
    FileManager::GetInstance().ResetDataReadsAndWrites();
    wclear(window);
    wrefresh(window);
    if (BTree::GetInstance().GetRootNum() != NO_ROOT)
        DisplayDataRecursive(BTree::GetInstance().GetRootNum());
    wprintw(window, "\nReads data: %lu Reads index: %lu\n", FileManager::GetInstance().GetDataReads(), FileManager::GetInstance().GetIndexReads());
    wprintw(window, "Press any key to continue\n");
    wrefresh(window);
    wgetch(window);
    wclear(window);
    FileManager::GetInstance().ResetDataReadsAndWrites();
    FileManager::GetInstance().ResetReadsAndWrites();
    Cache::GetInstance().ClearCache();
}

void Displayer::SetWindowAndDimensions(WINDOW *window, int width, int height)
{
    this->window = window;
    this->width = width;
    this->height = height;
}

void Displayer::DisplayTreeRecursive(size_t currHeight, size_t currNodeNumber)
{
    if (currHeight < BTree::GetInstance().GetHeight())
    {
        Node node;
        if (currNodeNumber != INVALID_NODE)
            node = FileManager::GetInstance().GetNode(currNodeNumber);
        Cache::GetInstance().Push(node, currNodeNumber);
        for (size_t i = 0; i <= BTree::GetInstance().GetOrder() * 2; i++)
        {
            DisplayTreeRecursive(currHeight + 1, node.childrenNodesNumbers[i]);
            horizontalOffsets[currHeight]++;
        }
        auto nodePair = Cache::GetInstance().Pop();
        DisplayNode(nodePair.first, nodePair.second, currHeight);
    }
    else
    {
        auto node = FileManager::GetInstance().GetNode(currNodeNumber);
        DisplayNode(node, currNodeNumber, currHeight);
    }
}
void Displayer::DisplayDataRecursive(size_t currNodeNumber)
{
    if (currNodeNumber != 0)
    {
        auto node = FileManager::GetInstance().GetNode(currNodeNumber);
        for (size_t i = 0; i <= BTree::GetInstance().GetOrder() * 2; i++)
        {
            DisplayDataRecursive(node.childrenNodesNumbers[i]);

            if (i < BTree::GetInstance().GetOrder() * 2)
                DisplayDataFromNode(node, currNodeNumber, i);
        }
    }
}

void Displayer::DisplayNode(Node &node, size_t nodeNumber, size_t height)
{
    if (nodeNumber != INVALID_NODE)
    {
        mvwprintw(window, height * 2, horizontalOffsets[height - 1] * NODE_WIDTH, "<%lu>", nodeNumber);
        mvwprintw(window, height * 2 + 1, horizontalOffsets[height - 1] * NODE_WIDTH, "%lu;", node.childrenNodesNumbers[0]);
        for (size_t i = 0; i < BTree::GetInstance().GetOrder() * 2; i++)
        {
            wprintw(window, "(%lu);%lu;", node.indexes[i].index, node.childrenNodesNumbers[i + 1]);
        }
        wrefresh(window);
    }
}

void Displayer::DisplayDataFromNode(Node &node, size_t nodeNumber, size_t pos)
{
    if (node.indexes[pos].index == INVALID_INDEX)
        return;
    auto dp = Cache::GetInstance().GetDataPage(node.indexes[pos].pageNumber);
    for (size_t j = 0; j < DATA_PAGE_SIZE; j++)
        if (dp.records[j].index == node.indexes[pos].index)
        {
            wprintw(window, "%lu %s\n", node.indexes[pos].index, dp.records[j].value.c_str());
            wrefresh(window);
            break;
        }
}