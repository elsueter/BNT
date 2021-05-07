// Network Structures --------------------------------------------------------------

bool &state::operator[] (int index){
    return vals[index];
}

bool state::operator ==(state in){
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

statePair &stateTable::operator [](int index){
    return table[index];
}

sequence::~sequence(){
    for(int i = 0; i < len; i++){
        delete states[i].vals;
    }
    delete states;
}

bool sequence::contains(state in){
    for(int i = 0; i < len; i++){
        if(in == states[i]){
            return true;
        }
    }
    return false;
}

void sequence::push_back(state in){
    state temp[len+1];
    for(int i = 0; i < len; i++){
        temp[i] = states[i];
    }
    temp[len] = in;
    states = temp;
}

state &sequence::operator [](int index){
    return states[index];
}

sequence &sequenceArr::operator [](int index){
    return sequences[index];
}

// booleanNetwork ------------------------------------------------------------------

// Constructors / Deconstructor

booleanNetwork::booleanNetwork(std::vector<std::vector<int>> inTT){
    int len = inTT.size()/2;
    int len1 = inTT[0].size();
    TT.table = new statePair[len];
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

    attractors = {new sequence[0], 0};
    traces = {new sequence[0], 0};
    uniqueTraces = {new sequence[0], 0};
}

booleanNetwork::booleanNetwork(stateTable inTT){
    TT = inTT;
}

booleanNetwork::~booleanNetwork(){
    // TT
    for(int i = 0; i < TT.len; i++){
        delete TT[i].t0.vals;
        delete TT[i].t1.vals;
    }
    delete TT.table;
    
    // Attractors
    /*for(int i = 0; i < attractors.len; i++){
        delete attractors[i].vals;
    }*/
    //delete attractors.sequences;

    // Traces
    /*for(int i = 0; i < traces.len; i++){
        delete traces[i].vals;
    }*/
    //delete traces.sequences;
    
    // Unique Traces
    /*for(int i = 0; i < uniqueTraces.len; i++){
        delete uniqueTraces[i].vals;
    }*/
    //delete uniqueTraces.sequences;
}

// Network Functions

void booleanNetwork::genTraces(){
    //std::thread threads[TT.len];
    for(int i = 0; i < TT.len; i++){
        traces.len++;
        traces.sequences = new sequence[traces.len];
        traces[i].states = new state[0];
        traces[i].states[0] = TT[i].t0;
        genTrace(traces[i]);
        //threads[i] = std::thread(&booleanNetwork::genTrace, this, std::ref(traces[i]));
    }
    
    //for(int i = 0; i < TT.len; i++){
        //threads[i].join();
        //threads[i].~thread();
    //}
}

void booleanNetwork::genTrace(sequence &trace){
    bool attractorHit = false;
    //while(!attractorHit){
        for(int i = 0; i < TT.len; i++){
            if(TT[i].t0 == trace[trace.len-1]){
                if(trace.contains(TT[i].t1)){
                    attractorHit = true;
                    break;
                }else{
                    trace.push_back(TT[i].t1);
                }
            }
        }
    //}
}

// variable exposure functions

stateTable booleanNetwork::getTT(){
    return TT;
}

sequenceArr booleanNetwork::getTraces(){
    return traces;
}