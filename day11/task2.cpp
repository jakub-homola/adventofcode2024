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

struct stone_hash
{
    size_t operator()(const stone & s) const
    {
        return s.num * 1000001 + s.blinks;
    }
};

struct stone_equal
{
    bool operator()(const stone & l, const stone & r) const
    {
        return l.num == r.num && l.blinks == r.blinks;
    }
};

using mymap = std::unordered_map<stone, long long, stone_hash, stone_equal>;

long long how_many_stones(stone s, mymap & m)
{
    auto it = m.find(s);
    if(it != m.end())
    {
        return it->second;
    }
    else
    {
        long long dig = num_digits(s.num);
        int b = s.blinks + 1;
        long long res;
        if(s.blinks == 75)
        {
            return 1;
        }
        else if(s.num == 0)
        {
            res = how_many_stones({1,b}, m);
        }
        else if(dig % 2 == 0)
        {
            long long half_dig = dig / 2;
            long long e = simple_pow(10, half_dig);
            res = how_many_stones({s.num / e, b}, m);
            res += how_many_stones({s.num % e, b}, m);
        }
        else
        {
            res = how_many_stones({s.num * 2024, b}, m);
        }
        m.insert({s, res});
        return res;
    }
}


int main()
{
    timer tm;
    tm.start();

    std::vector<std::string> lines = read_lines();
    std::string & line = lines[0];
    std::vector<char*> nums_str = split_string(line.data(), ' ');

    long long count = 0;
    mymap m;
    for(char * s : nums_str)
    {
        long long num = atoll(s);
        count += how_many_stones({num, 0}, m);
    }

    printf("%lld\n", count);


    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
