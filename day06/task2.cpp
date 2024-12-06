#include "../helpers/helpers.hpp"



bool does_loop(std::vector<std::string> lines, Point2<int> curr, direction dir)
{
    int h = lines.size() - 2;
    int w = lines[0].size() - 2;

    std::vector<std::vector<std::array<bool,5>>> visited(h+2, std::vector<std::array<bool,5>>(w+2, {false, false, false, false, false}));

    while(true)
    {
        if(lines[curr.y][curr.x] == '+')
        {
            return false;
        }

        if(visited[curr.y][curr.x][dir.val])
        {
            return true;
        }
        visited[curr.y][curr.x][dir.val] = true;

        lines[curr.y][curr.x] = dir_to_char(dir);
        Point2<int> next = curr + dir_to_point_int(dir);

        if(lines[next.y][next.x] == '#' || lines[next.y][next.x] == 'O')
        {
            dir = directions::turn_right(dir);
        }
        else
        {
            curr = next;
        }
    }
}


int main()
{
    timer tm;
    tm.start();

    std::vector<std::string> lines_orig = read_lines();
    int h = lines_orig.size();
    int w = lines_orig[0].size();

    std::vector<std::string> lines(h+2, std::string(w+2, '+'));
    for(int r = 0; r < h; r++)
    {
        memcpy(lines[r+1].data() + 1, lines_orig[r].data(), w);
    }

    Point2<int> start;
    for(int r = 1; r <= h; r++)
    {
        for(int c = 1; c <= w; c++)
        {
            if(lines[r][c] == '^')
            {
                start = Point2<int>(c,r);
            }
        }
    }
    Point2<int> curr = start;
    lines[curr.y][curr.x] = '.';

    int num_possible_obstacles = 0;
    direction dir = directions::north;
    while(true)
    {
        if(lines[curr.y][curr.x] == '+') break;

        Point2<int> next = curr + dir_to_point_int(dir);
        lines[curr.y][curr.x] = dir_to_char(dir);

        if(lines[next.y][next.x] == '.')
        {
            char orig = lines[next.y][next.x];
            lines[next.y][next.x] = 'O';
            bool loop = does_loop(lines, curr, dir);
            lines[next.y][next.x] = orig;
            if(loop)
            {
                num_possible_obstacles++;
            }
        }

        if(lines[next.y][next.x] == '#')
        {
            dir = directions::turn_right(dir);
        }
        else
        {
            curr = next;
        }
    }

    // for(int r = 0; r <= h+1; r++)
    // {
    //     printf("%s\n", lines[r].c_str());
    // }

    printf("%d\n", num_possible_obstacles);

    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
