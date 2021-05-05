#ifndef _utils_H_
#define _utils_H_

// STD includes ----------------------------------------------------------------------------

#include <initializer_list>

// Dynamic Array ----------------------------------------------------------------------------

template<typename T>
class arr{
    private:
        T *vals;
        int len;
    public:
        arr();
        arr(std::initializer_list<T> in);
        ~arr();

        void push_back(T in);
        void pop_back();
        void erase(int index);

        T *getVals();
        int size();

        bool equals(arr<T>);
        T &operator [](int index);
        void operator=(arr<T> in);
};
#include "utils.cpp"

#endif