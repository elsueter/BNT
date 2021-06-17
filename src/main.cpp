#include "crow.cpp"
#include <BNT/booleanNetwork.h>

// Printing (Temp) -----------------------------------------------

#include <iostream>

void printState(BooleanNetwork::state in){
    std::cout<<"{";
    for(int i = 0; i < in.size(); i++){
        std::cout<<in[i];
        if(i != in.size()-1){
            std::cout<<", ";
        }
    }
    std::cout<<"}";
}

void printSequence(BooleanNetwork::sequence in){
    for(int i = 0; i < in.size(); i++){
        printState(in[i]);
        if(i != in.size()-1){
            std::cout<<", ";
        }
    }
    std::cout<<std::endl;
}
void printSequenceArr(std::vector<BooleanNetwork::sequence> in){
    for(int i = 0; i < in.size(); i++){
        printSequence(in[i]);
    }
}

//Timing Class (temp for benchmarking) -----------------------------------------------

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
        std::cout << d.count() << " us"<<std::endl;
    }
    
    void restart() {
        stop();
        start();
    }
};

//Main -----------------------------------------------

int main(){
    BooleanNetwork::netStrucArr savedFiles = BooleanNetwork::parseFile();
    std::vector<BooleanNetwork::nodeNetwork> savedNetworks;
    for(auto& it: savedFiles){
        savedNetworks.push_back(BooleanNetwork::nodeNetwork(it));
    }

    crowApp(savedNetworks);

    return 0;
}
