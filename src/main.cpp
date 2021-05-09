#include "../include/boolnet.hpp"

//Temperary includes
#include "terminal/utils.hpp"
#include "network.cpp"

int main(){
    timer clock;

    basicNetwork net(BTT);
    printVector(net.getTT());

    booleanNetwork net1(BTT);
    printStateTable(net1.getTT());
    printSequenceTable(net1.getTraces());

    return 0;
}