#include "../helpers/helpers.hpp"



int main()
{
    timer tm;
    tm.start();

    std::vector<std::string> lines = read_lines();
    int ncases = (lines.size() - 1) / 4 + 1;

    int result = 0;
    for(int ci = 0; ci < ncases; ci++)
    {
        int bai = 4 * ci;
        int bbi = 4 * ci + 1;
        int pi = 4 * ci + 2;

        Point2<int> a, b, p;
        sscanf(lines[bai].c_str(), " Button A: X%d, Y%d", &a.x, &a.y);
        sscanf(lines[bbi].c_str(), " Button B: X%d, Y%d", &b.x, &b.y);
        sscanf(lines[pi].c_str(), " Prize: X=%d, Y=%d", &p.x, &p.y);

        int det = a.x * b.y - b.x * a.y;
        int detA = p.x * b.y - b.x * p.y;
        int detB = a.x * p.y - p.x * a.y;

        if(det == 0)
        {
            if(detA == 0 && detB == 0)
            {
                int aa = a.x;
                int bb = b.x;
                int pp = p.x;
                int nA = (1 << 30);
                int nB = (1 << 30);
                if(pp % aa == 0) nA = pp / aa;
                if(pp % bb == 0) nB = pp / bb;
                int tokens = std::min(3 * nA, 1 * nB);
                if(tokens < (1 << 30)) result += tokens;
            }
        }
        else
        {
            if(detA % det == 0 && detB % det == 0)
            {
                int nA = detA / det;
                int nB = detB / det;
                int tokens = 3 * nA + 1 * nB;
                result += tokens;
            }
        }
    }

    printf("%d\n", result);

    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
