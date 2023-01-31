import std.stdio;
import std.math;
import std.file;
import std.string;
import std.conv;

struct Valve {
    int rate;
    string[] connections;
}

void main(){
    string content = cast(string) read("inputs/input16_sample.txt");

    Valve[string] valves;

    foreach (line; content.splitLines()){
        auto members = line.split(' ');

        Valve valve;

        // parse rate
        string rateStr = members[4].chompPrefix("rate=").chop();
        valve.rate = to!int(rateStr);

        // connections
        for (int i = 9; i < members.length; i++){
            string otherName = members[i];
            valve.connections ~= otherName;
        }

        string name = members[1];
        valves[name] = valve;
    }
    writeln(valves);
}
