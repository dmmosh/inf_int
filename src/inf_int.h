
#ifndef __INF_INT_H__
#define __INF_INT_H__
#include <iostream> //testing purposes, remove on actual release
#include <limits>
#include <bits/stdc++.h>
#include <bitset>
#include <memory>
#define N '\n'
#define BITS(x) std::bitset<sizeof(x)*8>(x)


template <typename T>
inline constexpr T max(const T& input){
    return (T)std::numeric_limits<T>::max();
}

template <typename T>
inline constexpr T min(const T& input){
    return (T)std::numeric_limits<T>::min();
}

template <typename T, typename U>
bool overflow(const T& val1, const T& base1, const U& val2, const U& base2){
    return true;
};


void test();

template<typename T>
class inf_int{
    public:
    T buffer; // the buffer 
    T base; // the base, starting 0 
    bool round_up; // round up or down
    std::unique_ptr<inf_int<T>> extra_base; //extra base, allocs only if need be

    //constructors
    inf_int();
    inf_int(const T& init_val);
    inf_int(const inf_int& init_val);

    //functions
    void bound_check();
    inline void base_up(); 
    inline void base_down(); 

    // operator overloading
    template<typename U>
    inf_int<T>& operator+=(const U& add); 
    inf_int<T>& operator+=(const inf_int& value); 


    template<typename U>
    inf_int<T>& operator+(const U& value); 
    inf_int<T>& operator+(const inf_int& value); 

    template<typename U>
    inf_int<T>& operator=(const U& value); 
    inf_int<T>& operator=(const inf_int& value); 
    
};



// template class implementations (all of them)
template <typename T>
inf_int<T>::inf_int():
buffer(0),
extra_base(nullptr)
{
    return;
};

template <typename T>
inf_int<T>::inf_int(const T& init_val):
buffer(init_val),
base(2),
extra_base(nullptr)
{
    return;
};


template <typename T>
inf_int<T>::inf_int(const inf_int& init_val):
buffer(init_val.buffer),
base(init_val.base),
extra_base(nullptr)
{   
    return;
};



template <typename T>
inline void inf_int<T>::base_up() {
    if (base == max) {
        extra_base = std::make_unique<inf_int<T>>(base);
    } else {
        base++;
    }
};

template <typename T>
inline void inf_int<T>::base_down() {
    if (base>1) base--;
};





template<typename T>
std::ostream& operator<<(std::ostream& cout, const inf_int<T>& inf){
    if (inf.base == 2){
        cout << inf.buffer;
        return cout;
    }

};

template<class T> template<typename U>
inf_int<T>& inf_int<T>::operator+=(const U& add){
    this->buffer += add;
    return *this;
}; 

template<class T> template<typename U>
inf_int<T>& inf_int<T>::operator+(const U& value) {
    if (overflow(this->buffer, this->base, value, 2)) {
        this->buffer += value;
    };
    return *this;
}; 


template<class T>
inf_int<T>& inf_int<T>::operator+(const inf_int& value) {

}; 


template<class T> template<typename U>
inf_int<T>& inf_int<T>::operator=(const U& value) {
    this->buffer = value; 
    this->base = 2;
    return *this;
}; 

template<class T>
inf_int<T>& inf_int<T>::operator=(const inf_int& value){
    this->buffer = value.buffer; 
    this->base = value.base;
    return *this;
}; 





#endif //__INF_INT_H__