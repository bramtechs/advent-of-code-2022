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

static std::vector<Point> Visits;

static Point Head;
static Point Tail;

bool tail_has_visited(int x, int y){
    for (auto &point : Visits){
        if (point.x == x && point.y == y){
            return true;
        }
    }
    return false;
}

Movement parse_line(std::string &line){
    int len = line.size() - 2;
    int size = atoi(line.substr(2,len).c_str());

    char dir = line.at(0);
    return {dir, size};
}

bool tail_touches_head(){
    int diffX = abs(Head.x - Tail.x);
    int diffY = abs(Head.y - Tail.y);
    return diffX == 0 && diffY == 0 || (diffX <= 1 && diffY <= 1 && diffX != diffY);
}

void move_tail_towards_head(){
    int attempts = 0;
    while (!tail_touches_head()){

        int diffX = Head.x - Tail.x;
        int diffY = Head.y - Tail.y;

        if (diffX != 0){
            Tail.x += diffX > 0 ? 1:-1;
        }

        if (diffY != 0){
            Tail.y += diffY > 0 ? 1:-1;
        }

        Visits.push_back(Tail);

        assert(attempts < 100);
        attempts++;
    }
}

void move_rope(char dir){
    // move head 
    switch (dir){
        case 'R':
            Head.x++;
            break;
        case 'L':
            Head.x--;
            break;
        case 'U':
            Head.y++;
            break;
        case 'D':
            Head.y--;
            break;
        default:
            assert(false);
    }
    move_tail_towards_head();
}

void print_step(int width=6, int height=5){
    for (int y = height - 1; y >= 0; y--){
        for (int x = 0; x < width; x++){
            if (Head.x == x && Head.y == y){
                cout << 'H';
            }else if (Tail.x == x && Tail.y == y){
                cout << 'T';
            }else if (tail_has_visited(x,y)){
                cout << '#';
            }else{
                cout << '.';
            }
        }
        cout << endl;
    }
}

int main(){
    Head = {0,0};
    Tail = {0,0};
    Visits = {};

    auto lines = read_lines("inputs/input09_sample.txt");

    for (auto &line : lines){
        auto move = parse_line(line);
        cout << move.dir << "-" << move.amount << endl;
        cout << Head.x << "-" << Head.y << endl;
        for (int i = 0; i < move.amount; i++){
            move_rope(move.dir);
            cout << endl;
            print_step();
        }
    }

    return 0;
}
