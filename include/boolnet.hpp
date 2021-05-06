#ifndef _boolnet_H_
#define _boolnet_H_

// basicNetwork ------------------------------------------------------------------------------

#include <vector>

//Basic & messy implementation
class basicNetwork{
    private:
        std::vector<std::vector<int> > nodes;
        std::vector<std::vector<int> > TT;
        std::vector<std::vector<std::vector<int> > > attractors;
        std::vector<std::vector<std::vector<int> > > traces;
        std::vector<std::vector<std::vector<int> > > uniqueTraces;

        void iterate();
    public:
        basicNetwork(std::vector<std::vector<int> > inTT);

        std::vector<std::vector<int> > getTT();
        std::vector<std::vector<std::vector<int> > > getattractors();
        std::vector<std::vector<std::vector<int> > > gettraces();
        std::vector<std::vector<std::vector<int> > > getUniqueTraces();
};
#include "../src/models/basicNetwork.cpp"

// booleanNetwork ----------------------------------------------------------------------------


struct netTT{
    struct netTTrow{
        struct netState{
            bool *vals;
            int noNodes;
        };
        netState t, t1;
    };
};

class booleanNode{
};

class booleanNetwork{
};
#include "../src/models/booleanNetwork.cpp"

#endif