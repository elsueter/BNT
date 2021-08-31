#include <BNT/booleanAlgebra.h>

using namespace BooleanAlgebra;

bool leaf::evaluate(){
    return value;
}

bool notLeaf::evaluate(){
    return !value;
}

bool andLeaf::evaluate(){
    if(children[0].value && children[1].value){
        return true;
    }
    return false;
}

bool orLeaf::evaluate(){
    if(children[0].value || children[1].value){
        return true;
    }
    return false;
}

void boolTree::parseString(std::string in){
    
}