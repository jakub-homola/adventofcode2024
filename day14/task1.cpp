#include "../helpers/helpers.hpp"





int main()
{
    timer tm;
    tm.start();

    int size_x = 101;
    int size_y = 103;
    int timesteps = 100;
    int size_x_half = size_x / 2;
    int size_y_half = size_y / 2;

    std::vector<std::string> lines = read_lines();

    std::vector<int> qs(4, 0);
    for(int i = 0; i < lines.size(); i++)
    {
        std::string & l = lines[i];
        Point2 pos;
        Point2 vel;
        sscanf(l.c_str(), "p=%d,%d v=%d,%d", &pos.x, &pos.y, &vel.x, &vel.y);
        pos = pos + 100 * vel;
        pos.x = ((pos.x % size_x) + size_x) % size_x;
        pos.y = ((pos.y % size_y) + size_y) % size_y;
        if(pos.x == size_x_half || pos.y == size_y_half) continue;
        bool leftright = pos.x < size_x_half;
        bool updown = pos.y < size_y_half;
        qs[(int)leftright + 2 * (int)updown]++;
    }

    int result = qs[0] * qs[1] * qs[2] * qs[3];

    printf("%d\n", result);

    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
