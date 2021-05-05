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
        void condense();
    public:
        basicNetwork(std::vector<std::vector<int>> inTT);

        std::vector<std::vector<int>> getTT();
        std::vector<std::vector<std::vector<int>>> getattractors();
        std::vector<std::vector<std::vector<int>>> gettraces();
};
#include "basicNetwork.cpp"

// syncNetwork ------------------------------------------------------------------------------

class syncNetwork{
    private:

        struct netState{
            std::vector<std::vector<int>> state;
        };

        struct netTable{
            std::vector<netState> table;
        };

        netState nodes;
        netTable TT;
        netTable attractors;
        netTable traces;

    public:

        syncNetwork(std::vector<std::vector<int>> inTT);
};

#endif