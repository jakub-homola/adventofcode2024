#include "../helpers/helpers.hpp"



direction char_to_dir(char ch)
{
    switch(ch)
    {
        case '^': return directions::north;
        case '>': return directions::east;
        case 'v': return directions::south;
        case '<': return directions::west;
        default: return directions::none;
    }
}

struct hasher
{
    size_t operator()(const Loc2<int> & loc) const
    {
        return 100 * loc.r + loc.c;
    }
};

struct equalto
{
    size_t operator()(const Loc2<int> & l, const Loc2<int> & r) const
    {
        return l.r == r.r && l.c == r.c;
    }
};



int main()
{
    timer tm;
    tm.start();

    std::vector<std::string> lines = read_lines();

    auto it_empty = std::find_if(lines.begin(), lines.end(), [](std::string & s){ return s.empty(); });
    int h = it_empty - lines.begin();
    int w = lines[0].size();

    Loc2 robot;
    std::unordered_set<Loc2<int>,hasher,equalto> boxes;
    std::unordered_set<Loc2<int>,hasher,equalto> walls;
    for(int r = 0; r < h; r++)
    {
        for(int c = 0; c < w; c++)
        {
            if(lines[r][c] == '@')
            {
                robot = Loc2(r, 2*c);
            }
            if(lines[r][c] == 'O')
            {
                boxes.emplace(r, 2*c);
            }
            if(lines[r][c] == '#')
            {
                walls.emplace(r, 2*c);
                walls.emplace(r, 2*c+1);
            }
        }
    }

    for(auto it = it_empty + 1; it != lines.end(); it++)
    {
        std::string & line = *it;
        for(int i = 0; i < line.size(); i++)
        {
            // {
            //     std::vector<char[200]> toprint(h);
            //     for(int r = 0; r < h; r++)
            //     {
            //         memset(toprint[r], '.', sizeof(toprint[r]));
            //         toprint[r][2*w] = '\0';
            //     }
            //     for(auto it = walls.begin(); it != walls.end(); it++)
            //     {
            //         toprint[it->r][it->c] = '#';
            //     }
            //     for(auto it = boxes.begin(); it != boxes.end(); it++)
            //     {
            //         toprint[it->r][it->c] = '[';
            //         toprint[it->r][it->c+1] = ']';
            //     }
            //     toprint[robot.r][robot.c] = '@';
            //     for(int r = 0; r < h; r++)
            //     {
            //         printf("%s\n", toprint[r]);
            //     }
            //     printf("%c\n", line[i]);
            // }
            direction dir = char_to_dir(line[i]);
            Loc2 diff = dir_to_loc_int(dir);
            std::vector<Loc2<int>> boxes_topush;
            std::stack<Loc2<int>> locs_to_try;
            locs_to_try.push(robot + diff);
            bool ok = true;
            while(!locs_to_try.empty())
            {
                Loc2 loc = locs_to_try.top();
                locs_to_try.pop();
                auto it_wall = walls.find(loc);
                if(it_wall != walls.end())
                {
                    ok = false;
                    break;
                }
                if(directions::is_horizontal(dir))
                {
                    if(dir == directions::east)
                    {
                        auto it = boxes.find(loc);
                        if(it != boxes.end())
                        {
                            boxes_topush.push_back(loc);
                            boxes.erase(it);
                            locs_to_try.push(loc + 2 * diff);
                        }
                    }
                    if(dir == directions::west)
                    {
                        auto it = boxes.find(loc + Loc2(0,-1));
                        if(it != boxes.end())
                        {
                            boxes_topush.push_back(loc + Loc2(0,-1));
                            boxes.erase(it);
                            locs_to_try.push(loc + 2 * diff);
                        }
                    }
                }
                if(directions::is_vertical(dir))
                {
                    Loc2 loc_l = loc + Loc2(0,-1);
                    Loc2 loc_r = loc;
                    auto it_l = boxes.find(loc_l);
                    auto it_r = boxes.find(loc_r);
                    if(it_l != boxes.end())
                    {
                        boxes_topush.push_back(loc_l);
                        boxes.erase(it_l);
                        locs_to_try.push(loc_l + diff);
                        locs_to_try.push(loc_l + diff + Loc2(0,1));
                    }
                    if(it_r != boxes.end())
                    {
                        boxes_topush.push_back(loc_r);
                        boxes.erase(it_r);
                        locs_to_try.push(loc_r + diff);
                        locs_to_try.push(loc_r + diff + Loc2(0,1));
                    }
                }
            }
            for(Loc2 box : boxes_topush)
            {
                if(ok)
                {
                    boxes.insert(box + diff);
                }
                else
                {
                    boxes.insert(box);
                }
            }
            if(ok)
            {
                robot = robot + diff;
            }
        }
    }

    int result = 0;
    for(auto it = boxes.begin(); it != boxes.end(); it++)
    {
        Loc2 box = *it;
        result += 100 * box.r + box.c;
    }

    printf("%d\n", result);

    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
