#include "../helpers/helpers.hpp"



struct dir8
{
    int id;
    // 0 = N
    // 1 = NE
    // 2 = E
    // 3 = SE
    // 4 = S
    // 5 = SW
    // 6 = W
    // 7 = NW
    dir8(int num)
    {
        id = num;
    }
    Point2<int> to_diff()
    {
        switch(id)
        {
            case 0: return Point2<int>( 0, 1);
            case 1: return Point2<int>( 1, 1);
            case 2: return Point2<int>( 1, 0);
            case 3: return Point2<int>( 1,-1);
            case 4: return Point2<int>( 0,-1);
            case 5: return Point2<int>(-1,-1);
            case 6: return Point2<int>(-1, 0);
            case 7: return Point2<int>(-1, 1);
            default: return Point2<int>(0,0);
        }
    }
};

void get_str(std::vector<std::string> & lines, Point2<int> p, Point2<int> diff, int length, char * out)
{
    memset(out, '\0', length+1);

    for(int i = 0; i < length; i++)
    {
        if(p.y < 0 || p.x < 0 || p.y >= lines.size() || p.x >= lines[p.y].size()) break;
        out[i] = lines[p.y][p.x];
        p = p + diff;
    }
}



int main()
{
    std::vector<std::string> lines = read_lines();

    int count = 0;

    char str[4];
    for(int dir = 0; dir < 8; dir++)
    {
        if(dir % 2 == 0) continue; // only X, not +

        Point2<int> diff = dir8(dir).to_diff();
        std::vector<Point2<int>> other_diff = diff.get_orthogonal();

        for(int r = 0; r < lines.size(); r++)
        {
            for(int c = 0; c < lines[r].size(); c++)
            {
                Point2<int> start1 = Point2<int>(c,r) - diff;
                get_str(lines, start1, diff, 3, str);
                if(strcmp(str, "MAS") != 0) continue;
                for(int i = 0; i < other_diff.size(); i++)
                {
                    Point2<int> start2 = Point2<int>(c,r) - other_diff[i];
                    get_str(lines, start2, other_diff[i], 3, str);
                    if(strcmp(str, "MAS") != 0) continue;
                    count++;
                    // printf("%d   %3d %3d   %3d %3d\n", dir, start1.y, start1.x, start2.y, start2.x);
                }
            }
        }
    }

    count /= 2;
    printf("%d\n", count);

    return 0;
}
