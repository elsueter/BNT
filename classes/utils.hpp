#ifndef _utils_H_
#define _utils_H_

template <typename T>
class arr{
    private:
        T *buffer {};
        int size = 0;
    public:
        arr();
        arr(T in);
        template <typename... Ts>
        arr(T n, Ts... rest);

        int length();

        T &operator [](int index);
};
#include "array.cpp"
#endif