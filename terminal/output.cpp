
template<typename T>
void printVector(std::vector<T> in){
    std::cout<<"{";
    for(int i = 0; i < in.size(); i++){
        std::cout<<in[i];
        if(i < in.size()-1){
            std::cout<<", ";
        }
    }
    std::cout<<"} ";
}
template<typename T>
void printVector(std::vector<std::vector<T>> in){
    for(int i = 0; i < in.size(); i++){
        printVector(in[i]);
        if(i%2==1){
            std::cout<<std::endl;
        }
    }
    std::cout<<std::endl;
}
template<typename T>
void printVector(std::vector<std::vector<std::vector<T>>> in){
    for(int i = 0; i < in.size(); i++){
        for(int j = 0; j < in[i].size(); j++){
            printVector(in[i][j]);
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}