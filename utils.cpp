#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>
#include "mem_array.cpp"

typedef unsigned long uint;

std::vector<std::string> read_lines(const char *path)
{
    std::vector<std::string> lines;
    std::ifstream stream;
    stream.open(path);
    if (stream.is_open())
    {
        std::string line;
        while (std::getline(stream, line))
        {
            lines.push_back(line);
        }
    }
    else
    {
        std::cout << "Failed to read file!" << std::endl;
    }
    return lines;
}