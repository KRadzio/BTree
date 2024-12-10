#ifndef APP_HPP
#define APP_HPP

#include <ncurses.h>
#include <random>
#include <ctime>

#include "Displayer.hpp"
#include "BTree.hpp"

// int log_a_to_base_b(int a, int b)
// {
    // return log2(a) / log2(b);
// }

#define OUTPUT_FILE "./files/result.txt"

class App
{
public:
    static App &GetInstance();

    void MainLoop();

private:
    void AddRecords(size_t number);
    void DeleteRecords(size_t number);
    void TestTree(size_t number, unsigned int order);
    void AddRecord();
    void SearchRecord();
    void UpdateValue();
    void DeleteRecord();
    void ReadFromFile();
    void SetOrder();
    void Experiment();
    void ParseInputFile(std::string filepath);

private:
    App();
    ~App();

private:
    std::vector<bool> recordsInTree;
    bool run = true;
    WINDOW *window;
    int height;
    int width;
};

#endif
