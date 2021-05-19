#include "../include/booleanNetwork.h"

//Temperary includes
#include "terminal/utils.hpp"
#include "network.cpp"

int main(){
    timer clock;

    clock.start();
    booleanNetwork net1(BTT);
    clock.restart();
    net1.genTraces();
    clock.stop();

    printVector(net1.getTraces());
    std::cout<<std::endl;
    printVector(net1.getAttractors());
    std::cout<<std::endl;
    printVector(net1.getUniqueTraces());

    return 0;
}