#include "inf_int.h"


template <typename T>
inf_int<T>::inf_int():
buffer(0)
{

};

template <typename T>
inf_int<T>::inf_int(const T& init_val):
buffer(init_val),
base(2)
{

};


template <typename T>
inf_int<T>::inf_int(const inf_int& init_val):
buffer(init_val.buffer),
base(init_val.base)
{

};


template<class T> template<typename U>
inf_int<T>& inf_int<T>::operator+=(const U& add){
    this->buffer += add;
    return *this;
}; 
    



void test() {
    std::cout << "hello test";
};
