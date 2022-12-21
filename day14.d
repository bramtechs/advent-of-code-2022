import std.stdio;
import std.file;
import std.string;
import std.conv;

struct Point
{
    int x;
    int y;
}

struct Rectangle
{
    int x1;
    int y1;
    int x2;
    int y2;

    this(Point topLeft, Point bottomRight)
    {
        this.x1 = topLeft.x;
        this.y1 = topLeft.y;
        this.x2 = bottomRight.x;
        this.y2 = bottomRight.y;
    }
}

enum Tile
{
    ROCK,
    SOURCE,
    SAND,
}

alias Map = Tile[Point];
static Map map;

Rectangle getMapBounds(Map map)
{
    Point smallest = {int.max, int.max};
    Point biggest = {int.min, int.min};
    foreach (key, _; map)
    {
        if (key.x < smallest.x)
        {
            smallest.x = key.x;
        }
        if (key.y < smallest.y)
        {
            smallest.y = key.y;
        }

        if (key.x > biggest.x)
        {
            biggest.x = key.x;
        }
        if (key.y > biggest.y)
        {
            biggest.y = key.y;
        }
    }
    return Rectangle(smallest, biggest);
}

bool is_in_bounds(Point p, Rectangle b){
    if (p.x < b.x1) return false;
    if (p.x > b.x2) return false;
    if (p.y < b.y1) return false;
    if (p.y > b.y2) return false;
    return true;
}

bool is_solid(Point point){
    if (auto type = point in map){
        if (*type == Tile.ROCK || *type == Tile.SAND){
            return true;
        }
    }
    return false;
}

bool is_solid(int x, int y){
    Point p = { x, y };
    return is_solid(p);
}

void printMap(Rectangle bounds)
{
    for (int y = bounds.y1; y <= bounds.y2; y++)
    {
        for (int x = bounds.x1; x <= bounds.x2; x++)
        {
            char letter = '.';
            Point coord = {x, y};
            if (auto type = coord in map)
            {
                switch (*type)
                {
                    case Tile.ROCK:
                        letter = '#';
                        break;
                    case Tile.SOURCE:
                        letter = '+';
                        break;
                    case Tile.SAND:
                        letter = 'O';
                        break;
                    default:
                        assert(0);
                }
            }
            write(letter);
        }
        write('\n');
    }
}

void main()
{
    string content = cast(string) read("inputs/input14.txt");

    // source
    Point source = {500, 0};
    map[source] = Tile.SOURCE;

    // get rock lines map
    foreach (line; splitLines(content))
    {
        Point[] segments;
        foreach (coord; split(line, " -> "))
        {
            string[] coords = split(coord, ',');
            assert(coords.length == 2);
            Point p = {
                to!int(coords[0]),
                to!int(coords[1])
            };

            segments ~= p;
        }

        for(int i = 1; i < segments.length; i++){
            Point p1 = segments[i-1];
            Point p2 = segments[i];
    

            if (p1.x == p2.x){ // vertical
                int x = p1.x;
                if (p2.y < p1.y){
                    int c = p1.y;
                    p1.y = p2.y;
                    p2.y = c;
                }
                assert(p1.y < p2.y);
                for (int y = p1.y; y <= p2.y; ++y){
                    Point p = { x, y };
                    map[p] = Tile.ROCK;
                }
            }
            else if (p1.y == p2.y){ // horizontal
                int y = p1.y;
                if (p2.x < p1.x){
                    int c = p1.x;
                    p1.x = p2.x;
                    p2.x = c;
                }
                assert(p1.x < p2.x);
                for (int x = p1.x; x <= p2.x; ++x){
                    Point p = { x, y };
                    map[p] = Tile.ROCK;
                }
            }else{
                assert(false);
            }
        }
    }

    Rectangle bounds = getMapBounds(map);

    int units = 0;
    Point sand = source;
    while (true){
        sand = source;
        while (is_in_bounds(sand,bounds)){
            if (is_solid(sand.x,sand.y+1)){
                if (!is_solid(sand.x-1,sand.y+1)){
                    sand.x--;
                }else if (!is_solid(sand.x+1,sand.y+1)){
                    sand.x++;
                }else{
                    break;
                }
            }else{
                sand.y++;
            }
        }
        if (is_in_bounds(sand,bounds)){
            map[sand] = Tile.SAND;
            units++;
        }else{
            break;
        }
    }

    // print the map
    printMap(bounds);
    writeln(units);
}
