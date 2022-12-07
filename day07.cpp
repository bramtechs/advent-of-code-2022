#include "utils.cpp"

using namespace std;

struct File
{
    string name;
    uint size;

    File *parent;
    vector<File> children;

    File(string name, uint size = 0, File *parent = nullptr)
    {
        this->name = name;
        this->size = size;
        this->parent = parent;
    }

    uint get_size()
    {
        uint s = size;
        for (auto &child : children)
        {
            s += child.size;
        }
        return s;
    }

    bool is_dir()
    {
        return size == 0;
    }
};

struct Directory
{
    string name;

    vector<Directory> dirs;

    uint get_size()
    {
        uint size = 0;
        for (auto &file : files)
        {
            size += file.size;
        }
        for (auto &dir : dirs)
        {
            size += dir.get_size();
        }
        return size;
    }
};

int main()
{
    Directory root = {"/"};
    for (auto line : read_lines("inputs/input07_sample.txt"))
    {
    }
    return 0;
}