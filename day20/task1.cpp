#include "../helpers/helpers.hpp"



struct path
{
    Loc2<int> loc;
    int dist;
    path(Loc2<int> l, int d) : loc(l), dist(d) {}
};



int main()
{
    timer tm;
    tm.start();

    std::vector<std::string> input = read_lines();
    std::vector<std::string> grid = grid_pad(input, '#', 1);
    int h = grid.size();
    int w = grid[0].size();

    Loc2 start;
    Loc2 target;
    for(int r = 0; r < h; r++)
    {
        for(int c = 0; c < w; c++)
        {
            if(grid[r][c] == 'S') start = Loc2(r,c);
            if(grid[r][c] == 'E') target = Loc2(r,c);
        }
    }

    std::vector<std::vector<int>> dists(h, std::vector<int>(w));
    {
        std::deque<path> paths;
        paths.emplace_back(start, 0);
        while(!paths.empty())
        {
            path curr = paths.front();
            paths.pop_front();
            if(grid[curr.loc.r][curr.loc.c] == '#') continue;
            if(grid[curr.loc.r][curr.loc.c] == 'O') continue;
            grid[curr.loc.r][curr.loc.c] = 'O';
            dists[curr.loc.r][curr.loc.c] = curr.dist;
            paths.emplace_back(curr.loc + Loc2( 1, 0), curr.dist + 1);
            paths.emplace_back(curr.loc + Loc2(-1, 0), curr.dist + 1);
            paths.emplace_back(curr.loc + Loc2( 0, 1), curr.dist + 1);
            paths.emplace_back(curr.loc + Loc2( 0,-1), curr.dist + 1);
        }
    }

    std::unordered_map<int, int> cheats;
    {
        std::deque<path> paths;
        paths.emplace_back(start, 0);
        while(!paths.empty())
        {
            path curr = paths.front();
            paths.pop_front();
            if(grid[curr.loc.r][curr.loc.c] != 'O') continue;
            grid[curr.loc.r][curr.loc.c] = 'x';
            for(int d = 0; d < 4; d++)
            {
                Loc2 diff = 2 * dir_to_loc_int(direction(d));
                Loc2 next = curr.loc + diff;
                if(grid[next.r][next.c] == '#') continue;
                int nextdist = dists[next.r][next.c];
                int saved = nextdist - curr.dist - 2;
                if(saved > 0)
                {
                    auto it = cheats.find(saved);
                    if(it == cheats.end()) cheats.emplace(saved, 1);
                    else it->second++;
                }
            }
            paths.emplace_back(curr.loc + Loc2( 1, 0), curr.dist + 1);
            paths.emplace_back(curr.loc + Loc2(-1, 0), curr.dist + 1);
            paths.emplace_back(curr.loc + Loc2( 0, 1), curr.dist + 1);
            paths.emplace_back(curr.loc + Loc2( 0,-1), curr.dist + 1);
        }
    }

    int result = 0;
    for(auto it = cheats.begin(); it != cheats.end(); it++)
    {
        // printf("saved %6d: %6d times\n", it->first, it->second);
        if(it->first >= 100) result += it->second;
    }

    printf("%d\n", result);

    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
