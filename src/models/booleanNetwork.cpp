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

void state::operator =(state in){
    len = in.len;
    delete [] vals;
    vals = new bool[len];
    for(int i = 0; i < len; i++){
        vals[i] = in[i];
    }
}

stateTable::statePair &stateTable::operator [](int index){
    return table[index];
}


bool sequence::contains(state in){
    for(int i = 0; i < len; i++){
        if(states[i] == in){
            return true;
        }
    }
    return false;
}

state &sequence::operator [](int index){
    return states[index];
}

sequence &sequenceTable::operator [](int index){
    return table[index];
}

// booleanNetwork ------------------------------------------------------------------

// Constructors / Deconstructor

booleanNetwork::booleanNetwork(std::vector<std::vector<int> > inTT){

    int len = inTT.size()/2;
    int len1 = inTT[0].size();

    TT = {new stateTable::statePair[len], len};

    traces = {new sequence[len], len};

    for(int i = 0; i < len; i++){

        TT[i].t0 = {new bool[len1], len1};
        TT[i].t1 = {new bool[len1], len1};
        for(int j = 0; j < len1; j++){
            TT[i].t0[j] = inTT[i*2][j];
            TT[i].t1[j] = inTT[(i*2)+1][j];
        }

        traces[i] = {new state[1], 1};
        traces[i][0] = TT[i].t0;
    }
}

booleanNetwork::~booleanNetwork(){
    for(int i = 0; i < TT.len; i++){
        delete [] TT[i].t0.vals;
        delete [] TT[i].t1.vals;
    }
    delete [] TT.table;

    for(int i = 0; i < traces.len; i++){
        for(int j = 0; j < traces[i].len; j++){
            delete [] traces[i][j].vals;
        }
        delete [] traces[i].states;
    }
    delete [] traces.table;
}

// Network Functions

#include <iostream>

void booleanNetwork::genTraces(){
    for(int i = 0; i < traces.len; i++){
        genTrace(traces[i]);
    }
}

void booleanNetwork::genTrace(sequence &trace){
    int counter = 0;
    bool attractorHit = false;
    while(!attractorHit){
        for(int i = 0; i < TT.len; i++){
            if(TT[i].t0 == trace[trace.len-1]){
                if(trace.contains(TT[i].t1)){
                    attractorHit = true;
                }else{
                    sequence temp = {new state[trace.len], trace.len};
                    for(int j = 0; j < temp.len; j++){
                        temp[j] = {new bool[0], 0};
                        temp[j] = trace[j];
                        delete [] trace[j].vals;
                    }

                    delete [] trace.states;
                    trace.len ++;
                    trace.states = new state[trace.len];

                    for(int j = 0; j < temp.len; j++){
                        trace[j] = {new bool[0], 0};
                        trace[j] = temp[j];
                        delete [] temp[j].vals;
                    }
                    delete [] temp.states;

                    trace[trace.len-1] = {new bool[0], 0};
                    trace[trace.len-1] = TT[i].t1;
                }                
                break;
            }
        }
    }
}

// variable exposure functions

stateTable booleanNetwork::getTT(){
    return TT;
}

sequenceTable booleanNetwork::getTraces(){
    return traces;
}