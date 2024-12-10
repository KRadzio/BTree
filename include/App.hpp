#ifndef APP_HPP
#define APP_HPP

#include <ncurses.h>
#include <random>
#include <ctime>

#include "Displayer.hpp"
#include "BTree.hpp"

class App
{
public:
    static App& GetInstance();
    void Experiment(size_t numberOfRecords);

private:
    void AddRecords(size_t number);
    void DeleteRecords(size_t number);

private:
    App();
    ~App();
private:
    std::vector<bool> recordsInTree;
};

#endif
