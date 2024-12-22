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

    std::vector<int> yields(160000, 0);

    for(std::string & s : input)
    {
        long long num = atoll(s.c_str());

        std::unordered_set<int> seen;

        int prev_price = 0;
        int diffenc = 0;
        for(int i = 0; i < nrepeats; i++)
        {
            num = do_hash(num);
            int price = num % 10;
            int pricediff = price - prev_price;
            diffenc = (diffenc * 20 + pricediff + 10) % 160000;
            if(i >= 4)
            {
                if(!seen.contains(diffenc))
                {
                    seen.insert(diffenc);
                    yields[diffenc] += price;
                }
            }
            prev_price = price;
        }
    }

    int best = *std::max_element(yields.begin(), yields.end());

    printf("%d\n", best);

    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
