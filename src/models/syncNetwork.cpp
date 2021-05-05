// netTable ------------------------------------------------------------------------------
/*
netState& netTable::operator[](int index){
    return table[index];
}

netTable& netTable::operator=(const std::vector<std::vector<int>> in){
    for(int i = 0; i < in.size()/2; i++){
        table[i].push_back(in[i*2]);
        table[i].push_back(in[(i*2)+1]);
    }
    return *this;
}

// syncNetwork ------------------------------------------------------------------------------

syncNetwork::syncNetwork(std::vector<std::vector<int>> inTT){
    for(int i = 0; i < TT.size()/2; i++){
        nodes.push_back(TT[i*2]);        
    }
}*/