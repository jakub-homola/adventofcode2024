#include "../helpers/helpers.hpp"



int main()
{
    timer tm;
    tm.start();

    std::vector<std::string> lines_orig = read_lines();
    std::vector<std::string> lines = grid_pad(lines_orig, '.');
    int h = lines.size();
    int w = lines[0].size();

    std::vector<std::vector<bool>> visited(h, std::vector<bool>(w, false));

    int result = 0;
    for(int r = 1; r < h-1; r++)
    {
        for(int c = 1; c < w-1; c++)
        {
            if(!visited[r][c])
            {
                char crop = lines[r][c];
                std::deque<Loc2<int>> q;
                std::vector<Loc2<int>> hist;
                q.push_back({r,c});
                visited[r][c] = true;
                int perim = 0;
                int area = 0;
                while(!q.empty())
                {
                    Loc2<int> curr = q.front();
                    q.pop_front();
                    hist.push_back(curr);
                    area++;
                    for(int d = 0; d < 4; d++)
                    {
                        Loc2<int> diff = dir_to_loc_int(direction(d));
                        Loc2<int> next = curr + diff;
                        if(lines[next.r][next.c] == crop && !visited[next.r][next.c])
                        {
                            q.push_back(next);
                            visited[next.r][next.c] = true;
                        }
                        if(lines[next.r][next.c] != crop)
                        {
                            perim++;
                        }
                    }
                }
                for(int i = 0; i < hist.size(); i++)
                {
                    Loc2<int> curr = hist[i];
                    for(int d = 0; d < 4; d++)
                    {
                        Loc2<int> diff = dir_to_loc_int(direction(d));
                        Loc2<int> next = curr + diff;
                        Loc2<int> diff2 = dir_to_loc_int(directions::turn_right(direction(d)));
                        Loc2<int> next2 = curr + diff2;
                        Loc2<int> next3 = curr + diff + diff2;
                        if(lines[next.r][next.c] == crop && lines[next2.r][next2.c] != crop && lines[next3.r][next3.c] != crop)
                        {
                            perim--;
                        }
                    }
                }
                result += area * perim;
            }
        }
    }

    printf("%d\n", result);

    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
