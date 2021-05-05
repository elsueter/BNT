#include "boolnet.hpp"

// Utils ------------------------------------------------------------------------------------

template<typename T>
int vecContains(std::vector<T> vec, T check){
    for(int i = 0; i < vec.size(); i++){
        if(vec[i] == check){
            return i;
        }
    }
    return -1;
}

template<typename T>
bool vecPermContains(std::vector<std::vector<T>> vec, std::vector<T> check){
    for(int i = 0; i < check.size(); i++){
        if(vecContains(vec, check)>-1){
            return true;
        }
        if(check.size()>1){
            T temp = check[0];
            for(int j = 1; j < check.size(); j++){
                check[j-1] = check[j];
            }
            check[check.size()-1] = temp;
        }
    }
    return false;
}

// basicNetwork ------------------------------------------------------------------------------

basicNetwork::basicNetwork(std::vector<std::vector<int>> inTT){
    TT = inTT;
    for(int i = 0; i < TT.size()/2; i++){
        nodes.push_back(TT[i*2]);        
    }
    iterate();
}

void basicNetwork::iterate(){
    std::vector<std::vector<std::vector<int>>> tempAtt;
    for(int k = 0; k < nodes.size(); k++){
        traces.push_back(std::vector<std::vector<int>>());
        traces[k].push_back(nodes[k]);
        std::vector<std::vector<int>> pStates;
        pStates.push_back(nodes[k]);
        bool attractorHit = false;
        while(!attractorHit){
            for(int i = 0; i < TT.size()/2; i++){
                if(nodes[k] == TT[(i*2)] && !attractorHit){
                    nodes[k] = TT[(i*2)+1];
                    traces[k].push_back(nodes[k]);
                    int index = vecContains(pStates, nodes[k]);
                    if(index > -1){
                        std::vector<std::vector<int>> temp;
                        for(int j = index; j < pStates.size(); j++){
                            temp.push_back(pStates[j]);
                        }
                        tempAtt.push_back(temp);
                        attractorHit = true;
                        break;
                    }else{
                        pStates.push_back(nodes[k]);
                    }
                    break;
                }
            }
        }
        attractorHit = false;
    }
    for(int i = 0; i < tempAtt.size(); i++){
        if(!vecPermContains(attractors, tempAtt[i])){
            attractors.push_back(tempAtt[i]);
        }
    }
}

std::vector<std::vector<int>> basicNetwork::getTT(){
    return TT;
}
std::vector<std::vector<std::vector<int>>> basicNetwork::getattractors(){
    return attractors;
}
std::vector<std::vector<std::vector<int>>> basicNetwork::gettraces(){
    return traces;
}