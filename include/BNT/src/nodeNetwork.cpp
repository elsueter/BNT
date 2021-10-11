#include <BNT/booleanNetwork.h>

// Utils ------------------------------------------------------------------------------------------------------------

std::vector<bool> toBin(int n, int len)
{
    std::vector<bool> out(len, 0);

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
        it.getNext(in);
        it.update();
    }
}

void nodeNetwork::iterateNode(state in, int index){
    nodes[index].getNext(in);
    nodes[index].update();
}

void nodeNetwork::updateStructure(netStruc in){
    
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

void nodeNetwork::asynchIterate(){
    trace.clear();
    trace.push_back(getState());
    bool attractorHit = false;
    while(!attractorHit){
        //need to iterate over multiple values here
        iterateNode(getState(), 0);

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

void nodeNetwork::asynchIterate(state start){
    setState(start);
    asynchIterate();
}

void nodeNetwork::generateStateGraph(){
    for(int i = 0; i < 1 << nodes.size(); i++){
        synchronusIterate(toBin(i, nodes.size()));
    }
}

void nodeNetwork::generateAsynchStateGraph(){
    for(int i = 0; i < 1 << nodes.size(); i++){
        asynchIterate(toBin(i, nodes.size()));
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

std::string nodeNetwork::getTraceS(){
    std::string out = "dinetwork {node[shape=circle color=black style=filled fillcolor=white] \n  edge [length=100, color=black, fontcolor=black];";
    for(int i = 0; i < trace.size(); i++){
        out += '"';
        for(int j = 0; j < trace[i].size(); j++){
            out += std::to_string(trace[i][j]);
        }
        out += '"';
        if(i != trace.size()-1){
            out += "->";
        }
    }
    out += ';';
    out += '"';
    for(int i = 0; i < trace[0].size(); i++){
        out += std::to_string(trace[0][i]);
    }
    out += '"';
    out += "[\nfontcolor=white\ncolor=grey\nfillcolor=red,\n]";
    out += "}";
    return out;
}

std::string nodeNetwork::getAttractorsS(){
    std::string out = "dinetwork {node[shape=circle color=black style=filled fillcolor=white] \n  edge [length=100, color=black, fontcolor=black];";
    for(auto it: attractors){
        for(int i = 0; i < it.size(); i++){
            out += '"';
            for(int j = 0; j < it[i].size(); j++){
                out += std::to_string(it[i][j]);
            }
            out += '"';
            out += "->";
        }
        out += '"';
        for(int i = 0; i < it[0].size(); i++){
            out += std::to_string(it[0][i]);
        }
        out += '"';
        out += ';';
    }
    out += "}";
    return out;
}

std::string nodeNetwork::getUniqueTracesS(){
    sequence used;
    std::string out = "dinetwork {node[shape=circle color=black style=filled fillcolor=white] \n  edge [length=100, color=black, fontcolor=black];";
    for(auto it: uniqueTraces){
        for(int i = 0; i < it.size(); i++){
            if(vectorContains(used, it[i]) > -1){
                out += '"';
                for(int j = 0; j < it[i].size(); j++){
                    out += std::to_string(it[i][j]);
                }
                out += '"';
                break;
            }else{
                used.push_back(it[i]);
            }
            out += '"';
            for(int j = 0; j < it[i].size(); j++){
                out += std::to_string(it[i][j]);
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
    std::string out = "dinetwork {node[shape=circle color=black style=filled fillcolor=white] \n  edge [length=100, color=black, fontcolor=black];";
    for(auto &it: nodes){
        std::vector<std::string> parts = {""};
        int part = -1;
        for(int i = 0; i < it.exp.size(); i++){
            if(part > -1){
                if(it.exp[i] == '|' || it.exp[i] == '&'){
                    parts.push_back("");
                    part++;
                }else{
                    if(it.exp[i] != ' '){
                        parts[part] += it.exp[i];
                    }
                }
            }else{
                if(it.exp[i] == '='){
                    part++;
                }
            }
        }

        for(auto temp: parts){
            if(temp[0] == '!'){
                temp = temp.substr(1, temp.size());
                out += '"' + temp  + '"' + "->" + '"' + it.label + '"' + "[arrowhead=tee]" + ';';
            }else{
                out += '"' + temp  + '"' + "->" + '"' + it.label + '"' + ';';
            }
        }
    }
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