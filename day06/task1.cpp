#include "../helpers/helpers.hpp"



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

    Point2<int> curr;
    for(int r = 1; r <= h; r++)
    {
        for(int c = 1; c <= w; c++)
        {
            if(lines[r][c] == '^')
            {
                curr = Point2<int>(c,r);
            }
        }
    }

    direction dir = directions::north;
    while(true)
    {
        if(lines[curr.y][curr.x] == '+') break;

        lines[curr.y][curr.x] = 'X';
        Point2<int> next = curr + dir_to_point_int(dir);

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

    int count = 0;
    for(int r = 1; r <= h; r++)
    {
        for(int c = 1; c <= w; c++)
        {
            if(lines[r][c] == 'X')
            {
                count++;
            }
        }
    }

    printf("%d\n", count);

    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
