//#include <inf_int.h>
#include <inf_int.h>
#include <iostream>
#include <limits>
#include <bits/stdc++.h>
#include <bitset>
#define N '\n'
#define T '\t'


/*

clang++ -linf_int -std=c++20 ./src/test.cpp -o test && git-all && ./test

if the last bit is a 1 (negative, substract) then use & operator
if the last bit is 0
*/

typedef struct test{ //testing struct
    int8_t val, base;
}test;

void debug(const test& in){
    std::cout << N << BITS(in.val) << N << base_convert<int>(in.val, in.base, 2);
    std::cout << "  (base " << (int)in.base << ")" << N;
    //std::cout << N << BITS(in.val_convert) << T << (int)base_convert<int8_t>(in.val_convert, in.val_convert_base, 2) << N;
}

int main(void){

    // BASE CONVERSION TESTING
    test in1 = {60, 2}; // 81
    test in2 = {0b01100101, 4}; // 90

    // underflow errors TODO: fix
    // 01111111 base 3 to base 4
    // 00111000 base 4 to base 6


    int8_t in1_new_base =6;
    int8_t in2_new_base = 13;

    //test out1 = {base_convert<int8_t>(in1.val, in1.base, in1_new_base), in1_new_base};
    test out2 = {base_convert<int8_t>(in2.val, in2.base, in2_new_base), in2_new_base};

    //debug(in2);
    //debug(out2);
    //std::cout << std::pow(4,-100);

    // debug(in1);
    // debug(out1); skmklc

    //std::cout << BITS((int16_t)1000) << N;
    //inf_int<int8_t> a = 9897977987;
    
    //std::cout << a.info();
    inf_int<int8_t> a = 200;
    std::cout<<a.info();





}