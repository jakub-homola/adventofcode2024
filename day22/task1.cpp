#include "../helpers/helpers.hpp"



long long do_hash(long long x)
{
    constexpr long long pruner = (1 << 24) - 1;
    x ^= x * 64;
    x &= pruner;
    x ^= x >> 5;
    x &= pruner;
    x ^= x << 11;
    x &= pruner;
    return x;
}



int main()
{
    timer tm;
    tm.start();

    int nrepeats = 2000;

    std::vector<std::string> input = read_lines();

    long long result = 0;
    for(std::string & s : input)
    {
        long long num = atoll(s.c_str());

        for(int i = 0; i < nrepeats; i++) num = do_hash(num);

        result += num;
    }

    printf("%lld\n", result);

    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
