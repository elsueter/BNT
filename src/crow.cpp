//#define CROW_ENABLE_SSL
#define CROW_MAIN

#include <crow/app.h>
#include <crow/mustache.h>
#include <BNT/booleanNetwork.h>

void crowApp(std::vector<BooleanNetwork::nodeNetwork> savedNetworks){
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

    app.port(80).multithreaded().run();
}