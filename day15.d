import std.stdio;
import std.math;
import std.file;
import std.string;
import std.conv;

struct Sensor {
    int x;
    int y;

    int range;
}

int checkRow(int y){
    return -1;
}

int distance(int x1, int y1, int x2, int y2){
    int absX = abs(x1-x2);
    int absY = abs(y1-y2);
    return absX + absY;
}

unittest {
    assert(distance(2,2,8,8) == 12);
}

// map out all sensor locations

// calculate distances between sensor and closest beacon

// check if map pos does not overlap with 'distance circles'


void main(){
    writeln("hello world!");

    string content = cast(string) read("inputs/input15_sample.txt");

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
        writeln(sensor);
    }
}
