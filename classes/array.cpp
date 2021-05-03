#include "utils.hpp"

template<typename T>
arr<T>::arr(){
    T *buffer = {};
    size = 0;
}

template<typename T>
arr<T>::arr(T n){
    size++;
    T *temp = new T[size];
    for(int i = 1; i < size; i++){
        temp[i] = buffer[i-1];
    }
    temp[0] = n;
    buffer = temp;   
}

template<typename T>
template<typename... Ts>
arr<T>::arr(T n, Ts... rest) : arr(rest...){
    size++;
    T *temp = new T[size];
    for(int i = 1; i < size; i++){
        temp[i] = buffer[i-1];
    }
    temp[0] = n;
    buffer = temp;   
}

template<typename T>
int arr<T>::length(){
    return size;
}

template<typename T>
T &arr<T>::operator[](int index){
    return buffer[index];
} 