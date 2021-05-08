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
    vals = new bool[len];
    for(int i = 0; i < len; i++){
        vals[i] = in[i];
    }
}

stateTable::statePair &stateTable::operator [](int index){
    return table[index];
}

state &sequence::operator [](int index){
    return states[index];
}

sequence &sequenceTable::operator [](int index){
    return table[index];
}

void sequence::operator =(sequence in){
    len = in.len;
    states = new state[len];
    for(int i = 0; i < len; i++){
        states[i] = in[i];
    }
}

// booleanNetwork ------------------------------------------------------------------

// Constructors / Deconstructor

booleanNetwork::booleanNetwork(std::vector<std::vector<int> > inTT){

    int len = inTT.size()/2;
    int len1 = inTT[0].size();

    TT = {new stateTable::statePair[len], len};

    traces = {new sequence[TT.len], TT.len};

    for(int i = 0; i < TT.len; i++){

        TT[i].t0 = {new bool[len1], len1};
        TT[i].t1 = {new bool[len1], len1};
        for(int j = 0; j < TT.len; j++){
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
    delete TT.table;

    for(int i = 0; i < traces.len; i++){
        for(int j = 0; j < traces[i].len; j++){
            delete [] traces[i][j].vals;
        }
        delete [] traces[i].states;
    }
    delete [] traces.table;
}

// Network Functions

void booleanNetwork::genTraces(){
    for(int i = 0; i < traces.len; i++){
        genTrace(&traces[i]);
    }
}

void booleanNetwork::genTrace(sequence *trace){
    for(int i = 0; i < TT.len; i++){
        if(TT[i].t0 == trace->states[trace->len-1]){
            trace->states[0] = TT[i].t1;
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