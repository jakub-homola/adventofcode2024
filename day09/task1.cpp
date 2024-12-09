#include "../helpers/helpers.hpp"



int main()
{
    timer tm;
    tm.start();


    std::vector<std::string> lines = read_lines();
    std::string & line = lines[0];

    std::vector<int> disk;
    bool space = false;
    int curr_fileid = 0;
    for(char c : line)
    {
        int size = c - '0';
        if(space)
        {
            for(int i = 0; i < size; i++) disk.push_back(-1);
        }
        if(!space)
        {
            for(int i = 0; i < size; i++) disk.push_back(curr_fileid);
            curr_fileid++;
        }
        space = !space;
    }

    int idx_l = 0;
    int idx_r = disk.size() - 1;
    while(idx_l < idx_r)
    {
        if(disk[idx_l] == -1)
        {
            if(disk[idx_r] == -1)
            {
                idx_r--;
            }
            else
            {
                std::swap(disk[idx_l], disk[idx_r]);
                idx_l++;
                idx_r--;
            }
        }
        else
        {
            idx_l++;
        }
    }

    long long result = 0;
    for(int i = 0; i < disk.size(); i++)
    {
        if(disk[i] == -1) break;
        result += i * disk[i];
    }

    printf("%lld\n", result);

    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
