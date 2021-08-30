#include <BNT/booleanNetwork.h>
#include <BNT/booleanAlgebra.h>

using namespace BooleanNetwork;

#include <iostream>

netStruc BooleanNetwork::parseFile(std::string path){
    netStruc out;

    std::ifstream ifs(path);
    std::string content( (std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()    ) );

    crow::json::rvalue network = crow::json::load(content);

    if(network.has("expressions")){
        out.reserve(network["expressions"].size());
        for(auto& expression: network["expressions"]){
            node temp = {{}, "", "", 0, 0};
            temp.exp = expression.s();
            out.push_back(temp);
        }
        if(!network.has("truthTables")){
            //parse truth tables and write to file
        }
        int i = 0;
        for(auto& netIt: network["truthTables"]){
            for(auto& it: netIt){
                statePair tempRow;
                for(auto& in: it["in"]){
                    nodeMap tempNode;
                    tempNode.nodeName = in[0].i();
                    tempNode.nodeValue = in[1].i();
                    tempRow.in.push_back(tempNode);
                }
                tempRow.out = it["out"].i();
                out[i].TT.push_back(tempRow);
            }
            out[i].label = netIt.key();
            i++;
        }
    }
    return out;
}

netStruc BooleanNetwork::parseExpressions(crow::json::rvalue in){
    netStruc out;

    for(auto &it: in["exp"]){
    }

    return out;
}