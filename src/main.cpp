//#define CROW_ENABLE_SSL
#define CROW_MAIN

#include <crow/app.h>
#include <crow/mustache.h>
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

    //Crow app and routing lambda functions (Web Server)
    crow::SimpleApp app;

    //Base request and main page fetch
    crow::mustache::set_base(".");
    CROW_ROUTE(app,"/")
    ([]{
        crow::mustache::context ctx;
        auto page = crow::mustache::load("index.html");
        return page.render();
    });
    
    //Other route lambda function (to be updated)
    CROW_ROUTE(app, "/gen")
    ([]{
        return crow::response(200);
    });
    
    CROW_ROUTE(app, "/del")
    ([&savedNetworks]{
        savedNetworks[1].clear();
        return crow::response(200);
    });

    CROW_ROUTE(app, "/fetch")
    ([&savedNetworks]{ 
        crow::json::wvalue x;
        x["traces"] = savedNetworks[1].getTrace();
        x["attractors"] = savedNetworks[1].getAttractors();
        x["uniqueTraces"] = savedNetworks[1].getUniqueTraces();
        return x;
    });

    CROW_ROUTE(app, "/sendState")
    .methods("POST"_method)
    ([&savedNetworks](const crow::request& req){
        auto x = crow::json::load(req.body);
        if (!x)
            return crow::response(400);
        savedNetworks[1].synchronusIterate(x["state"]);
        crow::json::wvalue y;
        y["traces"] = savedNetworks[1].getTrace();
        return crow::response(y);
    });

    app.port(18080).multithreaded().run();

    return 0;
}
