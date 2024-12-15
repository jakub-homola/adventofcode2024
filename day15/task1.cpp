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



int main()
{
    timer tm;
    tm.start();

    std::vector<std::string> lines = read_lines();

    auto it_empty = std::find_if(lines.begin(), lines.end(), [](std::string & s){ return s.empty(); });
    int h = it_empty - lines.begin();
    int w = lines[0].size();

    Loc2 robot;
    for(int r = 0; r < h; r++)
    {
        for(int c = 0; c < w; c++)
        {
            if(lines[r][c] == '@')
            {
                robot = Loc2(r,c);
                lines[r][c] = '.';
            }
        }
    }

    for(auto it = it_empty + 1; it != lines.end(); it++)
    {
        std::string & line = *it;
        for(int i = 0; i < line.size(); i++)
        {
            direction dir = char_to_dir(line[i]);
            Loc2 diff = dir_to_loc_int(dir);
            Loc2 src = robot + diff;
            Loc2 curr = src;
            while(true)
            {
                char ch = lines[curr.r][curr.c];
                if(ch == '#')
                {
                    break;
                }
                else if(ch == '.')
                {
                    std::swap(lines[src.r][src.c], lines[curr.r][curr.c]);
                    robot = robot + diff;
                    break;
                }
                else if(ch == 'O')
                {
                    curr = curr + diff;
                }
                else
                {
                    throw std::runtime_error("this should not happen");
                }
            }
        }
    }

    int result = 0;
    for(int r = 0; r < h; r++)
    {
        for(int c = 0; c < w; c++)
        {
            if(lines[r][c] == 'O')
            {
                result += 100 * r + c;
            }
        }
    }

    printf("%d\n", result);

    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
