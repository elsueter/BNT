#include <vector>

class node{
    private:
        bool state;
        std::vector<node> neigh;
        std::vector<int> TT;
    public:
        node(std::vector<int> inTT);

        void updateNeigh(std::vector<node> inN);
};

class network{
    private:
        std::vector<node> nodes;
    public:
        network();
};

class basicNetwork{
    private:
        std::vector<std::vector<int>> TT;
    public:
        basicNetwork();
};