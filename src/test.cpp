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

    inf_int<int8_t> a;
    a = 100;

    std::cout << a.get_base<int>() << N << BITS(a.get_buffer()) << N << max<int8_t, int>(a) << N << a.value<int>() << N ;

}