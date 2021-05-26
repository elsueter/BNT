#include <crow.h>
#include <BNT/booleanNetwork.h>

std::vector<std::vector<int> > ATT = {{0, 0}, {1, 0},
                                     {0, 1}, {0, 0},
                                     {1, 0}, {1, 1},
                                     {1, 1}, {0, 1}};

std::vector<std::string> ALS = {"A = !B", "B = A"};

std::vector<std::vector<int> > BTT = {{0, 0, 0}, {0, 0, 0},
                                     {0, 0, 1}, {1, 1, 0},
                                     {0, 1, 0}, {0, 0, 0},
                                     {0, 1, 1}, {0, 1, 0},
                                     {1, 0, 0}, {0, 0, 1},
                                     {1, 0, 1}, {1, 1, 1},
                                     {1, 1, 0}, {0, 0, 1},
                                     {1, 1, 1}, {0, 1, 1}};

std::vector<std::string> BLS = {"A = C v !B", "B = C", "C = A"};
                                     
std::vector<std::vector<int> > CTT = {{0, 0, 0}, {0, 1, 1},
                                     {0, 0, 1}, {0, 0, 1},
                                     {0, 1, 0}, {0, 1, 1},
                                     {0, 1, 1}, {1, 0, 1},
                                     {1, 0, 0}, {0, 1, 0},
                                     {1, 0, 1}, {0, 0, 0},
                                     {1, 1, 0}, {0, 1, 0},
                                     {1, 1, 1}, {1, 0, 0}};

int main(){
    BooleanNetwork::basicNetwork net(CTT);

    BooleanNetwork::nodeNetwork net1(BLS);

    crow::SimpleApp app;

    crow::mustache::set_base(".");
    CROW_ROUTE(app,"/")
    ([&net]{
        crow::mustache::context ctx;
        auto page = crow::mustache::load("index.html");
        return page.render();
    });
    
    CROW_ROUTE(app, "/gen")
    ([&net]{ 
        net.genTraces();
        return crow::response(200);
    });
    
    CROW_ROUTE(app, "/del")
    ([&net]{ 
        net.del();
        return crow::response(200);
    });

    CROW_ROUTE(app, "/fetch")
    ([&net]{ 
        crow::json::wvalue x;
        x["truthTable"] = net.getTT();
        x["traces"] = net.getTraces();
        x["attractors"] = net.getAttractors();
        x["uniqueTraces"] = net.getUniqueTraces(); 
        return x;
    });

    app.port(443).ssl_file("/etc/letsencrypt/live/elsueter.dev/fullchain.pem ").multithreaded().run();

    return 0;
}