#include <BNT/booleanAlgebra.h>

using namespace BooleanAlgebra;

#include <iostream>

std::vector<std::string> splitString(std::string in){
    std::vector<std::string> out;
    out.push_back("");

    for(auto& character: in){
        out[out.size()-1] += character;
        if(character == '&' || character == '|' || character == '='){
            out.push_back("");
        }
    }
    return out;
}

tree::tree(crow::json::rvalue in){
    for(auto& expression: in["exp"]){
        std::vector<std::string> exp = splitString(expression.s());
        for(auto& it: exp){
            std::cout<<it<<", ";
        }
        std::cout<<std::endl;
    }
}

BooleanNetwork::netStruc tree::getNetStruc(){
    BooleanNetwork::netStruc temp;
    return temp;
}