#ifndef _boolnet_H_
#define _boolnet_H_

#include <vector>
#include <thread>

// basicNetwork ------------------------------------------------------------------------------

//Basic & messy implementation
class basicNetwork{
    private:
        std::vector<std::vector<int>> nodes;
        std::vector<std::vector<int>> TT;
        std::vector<std::vector<std::vector<int>>> attractors;
        std::vector<std::vector<std::vector<int>>> traces;
        std::vector<std::vector<std::vector<int>>> uniqueTraces;
    public:
        basicNetwork(std::vector<std::vector<int>> inTT);
        void iterate();

        std::vector<std::vector<int>> getTT();
        std::vector<std::vector<std::vector<int>>> getattractors();
        std::vector<std::vector<std::vector<int>>> gettraces();
        std::vector<std::vector<std::vector<int>>> getUniqueTraces();
};
#include "../src/models/basicNetwork.cpp"

// booleanNetwork ----------------------------------------------------------------------------

struct state{
    bool *vals;
    int len;
    bool &operator [](int index);
};

struct statePair{
    state t0;
    state t1;
};

struct stateTable{
    statePair *table;
    int len;
    statePair &operator [](int index);
};

struct sequence{
    state *states;
    int len;
    state &operator [](int index);
}; 
                                                                                              
class booleanNetwork{
    private:
        stateTable TT;
        sequence attractors;
        sequence traces;
        sequence uniqueTraces;

        void genTrace(state in);
    public:
        booleanNetwork(std::vector<std::vector<int>> inTT);
        booleanNetwork(stateTable inTT);

        void genTraces();

        stateTable getTT();
};
#include "../src/models/booleanNetwork.cpp"

#endif