#include "../helpers/helpers.hpp"



struct path
{
    Loc2<int> loc;
    int steps;
    path() {}
    path(Loc2<int> l, int s) : loc(l), steps(s) {}
};

struct locint_hasher
{
    size_t operator()(const Loc2<int> & loc) const
    {
        return ((size_t)loc.r * 101) | loc.c;
    }
};

enum struct search
{
    bfs,
    dfs
};

std::list<Loc2<int>> find_shortest_path(const std::vector<std::string> & grid, Loc2<int> start, Loc2<int> target, search s)
{
    std::unordered_map<Loc2<int>, int, locint_hasher> dists;

    {
        std::deque<path> paths;
        paths.emplace_back(start, 0);
        while(!paths.empty())
        {
            path p;
            if(s == search::bfs)
            {
                p = paths.front();
                paths.pop_front();
            }
            if(s == search::dfs)
            {
                p = paths.back();
                paths.pop_back();
            }
            if(grid[p.loc.r][p.loc.c] == '#') continue;
            auto it = dists.find(p.loc);
            if(it != dists.end() && p.steps >= it->second) continue;
            dists.emplace(p.loc, p.steps);
            if(p.loc == target) break;
            paths.emplace_back(p.loc + Loc2( 1, 0), p.steps + 1);
            paths.emplace_back(p.loc + Loc2(-1, 0), p.steps + 1);
            paths.emplace_back(p.loc + Loc2( 0, 1), p.steps + 1);
            paths.emplace_back(p.loc + Loc2( 0,-1), p.steps + 1);
        }
    }

    std::list<Loc2<int>> ret;
    auto it_tgt = dists.find(target);
    if(it_tgt == dists.end()) return ret;

    {
        Loc2 curr = target;
        while(true)
        {
            ret.push_front(curr);
            if(curr == start) break;
            int currdist = dists.find(curr)->second;
            std::vector<Loc2<int>> candidates;
            candidates.reserve(4);
            candidates.push_back(curr + Loc2( 1, 0));
            candidates.push_back(curr + Loc2(-1, 0));
            candidates.push_back(curr + Loc2( 0, 1));
            candidates.push_back(curr + Loc2( 0,-1));
            for(Loc2 l : candidates)
            {
                auto it = dists.find(l);
                if(it != dists.end() && it->second < currdist)
                {
                    curr = l;
                    break;
                }
            }
        }
    }

    return ret;
}

void remove_equal_neigh(std::list<Loc2<int>> path, std::list<Loc2<int>>::iterator it1, std::list<Loc2<int>>::iterator it2, std::vector<std::string> & grid)
{
    while(*it1 == *it2)
    {
        auto prev = std::prev(it1);
        auto next = std::next(it2);
        if(*prev == *next)
        {
            grid[it1->r][it1->c] = '.';
            path.erase(it1);
            path.erase(it2);
        }
        else
        {
            path.erase(it1);
        }
        it1 = prev;
        it2 = next;
    }
}



int main(int argc, char ** argv)
{
    timer tm;
    tm.start();

    int size = 71;
    if(argc > 1) size = atoi(argv[1]);

    std::vector<std::string> lines = read_lines();

    std::vector<std::string> space = grid_pad(std::vector(size, std::string(size, '.')), '#', 1);

    Loc2 start(1,1);
    Loc2 target(size, size);
    std::list<Loc2<int>> curr_path = find_shortest_path(space, start, target, search::dfs);

    for(Loc2 l : curr_path) space[l.r][l.c] = 'O';

    // for(int r = 0; r < space.size(); r++) printf("%s\n", space[r].c_str());

    Loc2 result;
    for(int l = 0; l < lines.size(); l++)
    {
        Loc2 loc_block;
        sscanf(lines[l].c_str(), "%d,%d", &loc_block.c, &loc_block.r);
        loc_block.r++;
        loc_block.c++;
        char orig_space_char = space[loc_block.r][loc_block.c];
        space[loc_block.r][loc_block.c] = '#';
        // printf("impact at %d,%d %c\n", loc_block.r, loc_block.c, orig_space_char);

        if(orig_space_char != 'O') continue;
        if(loc_block == start || loc_block == target)
        {
            result = loc_block;
            break;
        }

        auto it_first_occur = std::find(curr_path.begin(), curr_path.end(), loc_block);
        auto it_last_occur_rev = std::find(curr_path.rbegin(), curr_path.rend(), loc_block);
        auto it_last_occur = std::next(it_last_occur_rev).base();
        auto it_last_occur_next = std::next(it_last_occur);
        for(auto it = it_first_occur; it != it_last_occur_next; it++) if(*it != loc_block) space[it->r][it->c] = '.';
        auto it_prev = std::prev(it_first_occur);
        auto it_next = std::next(it_last_occur);
        Loc2 loc_prev = *it_prev;
        Loc2 loc_next = *it_next;
        curr_path.erase(it_first_occur, std::next(it_last_occur));
        std::list<Loc2<int>> toinsert = find_shortest_path(space, loc_prev, loc_next, search::bfs);
        if(toinsert.size() == 0)
        {
            result = loc_block;
            break;
        }
        for(Loc2 l : toinsert) space[l.r][l.c] = 'O';
        curr_path.insert(it_next, toinsert.begin(), toinsert.end());

        remove_equal_neigh(curr_path, it_prev, std::next(it_prev), space);
        remove_equal_neigh(curr_path, std::prev(it_next), it_next, space);
        
        // for(int r = 0; r < space.size(); r++) printf("%s\n", space[r].c_str());
    }

    printf("%d,%d\n", result.c-1, result.r-1);

    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
