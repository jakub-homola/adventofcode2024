#include "../helpers/helpers.hpp"



struct node
{
    std::vector<int> neigh_ids;
    bool visited = false;
};

struct edge
{
    int ida;
    int idb;
};



int main()
{
    timer tm;
    tm.start();

    std::vector<std::string> input = read_lines();

    std::vector<node> nodes(26 * 26);
    std::vector<edge> edges;

    for(std::string & line : input)
    {
        int id1 = 26 * (line[0] - 'a') + (line[1] - 'a');
        int id2 = 26 * (line[3] - 'a') + (line[4] - 'a');
        nodes[id1].neigh_ids.push_back(id2);
        nodes[id2].neigh_ids.push_back(id1);
        edges.push_back(edge{id1,id2});
        edges.push_back(edge{id2,id1});
    }

    for(node & n : nodes)
    {
        if(n.neigh_ids.size() > 0) std::sort(n.neigh_ids.begin(), n.neigh_ids.end());
    }

    int result = 0;
    for(edge & e : edges)
    {
        std::vector<int> & na = nodes[e.ida].neigh_ids;
        std::vector<int> & nb = nodes[e.idb].neigh_ids;
        int ia = 0;
        int ib = 0;
        while(ia < na.size() && ib < nb.size())
        {
            if(na[ia] == nb[ib])
            {
                if(e.ida / 26 + 'a' == 't' || e.idb / 26 + 'a' == 't' || na[ia] / 26 + 'a' == 't')
                {
                    result++;
                }
                ia++;
                ib++;
            }
            else if(na[ia] < nb[ib]) ia++;
            else ib++;
        }
    }
    result /= 6;

    printf("%d\n", result);

    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
