#include "utils.cpp"
#include <utility>

using namespace std;

struct Movement {
    char dir;
    int amount;
};

struct Point {
    int x;
    int y;
};

Movement parse_line(std::string &line){

    int len = line.size() - 2;
    int size = atoi(line.substr(2,len).c_str());
    return {line.at(0), size};
}

int main(){
    Point head = {0,0};
    Point tail = {0,0};

    auto lines = read_lines("inputs/input09_sample.txt");

    for (auto &line : lines){
        auto move = parse_line(line);
        cout << move.dir << "-" << move.amount << endl;
    }

    return 0;
}
