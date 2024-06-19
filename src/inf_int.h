
#ifndef __INF_INT_H__
#define __INF_INT_H__
#include <iostream> //testing purposes, remove on actual release
#include <limits>
#include <bits/stdc++.h>
#include <bitset>
#include <memory>
#define N '\n'
#define BITS(x) std::bitset<sizeof(x)*8>(x)
#define LEFT_BIT(x) ((int8_t)log2(x))
#define INT8(x) static_cast<int8_t>(x)

// MAX AND MIN, O(1) time

template <typename T>
inline constexpr T max(const T& input){
    return (T)std::numeric_limits<T>::max();
}

template <typename T>
inline constexpr T min(const T& input){
    return (T)std::numeric_limits<T>::min();
}



// base conversion NOTE: data types of all have to match, make sure to CAST 
template <typename T>
constexpr T base_convert(T val, const T& base_cur, const T& base_new){
    T out = 0;
    
    //ONLY BASE UP FOR NOW

    int8_t i = LEFT_BIT(val); // length of the bits
    // since the biggest data type is 64 bits, 1 byte int is enough
    // note: base conversions will ALWAYS round down, meaning numbers will either get floored or remain the same
    // the numbers will also never increase in bit length, 
    // therefore new number will always have leftmost turned on bit on/right of the old
    // clz command runtime is O(1)
    // iterate through the out number

    while(val >0 && i >= 0) {
        //std::cout << val << i;
        auto minus = pow(base_new, i);
        if(minus <= val){
            val-=minus;
            out += 1<< i;
        }
        i--;
    }

    return out;
};


template <typename T, typename U> // if overflow, returns -1 if not returns the addition
inline constexpr T add(const T& val1, const T& base1, const U& val2, const U& base2){


    return true;
};

// FUNCTION DECLARATIONS
// if theres another template other than T, then dont use friend keyword

void test();


template<typename T>
class inf_int{
    T buffer; // the buffer 
    T base; // the base, starting 0 
    std::unique_ptr<inf_int<T>> extra_base; //extra base, allocs only if need be

    public: 
    //constructors
    inf_int();

    template <typename U>
    inf_int(U value);
    inf_int(const inf_int& init_val);

    // FUNCTIONS    
    void bound_check();
    inline void base_up(); // moves bases up
    inline void base_down();  // moves bases down

    inline T get_buffer(); // outs the buffer
    inline T get_base(); // outs the base

    template<typename U>
    inline U get_buffer(); // outs the buffer in a data type

    template<typename U>
    inline U get_base(); // outs the base in a data type

    // OPERATOR OVERLOADING

    template<typename U>
    inf_int<T>& operator+=(const U& add); 
    inf_int<T>& operator+=(const inf_int& value); 


    template<typename U>
    inf_int<T>& operator+(const U& value); 
    inf_int<T>& operator+(const inf_int& value); 

    template<typename U>
    inf_int<T>& operator=(U value); 
    inf_int<T>& operator=(const inf_int& value); 

};  



// template class implementations (all of them)
template <typename T>
inf_int<T>::inf_int():
buffer(0),
extra_base(nullptr)
{
    return;
};

template <typename T> 
template <typename U> 
inf_int<T>::inf_int(U value):
buffer(max(this->buffer)),
base(2),
extra_base(nullptr)
{
    while(value > this->buffer){
        value = base_convert(value, static_cast<U>(this->base), static_cast<U>(this->base+1));
        this->base++;
    }
    this->buffer = value; 

    return;
};


template <typename T>
inf_int<T>::inf_int(const inf_int& init_val):
buffer(init_val.buffer()),
base(init_val.base()),
extra_base(nullptr)
{   
    return;
};



// FUNCTIONS

template <typename T>
inline void inf_int<T>::base_up() {
    this->buffer = base_convert(this->buffer, this->base, this->base+1);
    this->base++;
};

template <typename T>
inline void inf_int<T>::base_down() {
    if (this->base >2) {
        this->buffer = base_convert(this->buffer, this->base, this->base-1);
        this->base--;
    };
};

template <typename T>
inline T inf_int<T>::get_buffer(){
    return this->buffer;
};


template <typename T>
inline T inf_int<T>::get_base() {
    return this->base;
};

template <typename T>
template <typename U>
inline U inf_int<T>::get_buffer(){
    return static_cast<U>(this->buffer);
};


template <typename T>
template <typename U>
inline U inf_int<T>::get_base() {
    return static_cast<U>(this->base);
};


template<typename T>
std::ostream& operator<<(std::ostream& cout, const inf_int<T>& inf){
    if (inf.get_base == 2){
        cout << inf.get_buffer;
        return cout;
    }

};

template<typename T>
template<typename U>
inf_int<T>& inf_int<T>::operator+=(const U& add){
    this->buffer += add;
    return *this;
}; 

template<class T> template<typename U>
inf_int<T>& inf_int<T>::operator+(const U& value) {
    T sum = add(this->buffer, this->base, value, 2);
    this->buffer = sum;
    return *this;
}; 


template<class T>
inf_int<T>& inf_int<T>::operator+(const inf_int& value) {

}; 


template<class T> template<typename U>
inf_int<T>& inf_int<T>::operator=(U value) {
    this->base = 2;

    // increases the value until it fits in the data type
    while(value > max(this->buffer)){
        value = base_convert(value, static_cast<U>(this->base), static_cast<U>(this->base+1));
        this->base++;
    }

    this->buffer = value; 
    return *this;
}; 

template<class T>
inf_int<T>& inf_int<T>::operator=(const inf_int& value){
    this->buffer = value.buffer; 
    this->base = value.base;
    return *this;
}; 





#endif //__INF_INT_H__