#include "../include/boolnet.hpp"

//Temperary includes
#include "terminal/utils.hpp"
#include "network.cpp"

int main(){
    timer clock;

    clock.start();
    basicNetwork net(BTT);
    clock.stop();
    //printVector(net.getTT());

    clock.start();
    booleanNetwork net1(BTT);
    clock.stop();
    net1.genTraces();
    //printStateTable(net1.getTT());
    //printSequenceTable(net1.getTraces());

    return 0;
}