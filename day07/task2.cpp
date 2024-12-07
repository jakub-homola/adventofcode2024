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

long long concat_nums(long long l, long long r)
{
    long long r_digits = num_digits(r);
    long long mult = simple_pow(10, r_digits);
    long long res = l * mult + r;
    return res;
}

bool can_be_calculated(long long target, long long curr, long long * nums_left, size_t nums_left_cnt)
{
    if(curr > target) return false;
    if(nums_left_cnt == 0)
    {
        if(curr == target) return true;
        else return false;
    }

    long long num = nums_left[0];
    long long val_mult = curr * num;
    long long val_plus = curr + num;
    long long val_concat = concat_nums(curr, num);
    bool can_mult = can_be_calculated(target, val_mult, nums_left + 1, nums_left_cnt - 1);
    if(can_mult) return true;
    bool can_plus = can_be_calculated(target, val_plus, nums_left + 1, nums_left_cnt - 1);
    if(can_plus) return true;
    bool can_concat = can_be_calculated(target, val_concat, nums_left + 1, nums_left_cnt - 1);
    if(can_concat) return true;
    return false;
}



int main()
{
    timer tm;
    tm.start();

    std::vector<std::string> lines = read_lines();

    long long result = 0;
    for(std::string & line : lines)
    {
        std::vector<char*> nums_str = split_string(line.data(), ' ');
        long long target = atoll(nums_str[0]);
        std::vector<long long> nums(nums_str.size() - 1);
        std::transform(nums_str.begin() + 1, nums_str.end(), nums.begin(), atoll);

        bool can = can_be_calculated(target, 0, nums.data(), nums.size());
        if(can)
        {
            result += target;
        }
    }

    printf("%lld\n", result);



    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
