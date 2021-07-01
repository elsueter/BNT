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

//Main -----------------------------------------------

#include <time.h>

int main(){
    clock_t start, end;
    double cpu_time_used;

    BooleanNetwork::netStrucArr savedFiles = BooleanNetwork::parseFile();
    std::vector<BooleanNetwork::nodeNetwork> savedNetworks;
    for(auto& it: savedFiles){
        savedNetworks.push_back(BooleanNetwork::nodeNetwork(it));
    }

    for(auto it: savedNetworks){
        start = clock();
        it.generateStateGraph();
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        std::cout<<cpu_time_used<<" s"<<std::endl;
        std::cout<<std::endl;
        printSequenceArr(it.getUniqueTraces());
        std::cout<<std::endl;
        printSequenceArr(it.getAttractors());
        std::cout<<std::endl;
        std::cout<<it.getNodesS()<<std::endl;
    }
    
    /*
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
        savedNetworks[2].clear();
        return crow::response(200);
    });

    CROW_ROUTE(app, "/fetch")
    ([&savedNetworks]{ 
        crow::json::wvalue x;
        savedNetworks[2].generateStateGraph();
        x["traces"] = savedNetworks[2].getTraceS();
        x["attractors"] = savedNetworks[2].getAttractorsS();
        x["uniqueTraces"] = savedNetworks[2].getUniqueTracesS();
        return x;
    });

    CROW_ROUTE(app, "/sendState")
    .methods("POST"_method)
    ([&savedNetworks](const crow::request& req){
        auto x = crow::json::load(req.body);
        if (!x)
            return crow::response(400);
        savedNetworks[2].synchronusIterate(x["state"]);
        crow::json::wvalue y;
        y["traces"] = savedNetworks[2].getTraceS();
        y["attractors"] = savedNetworks[2].getAttractorsS();
        y["uniqueTraces"] = savedNetworks[2].getUniqueTracesS();
        return crow::response(y);
    });

    app.port(18080).multithreaded().run();*/
    return 0;
}