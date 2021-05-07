void timer::start(){
    t = std::clock();
}

void timer::stop(){
    std::cout << "Time: " << (std::clock() - t) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;
}

void timer::restart(){
    stop();
    start();
}