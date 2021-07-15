#include <crow/app.h>
#include <crow/mustache.h>
#include <BNT/booleanNetwork.h>

#define CROW_MAIN

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

int main(){

    BooleanNetwork::netStrucArr savedFiles = BooleanNetwork::parseFile("networks/savedNetworks.json");
    std::vector<BooleanNetwork::nodeNetwork> savedNetworks;
    for(auto& it: savedFiles){
        savedNetworks.push_back(BooleanNetwork::nodeNetwork(it));
    }

    for(auto &it: savedNetworks){
        it.generateStateGraph();
        std::cout<<"Attractors:\n"<<it.getAttractorsS()<<"\n\n";
        std::cout<<"UniqueTraces:\n"<<it.getUniqueTracesS()<<"\n\n";
        std::cout<<"Nodes:\n"<<it.getNodesS()<<"\n\n";
        std::cout<<"Expressions:\n"<<it.getNodesExpS()<<"\n\n";
        std::cout<<"\n";
    }
    
    //Crow app and routing lambda functions (Web Server)
    crow::SimpleApp app;

    //Base request and main page fetch
    crow::mustache::set_base(".");
    CROW_ROUTE(app,"/")
    ([]{
        auto page = crow::mustache::load("webApp/index.html");
        return page.render();
    });
    
    //Other route lambda function (to be updated)
    CROW_ROUTE(app, "/getNet")
    ([&savedNetworks]{
        crow::json::wvalue x;
        x["exp"] = savedNetworks[2].getNodesExpS();
        return crow::response(x);
    });
    
    CROW_ROUTE(app, "/clearNet")
    ([&savedNetworks]{
        savedNetworks[2].clear();
        return crow::response(200);
    });

    CROW_ROUTE(app, "/getSG")
    ([&savedNetworks]{ 
        crow::json::wvalue x;
        savedNetworks[2].generateStateGraph();
        x["traces"] = savedNetworks[2].getTraceS();
        x["attractors"] = savedNetworks[2].getAttractorsS();
        x["uniqueTraces"] = savedNetworks[2].getUniqueTracesS();
        return crow::response(x);
    });

    CROW_ROUTE(app, "/sendS")
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

    //Catchall route for resources
    CROW_ROUTE(app,"/<path>")
    ([](const crow::request& req, crow::response& res, std::string in){
        res.set_static_file_info("webApp/" + in);
        res.end();
    });

    app.port(18080).multithreaded().run();
    return 0;
}