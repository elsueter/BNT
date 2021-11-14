#include <crow/app.h>
#include <crow/mustache.h>
#include <BNT/booleanNetwork.h>
#include <BNT/booleanAlgebra.h>

#define CROW_MAIN

//Main -----------------------------------------------

int main(){

    BooleanNetwork::netStruc savedNetwork = BooleanNetwork::parseFile("networks/savedNetworks.json");
    BooleanNetwork::nodeNetwork network(savedNetwork);
    
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
    ([&network]{
        crow::json::wvalue x;
        x["exp"] = network.getNodesExpS();
        x["nodes"] = network.getNodesS();
        return crow::response(x);
    });
    
    CROW_ROUTE(app, "/clearNet")
    ([&network]{
        network.clear();
        return crow::response(200);
    });

    CROW_ROUTE(app, "/getSG")
    ([&network]{ 
        crow::json::wvalue x;
        network.generateStateGraph();
        x["traces"] = network.getTraceS();
        x["attractors"] = network.getAttractorsS();
        x["uniqueTraces"] = network.getUniqueTracesS();
        return crow::response(x);
    });

    CROW_ROUTE(app, "/inputNodes")
    .methods("POST"_method)
    ([&network](const crow::request& req){
        auto x = crow::json::load(req.body);
        if (!x)
            return crow::response(400);
        
        BooleanAlgebra::tree newTree(x);

        //network = BooleanNetwork::nodeNetwork(newTree.getNetStruc());
                
        crow::json::wvalue y;
        y["nodes"] = network.getNodesS();
        return crow::response(y);
    });

    CROW_ROUTE(app, "/sendS")
    .methods("POST"_method)
    ([&network](const crow::request& req){
        auto x = crow::json::load(req.body);
        if (!x)
            return crow::response(400);
        network.synchronusIterate(x["state"]);
        crow::json::wvalue y;
        y["traces"] = network.getTraceS();
        y["attractors"] = network.getAttractorsS();
        y["uniqueTraces"] = network.getUniqueTracesS();
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