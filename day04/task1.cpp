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



int main()
{
    std::vector<std::string> lines = read_lines();

    int count = 0;

    char str[5];
    for(int dir = 0; dir < 8; dir++)
    {
        Point2<int> diff = dir8(dir).to_diff();

        for(int r = 0; r < lines.size(); r++)
        {
            for(int c = 0; c < lines[r].size(); c++)
            {
                memset(str, '\0', sizeof(str));
                Point2 curr(r,c);
                for(int i = 0; i < 4; i++)
                {
                    if(curr.y < 0 || curr.x < 0 || curr.y >= lines.size() || curr.x >= lines[curr.y].size()) break;
                    str[i] = lines[curr.y][curr.x];
                    curr = curr + diff;
                }
                if(strcmp(str, "XMAS") == 0) count++;
            }
        }
    }

    printf("%d\n", count);

    return 0;
}
