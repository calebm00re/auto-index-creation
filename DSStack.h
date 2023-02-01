//
// Created by Caleb Moore on 3/22/21.
//

#ifndef INC_21S_PA02_DSSTACK_H
#define INC_21S_PA02_DSSTACK_H
#include "DSVector.h"

template <class T>
class DSStack{
private:
    //variable to hold data
    DSVector<T>* data;
public:
    //constructors
    DSStack();
    DSStack(const DSStack&);

    //assignment operator
    DSStack& operator= (const DSStack&);

    //functions
    bool is_empty();
    void push(const T& v);
    T pop();
    T& top();

    //destructor
    ~DSStack();
};

template<class T>
DSStack<T>::DSStack() {
//default ... do nothing
}

template<class T>
DSStack<T>::DSStack(const DSStack & rhs) {
    delete data;

    data = new DSVector<T>;
    data = rhs.data;
}

template<class T>
DSStack<T> &DSStack<T>::operator=(const DSStack & rhs) {
    delete data;

    data = new DSVector<T>;
    data = rhs.data;
    return *this;
}

template<class T>
bool DSStack<T>::is_empty() {
    if (data->get_size() == 0){
        return true;
    }
    return false;
}

template<class T>
void DSStack<T>::push(const T &v) {
    data->push_back(v);
}

template<class T>
T DSStack<T>::pop() {
    T temp = data[data->get_size() - 1];
    data->erase_at(data->get_size() - 1);
    return temp;
}

template<class T>
T &DSStack<T>::top() {
    return data[data->get_size() - 1];
}

template<class T>
DSStack<T>::~DSStack() {
    delete data;
}

#endif //INC_21S_PA02_DSSTACK_H
