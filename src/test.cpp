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

    inf_int<int8_t> a = 20;
    inf_int<int8_t> b = 40;


    a = b;

    b = a + a;


    //a = 2000;vd
    //std::cout << BITS(a.get_buffer()) << N <<  a.value<int>() << N ;
    int8_t c = 124;

    std::cout << (int)min(c) << N << overflow(c, 10);

}