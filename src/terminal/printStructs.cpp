void printState(state in){
    std::cout<<"{";
    for(int i = 0; i < in.size(); i++){
        std::cout<<in[i];
        if(i < in.size()-1){
            std::cout<<", ";
        }
    }
    std::cout<<"} ";
}

/*void printStatePair(stateTable::statePair in){
    printState(in.t0);
    printState(in.t1);
    std::cout<<std::endl;
}

void printStateTable(stateTable in){
    std::cout<<"Table:"<<std::endl;
    for(int i = 0; i < in.len; i++){
        printStatePair(in[i]);
    }
    std::cout<<std::endl;
}

void printSequence(sequence in){
    for(int i = 0; i < in.len; i++){
        printState(in[i]);
    }
}

void printSequenceTable(sequenceTable in){
    std::cout<<"Sequence Table: "<<std::endl;
    for(int i = 0; i < in.len; i++){
        printSequence(in[i]);
        std::cout<<std::endl;
    }
}*/

template<typename T>
void printVector(std::vector<std::vector<std::vector<T>>> in){
    for(int i = 0; i < in.size(); i++){
        for(int j = 0; j < in[i].size(); j++){
            printVector(in[i][j]);
        }
        std::cout<<std::endl;
    }
}

template<typename T>
void printVector(std::vector<std::vector<T>> in){
    for(int i = 0; i < in.size(); i++){
        printVector(in[i]);
        if(i%2 == 1){
            std::cout<<std::endl;
        }
    }
}

template<typename T>
void printVector(std::vector<T> in){
    std::cout<<"{";
    for(int i = 0; i < in.size(); i++){
        std::cout<<in[i];
        if(i < in.size()-1){
            std::cout<<", ";
        }
    }
    std::cout<<"} ";
}