#include <BNT/booleanNetwork.h>

using namespace BooleanNetwork;

void nodeNetwork::iterateAll(state in){
    //Iterates over every node in the network, generated the future state and steps forwards
    for(auto& it: nodes){
        it.check(in);
        it.update();
    }
}

nodeNetwork::nodeNetwork(netStruc in){
    nodes = in;
}

void nodeNetwork::setState(state start){
    for(int i = 0; i < start.size(); i++){
        nodes[i].curr = start[i];
    }
}

void nodeNetwork::synchronusIterate(){
    trace.clear();
    trace.push_back(getState());
    bool attractorHit = false;
    while(!attractorHit){
        iterateAll(getState());
        if(vectorContains(trace, getState())){
            attractorHit = true;
        }
        trace.push_back(getState());
    }
}

void nodeNetwork::synchronusIterate(state start){
    setState(start);
    synchronusIterate();
}

void nodeNetwork::synchronusIterate(crow::json::rvalue startJSON){
    state start;
    start.reserve(startJSON.size());
    for(auto& it: startJSON){
        start.push_back(it.i());
    }
    synchronusIterate(start);
}

void nodeNetwork::clear(){
    trace.clear();
    attractors.clear();
    uniqueTraces.clear();
}

state nodeNetwork::getState(){
    state out;
    for(auto& it: nodes){
        out.push_back(it.curr);
    }
    return out;
}

std::string nodeNetwork::getTrace(){
    std::string out = "dinetwork {node[shape=circle];";
    for(int i = 0; i < trace.size(); i++){
        out += '"';
        for(auto& num: trace[i]){
            out += std::to_string(num);
        }
        out += '"';
        if(i != trace.size()-1){
            out += "->";
        }
    }
    out += ';';
    out += "}";
    return out;
}

std::vector<sequence> nodeNetwork::getAttractors(){
    return attractors;
}

std::vector<sequence> nodeNetwork::getUniqueTraces(){
    return uniqueTraces;
}