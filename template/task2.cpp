#include "../helpers/helpers.hpp"



int main()
{
    timer tm;
    tm.start();







    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
