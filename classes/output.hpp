#ifndef _output_H_
#define _output_H_
#include <iostream>

template<typename T>
void printVector(std::vector<T> in);
template<typename T>
void printVector(std::vector<std::vector<T>> in);
template<typename T>
void printVector(std::vector<std::vector<std::vector<T>>> in);
#include "output.cpp"

#endif