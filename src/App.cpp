#include "App.hpp"

App::App()
{
    std::ofstream file;
    file.open(OUTPUT_FILE, std::ios_base::trunc);
    file.close();
    BTree::GetInstance().SetOrder(DEFAULT_BTREE_ORDER);
    initscr();
    getmaxyx(stdscr, height, width);
    window = newwin(height - 2, width - 2, 1, 1);
    scrollok(window, TRUE);
    raw();
    noecho();
    curs_set(0);
}
App::~App() {}

App &App::GetInstance()
{
    static App *instance = new App;
    return *instance;
}

void App::Experiment()
{
    srand(time(NULL));

    std::vector<size_t> numberOfRecords = {20, 50, 100, 200, 500, 1000, 10000};

    for (size_t i = 0; i < numberOfRecords.size(); i++)
    {
        TestTree(numberOfRecords[i], 2);
        TestTree(numberOfRecords[i], 5);
        TestTree(numberOfRecords[i], 10);
        TestTree(numberOfRecords[i], 50);
        TestTree(numberOfRecords[i], 100);
    }
}

void App::MainLoop()
{
    char c;
    wclear(window);
    while (run)
    {
        wprintw(window, "1) Search record\n");
        wprintw(window, "2) Add record\n");
        wprintw(window, "3) Delete record\n");
        wprintw(window, "4) Update value\n");
        wprintw(window, "5) Read from file\n");
        wprintw(window, "p) Print BTree\n");
        wprintw(window, "d) Print data file\n");
        wprintw(window, "o) Set BTree order\n");
        wprintw(window, "e) Experiment\n");
        wprintw(window, "q) Quit\n");
        wrefresh(window);
        c = wgetch(window);
        switch (c)
        {
        case 0x31:
            SearchRecord();
            wclear(window);
            break;
        case 0x32:
            AddRecord();
            wclear(window);
            break;
        case 0x33:
            DeleteRecord();
            wclear(window);
            break;
        case 0x34:
            UpdateValue();
            wclear(window);
            break;
        case 0x35:
            ReadFromFile();
            wclear(window);
            break;
        case 0x64:
            Displayer::GetInstance().DiplayData();
            wclear(window);
            break;
        case 0x6F:
            SetOrder();
            wclear(window);
            break;
        case 0x70:
            Displayer::GetInstance().DiplayTree();
            wclear(window);
            break;
        case 0x71:
            run = false;
            break;
        case 0x65:
            Experiment();
            wclear(window);
            break;
        default:
            wclear(window);
            break;
        }
    }
    echo();
    curs_set(1);
    endwin();
}

void App::AddRecords(size_t number)
{
    RecordData rd;
    rd.value = "abc";
    recordsInTree = std::vector<bool>(number);
    for (size_t i = 0; i < number; i++)
        recordsInTree[i] = false;

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
        BTree::GetInstance().Add(rd);
    }
}

void App::DeleteRecords(size_t number)
{
    for (size_t i = 0; i < number; i++)
    {
        size_t randomNumber = (rand() % number) + 1;
        if (recordsInTree[randomNumber - 1] == true)
        {
            recordsInTree[randomNumber - 1] = false;
            BTree::GetInstance().Delete(randomNumber);
        }
        else
        {
            for (size_t j = 0; j < number; j++)
                if (recordsInTree[j] == true)
                {
                    recordsInTree[j] = false;
                    BTree::GetInstance().Delete(j + 1);
                    break;
                }
        }
    }
}

void App::TestTree(size_t number, unsigned int order)
{
    std::ofstream file;
    file.open(OUTPUT_FILE, std::ios_base::app);
    file << "Records: " << number << std::endl;
    BTree::GetInstance().SetOrder(order);
    AddRecords(number);
    DeleteRecords(number);
    file << "Order: " << BTree::GetInstance().GetOrder() << " Reads: " << FileManager::GetInstance().GetTotalIndexReads() << " Writes: " << FileManager::GetInstance().GetTotalIndexWrites() << std::endl;
    float averageSearchReads = (float)BTree::GetInstance().GetSearchReads() / (number * 2);
    float averageAddReads = (float)BTree::GetInstance().GetAddReads() / number;
    float averageDeleteReads = (float)BTree::GetInstance().GetDeleteReads() / number;
    float averageAddWrites = (float)BTree::GetInstance().GetAddWrites() / number;
    float averageDeleteWrites = (float)BTree::GetInstance().GetDeleteWrites() / number;
    file << "Average search reads " << averageSearchReads
         << " Average add reads " << averageAddReads << " Average add writes " << averageAddWrites
         << " Average delete reads " << averageDeleteReads << " Average delete writes " << averageDeleteWrites << std::endl;
    file.close();
}

void App::AddRecord()
{
    wclear(window);
    char c = 0x00;
    RecordData rd;
    char buff[100];
    std::string line;
    while (c != 0x1B)
    {
        wprintw(window, "1) Insert index and value\n");
        wprintw(window, "ESC) Quit\n");
        wrefresh(window);
        c = wgetch(window);
        switch (c)
        {
        case 0x31:
            curs_set(1);
            echo();
            wgetstr(window, buff);
            curs_set(0);
            line = buff;
            rd.index = std::stoul(line);
            wgetstr(window, buff);
            rd.value = buff;
            noecho();
            BTree::GetInstance().Add(rd, false);
            c = 0x1B;
            break;
        default:
            wclear(window);
            break;
        }
        wprintw(window, "Reads(including searcg): %lu, writes: %lu\n", FileManager::GetInstance().GetIndexReads(), FileManager::GetInstance().GetIndexWrites());
        wprintw(window, "Press any key to continue\n");
        wrefresh(window);
        wgetch(window);
        wclear(window);
        FileManager::GetInstance().ResetReadsAndWrites();
    }
}
void App::SearchRecord() {}
void App::UpdateValue() {}
void App::DeleteRecord() {}
void App::ReadFromFile()
{
    wclear(window);
    char c = 0x00;
    std::string path = "./files/";
    char buff[100];
    while (c != 0x1B)
    {
        wprintw(window, "1) Insert file name\n");
        wprintw(window, "ESC) Quit\n");
        wrefresh(window);
        c = wgetch(window);
        switch (c)
        {
        case 0x31:
            curs_set(1);
            echo();
            wgetstr(window, buff);
            curs_set(0);
            path += buff;
            noecho();
            ParseInputFile(path);
            wclear(window);
            c = 0x1B;
            break;
        default:
            wclear(window);
            break;
        }
    }
}
void App::SetOrder() {}

void App::ParseInputFile(std::string filepath)
{
    std::ifstream file;
    std::string line;
    RecordData rd;
    size_t key;
    file.open(filepath);
    while (getline(file, line))
    {
        std::stringstream ss(line);
        switch (line[0])
        {
        case 0x61:
            getline(ss, line, DELIMITER);
            getline(ss, line, DELIMITER);
            rd.index = std::stoul(line);
            getline(ss, line);
            rd.value = line;
            BTree::GetInstance().Add(rd);
            break;
        case 0x75:
            getline(ss, line, DELIMITER);
            getline(ss, line, DELIMITER);
            rd.index = std::stoul(line);
            getline(ss, line);
            rd.value = line;
            BTree::GetInstance().Update(rd);
            break;
        case 0x64:
            getline(ss, line, DELIMITER);
            getline(ss, line);
            key = std::stoul(line);
            BTree::GetInstance().Delete(key);
            break;
        default:
            break;
        }
    }

    file.close();
}