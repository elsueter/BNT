#include "../include/booleanNetwork.h"

#define CROW_MAIN
#include "include/crow_all.h"

int main(){
    crow::SimpleApp app;

    crow::mustache::set_base(".");
    CROW_ROUTE(app,"/")
    ([]{
        crow::mustache::context ctx;
        auto page = crow::mustache::load("webApp/index.html");
        return page.render();
    });

    CROW_ROUTE(app, "/json")
    ([]{
        crow::json::wvalue x;
        x["message"] = "Hello, World!";
        return x;
    });

    app.port(18080).multithreaded().run();

    return 0;
}