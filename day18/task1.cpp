#include "../helpers/helpers.hpp"



struct path
{
    Loc2<int> loc;
    int steps;
    path(Loc2<int> l, int s) : loc(l), steps(s) {}
};



int main(int argc, char ** argv)
{
    timer tm;
    tm.start();

    int size = 71;
    if(argc > 1) size = atoi(argv[1]);
    int count = 1024;

    std::vector<std::string> lines = read_lines();

    std::vector<std::vector<char>> space(size, std::vector<char>(size, '.'));

    int realcount = std::min(count, (int)lines.size());
    for(int l = 0; l < count; l++)
    {
        Point2 pt;
        sscanf(lines[l].c_str(), "%d,%d", &pt.x, &pt.y);
        space[pt.y][pt.x] = '#';
    }

    Loc2 start(0,0);
    Loc2 target(size-1, size-1);
    std::deque<path> paths;
    paths.emplace_back(start, 0);
    int result;
    while(!paths.empty())
    {
        path p = paths.front();
        paths.pop_front();
        if(p.loc.r < 0 || p.loc.r >= size || p.loc.c < 0 || p.loc.c >= size) continue;
        if(space[p.loc.r][p.loc.c] != '.') continue;
        space[p.loc.r][p.loc.c] = 'O';
        if(p.loc == target)
        {
            result = p.steps;
            break;
        }
        paths.emplace_back(p.loc + Loc2( 1, 0), p.steps + 1);
        paths.emplace_back(p.loc + Loc2(-1, 0), p.steps + 1);
        paths.emplace_back(p.loc + Loc2( 0, 1), p.steps + 1);
        paths.emplace_back(p.loc + Loc2( 0,-1), p.steps + 1);
    }

    printf("%d\n", result);

    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
