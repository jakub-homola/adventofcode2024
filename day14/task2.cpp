#include "../helpers/helpers.hpp"



struct robot
{
    Point2<int> pos;
    Point2<int> vel;
};


int main()
{
    timer tm;
    tm.start();

    int size_x = 101;
    int size_y = 103;

    std::vector<std::string> lines = read_lines();
    std::vector<robot> robots(lines.size());

    for(int i = 0; i < lines.size(); i++)
    {
        std::string & l = lines[i];
        robot & r = robots[i];
        sscanf(l.c_str(), "p=%d,%d v=%d,%d", &r.pos.x, &r.pos.y, &r.vel.x, &r.vel.y);
    }

    std::vector<std::string> img_empty(size_y, std::string(101, '.'));
    std::vector<std::string> img;
    for(int it = 1; ; it++)
    {
        for(int i = 0; i < robots.size(); i++)
        {
            robot & r = robots[i];
            r.pos = r.pos + r.vel;
            r.pos.x = (r.pos.x + size_x) % size_x;
            r.pos.y = (r.pos.y + size_y) % size_y;
        }

        // 12 and 35 empirically observed, there were "weird horizontal and vertical lines"
        if((it - 12) % 103 == 0 && (it - 35) % 101 == 0)
        {
            img = img_empty;
            for(int i = 0; i < robots.size(); i++)
            {
                robot & r = robots[i];
                img[r.pos.y][r.pos.x] = 'X';
            }

            printf("\n\n\nIteration %d\n", it);
            for(int r = 0; r < size_y; r++)
            {
                printf("%s\n", img[r].c_str());
            }

            // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            break;
        }
    }

    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
