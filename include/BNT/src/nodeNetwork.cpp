#include <BNT/booleanNetwork.h>

#include <iostream>

using namespace BooleanNetwork;

nodeNetwork::nodeNetwork(std::vector<std::string> in){
    baseLogic = in;
    nodes = parseExpression(in);
    std::cout<<nodes[0].getVal({1, 0, 0})<<std::endl;
}