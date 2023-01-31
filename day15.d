import std.stdio;
import std.math;
import std.file;
import std.string;
import std.conv;

struct Bounds {
    int x1;
    int y1;

    int x2;
    int y2;
}

struct Sensor {
    int x;
    int y;

    int range;
}

int distance(int x1, int y1, int x2, int y2){
    int absX = abs(x1-x2);
    int absY = abs(y1-y2);
    return absX + absY;
}

unittest {
    assert(distance(2,2,8,8) == 12);
}

int checkRow(int y, Bounds bounds, ref Sensor[] sensors){
    int invalid = 0;
    for (int x = bounds.x1; x <= bounds.x2; x++){
        bool ranged = false;
        foreach (sensor; sensors){
            int dis = distance(x,y,sensor.x,sensor.y);
            if (dis < sensor.range){
                // can't be beacon
                invalid++;
                ranged = true;
            }
        }
        char c = '.';
        if (ranged) {
            c = '#';
        }
        write(c);
    }
    write('\n');
    return invalid;
}

// -4,-2, 25, 22
void printMap(Bounds bounds, ref Sensor[] sensors){
    for (int y = bounds.y1; y <= bounds.y2; y++){
        for (int x = bounds.x1; x <= bounds.x2; x++){
            char symbol = '.';
            foreach (sensor; sensors) {
                if (sensor.x == x && sensor.y == y) {
                    symbol = 'X';
                    break;
                }
            }
            write(symbol);
        }
        write('\n');
    }
}

// map out all sensor locations

// calculate map bounds

// calculate distances between sensor and closest beacon

// check if map pos does not overlap with 'distance circles'


void main(){
    string content = cast(string) read("inputs/input15_sample.txt");

    Sensor[] sensors;

    foreach (line; splitLines(content))
    {
        if (line.empty) continue;

        int x = to!int(line.split("x=")[1].split(",")[0]);
        int y = to!int(line.split("y=")[1].split(":")[0]);

        int beaconX = to!int(line.split("x=")[2].split(",")[0]);
        int beaconY = to!int(line.split("y=")[2]);

        int range = distance(x,y,beaconX,beaconY);

        Sensor sensor = {
            x, y, range
        };
        sensors ~= sensor;
    }

    Bounds b = {
        -2,-2, 25, 22
    };
    writeln(checkRow(9,b,sensors));
    writeln(checkRow(10,b,sensors));
    writeln(checkRow(11,b,sensors));

    printMap(b,sensors);

    writeln(sensors);
}
