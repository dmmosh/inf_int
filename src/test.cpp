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

    inf_int<int> a = 10;
    // the int limit is: 2147483647
    inf_int<int8_t> b = 20;

    std::cout << a.info();

    a = a +10 + b + a + 10 + 10 ;


    std::cout << a.info();



}