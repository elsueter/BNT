#ifndef _booleanAlgebra_H_
#define _booleanAlgebra_H_
#pragma once

#include <string>
#include <vector>

namespace BooleanAlgebra{

    //Boolean Tree ------------------------------------------------------------------------------------

    struct leaf{
        bool value;
        std::string label;

        bool evaluate();
    };

    struct notLeaf: leaf{
        bool evaluate();
    };

    struct andLeaf:leaf{
        leaf children[2];

        bool evaluate();
    };

    struct orLeaf:leaf{
        leaf children[2];

        bool evaluate();
    };

    struct boolTree{
        std::vector<leaf> nodes;
        bool result;

        void parseString(std::string in);
        bool solve(std::vector<bool> in);
    };
}

#endif