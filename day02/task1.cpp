#include "../helpers/helpers.hpp"



int main()
{
    std::vector<std::string> lines = read_lines();

    std::vector<std::vector<int>> levels;

    for(size_t l = 0; l < lines.size(); l++)
    {
        std::vector<char*> substrs = split_string(lines[l].data(), ' ');

        levels.push_back(std::vector<int>());
        std::vector<int> & curr = levels.back();
        for(size_t i = 0; i < substrs.size(); i++)
        {
            curr.push_back(atoi(substrs[i]));
        }
    }

    int num_good = 0;
    for(size_t l = 0; l < levels.size(); l++)
    {
        bool ok = true;
        int monotonicity = 0;
        std::vector<int> level = levels[l];
        for(size_t i = 1; i < level.size(); i++)
        {
            int prev = level[i-1];
            int curr = level[i];
            int diff = std::abs(curr - prev);
            if(curr > prev) monotonicity++;
            if(curr < prev) monotonicity--;
            if(diff < 1 || diff > 3)
            {
                ok = false;
                break;
            }
        }
        ok = ok && ((size_t)std::abs(monotonicity) + 1 == level.size());
        if(ok) num_good++;
    }

    printf("%d\n", num_good);

    return 0;
}
