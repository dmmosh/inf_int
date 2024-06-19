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

    inf_int<int8_t> a = 2000;


    std::cout << a.get_base<int>() << N << BITS(a.get_buffer()) << N << (pow(a.get_base(), sizeof(a.get_buffer())*8-1)-1)/(a.get_base()-1) << N ;

}