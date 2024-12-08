#include "../helpers/helpers.hpp"



int main()
{
    timer tm;
    tm.start();

    std::vector<std::string> lines = read_lines();
    int h = lines.size();
    int w = lines[0].size();

    std::map<char,std::vector<Point2<int>>> ant;
    for(int r = 0; r < h; r++)
    {
        for(int c = 0; c < w; c++)
        {
            char ch = lines[r][c];
            if(ch != '.')
            {
                auto it = ant.find(ch);
                if(it == ant.end())
                {
                    it = ant.insert({ch, std::vector<Point2<int>>()}).first;
                }
                it->second.push_back({c,r});
            }
        }
    }

    std::vector<std::vector<char>> anodes(h, std::vector<char>(w, '\0'));

    for(auto it = ant.begin(); it != ant.end(); it++)
    {
        char ch = it->first;
        std::vector<Point2<int>> & locs = it->second;
        for(int i = 0; i < locs.size(); i++)
        {
            Point2<int> pi = locs[i];
            for(int j = i+1; j < locs.size(); j++)
            {
                Point2<int> pj = locs[j];
                Point2<int> delta = pi - pj;
                Point2<int> curr = pi;
                while(curr.x >= 0 && curr.x < w && curr.y >= 0 && curr.y < h)
                {
                    anodes[curr.y][curr.x] = '#';
                    curr = curr + delta;
                }
                curr = pj;
                while(curr.x >= 0 && curr.x < w && curr.y >= 0 && curr.y < h)
                {
                    anodes[curr.y][curr.x] = '#';
                    curr = curr - delta;
                }
            }
        }
    }

    int count = 0;
    for(int r = 0; r < h; r++)
    {
        for(int c = 0; c < w; c++)
        {
            if(anodes[r][c] == '#') count++;
        }
    }

    printf("%d\n", count);

    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
