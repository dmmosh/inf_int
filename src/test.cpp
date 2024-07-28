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
    int8_t val, base, val_convert, val_convert_base;
}test;

int main(void){

    //inf_int<int8_t> a = 1000;

    //inf_int<int8_t> a = -200;
    //inf_int<int8_t> b = 38192;


    //a +=b;
    test in1 = {0b00001111, 2}; // 15
    test in2 = {0b00010000, 3}; // 121

    in1.val_convert_base = 3;
    in2.val_convert_base = 4;

    in1.val_convert = base_convert<int8_t>(in1.val, in1.base, in1.val_convert_base);
    in2.val_convert = base_convert<int8_t>(in2.val, in2.base, in2.val_convert_base);


    std::cout << N << BITS(in2.val) << T << (int)base_convert<int8_t>(in2.val, in2.base, 2);
    std::cout << N << BITS(in2.val_convert) << T << (int)base_convert<int8_t>(in2.val_convert, in2.val_convert_base, 2) << N;
}