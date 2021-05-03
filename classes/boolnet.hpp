#include "utils.hpp"

class node{
    private:
        bool state;
        arr<node> neigh;
        arr<int> TT;
    public:
        node(arr<int> inTT);

        void updateNeigh(arr<node> inN);
};

class network{
    private:
        arr<node> nodes;
    public:
        network();
};