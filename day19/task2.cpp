#include "../helpers/helpers.hpp"



bool fits(const char * towel, const char * pattern)
{
    while(true)
    {
        if(*towel == '\0') return true;
        if(*pattern == '\0') return false;
        if(*towel != *pattern) return false;
        towel++;
        pattern++;
    }
}

long long is_pattern_possible(std::vector<std::string> & towels, const char * pattern, std::unordered_map<const char *,long long> & mem)
{
    if(*pattern == '\0') return 1;
    auto it = mem.find(pattern);
    if(it != mem.end()) return it->second;
    long long ways = 0;
    for(int t = 0; t < towels.size(); t++)
    {
        if(fits(towels[t].c_str(), pattern))
        {
            ways += is_pattern_possible(towels, pattern + towels[t].length(), mem);
        }
    }
    mem.emplace(pattern, ways);
    return ways;
}


int main()
{
    timer tm;
    tm.start();

    std::vector<std::string> input = read_lines();

    std::vector<std::string> towels;
    std::string curr_towel;
    for(char * c = input[0].data(); *c != '\0'; c++)
    {
        if(*c == ',')
        {
            towels.emplace_back(std::move(curr_towel));
            curr_towel.clear();
            continue;
        }
        if(*c == ' ') continue;
        curr_towel.push_back(*c);
    }
    towels.emplace_back(std::move(curr_towel));

    long long result = 0;
    for(int l = 2; l < input.size(); l++)
    {
        std::string & line = input[l];

        std::unordered_map<const char *,long long> mem;
        result += is_pattern_possible(towels, line.c_str(), mem);
    }

    printf("%lld\n", result);

    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
