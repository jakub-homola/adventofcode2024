#include "../helpers/helpers.hpp"



int main()
{
    std::vector<std::string> lines = read_lines();

    std::vector<std::string> lines_order;
    std::vector<std::string> lines_print;
    bool empty_encountered = false;
    for(std::string & line : lines)
    {
        if(line.length() == 0)
        {
            empty_encountered = true;
            continue;
        }
        if(!empty_encountered)
        {
            lines_order.emplace_back(std::move(line));
        }
        if(empty_encountered)
        {
            lines_print.emplace_back(std::move(line));
        }
    }

    constexpr int max_pagenum = 100;
    bool must_preceed[max_pagenum][max_pagenum];
    std::memset(must_preceed, 0, sizeof(must_preceed));

    for(std::string & line : lines_order)
    {
        int first, second;
        sscanf(line.c_str(), "%d|%d", &first, &second);
        if(first >= max_pagenum || second >= max_pagenum) throw std::runtime_error("out of range\n");
        must_preceed[first][second] = true;
    }

    int result = 0;
    for(std::string & line : lines_print)
    {
        std::vector<char*> linesplit = split_string(line.data(), ',');
        std::vector<int> pages_print(linesplit.size());
        std::transform(linesplit.begin(), linesplit.end(), pages_print.begin(), atoi);

        bool ok = true;
        for(int i = 0; i < pages_print.size(); i++)
        {
            for(int j = i+1; j < pages_print.size(); j++)
            {
                int first = pages_print[i];
                int second = pages_print[j];
                if(must_preceed[second][first])
                {
                    ok = false;
                }
            }
        }

        if(!ok)
        {
            std::sort(pages_print.begin(), pages_print.end(), [&](int l, int r) {
                return must_preceed[l][r];
            });

            int middle_page = pages_print[pages_print.size() / 2];
            result += middle_page;
        }
    }

    printf("%d\n", result);

    return 0;
}
