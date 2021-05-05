#include "classes/boolnet.hpp"
#include "classes/output.hpp"
#include "network.cpp"

int main(){

    basicNetwork netA(ATT);
    printVector(netA.getTT());
    printVector(netA.gettraces());
    printVector(netA.getattractors());

    return 0;
}