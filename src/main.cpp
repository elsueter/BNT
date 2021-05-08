#include "../include/boolnet.hpp"

//Temperary includes
#include "terminal/utils.hpp"
#include "network.cpp"

int main(){
    timer clock;

    basicNetwork net(BTT);
    net.iterate();
    printVector(net.getTT());

    booleanNetwork net1(BTT);
    net1.genTraces();
    printStateTable(net1.getTT());

    return 0;
}