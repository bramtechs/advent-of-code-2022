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
}

alias Map = Tile[Point];

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

void printMap(Map map, Rectangle bounds)
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
    string content = cast(string) read("inputs/input14_sample.txt");

    // define the map
    Map map;

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

    // print the map
    Rectangle bounds = getMapBounds(map);
    writeln(bounds);
    printMap(map, bounds);
}
