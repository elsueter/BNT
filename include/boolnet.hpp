#ifndef _boolnet_H_
#define _boolnet_H_

#include <vector>

// basicNetwork ------------------------------------------------------------------------------

//Basic & messy implementation
class basicNetwork{
    private:
        std::vector<std::vector<int>> nodes;
        std::vector<std::vector<int>> TT;
        std::vector<std::vector<std::vector<int>>> attractors;
        std::vector<std::vector<std::vector<int>>> traces;

        void iterate();
    public:
        basicNetwork(std::vector<std::vector<int>> inTT);

        std::vector<std::vector<int>> getTT();
        std::vector<std::vector<std::vector<int>>> getattractors();
        std::vector<std::vector<std::vector<int>>> gettraces();
};
#include "../src/models/basicNetwork.cpp"

// syncNetwork ------------------------------------------------------------------------------
/*
struct netState{
    std::vector<int> state;
};

struct netTable{
    std::vector<std::vector<netState>> table;
    netTable& operator=(const std::vector<std::vector<int>> in);
    netState& operator[](int index);
};

class syncNetwork{
    private:

        std::vector<netState> nodes;
        netTable TT;
        netTable attractors;
        netTable traces;

        void iterate();

    public:
        syncNetwork(std::vector<std::vector<int>> inTT);
};
#include "../src/models/syncNetwork.cpp"
*/
#endif