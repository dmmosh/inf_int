#include <inf_int.h>
#include <iostream>
#include <limits>
#include <bits/stdc++.h>
#include <bitset>

#define N '\n'
#define BITS(x) std::bitset<8>(x)
#define int8 int8_t
#define SIGNED_MAX(x) (~(-1 << (sizeof(x) * 8 - 1)))


template <typename T>
inline constexpr T max(const T& input){
    return ~(-1 << (sizeof(input) * 8 - 1));
}

/*
if the last bit is a 1 (negative, substract) then use & operator
if the last bit is 0
*/

int main(void){
    int8 hi = -128;

    std::cout << (int)max(hi);
    test();


}