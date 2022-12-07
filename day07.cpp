#include "utils.cpp"

// why did I choose C++ for this day??

using namespace std;

typedef std::pair<std::string, std::string> Members;

struct File
{
    string name;
    uint size;

    File *parent;
    MemoryArray<File> *children;

    File(string name, uint size = 0)
    {
        this->name = name;
        this->size = size;
        this->parent = nullptr;
        this->children = (MemoryArray<File> *)calloc(1, sizeof(MemoryArray<File>)); // copium
    }

    File *create_directory(std::string name)
    {
        // cout << "Creating folder " << name << endl;
        File folder = File(name);
        return add_child(folder);
    }

    File *change_directory(std::string name)
    {
        if (name == "..")
        {
            assert(parent != nullptr);
            return parent;
        }
        if (name == "/" && parent == nullptr)
        {
            return this;
        }

        for (int i = 0; i < children->count; i++)
        {
            File *file = children->get(i);
            if (file->name == name)
            {
                // cout << "Changed folder to " << name << endl;
                return file;
            }
        }
        cout << "!! Didn't find folder " << name << endl;
        assert(false);
        return nullptr;
    }

    File *add_child(File file)
    {
        file.parent = this;
        // cout << "Adding file " << file.get_path() << endl;
        return children->push(file);
    }

    std::string get_path()
    {
        if (parent != nullptr)
        {
            return parent->get_path() + "/" + name;
        }
        return name;
    }

    void collect_subdirs(std::vector<File *> *vector)
    {
        for (int i = 0; i < children->count; i++)
        {
            File *file = children->get(i);
            if (file->is_dir())
            {
                vector->push_back(file);
                file->collect_subdirs(vector);
            }
        }
    }

    void print()
    {
        cout << get_path() << " with " << size << " " << name << endl;
        for (int i = 0; i < children->count; i++)
        {
            File *file = children->get(i);
            file->print();
        }
    }

    uint get_size()
    {
        uint s = size;
        for (int i = 0; i < children->count; i++)
        {
            File *file = children->get(i);
            s += file->get_size();
        }
        return s;
    }

    bool is_dir()
    {
        return size == 0;
    }
};

static File RootFile = File("/");
static File *CurrentFile = &RootFile;

Members str_get_members(const std::string &line, bool isCmd)
{
    int i = isCmd ? 2 : 0;
    std::string first, second;
    char c = line.at(i);
    while (c != ' ')
    {
        first += c;
        i++;
        if (i >= line.length())
        {
            return {first, ""}; // cmd with no argument
        }
        c = line.at(i);
    }
    for (int j = i + 1; j < line.length(); j++)
    {
        second += line.at(j);
    }
    return {first, second}; // output with two arguments
}

inline bool str_is_command(const std::string cmd)
{
    assert(cmd.length() > 0);
    return cmd.at(0) == '$';
}

int run_line(int i, std::vector<string> &lines)
{
    auto &line = lines.at(i);
    assert(str_is_command(line));
    // cout << line << endl;

    // run command
    auto mem = str_get_members(line, true);
    // cout << mem.first << " : " << mem.second << endl;

    if (mem.first == "cd")
    {
        CurrentFile = CurrentFile->change_directory(mem.second);
    }

    for (int j = i + 1; j < lines.size(); j++)
    {
        auto &out = lines.at(j);
        if (!str_is_command(out))
        {
            // cout << "->" << out << endl;
            auto mem = str_get_members(out, false);
            // cout << "|-> " << mem.first << " : " << mem.second << endl;

            if (mem.first == "dir")
            {
                File *folder = CurrentFile->create_directory(mem.second);
            }
            else
            { // gave file
                uint size = atoi(mem.first.c_str());
                File file = File(mem.second, size);
                CurrentFile->add_child(file);
            }
        }
        else
        {
            return j;
        }
    }
    return lines.size(); // reached the end
}

uint get_size_sum()
{
    std::vector<File *> dirs;
    RootFile.collect_subdirs(&dirs);

    uint total = 0; // needs to be explicitely declared, learned this the hard way
    for (auto &dir : dirs)
    {
        uint size = dir->get_size();
        if (size <= 100000)
        {
            // cout << dir->get_path() << " size: " << size << endl;
            total += size;
        }
    }
    return total;
}

int main()
{
    auto lines = read_lines("inputs/input07.txt");

    int i = 0;
    while (i < lines.size())
    {
        i = run_line(i, lines);
    }

    cout << get_size_sum() << endl;

    return 0;
}