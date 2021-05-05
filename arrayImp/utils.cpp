// Dynamic Array ----------------------------------------------------------------------------

template<typename T>
arr<T>::arr(){
    vals = new T[0];
    len = 0;
}

template<typename T>
arr<T>::arr(std::initializer_list<T> in){
    len = in.size();
    vals = new T[len];
    
    int i = 0;
    for (auto it = in.begin(); it != in.end(); ++it, i++){
        vals[i] = *it;
    }
}

template<typename T>
arr<T>::~arr(){
    delete vals;
}

template<class T>
void arr<T>::operator = (arr<T> in)
{
    len = in.size();
    vals = new T [len];
    for (int i = 0; i < len; i++){
        vals[i] = in[i];
    }
}

template<typename T>
void arr<T>::push_back(T in){
    T *temp = vals;
    len++;
    vals = new T[len];
    for(int i = 0; i < len-1;i++){
        vals[i] = temp[i];
    }
    vals[len-1] = in;
    delete temp;
}

template<typename T>
void arr<T>::pop_back(){
    T *temp = vals;
    len--;
    vals = new T[len];
    for(int i = 0; i < len;i++){
        vals[i] = temp[i];
    }
    delete temp;
}

template<typename T>
void arr<T>::erase(int index){
    T *temp = vals;
    len--;
    vals = new T[len];
    for(int i = 0; i == len;i++){
        if(i != index){
            vals[i] = temp[i];
        }
    }
    delete temp;
}

template<typename T>
T *arr<T>::getVals(){
    return vals;
}

template<typename T>
int arr<T>::size(){
    return len;
}

template<typename T>
T &arr<T>::operator [](int index){
    return vals[index];
}