#include <BNT/booleanNetwork.h>

using namespace BooleanNetwork;

void nodeNetwork::iterateAll(state in){
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
    sequence temp;
    temp.push_back(getState());
    bool attractorHit = false;
    while(!attractorHit){
        iterateAll(getState());
        if(vectorContains(temp, getState())){
            attractorHit = true;
        }
        temp.push_back(getState());
    }
    traces.push_back(temp);
}

void nodeNetwork::synchronusIterate(state start){
    setState(start);
    synchronusIterate();
}

void nodeNetwork::synchronusIterate(crow::json::rvalue start){
    state temp;
    temp.reserve(start.size());
    for(auto& it: start){
        temp.push_back(it.i());
    }
    setState(temp);
    synchronusIterate();
}

state nodeNetwork::getState(){
    state out;
    for(auto& it: nodes){
        out.push_back(it.curr);
    }
    return out;
}

std::string nodeNetwork::getTraces(){
    std::string out = "dinetwork {node[shape=circle];";
    for(auto& trace: traces){
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
    }
    out += "}";
    return out;
}

std::vector<sequence> nodeNetwork::getAttractors(){
    return attractors;
}

std::vector<sequence> nodeNetwork::getUniqueTraces(){
    return uniqueTraces;
}