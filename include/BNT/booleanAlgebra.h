#ifndef _booleanAlgebra_H_
#define _booleanAlgebra_H_
#pragma once

#include <BNT/booleanNetwork.h>
#include <string>
#include <vector>

namespace BooleanAlgebra{

    //Boolean Tree ------------------------------------------------------------------------------------

    struct node{
        std::string val;
        node* right;
        node* left;
        int op;
    };

    class tree{
        private:
            node root;
        public:
            tree(crow::json::rvalue in);

            BooleanNetwork::netStruc getNetStruc();
    };
}

#endif