#include "../include/boolnet.hpp"

//Temperary includes
#include "../terminal/output.hpp"
#include "network.cpp"

int main(){

    basicNetwork netA(BTT);
    printVector(netA.getTT());
    printVector(netA.gettraces());
    printVector(netA.getattractors());

    return 0;
}