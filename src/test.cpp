//#include <inf_int.h>
#include <inf_int.h>
#include <iostream>
#include <limits>
#include <bits/stdc++.h>
#include <bitset>


/*
if the last bit is a 1 (negative, substract) then use & operator
if the last bit is 0
*/

int main(void){

    //inf_int<int8_t> a = 1000;

    inf_int<int> a;
    a =  2;

    //a = 2000;
    //std::cout << BITS(a.get_buffer()) << N <<  a.value<int>() << N ;

    std::cout << a.info() ;

}