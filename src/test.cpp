//#include <inf_int.h>
#include <inf_int.h>
#include <iostream>
#include <limits>
#include <bits/stdc++.h>
#include <bitset>
#define N '\n'


/*

clang++ -linf_int -std=c++20 ./src/test.cpp -o test && git-all && ./test

if the last bit is a 1 (negative, substract) then use & operator
if the last bit is 0
*/


int main(void){

    //inf_int<int8_t> a = 1000;

    inf_int<uint8_t> a = 2000;
    inf_int<int8_t> b = 38192;


    std::cout << a.info() << b.info();
    a +=b;
    std::cout << a.info() << valid::max<uint8_t, int>(a) << N << valid::min<uint8_t, int>(a) << N;

    int8_t out = base_convert<int8_t>(64, 4,3);
    std::cout << N << (int)out << N << BITS(out)<< N;


}