#ifndef _booleanAlgebra_H_
#define _booleanAlgebra_H_
#pragma once

#include <BNT/booleanNetwork.h>
#include <string>
#include <vector>

namespace BooleanAlgebra{

    //Boolean Tree ------------------------------------------------------------------------------------

    class leaf{
        private:
            bool value;
            int type;
            std::vector<leaf> children;
            std::string label;

        public:
            leaf();
            leaf(std::string in);
            leaf(std::vector<std::string> in);

            bool evaluate();

            std::string print(int depth);
    };

    class boolTree{
        private:
            leaf tree;
            BooleanNetwork::node node;

        public:
            boolTree(std::string in);

            bool solve(std::vector<bool> in);
    };
}

#endif