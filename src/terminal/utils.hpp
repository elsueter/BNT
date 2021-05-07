#ifndef _output_H_
#define _output_H_

#include <iostream>
#include <ctime>

struct timer{
    std::clock_t t;
    void start();
    void stop();
    void restart();
};
#include "utilityFuncs.cpp"

void printState(state in);
void printStatePair(statePair in);
void printStateTable(stateTable in);

template<typename T>
void printVector(std::vector<T> in);
template<typename T>
void printVector(std::vector<std::vector<T>> in);
template<typename T>
void printVector(std::vector<std::vector<std::vector<T>>> in);
#include "printStructs.cpp"

#endif