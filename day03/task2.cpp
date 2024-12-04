#include "../helpers/helpers.hpp"



int main()
{
    std::vector<std::string> lines = read_lines();

    std::regex rgx("mul\\(\\d{1,3},\\d{1,3}\\)|do\\(\\)|don't\\(\\)");

    int result = 0;
    bool enabled = true;
    for(size_t l = 0; l < lines.size(); l++)
    {
        auto begin = std::sregex_iterator(lines[l].begin(), lines[l].end(), rgx);
        auto end = std::sregex_iterator();

        for(auto it = begin; it != end; it++)
        {
            const char * s = it->str().c_str();
            if(strcmp(s, "do()") == 0)
            {
                enabled = true;
            }
            else if(strcmp(s, "don't()") == 0)
            {
                enabled = false;
            }
            else if(enabled)
            {
                int n1, n2;
                sscanf(s, "mul(%d,%d)", &n1, &n2);
                result += n1 * n2;
            }
        }
    }

    printf("%d\n", result);

    return 0;
}
