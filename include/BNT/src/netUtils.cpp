#include <BNT/booleanNetwork.h>

using namespace BooleanNetwork;

bool node::getVal(state in){
    for(int i = 0; i < in.size(); i++){
        for(int j = 0; j < nodes.size(); j++){
            if(i == nodes[j]){
                if(tt[j] != in[i]){
                    return false;
                }
            }
        }
    }
    return true;
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

std::vector<node> BooleanNetwork::parseExpression(std::vector<std::string> in){
    std::vector<node> out;
    for(int i = 0; i < in.size(); i++){
        std::vector<std::string> temp = splitString(in[i]);
        node tempNode;
        for(int j = 2; j < temp.size(); j++){
            if(temp[j][0] == '^' || temp[j][0] == 'v'){
                tempNode.ops.push_back(temp[j][0]);
            }else if(temp[j][0] == '!'){
                tempNode.nodes.push_back((int)temp[j][1]-65);
                tempNode.tt.push_back(0);
            }else{
                tempNode.nodes.push_back((int)temp[j][0]-65);
                tempNode.tt.push_back(1);
            }
        }
        out.push_back(tempNode);
    }
    return out;
}