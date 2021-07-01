#include <BNT/booleanNetwork.h>

using namespace BooleanNetwork;

#include <iostream>

netStrucArr BooleanNetwork::parseFile(){
    netStrucArr out;

    std::ifstream ifs("savedNetworks.json");
    std::string content( (std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()    ) );

    crow::json::rvalue x = crow::json::load(content);

    for(auto& network: x){
        netStruc net;
        if(network.has("expressions") && network.has("truthTables")){
            net.reserve(network["expressions"].size());
            for(auto& expression: network["expressions"]){
                node temp = {{}, "", "", 0, 0};
                temp.exp = expression.s();
                net.push_back(temp);
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
                    net[i].TT.push_back(tempRow);
                }
                net[i].label = netIt.key();
                i++;
            }
        }
        else if(network.has("expressions")){
            net.reserve(network["expressions"].size());
            for(auto& expression: network["expressions"]){
                node temp = {{}, "", 0, 0};
                temp.exp = expression.s();
                //-> insert expression parser
                net.push_back(temp);
            }
        }
        else if(network.has("truthTables")){
            net.reserve(network["truthTables"].size());
            for(int i = 0; i < network["truthTables"].size(); i++){
                node temp = {{}, "", 0, 0};
                for(auto& it: network["truthTables"][i]){
                    statePair tempRow;
                    for(auto& in: it["in"]){
                        nodeMap tempNode;
                        tempNode.nodeName = in[0].i();
                        tempNode.nodeValue = in[1].i();
                        tempRow.in.push_back(tempNode);
                    }
                    tempRow.out = it["out"].i();
                    temp.TT.push_back(tempRow);
                }
                net.push_back(temp);
            }
        }
        out.push_back(net);
    }
    return out;
}