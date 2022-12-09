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

void log_visit(Point p){
    for (auto &visit : Visits){
        if (visit.x == p.x && visit.y == p.y){
            return; // already added
        }
    }
    Visits.push_back(p);
}

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

bool points_touch(Point one, Point two){
    int diffX = abs(one.x - two.x);
    int diffY = abs(one.y - two.y);

    if (diffX == 0 && diffY == 0) // overlapping
        return true;

    if (diffX > 1 || diffY > 1) // distance to large
        return false;

    return true; // close enough
}

bool tail_touches_head(){
    return points_touch(Tail,Head);
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

        log_visit(Tail);

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

void print_step(int width, int height, bool visits=false){
    for (int y = height - 1; y >= 0; y--){
        for (int x = 0; x < width; x++){
            if (visits){
                if (tail_has_visited(x,y)){
                    cout << '#';
                }else{
                    cout << '.';
                }
            }
            else if (Head.x == x && Head.y == y){
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

    log_visit(Tail);

    // cout << points_touch({3,3},{4,4}) << endl;

    // return 0;

    auto lines = read_lines("inputs/input09_sample.txt");

    for (auto &line : lines){
        auto move = parse_line(line);
        // cout << move.dir << "-" << move.amount << endl;
        // cout << Head.x << "-" << Head.y << endl;
        for (int i = 0; i < move.amount; i++){
            move_rope(move.dir);
            // print_step(6,5,false);
            // cout << endl;
        }
    }
    print_step(6,5,true);

    cout << Visits.size() << endl;

    return 0;
}
