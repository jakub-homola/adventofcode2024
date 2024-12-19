#include "../helpers/helpers.hpp"



void set_leads(std::vector<std::vector<Loc2<int>>> & leads, Loc2<int> a)
{
    std::vector<Loc2<int>> path;
    while(leads[a.r][a.c] != a)
    {
        path.push_back(a);
        a = leads[a.r][a.c];
    }
    for(Loc2<int> x : path)
    {
        leads[x.r][x.c] = a;
    }
}

bool are_in_same_component(std::vector<std::vector<Loc2<int>>> & leads, Loc2<int> a, Loc2<int> b)
{
    set_leads(leads, a);
    set_leads(leads, b);
    return leads[a.r][a.c] == leads[b.r][b.c];
}

void join_components(std::vector<std::vector<Loc2<int>>> & leads, Loc2<int> a, Loc2<int> b)
{
    set_leads(leads, a);
    set_leads(leads, b);
    a = leads[a.r][a.c];
    b = leads[b.r][b.c];
    leads[a.r][a.c] = b;
}



int main(int argc, char ** argv)
{
    timer tm;
    tm.start();

    int size = 71;
    if(argc > 1) size = atoi(argv[1]);
    int count = 1024;

    std::vector<std::string> lines = read_lines();
    std::vector<Loc2<int>> obstacles(lines.size());
    std::transform(lines.begin(), lines.end(), obstacles.begin(), [](const std::string & s){ Loc2<int> l; sscanf(s.c_str(), "%d,%d", &l.c, &l.r); l.r++; l.c++; return l;});

    std::vector<std::string> space = grid_pad(std::vector(size, std::string(size, '.')), '#', 1);
    Loc2 start(1,1);
    Loc2 target(size, size);
    for(Loc2<int> lol : obstacles) space[lol.r][lol.c] = '#';

    std::vector<std::vector<Loc2<int>>> leads(size+2, std::vector<Loc2<int>>(size+2));
    for(int r = 1; r <= size; r++)
    {
        for(int c = 1; c <= size; c++)
        {
            if(space[r][c] != '.') continue;
            Loc2 lead(r,c);
            std::deque<Loc2<int>> locs;
            locs.push_back(lead);
            while(!locs.empty())
            {
                Loc2 curr = locs.front();
                locs.pop_front();
                if(space[curr.r][curr.c] != '.') continue;
                leads[curr.r][curr.c] = lead;
                space[curr.r][curr.c] = 'O';
                locs.push_back(curr + Loc2( 1, 0));
                locs.push_back(curr + Loc2(-1, 0));
                locs.push_back(curr + Loc2( 0, 1));
                locs.push_back(curr + Loc2( 0,-1));
            }
        }
    }

    Loc2 result;
    for(int i = obstacles.size() - 1; i >= 0; i--)
    {
        Loc2 obst = obstacles[i];
        std::vector<Loc2<int>> neighs;
        for(int d = 0; d < 4; d++)
        {
            Loc2 diff = dir_to_loc_int(direction(d));
            Loc2 neigh = obst + diff;
            if(space[neigh.r][neigh.c] != '#') neighs.push_back(neigh);
        }
        if(neighs.size() > 0) leads[obst.r][obst.c] = neighs.front();
        else leads[obst.r][obst.c] = obst;
        space[obst.r][obst.c] = 'O';
        for(int j = 1; j < neighs.size(); j++)
        {
            join_components(leads, neighs[j-1], neighs[j]);
        }
        if(are_in_same_component(leads, start, target))
        {
            result = obstacles[i];
            break;
        }
    }

    printf("%d,%d\n", result.c-1, result.r-1);

    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
