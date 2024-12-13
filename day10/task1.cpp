#include "../helpers/helpers.hpp"



struct path
{
    Point2<int> start;
    Point2<int> curr;
};
bool operator==(const path & l, const path & r)
{
    return l.start == r.start && l.curr == r.curr;
}
bool operator!=(const path & l, const path & r)
{
    return l.start != r.start || l.curr != r.curr;
}

struct hash_point
{
    size_t operator()(const Point2<int> & p) const
    {
        return p.x * 54321 + p.y;
    }
};
struct hash_path
{
    size_t operator()(const path & p) const
    {
        hash_point h;
        return h(p.start) + 12345 * h(p.curr);
    }
};



int main()
{
    timer tm;
    tm.start();

    std::vector<std::string> lines = read_lines();
    int h = lines.size();
    int w = lines[0].size();

    std::unordered_set<path,hash_path> paths;
    for(int r = 0; r < h; r++)
    {
        for(int c = 0; c < w; c++)
        {
            if(lines[r][c] == '0')
            {
                Point2<int> here(c,r);
                paths.insert({here, here});
            }
        }
    }

    for(int k = 1; k <= 9; k++)
    {
        std::unordered_set<path,hash_path> new_paths;
        for(path p : paths)
        {
            for(int d = 0; d < 4; d++)
            {
                Point2<int> diff = dir_to_point_int(direction(d));
                Point2<int> next = p.curr + diff;
                if(next.x >= 0 && next.x < w && next.y >= 0 && next.y < h && lines[next.y][next.x] == '0' + k)
                {
                    new_paths.insert({p.start, next});
                }
            }
        }
        std::swap(paths, new_paths);
    }

    printf("%zu\n", paths.size());

    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
