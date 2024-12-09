#include "../helpers/helpers.hpp"



struct chunk
{
    int id;
    int size;
    int startpos;
    long long get_partial_result()
    {
        long long res = 0;
        for(int j = 0; j < size; j++)
        {
            res += id * (startpos + j);
        }
        return res;
    }
};

int main()
{
    timer tm;
    tm.start();


    std::vector<std::string> lines = read_lines();
    std::string & line = lines[0];

    std::vector<chunk> spaces;
    std::vector<chunk> files;
    spaces.reserve(line.size() + 1);
    files.reserve(line.size() + 1);

    bool space = false;
    int cfi = 0;
    int curr_pos = 0;
    for(char c : line)
    {
        if(space) spaces.push_back({-1, c - '0', curr_pos});
        else files.push_back({cfi++, c - '0', curr_pos});
        curr_pos += c - '0';
        space = !space;
    }

    long long result = 0;
    for(int i = 0; i < files.size(); i++)
    {
        result += files[i].get_partial_result();
    }

    for(int fi = files.size() - 1; fi >= 0; fi--)
    {
        chunk & f = files[fi];
        for(int si = 0; si < fi; si++)
        {
            chunk & s = spaces[si];
            if(s.size >= f.size)
            {
                result -= f.get_partial_result();
                f.startpos = s.startpos;
                s.size -= f.size;
                s.startpos += f.size;
                result += f.get_partial_result();
                break;
            }
        }
    }

    printf("%lld\n", result);

    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
