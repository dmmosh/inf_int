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

    //inf_int<int8_t> a = -200;
    //inf_int<int8_t> b = 38192;


    //a +=b;

    int8_t in1 = 0b00011111;
    int8_t in2 = 121;
    int8_t out1 = base_convert<int8_t>(in1, 3,2);
    int8_t out2 = base_convert<int8_t>(in2,2,3);

    std::cout << BITS(in1) << N << BITS(out1) << N << N << BITS(in2) << N << BITS(out2) << N;


}