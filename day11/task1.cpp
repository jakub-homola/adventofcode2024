#include "../helpers/helpers.hpp"



long long num_digits(long long x, long long base = 10)
{
    if(x == 0) return 1;
    long long d = 0;
    while(x > 0)
    {
        x /= base;
        d++;
    }
    return d;
}

long long simple_pow(long long x, long long e)
{
    long long res = 1;
    while(e-- > 0) res *= x;
    return res;
}

struct stone
{
    long long num;
    int blinks;
};


int main()
{
    timer tm;
    tm.start();

    std::vector<std::string> lines = read_lines();
    std::string & line = lines[0];
    std::vector<char*> nums_str = split_string(line.data(), ' ');

    std::stack<stone> stones;
    for(char * s : nums_str)
    {
        stones.push({atoll(s), 0});
    }

    long long count = 0;
    while(!stones.empty())
    {
        stone s = stones.top();
        stones.pop();
        if(s.blinks == 25)
        {
            count++;
            continue;
        }

        long long dig = num_digits(s.num);
        int b = s.blinks + 1;
        if(s.num == 0)
        {
            stones.push({1, b});
        }
        else if(dig % 2 == 0)
        {
            long long half_dig = dig / 2;
            long long e = simple_pow(10, half_dig);
            stones.push({s.num / e, b});
            stones.push({s.num % e, b});
        }
        else
        {
            stones.push({s.num * 2024, b});
        }
    }

    printf("%lld\n", count);


    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
