#include "../helpers/helpers.hpp"



struct path
{
    Loc2<int> loc;
    int dist;
    path(Loc2<int> l, int d) : loc(l), dist(d) {}
};

int taxicab_dist(Loc2<int> a, Loc2<int> b)
{
    return std::abs(a.r - b.r) + std::abs(a.c - b.c);
}



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
    std::vector<Loc2<int>> locs_on_path;
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
            locs_on_path.push_back(curr.loc);
            paths.emplace_back(curr.loc + Loc2( 1, 0), curr.dist + 1);
            paths.emplace_back(curr.loc + Loc2(-1, 0), curr.dist + 1);
            paths.emplace_back(curr.loc + Loc2( 0, 1), curr.dist + 1);
            paths.emplace_back(curr.loc + Loc2( 0,-1), curr.dist + 1);
        }
    }

    std::unordered_map<int, int> cheats;
    {
        for(int i = 0; i < locs_on_path.size(); i++)
        {
            for(int j = i + 1; j < locs_on_path.size(); j++)
            {
                Loc2 a = locs_on_path[i];
                Loc2 b = locs_on_path[j];
                int dist = taxicab_dist(a, b);
                if(dist <= 20)
                {
                    int saved = dists[b.r][b.c] - dists[a.r][a.c] - dist;
                    if(saved > 0)
                    {
                        auto it = cheats.find(saved);
                        if(it == cheats.end()) cheats.emplace(saved, 1);
                        else it->second++;
                    }
                }
            }
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
