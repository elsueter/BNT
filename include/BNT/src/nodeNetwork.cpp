#include <BNT/booleanNetwork.h>

using namespace BooleanNetwork;

nodeNetwork::nodeNetwork(std::vector<std::string> in){
    baseLogic = in;
    nodes = parseExpression(in);
}