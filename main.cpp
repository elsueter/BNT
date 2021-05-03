#include "classes/utils.hpp"
#include "classes/boolnet.hpp"

/*  Graph A (from document)
    Nodes: {A, B}
    Rules: {A = !B}, {B = A}
    Truth Table:{{0, 0}, {1, 0},
                 {0, 1}, {0, 0},
                 {1, 0}, {1, 1},
                 {1, 1}, {0, 1}}

    A Truth Table: {0, 1,
                    1, 0}

    B Truth Table: {0, 0,
                    1, 1}
*/

arr<int> A0TT[4] = {0, 1, 
                    1, 0};

arr<int> A1TT[4] = {0, 0, 
                    1, 1};

int main(){

    return 0;
}