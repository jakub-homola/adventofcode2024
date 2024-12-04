#include "../helpers/helpers.hpp"



int main()
{
    std::vector<std::string> lines = read_lines();

    std::regex rgx("mul\\(\\d{1,3},\\d{1,3}\\)");

    int result = 0;
    for(size_t l = 0; l < lines.size(); l++)
    {
        auto begin = std::sregex_iterator(lines[l].begin(), lines[l].end(), rgx);
        auto end = std::sregex_iterator();

        for(auto it = begin; it != end; it++)
        {
            const char * s = it->str().c_str();
            int n1, n2;
            sscanf(s, "mul(%d,%d)", &n1, &n2);
            result += n1 * n2;
        }
    }

    printf("%d\n", result);

    return 0;
}
