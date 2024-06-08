
#ifndef __INF_INT_H__
#define __INF_INT_H__
#include <iostream> //testing purposes, remove on actual release
#include <limits>
#include <bits/stdc++.h>
#include <bitset>

#define BITS(x) std::bitset<8>(x)
#define int8 std::int_fast8_t

void test();

class inf_int{
    int8 buffer;
    public:
    inf_int();
};



#endif //__INF_INT_H__