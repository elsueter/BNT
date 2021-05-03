#include "boolnet.hpp"

node::node(arr<int> inTT){
    TT = inTT;
    state = false;
}

void node::updateNeigh(arr<node> inN){
    neigh = inN;
}