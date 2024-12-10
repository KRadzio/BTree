#include "App.hpp"

// order 2, 10, 50
// records 20, 50, 100
App::App() {}
App::~App() {}

App &App::GetInstance()
{
    static App *instance = new App;
    return *instance;
}

void App::Experiment(size_t numberOfRecords)
{
    srand(time(NULL));

    BTree::GetInstance().SetOrder(2);
    AddRecords(numberOfRecords);
    DeleteRecords(numberOfRecords);

    BTree::GetInstance().SetOrder(10);
    AddRecords(numberOfRecords);
    DeleteRecords(numberOfRecords);

    BTree::GetInstance().SetOrder(50);
    AddRecords(numberOfRecords);
    DeleteRecords(numberOfRecords);
}

void App::AddRecords(size_t number)
{
    RecordData rd;
    rd.value = "abc";
    recordsInTree = std::vector<bool>(number) = {false};
    std::ofstream file;
    file.open("./files/add.txt");

    for (size_t i = 0; i < number; i++)
    {
        size_t randomNumber = (rand() % number) + 1;
        if (recordsInTree[randomNumber - 1] == false)
        {
            recordsInTree[randomNumber - 1] = true;
            rd.index = randomNumber;
        }
        else
        {
            for (size_t j = 0; j < number; j++)
                if (recordsInTree[j] == false)
                {
                    recordsInTree[j] = true;
                    rd.index = j + 1;
                    break;
                }
        }
        file << rd.index << std::endl;
        BTree::GetInstance().Add(rd);
    }
    file.close();
}

void App::DeleteRecords(size_t number)
{
    std::ofstream file;
    file.open("./files/delete.txt");
    for (size_t i = 0; i < number; i++)
    {
        size_t randomNumber = (rand() % number) + 1;
        if (recordsInTree[randomNumber - 1] == true)
        {
            recordsInTree[randomNumber - 1] = false;
            file << randomNumber << std::endl;
            BTree::GetInstance().Delete(randomNumber);
        }
        else
        {
            for (size_t j = 0; j < number; j++)
                if (recordsInTree[j] == true)
                {
                    recordsInTree[j] = false;
                    file << j + 1 << std::endl;
                    BTree::GetInstance().Delete(j + 1);
                    break;
                }
        }
    }
    file.close();
}