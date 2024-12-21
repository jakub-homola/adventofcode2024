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



std::vector<std::vector<std::string>> expand(std::string & presses)
{
    std::vector<std::vector<std::string>> inner;
    char a = 'A';
    for(int i = 0; i < presses.length(); i++)
    {
        char b = presses[i];
        inner.emplace_back(get_all_paths(a, b));
        a = b;
    }
    return inner;
}

struct mykey
{
    std::string str;
    int nlvl;
    mykey(std::string & s, int n) : str(s), nlvl(n) {}
    struct hasher
    {
        size_t operator()(const mykey & k) const
        {
            size_t ret = k.nlvl;
            for(int i = 0; i < k.str.length(); i++)
            {
                ret *= 31;
                ret += k.str[i];
            }
            return ret;
        }
    };
    struct comparator
    {
        bool operator()(const mykey & l, const mykey & r) const
        {
            return l.nlvl == r.nlvl && l.str == r.str;
        }
    };
};
using mymap = std::unordered_map<mykey, long long, mykey::hasher, mykey::comparator>;

long long get_min_length_nlevels(std::string & presses, int nlevels, mymap & mem)
{
    if(nlevels == 0) return presses.length();
    mykey key(presses, nlevels);
    auto it = mem.find(key);
    if(it != mem.end()) return it->second;

    long long ret = 0;
    std::vector<std::vector<std::string>> inner = expand(presses);
    for(int i = 0; i < inner.size(); i++)
    {
        long long minlen = (long long)1 << 60;
        for(auto it2 = inner[i].begin(); it2 != inner[i].end(); it2++)
        {
            long long len = get_min_length_nlevels(*it2, nlevels - 1, mem);
            minlen = std::min(minlen, len);
        }
        ret += minlen;
    }
    mem.emplace(key, ret);
    return ret;
}



int main()
{
    timer tm;
    tm.start();

    std::vector<std::string> input = read_lines();

    long long result = 0;
    for(std::string & code : input)
    {
        mymap mem;
        long long minlen = get_min_length_nlevels(code, 26, mem);

        int num;
        sscanf(code.c_str(), "%d", &num);
        result += num * minlen;
    }

    printf("%lld\n", result);

    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
