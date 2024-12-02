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
        std::vector<int> level = levels[l];
        if(level.size() == 2)
        {
            num_good++;
            continue;
        }

        std::vector<int> diffs1;
        std::vector<int> diffs2;
        for(size_t i = 1; i < level.size(); i++)
        {
            size_t ii = i-1;
            int prev = level[ii];
            int curr = level[i];
            diffs1.push_back(curr - prev);
        }
        for(size_t i = 2; i < level.size(); i++)
        {
            size_t ii = i-2;
            int prev = level[ii];
            int curr = level[i];
            diffs2.push_back(curr - prev);
        }

        int monotonicity = 0;
        for(size_t i = 0; i < diffs1.size(); i++)
        {
            if(diffs1[i] > 0) monotonicity++;
            if(diffs1[i] < 0) monotonicity--;
        }
        if(diffs1.size() == 2 && monotonicity == 0)
        {
            if(diffs2[0] > 0) monotonicity++;
            if(diffs2[0] < 0) monotonicity--;
        }
        bool is_incr = (monotonicity > 0);
        bool is_decr = (monotonicity < 0);

        int num_outliers = 0;
        bool ok = true;
        for(size_t i = 0; i < diffs1.size(); i++)
        {
            int d = diffs1[i];
            int da = std::abs(d);
            bool diff_ok = (da >=1 && da <= 3);
            bool mono_ok = ((is_incr && d > 0) || (is_decr && d < 0));
            if(!diff_ok || !mono_ok)
            {
                if(i == diffs1.size() - 1)
                {
                    num_outliers++;
                    continue;
                }

                d = diffs2[i];
                da = std::abs(d);
                diff_ok = (da >=1 && da <= 3);
                mono_ok = ((is_incr && d > 0) || (is_decr && d < 0));
                if(diff_ok && mono_ok)
                {
                    num_outliers++;
                    i++;
                }
                else
                {
                    if(i == 0)
                    {
                        num_outliers++;
                    }
                    else
                    {
                        ok = false;
                        break;
                    }
                }
            }
        }

        if(ok && num_outliers <= 1)
        {
            num_good++;
        }
    }

    printf("%d\n", num_good);

    return 0;
}
