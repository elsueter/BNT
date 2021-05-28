#include <BNT/booleanNetwork.h>

//Timing functions

#include <chrono>

struct timer {
    std::chrono::high_resolution_clock::time_point t;
    void start() {
        t = std::chrono::high_resolution_clock::now();
    }

    void stop() {
        auto t1 = std::chrono::high_resolution_clock::now();
        std::chrono::duration< double > fs = t1 - t;
        std::chrono::microseconds d = std::chrono::duration_cast<std::chrono::microseconds>(fs);
        std::cout << d.count() << " us\n";
    }
    
    void restart() {
        stop();
        start();
    }
};

#include <iostream>

using namespace BooleanNetwork;

void BooleanNetwork::parseFile(){
    
    std::ifstream ifs("savedNetworks.json");
    std::string content( (std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()    ) );

    crow::json::rvalue x = crow::json::load(content);

    for(auto& network: x){
        std::vector<node> net;
        if(network.has("expressions")){
            net.reserve(network["expressions"].size());
            for(auto& expression: network["expressions"]){
                node temp;
                temp.exp = expression.s();
                net.push_back(temp);
            }
            for(auto& it: net){
                std::cout<<it.exp<<std::endl;
            }
        }else{
            net.reserve(network["truthTables"].size());
            for(auto& rs: network["truthTables"]){
                node temp;
                temp.TT = rs.s();
                net.push_back(temp);
            }
            for(auto& it: net){
                std::cout<<it.exp<<std::endl;
            }
        }
    }
}