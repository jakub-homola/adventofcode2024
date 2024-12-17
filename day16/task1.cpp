#include "../helpers/helpers.hpp"



struct path
{
    Loc2<int> loc;
    direction dir;
    int score;
    path(Loc2<int> l, direction d, int s) : loc(l), dir(d), score(s) {}
    struct comparator
    {
        bool operator()(const path & l, const path & r) const
        {
            return l.score > r.score;
        }
    };
};



int main()
{
    timer tm;
    tm.start();

    std::vector<std::string> lines = read_lines();
    int h = lines.size();
    int w = lines[0].size();

    std::vector<std::vector<std::array<bool,4>>> visited(h, std::vector<std::array<bool,4>>(w, std::array<bool,4>({false,false,false,false})));

    Loc2 start(h-2,1);
    Loc2 target(1, w-2);
    std::priority_queue<path,std::vector<path>,path::comparator> paths;
    paths.emplace(start, directions::east, 0);

    int result;
    while(!paths.empty())
    {
        path curr = paths.top();
        paths.pop();
        if(lines[curr.loc.r][curr.loc.c] == '#') continue;
        bool & vis = visited[curr.loc.r][curr.loc.c][curr.dir.val];
        if(vis) continue;
        vis = true;
        
        if(curr.loc == target)
        {
            result = curr.score;
            break;
        }

        Loc2 diff = dir_to_loc_int(curr.dir);
        paths.emplace(curr.loc + diff, curr.dir, curr.score + 1);
        paths.emplace(curr.loc, directions::turn_right(curr.dir), curr.score + 1000);
        paths.emplace(curr.loc, directions::turn_left(curr.dir), curr.score + 1000);
    }

    printf("%d\n", result);

    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
