#include "../helpers/helpers.hpp"



int main()
{
    std::vector<int> listL;
    std::vector<int> listR;

    while(true)
    {
        int l, r;
        int cnt = scanf("%d%d", &l, &r);
        if(cnt < 2) break;
        listL.push_back(l);
        listR.push_back(r);
    }

    std::sort(listL.begin(), listL.end());
    std::sort(listR.begin(), listR.end());

    int dist = 0;
    for(size_t i = 0; i < listL.size(); i++)
    {
        int d = std::abs(listL[i] - listR[i]);
        dist += d;
    }

    printf("%d\n", dist);

    return 0;
}
