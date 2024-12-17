#include "../helpers/helpers.hpp"




int main()
{
    timer tm;
    tm.start();

    std::vector<std::string> lines = read_lines();

    std::vector<char*> program_strs = split_string(lines[4].data() + 9, ',');
    std::vector<int32_t> program(program_strs.size());
    std::transform(program_strs.begin(), program_strs.end(), program.begin(), atoi);

    uint64_t A = 0;
    int i = program.size() - 1;
    std::vector<int> js(program.size(), 0);
    while(i >= 0)
    {
        bool ok = false;
        int end = 8;
        if(i == program.size() - 1) end = 1<<30;
        for(int & j = js[i]; j < end; j++)
        {
            uint64_t a = (A << 3) | j;
            if(i == program.size() - 1) a = j;
            uint64_t B = ((a & 7) ^ 5 ^ (a >> ((a & 7) ^ 1))) & 7;
            if(B == program[i])
            {
                A = a;
                ok = true;
                break;
            }
        }
        if(ok)
        {
            i--;
        }
        else
        {
            js[i] = 0;
            i++;
            js[i]++;
            A >>= 3;
        }
    }
    
    printf("%lu\n", A);

    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
