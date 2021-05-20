#include <crow.h>
#include <booleanNetwork.h>

std::vector<std::vector<int> > ATT = {{0, 0}, {1, 0},
                                     {0, 1}, {0, 0},
                                     {1, 0}, {1, 1},
                                     {1, 1}, {0, 1}};

std::vector<std::vector<int> > BTT = {{0, 0, 0}, {0, 0, 0},
                                     {0, 0, 1}, {1, 1, 0},
                                     {0, 1, 0}, {0, 0, 0},
                                     {0, 1, 1}, {0, 1, 0},
                                     {1, 0, 0}, {0, 0, 1},
                                     {1, 0, 1}, {1, 1, 1},
                                     {1, 1, 0}, {0, 0, 1},
                                     {1, 1, 1}, {0, 1, 1}};

                                     
std::vector<std::vector<int>> CTT = {{0, 0, 0}, {0, 1, 1},
                                     {0, 0, 1}, {0, 0, 1},
                                     {0, 1, 0}, {0, 1, 1},
                                     {0, 1, 1}, {1, 0, 1},
                                     {1, 0, 0}, {0, 1, 0},
                                     {1, 0, 1}, {0, 0, 0},
                                     {1, 1, 0}, {0, 1, 0},
                                     {1, 1, 1}, {1, 0, 0}};

int main(){
    BooleanNetwork::basicNetwork net(CTT);

    crow::SimpleApp app;

    crow::mustache::set_base(".");
    CROW_ROUTE(app,"/")
    ([&net]{
        crow::mustache::context ctx;
        auto page = crow::mustache::load("webApp/index.html");
        return page.render();
    });

    CROW_ROUTE(app, "/json")
    ([&net]{ 
        crow::json::wvalue x;
        x["truthTable"] = net.getTT();
        x["traces"] = net.getTraces();
        x["attractors"] = net.getAttractors();
        x["uniqueTraces"] = net.getUniqueTraces(); 
        return x;
    });

    app.port(18080).multithreaded().run();

    return 0;
}