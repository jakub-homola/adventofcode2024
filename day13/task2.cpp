#include "../helpers/helpers.hpp"



int main()
{
    timer tm;
    tm.start();

    std::vector<std::string> lines = read_lines();
    int ncases = (lines.size() - 1) / 4 + 1;

    long long toadd = 10000000000000;

    long long result = 0;
    for(int ci = 0; ci < ncases; ci++)
    {
        long long bai = 4 * ci;
        long long bbi = 4 * ci + 1;
        long long pi = 4 * ci + 2;

        Point2<long long> a, b, p;
        sscanf(lines[bai].c_str(), " Button A: X%lld, Y%lld", &a.x, &a.y);
        sscanf(lines[bbi].c_str(), " Button B: X%lld, Y%lld", &b.x, &b.y);
        sscanf(lines[pi].c_str(), " Prize: X=%lld, Y=%lld", &p.x, &p.y);

        p.x += toadd;
        p.y += toadd;

        long long det = a.x * b.y - b.x * a.y;
        long long detA = p.x * b.y - b.x * p.y;
        long long detB = a.x * p.y - p.x * a.y;

        if(det == 0)
        {
            if(detA == 0 && detB == 0)
            {
                long long aa = a.x;
                long long bb = b.x;
                long long pp = p.x;
                long long nA = (1ll << 60);
                long long nB = (1ll << 60);
                if(pp % aa == 0) nA = pp / aa;
                if(pp % bb == 0) nB = pp / bb;
                long long tokens = std::min(3 * nA, 1 * nB);
                if(tokens < (1ll << 60)) result += tokens;
            }
        }
        else
        {
            if(detA % det == 0 && detB % det == 0)
            {
                long long nA = detA / det;
                long long nB = detB / det;
                long long tokens = 3 * nA + 1 * nB;
                result += tokens;
            }
        }
    }

    printf("%lld\n", result);

    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
