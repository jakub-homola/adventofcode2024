#include "../helpers/helpers.hpp"



int main()
{
    timer tm;
    tm.start();

    std::vector<std::string> lines = read_lines();

    uint64_t A, B, C;
    sscanf(lines[0].c_str(), "Register A: %lu", &A);
    sscanf(lines[1].c_str(), "Register B: %lu", &B);
    sscanf(lines[2].c_str(), "Register C: %lu", &C);

    std::vector<char*> program_strs = split_string(lines[4].data() + 9, ',');
    std::vector<int> program(program_strs.size());
    std::transform(program_strs.begin(), program_strs.end(), program.begin(), atoi);

    int pc = 0;
    std::vector<int> out;
    while(pc < program.size())
    {
        uint64_t instr = program[pc];
        uint64_t op = program[pc + 1];
        uint64_t literal = op;
        uint64_t combo = op;
        if(op == 4) combo = A;
        if(op == 5) combo = B;
        if(op == 6) combo = C;
        
        switch(instr)
        {
        case 0: // adv
            A = A >> combo;
            break;
        case 1: // bxl
            B = B ^ literal;
            break;
        case 2: // bst
            B = combo & 7;
            break;
        case 3: // jnz
            if(A != 0) pc = (int)literal - 2;
            break;
        case 4: // bxc
            B = B ^ C;
            break;
        case 5: // out
            out.push_back(combo & 7);
            break;
        case 6: // bdv
            B = A >> combo;
            break;
        case 7: // cdv
            C = A >> combo;
            break;
        }

        pc += 2;
    }

    for(size_t i = 0; i < out.size(); i++)
    {
        if(i > 0) printf(",");
        printf("%d", out[i]);
    }
    printf("\n");

    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
