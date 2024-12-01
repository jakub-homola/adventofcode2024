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

    int res = 0;
    size_t i = 0;
    size_t j = 0;
    while(i < listL.size())
    {
        int l = listL[i];
        int cntL = 1;
        i++;
        while(i < listL.size() && listL[i] == l) {i++; cntL++;}
        int cntR = 0;
        while(j < listR.size() && listR[j] < l) j++;
        while(j < listR.size() && listR[j] == l) {j++; cntR++;}
        res += l * cntL * cntR;
    }

    printf("%d\n", res);

    return 0;
}
