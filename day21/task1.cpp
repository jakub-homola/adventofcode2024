#include "../helpers/helpers.hpp"



Loc2<int> get_loc(char key)
{
    switch(key)
    {
        case '0': return Loc2(-1,1);
        case 'A': return Loc2(-1,2);
        case '<': return Loc2(-2,0);
        case '>': return Loc2(-2,2);
        case '^': return Loc2(-1,1);
        case 'v': return Loc2(-2,1);
        default:
            int num = key - '0' - 1;
            return Loc2(num / 3, num % 3);
    }
}



std::vector<std::string> get_all_paths(char a, char b)
{
    Loc2 loc_a = get_loc(a);
    Loc2 loc_b = get_loc(b);
    Loc2 diff = loc_b - loc_a;

    std::string p1;
    for(int j = 0; j < diff.c; j++) p1.push_back('>');
    for(int j = 0; j > diff.c; j--) p1.push_back('<');
    for(int j = 0; j < diff.r; j++) p1.push_back('^');
    for(int j = 0; j > diff.r; j--) p1.push_back('v');
    p1.push_back('A');
    
    std::string p2;
    for(int j = 0; j < diff.r; j++) p2.push_back('^');
    for(int j = 0; j > diff.r; j--) p2.push_back('v');
    for(int j = 0; j < diff.c; j++) p2.push_back('>');
    for(int j = 0; j > diff.c; j--) p2.push_back('<');
    p2.push_back('A');

    if(loc_a.r == -1 && loc_b.c == 0) return std::vector<std::string>{p2};
    if(loc_a.c == 0 && loc_b.r == -1) return std::vector<std::string>{p1};
    if(loc_a.r == loc_b.r || loc_a.c == loc_b.c) return std::vector<std::string>{p1};
    return std::vector<std::string>{p1, p2};
}



struct press_seq
{
    std::string presses;
    std::vector<std::vector<press_seq>> inner_seqs;
};



void expand(press_seq & ps)
{
    char a = 'A';
    for(int i = 0; i < ps.presses.length(); i++)
    {
        char b = ps.presses[i];
        ps.inner_seqs.emplace_back();
        std::vector<std::string> allpaths = get_all_paths(a, b);
        std::vector<press_seq> & inners = ps.inner_seqs.back();
        inners.resize(allpaths.size());
        std::transform(allpaths.begin(), allpaths.end(), inners.begin(), [](std::string s){ press_seq ret; ret.presses = s; return ret; });
        a = b;
    }
}


void expand_nlevels(press_seq & ps, int nlevels)
{
    if(nlevels == 0) return;

    expand(ps);
    for(auto it1 = ps.inner_seqs.begin(); it1 != ps.inner_seqs.end(); it1++)
    {
        for(auto it2 = it1->begin(); it2 != it1->end(); it2++)
        {
            expand_nlevels(*it2, nlevels - 1);
        }
    }
}

int get_min_length_nlevels(press_seq & ps, int nlevels)
{
    if(nlevels == 0) return ps.presses.length();

    int ret = 0;
    for(auto it1 = ps.inner_seqs.begin(); it1 != ps.inner_seqs.end(); it1++)
    {
        int minlen = 1<<30;
        for(auto it2 = it1->begin(); it2 != it1->end(); it2++)
        {
            int len = get_min_length_nlevels(*it2, nlevels - 1);
            minlen = std::min(minlen, len);
        }
        ret += minlen;
    }
    return ret;
}

// void print(press_seq & ps, int level = 0)
// {
//     int minlen = get_min_length_nlevels(ps, 3-level);
//     for(int i = 0; i < level; i++) printf("    ");
//     printf("%s   %d\n", ps.presses.c_str(), minlen);
//     for(int i = 0; i < ps.inner_seqs.size(); i++)
//     {
//         for(int i = 0; i < level; i++) printf("    ");
//         char a = 'A';
//         if(i > 0) a = ps.presses[i-1];
//         char b = ps.presses[i];
//         printf("  %c -> %c:\n", a, b);
//         for(int j = 0; j < ps.inner_seqs[i].size(); j++)
//         {
//             print(ps.inner_seqs[i][j], level + 1);
//         }
//     }
// }



int main()
{
    timer tm;
    tm.start();

    std::vector<std::string> input = read_lines();

    int result = 0;
    for(std::string & code : input)
    {
        press_seq ps;
        ps.presses = code;

        expand_nlevels(ps, 3);

        int minlen = get_min_length_nlevels(ps, 3);

        int num;
        sscanf(code.c_str(), "%d", &num);
        result += num * minlen;
    }

    printf("%d\n", result);

    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
