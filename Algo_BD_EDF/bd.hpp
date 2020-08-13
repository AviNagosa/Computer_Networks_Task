#include <iostream>
#include "fstream"
#include "string"
#include <cmath>
#include <queue> 
using namespace std;

namespace bd
{
    struct Packet
    {
        int packet_slack;
        int packet_value;

        Packet(){}
        Packet(int s, int v) : packet_slack(s), packet_value(v) {};
    };

    int convertToInt(string);
    int decreas(queue<Packet>&);
    int arrival_phase(string&,queue<Packet>&,int,int&); 
    int processing_phase(queue <Packet>&);
    void BOUNDED_DELAY(int,string);
};
