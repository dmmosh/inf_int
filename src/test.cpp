//#include <inf_int.h>
#include <inf_int.h>
#include <iostream>
#include <limits>
#include <bits/stdc++.h>
#include <bitset>


/*

clang++ -linf_int -std=c++20 ./src/test.cpp -o test && git-all && ./test

if the last bit is a 1 (negative, substract) then use & operator
if the last bit is 0
*/

int main(void){

    //inf_int<int8_t> a = 1000;

    inf_int<unsigned int> a = 9999999999999999999;

    //a = 2000;
    //std::cout << BITS(a.get_buffer()) << N <<  a.value<int>() << N ;

    std::cout << a.info() ;

}