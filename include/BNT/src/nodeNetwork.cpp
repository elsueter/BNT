#include <BNT/booleanNetwork.h>

// Utils ------------------------------------------------------------------------------------------------------------

std::vector<int> toBin(int n, int len)
{
    std::vector<int> out(len, 0);

    while (n > 0) {
        out[len-1] = n % 2;
        n = n >> 1;
        len--;
    }

	return out;
}

// Boolnet ------------------------------------------------------------------------------------------------------------

using namespace BooleanNetwork;

nodeNetwork::nodeNetwork(netStruc in){
    nodes = in;
}

void nodeNetwork::iterateAll(state in){
    //Iterates over every node in the network, generated the future state and steps forwards
    for(auto& it: nodes){
        it.check(in);
        it.update();
    }
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

        int index = vectorContains(trace, getState());
        if(index > -1){
            attractorHit = true;
            sequence temp;
            temp.reserve(trace.size()-index);
            for(int i = index; i < trace.size(); i++){
                temp.push_back(trace[i]);
            }
            if(!vecArrContains(attractors, temp)){
                attractors.push_back(temp);
            }
        }
        trace.push_back(getState());
    }
    vectorUniqueAdd(uniqueTraces, trace);
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

void nodeNetwork::generateStateGraph(){
    for(int i = 0; i < 1 << nodes.size(); i++){
        synchronusIterate(toBin(i, nodes.size()));
    }
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

sequence nodeNetwork::getTrace(){
    return trace;
}

std::string nodeNetwork::getTraceS(){
    std::string out = "dinetwork {node[shape=circle] \n  edge [length=100, color=white, fontcolor=black];";
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
    out += '"';
    for(auto& num: trace[0]){
        out += std::to_string(num);
    }
    out += '"';
    out += "[\nfontcolor=white,\ncolor=red,\n]";
    out += "}";
    return out;
}

std::vector<sequence> nodeNetwork::getAttractors(){
    return attractors;
}

std::string nodeNetwork::getAttractorsS(){
    std::string out = "dinetwork {node[shape=circle] \n  edge [length=100, color=white, fontcolor=black];";
    for(auto it: attractors){
        for(int i = 0; i < it.size(); i++){
            out += '"';
            for(auto& num: it[i]){
                out += std::to_string(num);
            }
            out += '"';
            out += "->";
        }
        out += '"';
        for(auto& num: it[0]){
            out += std::to_string(num);
        }
        out += '"';
        out += ';';
    }
    out += "}";
    return out;
}

std::vector<sequence> nodeNetwork::getUniqueTraces(){
    return uniqueTraces;
}

std::string nodeNetwork::getUniqueTracesS(){
    sequence used;
    std::string out = "dinetwork {node[shape=circle] \n  edge [length=100, color=white, fontcolor=black];";
    for(auto it: uniqueTraces){
        for(int i = 0; i < it.size(); i++){
            if(vectorContains(used, it[i]) > -1){
                out += '"';
                for(auto& num: it[i]){
                    out += std::to_string(num);
                }
                out += '"';
                break;
            }else{
                used.push_back(it[i]);
            }
            out += '"';
            for(auto& num: it[i]){
                out += std::to_string(num);
            }
            out += '"';
            if(i != it.size()-1){
                out += "->";
            }
        }
        out += ';';
    }
    out += "}";
    return out;
}

std::string nodeNetwork::getNodesS(){
    std::string out = "dinetwork {node[shape=circle] \n  edge [length=100, color=white, fontcolor=black];";
    for(auto it: nodes){
        out += '"';
        out += it.label;
        out += '"';
    }
    out += ';';
    out += "}";
    return out;
}

std::string nodeNetwork::getNodesExpS(){
    std::string out = "";
    for(auto it: nodes){
        out += it.exp;
        out += "\n";
    }
    return out;
}