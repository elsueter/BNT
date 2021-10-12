#include <BNT/booleanNetwork.h>

using namespace BooleanNetwork;

bool statePair::operator ==(state input){
    for(auto& it: in){
        if(input[it.nodeName] != it.nodeValue){
            return false;
        }
    }
    return true;
}

void node::getNext(state in){
    for(auto& it: TT){
        if(it == in){
            next = it.out;
        }
    }
}

void node::update(){
    curr = next;
}