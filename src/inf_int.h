
#ifndef __INF_INT_H__
#define __INF_INT_H__
#include <iostream> //testing purposes, remove on actual release
#include <limits>
#include <bits/stdc++.h>
#include <bitset>
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


void test();

template<typename T>
class inf_int{
    T buffer; // the buffer 
    T base; // the base, starting 0 
    public:
    inf_int();
    inf_int(const T& init_val);
    inf_int(const inf_int& init_val);

    template<typename U>
    inf_int<T>& operator+=(const U& add); 
};



#endif //__INF_INT_H__