//#define CROW_ENABLE_SSL
#define CROW_MAIN

#include <crow.h>
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

//Timing functions (temp) -----------------------------------------------

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

//Main -----------------------------------------------

int main(){
    BooleanNetwork::netStrucArr savedFiles = BooleanNetwork::parseFile();
    std::vector<BooleanNetwork::nodeNetwork> savedNetworks;
    for(auto& it: savedFiles){
        savedNetworks.push_back(BooleanNetwork::nodeNetwork(it));
    }

    crow::SimpleApp app;

    crow::mustache::set_base(".");
    CROW_ROUTE(app,"/")
    ([]{
        crow::mustache::context ctx;
        auto page = crow::mustache::load("index.html");
        return page.render();
    });
    
    CROW_ROUTE(app, "/gen")
    ([]{
        return crow::response(200);
    });
    
    CROW_ROUTE(app, "/del")
    ([&savedNetworks]{
        savedNetworks.clear();
        return crow::response(200);
    });

    CROW_ROUTE(app, "/fetch")
    ([&savedNetworks]{ 
        crow::json::wvalue x;
        x["traces"] = savedNetworks[1].getTraces();
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
        y["traces"] = savedNetworks[1].getTraces();
        return crow::response(y);
    });

    //app.ssl_file("/etc/letsencrypt/live/elsueter.dev/fullchain.pem");

    app.port(80).multithreaded().run();

    return 0;
}
