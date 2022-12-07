#include "utils.cpp"

using namespace std;

typedef std::pair<std::string, std::string> Members;

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
    for (int j = i; j < line.length(); j++)
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

int parse_command(int i, std::vector<string> &lines)
{
    auto &line = lines.at(i);
    assert(str_is_command(line));
    // cout << line << endl;

    // run command
    auto mem = str_get_members(line, true);
    cout << mem.first << " : " << mem.second << endl;

    for (int j = i + 1; j < lines.size(); j++)
    {
        auto &out = lines.at(j);
        if (!str_is_command(out))
        {
            // cout << "|->" << out << endl;
            auto mem = str_get_members(out, false);
            cout << "|-> " << mem.first << " : " << mem.second << endl;
        }
        else
        {
            return j;
        }
    }
    return lines.size(); // reached the end
}

int main()
{
    File root = File("/");
    auto lines = read_lines("inputs/input07_sample.txt");

    int i = 0;
    while (i < lines.size())
    {
        i = parse_command(i, lines);
    }

    return 0;
}