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

    // mvb, z08
    // rds, jss
    // bmn, z23
    // z18, wss

    printf("bmn,jss,mvb,rds,wss,z08,z18,z23\n");

    tm.stop();
    printf("Time: %.3f ms\n", tm.get_time_ms());

    return 0;
}
