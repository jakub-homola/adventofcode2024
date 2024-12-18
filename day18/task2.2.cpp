#include "../helpers/helpers.hpp"




bool path_exists(std::vector<std::string> grid, Loc2<int> start, Loc2<int> target)
{
    std::deque<Loc2<int>> locs;
    locs.push_back(start);
    while(!locs.empty())
    {
        Loc2 loc = locs.front();
        locs.pop_front();
        if(grid[loc.r][loc.c] != '.') continue;
        grid[loc.r][loc.c] = 'O';
        if(loc == target) return true;
        locs.push_back(loc + Loc2( 1, 0));
        locs.push_back(loc + Loc2(-1, 0));
        locs.push_back(loc + Loc2( 0, 1));
        locs.push_back(loc + Loc2( 0,-1));
    }
    return false;
}


int main()
{
    timer tm;
    tm.start();

    int size = 71;
    int count = 1024;

    std::vector<std::string> lines = read_lines();
    std::vector<Loc2<int>> obstacles(lines.size());
    std::transform(lines.begin(), lines.end(), obstacles.begin(), [](const std::string & s){ Loc2<int> l; sscanf(s.c_str(), "%d,%d", &l.c, &l.r); l.r++; l.c++; return l;});

    std::vector<std::string> space = grid_pad(std::vector(size, std::string(size, '.')), '#', 1);
    Loc2 start(1,1);
    Loc2 target(size, size);

    int l = -1;
    int r = obstacles.size() - 1; // indicates last placed obstacle index
    std::vector<std::string> space_l = space;
    std::vector<std::string> space_r = space;
    for(Loc2<int> lol : obstacles) space_r[lol.r][lol.c] = '#';
    Loc2 result;
    while(true)
    {
        if(l + 1 == r)
        {
            result = obstacles[r];
            break;
        }
        int c = (l + r) / 2;
        std::vector<std::string> space_c = space_l;
        for(int i = l + 1; i <= c; i++)
        {
            Loc2<int> & loc = obstacles[i];
            space_c[loc.r][loc.c] = '#';
        }
        bool possible = path_exists(space_c, start, target);
        if(possible)
        {
            l = c;
            space_l = std::move(space_c);
        }
        else
        {
            r = c;
            space_r = std::move(space_c);
        }
    }

    printf("%d,%d\n", result.c-1, result.r-1);

    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
