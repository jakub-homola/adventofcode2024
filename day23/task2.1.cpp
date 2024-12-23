#include "../helpers/helpers.hpp"



struct node
{
    std::vector<int> neigh_ids;
    bool visited = false;
};

struct clique
{
    std::vector<int> nodeidxs;
    clique() {}
    clique(int n1, int n2)
    {
        if(n1 > n2)
        {
            nodeidxs.push_back(n2);
            nodeidxs.push_back(n1);
        }
        else
        {
            nodeidxs.push_back(n1);
            nodeidxs.push_back(n2);
        }
    }
    bool operator==(const clique & o) const = default;
    struct hasher
    {
        size_t operator()(const clique & c) const
        {
            size_t ret = 0;
            for(int i : c.nodeidxs)
            {
                ret *= 26 * 26;
                ret += i;
            }
            return ret;
        }
    };
};



bool is_subset(const std::vector<int> & big, const std::vector<int> & small)
{
    int ib = 0;
    int is = 0;
    while(true)
    {
        if(is == small.size())
        {
            return true;
        }
        else if(ib == big.size())
        {
            return false;
        }
        else if(big[ib] == small[is])
        {
            ib++;
            is++;
        }
        else if(big[ib] < small[is])
        {
            ib++;
        }
        else if(big[ib] > small[is])
        {
            return false;
        }
    }
}


int main()
{
    timer tm;
    tm.start();

    std::vector<std::string> input = read_lines();

    std::vector<node> nodes(26 * 26);
    std::unordered_set<clique,clique::hasher> cliques_curr;

    for(std::string & line : input)
    {
        int id1 = 26 * (line[0] - 'a') + (line[1] - 'a');
        int id2 = 26 * (line[3] - 'a') + (line[4] - 'a');
        nodes[id1].neigh_ids.push_back(id2);
        nodes[id2].neigh_ids.push_back(id1);
        cliques_curr.insert(clique(id1,id2));
    }

    for(node & n : nodes)
    {
        if(n.neigh_ids.size() > 0) std::sort(n.neigh_ids.begin(), n.neigh_ids.end());
    }

    while(true)
    {
        std::unordered_set<clique,clique::hasher> cliques_next;

        for(const clique & c : cliques_curr)
        {
            const std::vector<int> & potentials = nodes[c.nodeidxs[0]].neigh_ids;
            for(int pot : potentials)
            {
                bool issubset = is_subset(nodes[pot].neigh_ids, c.nodeidxs);
                if(issubset)
                {
                    clique cn = c;
                    cn.nodeidxs.push_back(pot);
                    std::sort(cn.nodeidxs.begin(), cn.nodeidxs.end());
                    cliques_next.emplace(std::move(cn));
                }
            }
        }

        if(cliques_next.size() == 0)
        {
            for(const clique & c : cliques_curr)
            {
                printf("maximal clique: ");
                for(int i = 0; i < c.nodeidxs.size(); i++)
                {
                    if(i > 0) printf(",");
                    printf("%c%c", c.nodeidxs[i] / 26 + 'a', c.nodeidxs[i] % 26 + 'a');
                }
                printf("\n");
            }
            break;
        }

        cliques_curr = std::move(cliques_next);
    }

    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
