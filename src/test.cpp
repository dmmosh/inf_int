#include <inf_int.h>
#include <iostream>
#include <limits>
#include <bits/stdc++.h>
#include <bitset>

#define N '\n'
#define BITS(x) std::bitset<8>(x)
#define int8 std::int_fast8_t


/*
if the last bit is a 1 (negative, substract) then use & operator
if the last bit is 0
*/

int main(void){
    char hi = -128;

    char size = ~0 >> 1;
    std::cout << (int)size;
    test();


}