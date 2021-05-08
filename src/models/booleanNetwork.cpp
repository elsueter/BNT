// Network Structures --------------------------------------------------------------

bool &state::operator [] (int index){
    return vals[index];
}

bool state::operator == (state in){
    if(in.len != len){
        return false;
    }
    for(int i = 0; i < len; i++){
        if(in[i] != vals[i]){
            return false;
        }
    }
    return true;
}

stateTable::statePair &stateTable::operator [](int index){
    return table[index];
}

state &sequence::operator [](int index){
    return states[index];
}

// booleanNetwork ------------------------------------------------------------------

// Constructors / Deconstructor

booleanNetwork::booleanNetwork(std::vector<std::vector<int> > inTT){
    int len = inTT.size()/2;
    int len1 = inTT[0].size();
    TT.table = new stateTable::statePair[len];
    TT.len = len;
    for(int i = 0; i < len; i++){
        TT[i].t0.vals = new bool[len1];
        TT[i].t0.len = len1;
        TT[i].t1.vals = new bool[len1];
        TT[i].t1.len = len1;
        for(int j = 0; j < len; j++){
            TT[i].t0[j] = inTT[i*2][j];
            TT[i].t1[j] = inTT[(i*2)+1][j];
        }
    }
}

booleanNetwork::booleanNetwork(stateTable inTT){
    TT = inTT;
}

booleanNetwork::~booleanNetwork(){
    for(int i = 0; i < TT.len; i++){
        delete TT[i].t0.vals;
        delete TT[i].t1.vals;
    }
    delete TT.table;
}

// Network Functions

#include "../terminal/utils.hpp"

void booleanNetwork::genTraces(){
}

void booleanNetwork::genTrace(sequence &trace){
    
}

// variable exposure functions

stateTable booleanNetwork::getTT(){
    return TT;
}