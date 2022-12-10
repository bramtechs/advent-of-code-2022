#include "utils.cpp"
// this solution could be better and is not designed for performance

#define cout std::cout
#define endl std::endl

std::pair<int, int> OFFSETS[4] = {
    {1, 0},
    {0, 1},
    {-1, 0},
    {0, -1},
};

typedef uint8_t byte;

struct Map
{
    int width;
    int height;
    byte *values;

    Map(int width, int height)
    {
        this->width = width;
        this->height = height;
        this->values = (byte *)calloc(width * height, sizeof(byte));
    }

    ~Map()
    {
        free(this->values);
    }

    byte at(int x, int y)
    {
        assert(x >= 0 && x < width && y >= 0 && y < height);
        int i = y * width + x;
        return values[i];
    }

    bool is_visible_from(int x, int y, byte dir)
    {
        assert(dir >= 0 && dir < 4);

        byte treeHeight = at(x, y);
        while (x > 0 && y > 0 && x < width - 1 && y < height - 1)
        {
            x += OFFSETS[dir].first;
            y += OFFSETS[dir].second;
            if (treeHeight <= at(x, y))
            {
                return false;
            }
        }
        return true;
    }

    bool is_visible(int x, int y)
    {
        // is on edge
        if (x == 0 || y == 0 || x == width - 1 || y == height - 1)
        {
            return true;
        }

        for (int d = 0; d < 4; d++)
        {
            if (is_visible_from(x, y, d))
            {
                return true;
            }
        }
        return false;
    }

    int calc_view_distance_from(int x, int y, byte dir)
    {
        assert(dir >= 0 && dir < 4);

        int distance = 0;
        byte treeHeight = at(x, y);
        while (x > 0 && y > 0 && x < width - 1 && y < height - 1)
        {
            x += OFFSETS[dir].first;
            y += OFFSETS[dir].second;

            if (treeHeight <= at(x, y))
            {
                break;
            }

            distance++;
        }
        return distance;
    }

    int calc_scenic_score(int x, int y)
    {
        int score = 1;
        for (int i = 0; i < 4; i++)
        {
            int dir_score = calc_view_distance_from(x,y,i);
            cout << dir_score << endl;
            score *= dir_score; 
        }
        return score;
    }

    void print(int x, int y)
    {
        byte val = at(x, y);
        if (is_visible(x, y))
        {
            cout << (int)val;
        }
        else
        {
            cout << '.';
        }
    }
};

Map *parse_map(std::vector<std::string> &lines)
{
    assert(lines.size() > 0);

    Map *map = new Map(lines.at(0).size(), lines.size());

    int i = 0;
    for (auto &line : lines)
    {
        for (auto &ch : line)
        {
            byte value = ch - '0';
            assert(value >= 0 && value < 10);
            map->values[i] = value;
            i++;
        }
    }
    return map;
}

int main()
{
    auto lines = read_lines("inputs/input08_sample.txt");
    Map *map = parse_map(lines);

    int visible = 0;
    int maxScore = 0;

    for (int y = 0; y < map->height; y++)
    {
        for (int x = 0; x < map->width; x++)
        {
            byte value = map->at(x, y);
            // map->print(x, y);

            int score = map->calc_scenic_score(x,y);
            if (score > maxScore) {
                maxScore = score;
            }

            if (map->is_visible(x, y))
                visible++;
        }
        // cout << endl;
    }

    cout << visible << endl;
    cout << maxScore << endl;

    delete map;

    return 0;
}
