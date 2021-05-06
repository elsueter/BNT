#include "../include/boolnet.hpp"

//Temperary includes
#include "terminal/output.hpp"
#include "network.cpp"

int main(){

    basicNetwork net(CTT);
    printVector(net.getTT());
    printVector(net.gettraces());
    printVector(net.getUniqueTraces());
    printVector(net.getattractors());

    return 0;
}