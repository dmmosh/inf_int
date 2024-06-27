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

    inf_int<int8_t> a = -200;
    inf_int<int8_t> b = 38192;


    std::cout << a.info() << b.info();
    a +=b;
    std::cout << a.info() << valid::max<int8_t, int>(a) << N << valid::min<int8_t, int>(a) << N;

    int8_t out1 = base_convert<int8_t>(0b00011111, 3,2); //-120
    int8_t out2 = base_convert<int8_t>(0b01111001, 2,3); //120
    std::cout << N << (int)out1 << N << BITS(out1)<< N << (int)out2 << N << BITS(out2);


}