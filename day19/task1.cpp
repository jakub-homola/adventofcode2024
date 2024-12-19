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

bool is_pattern_possible(std::vector<std::string> & towels, const char * pattern)
{
    if(*pattern == '\0') return true;
    for(int t = 0; t < towels.size(); t++)
    {
        if(fits(towels[t].c_str(), pattern))
        {
            if(is_pattern_possible(towels, pattern + towels[t].length()))
            {
                return true;
            }
        }
    }
    return false;
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

    int result = 0;
    for(int l = 2; l < input.size(); l++)
    {
        std::string & line = input[l];

        bool possible = is_pattern_possible(towels, line.c_str());
        if(possible) result++;
    }

    printf("%d\n", result);

    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
