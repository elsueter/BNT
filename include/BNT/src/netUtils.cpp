#include <BNT/booleanNetwork.h>
#include <iostream>

using namespace BooleanNetwork;

template<typename T>
void printVector(std::vector<T> in){
    std::cout<<"{";
    for(auto& it: in){
        std::cout<<it;
        if(it != in.back()){
            std::cout<<",";
        }
    }
    std::cout<<"}"<<std::endl;
}

std::vector<std::string> splitString(std::string in){
    std::vector<std::string> components = {""};
    components.reserve(in.length());
    int part = 0;
    for(int i = 0; i < in.length(); i++){
        if(in[i] == '=' || in[i] == '^' || in[i] == 'V'){
            components[part].pop_back();
            part++;
            components.push_back("");
            components[part] += in[i];
            i+=2;
            part++;
            components.push_back("");
        }
        components[part] += in[i];
    }
    components.shrink_to_fit();
    return components;
}

std::vector<int> convertString(std::vector<std::string> in){
    std::vector<int> vals;
    vals.reserve(in.size());
    for(auto& it: in){
        for(auto& ch: it){
            vals.push_back(ch - 65);
        }
    }
    vals.shrink_to_fit();
    return vals;
}

std::vector<statePair> BooleanNetwork::parseExpression(std::vector<std::string> in){
    for(int i = 0; i < in.size(); i++){
        std::vector<int> temp = convertString(splitString(in[i]));
        printVector(temp);
    }
    return {{{1},{2}}};
}