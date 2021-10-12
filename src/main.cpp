#include <BNT/booleanNetwork.h>

// Printing (Temp) -----------------------------------------------

#include <iostream>

void printState(BooleanNetwork::state in){
    std::cout<<"{";
    for(int i = 0; i < in.size(); i++){
        std::cout<<in[i];
        if(i != in.size()-1){
            std::cout<<", ";
        }
    }
    std::cout<<"}";
}

void printSequence(BooleanNetwork::sequence in){
    for(int i = 0; i < in.size(); i++){
        printState(in[i]);
        if(i != in.size()-1){
            std::cout<<", ";
        }
    }
    std::cout<<std::endl;
}

void printSequenceArr(std::vector<BooleanNetwork::sequence> in){
    for(int i = 0; i < in.size(); i++){
        printSequence(in[i]);
    }
}

//Main -----------------------------------------------

BooleanNetwork::node A = {
    {
        {{{1, 0}, {2, 0}, {3, 0}}, 0},
        {{{1, 0}, {2, 0}, {3, 1}}, 1},
        {{{1, 0}, {2, 1}, {3, 0}}, 0},
        {{{1, 0}, {2, 1}, {3, 1}}, 1},
        {{{1, 1}, {2, 0}, {3, 0}}, 0},
        {{{1, 1}, {2, 0}, {3, 1}}, 1},
        {{{1, 1}, {2, 1}, {3, 0}}, 1},
        {{{1, 1}, {2, 1}, {3, 1}}, 1}
    }, 
    "A = B & C | D",
    "A",
    0, 
    0
};

BooleanNetwork::node B = {
    {
        {{{2, 0}, {3, 0}}, 1},
        {{{2, 0}, {3, 1}}, 1},
        {{{2, 1}, {3, 0}}, 0},
        {{{2, 1}, {3, 1}}, 1}
    }, 
    "B = !C | D",
    "B",
    0, 
    0
};

BooleanNetwork::node C = {
    {
        {{{0, 0}}, 1},
        {{{0, 1}}, 0},
    }, 
    "C = !A",
    "C",
    0, 
    0
};

BooleanNetwork::node D = {
    {
        {{{0, 0}}, 0},
        {{{0, 1}}, 1},
    }, 
    "D = A",
    "D",
    0, 
    0
};

BooleanNetwork::node E = {
    {
        {{{1, 0}, {2, 0}}, 0},
        {{{1, 0}, {2, 1}}, 0},
        {{{1, 1}, {2, 0}}, 0},
        {{{1, 1}, {2, 1}}, 1}
    }, 
    "E = B & C",
    "E",
    0, 
    0
};

BooleanNetwork::netStruc network1 = {A, B, C, D, E};

int main(){
    BooleanNetwork::nodeNetwork net(network1);
    net.clear();
    net.generateStateGraph();
    std::cout<<net.getTraceS()<<"\n"<<std::endl;
    std::cout<<net.getAttractorsS()<<"\n"<<std::endl;
    std::cout<<net.getUniqueTracesS()<<"\n"<<std::endl;
    std::cout<<net.getNodesS()<<"\n"<<std::endl;
    std::cout<<net.getNodesExpS()<<std::endl;
    net.clear();
    net.setState({0, 0, 0, 0, 0});
    net.generateAsynchStateGraph();
    std::cout<<net.getTraceS()<<"\n"<<std::endl;
    std::cout<<net.getAttractorsS()<<"\n"<<std::endl;
    std::cout<<net.getUniqueTracesS()<<"\n"<<std::endl;
    std::cout<<net.getNodesS()<<"\n"<<std::endl;
    std::cout<<net.getNodesExpS()<<std::endl;
    return 0;
}