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
    std::vector<std::vector<std::array<int,4>>> lowest_scores(h, std::vector<std::array<int,4>>(w, std::array<int,4>({1<<30,1<<30,1<<30,1<<30})));

    Loc2 start(h-2,1);
    Loc2 target(1, w-2);
    std::priority_queue<path,std::vector<path>,path::comparator> paths;
    paths.emplace(start, directions::east, 0);

    int best = 1<<30;
    while(!paths.empty())
    {
        path curr = paths.top();
        paths.pop();
        if(lines[curr.loc.r][curr.loc.c] == '#') continue;
        bool & vis = visited[curr.loc.r][curr.loc.c][curr.dir.val];
        if(vis) continue;
        vis = true;
        if(curr.score > best) continue;

        int & ls = lowest_scores[curr.loc.r][curr.loc.c][curr.dir.val];
        ls = std::min(ls, curr.score);
        
        if(curr.loc == target)
        {
            best = curr.score;
        }

        Loc2 diff = dir_to_loc_int(curr.dir);
        paths.emplace(curr.loc + diff, curr.dir, curr.score + 1);
        paths.emplace(curr.loc, directions::turn_right(curr.dir), curr.score + 1000);
        paths.emplace(curr.loc, directions::turn_left(curr.dir), curr.score + 1000);
    }

    for(int r = 0; r < h; r++) for(int c = 0; c < w; c++) for(int d = 0; d < 4; d++) visited[r][c][d] = false;

    std::deque<path> paths2;
    paths2.emplace_back(target, directions::north, 0);
    paths2.emplace_back(target, directions::south, 0);
    paths2.emplace_back(target, directions::east, 0);
    paths2.emplace_back(target, directions::west, 0);
    while(!paths2.empty())
    {
        path p = paths2.front();
        paths2.pop_front();
        bool & vis = visited[p.loc.r][p.loc.c][p.dir];
        if(vis) continue;
        vis = true;

        lines[p.loc.r][p.loc.c] = 'O';

        int currscore = lowest_scores[p.loc.r][p.loc.c][directions::turn_around(p.dir)];

        std::vector<path> potentials;
        potentials.emplace_back(p.loc + dir_to_loc_int(p.dir), p.dir, 0);
        potentials.emplace_back(p.loc, directions::turn_left(p.dir), 0);
        potentials.emplace_back(p.loc, directions::turn_right(p.dir), 0);

        for(path & pp : potentials)
        {
            int nextscore = lowest_scores[pp.loc.r][pp.loc.c][directions::turn_around(pp.dir)];
            if(nextscore < currscore) paths2.push_back(pp);
        }
    }

    for(int r = 0; r < h; r++)
    {
        printf("%s\n", lines[r].c_str());
    }

    int result = 0;
    for(int r = 0; r < h; r++)
    {
        for(int c = 0; c < w; c++)
        {
            if(lines[r][c] == 'O') result++;
        }
    }

    printf("%d\n", result);

    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
