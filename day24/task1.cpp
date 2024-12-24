#include "../helpers/helpers.hpp"



struct wire
{
    std::vector<int> connected_gateidxs;
    bool state = false;
    wire() {}
    wire(bool s) : state(s) {}
};

struct gate
{
    char type;
    int ina;
    int inb;
    int out;
};

int str_to_id(char * str)
{
    int id = 0;
    for(int i = 0; i < 3; i++)
    {
        id *= 36;
        char c = str[i];
        if(c >= 'a' && c <= 'z') id += c - 'a';
        else if(c >= '0' && c <= '9') id += c - '0' + 26;
    }
    return id;
}



int main()
{
    timer tm;
    tm.start();

    std::vector<std::string> input = read_lines();
    auto it_middle = std::find(input.begin(), input.end(), "");

    std::unordered_map<int,wire> wires;
    std::vector<int> zwires;
    std::vector<gate> gates;

    std::unordered_set<int> wires_updated_set;
    std::deque<int> wires_updated_queue;

    for(auto it = input.begin(); it != it_middle; it++)
    {
        char s[3];
        int v;
        sscanf(it->c_str(), "%c%c%c: %d", s+0, s+1, s+2, &v);
        int id = str_to_id(s);
        wires.emplace(id, wire((bool)v));
        wires_updated_set.insert(id);
        wires_updated_queue.push_back(id);
        if(s[0] == 'z') zwires.push_back(id);
    }

    for(auto it = it_middle + 1; it != input.end(); it++)
    {
        std::vector<char*> tokens = split_string(it->data(), ' ');
        int ida = str_to_id(tokens[0]);
        int idb = str_to_id(tokens[2]);
        int ido = str_to_id(tokens[4]);
        if(tokens[4][0] == 'z') zwires.push_back(ido);
        char type = tokens[1][0];
        gates.push_back(gate{type, ida, idb, ido});
        auto ito = wires.find(ido);
        if(ito == wires.end()) ito = wires.emplace(ido, wire()).first;
        auto ita = wires.find(ida);
        if(ita == wires.end()) ita = wires.emplace(ida, wire()).first;
        auto itb = wires.find(idb);
        if(itb == wires.end()) itb = wires.emplace(idb, wire()).first;
        ita->second.connected_gateidxs.push_back(gates.size() - 1);
        itb->second.connected_gateidxs.push_back(gates.size() - 1);
    }

    while(!wires_updated_queue.empty())
    {
        int widx = wires_updated_queue.front();
        wires_updated_queue.pop_front();
        wires_updated_set.erase(widx);
        for(int gidx : wires[widx].connected_gateidxs)
        {
            gate & g = gates[gidx];
            bool wa = wires[g.ina].state;
            bool wb = wires[g.inb].state;
            bool wo;
            if(g.type == 'A') wo = (wa && wb);
            if(g.type == 'O') wo = (wa || wb);
            if(g.type == 'X') wo = (wa != wb);
            wires[g.out].state = wo;
            if(wires_updated_set.find(g.out) == wires_updated_set.end())
            {
                wires_updated_set.insert(g.out);
                wires_updated_queue.push_back(g.out);
            }
        }
    }

    std::sort(zwires.begin(), zwires.end());

    long long unsigned result = 0;
    for(int i = zwires.size() - 1; i >= 0; i--)
    {
        int zw = zwires[i];
        result <<= 1;
        if(wires[zw].state) result ^= 1;
        // printf("%d", wires[zw].state);
    }
    // printf("\n");

    printf("%llu\n", result);

    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
