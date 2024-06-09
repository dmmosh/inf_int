#include <inf_int.h>
#include <iostream>
#include <limits>
#include <bits/stdc++.h>
#include <bitset>

#define N '\n'
#define BITS(x) std::bitset<64>(x)


template <typename T>
inline constexpr T max(const T& input){
    return (T)std::numeric_limits<T>::max();
}

template <typename T>
inline constexpr T min(const T& input){
    return (T)std::numeric_limits<T>::min();
}

/*
if the last bit is a 1 (negative, substract) then use & operator
if the last bit is 0
*/

int main(void){
    long hi = -2;

    long hi2 = ~((1 << (sizeof(hi)*8-1)) );
    std::cout << BITS(hi2) << N;
    std::cout << BITS((int)max(hi)) << N <<  (int)min(hi) << N ; 
    test();


}