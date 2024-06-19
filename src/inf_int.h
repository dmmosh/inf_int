
#ifndef __INF_INT_H__
#define __INF_INT_H__
#include <iostream> //testing purposes, remove on actual release
#include <limits>
#include <bits/stdc++.h>
#include <bitset>
#include <memory>
#define N '\n'

// macros
#define BITS(x) std::bitset<sizeof(x)*8>(x)
#define INT8(x) static_cast<int8_t>(x)

template <typename T>
inline constexpr T LEFT_BIT(const T& input){ // leftmost bit ( starting from 0)
    // ex 10 would give 3, 1010, leftmost bit is 2^3 aka 8
    if (input >0) { // if input is over 0
        return static_cast<T>(log2(input));
    } else if (input <0){ // cant have negative logs
        return static_cast<T>(sizeof(input)*8-1);
    };
    return -1; // if input is 0
}

template <typename T, typename U>
inline constexpr U LEFT_BIT(const T& input){ // leftmost bit ( starting from 0)
    // ex 10 would give 3, 1010, leftmost bit is 2^3 aka 8
    if (input >0) { // if input is over 0
        return static_cast<U>(log2(input));
    } else if (input <0){ // cant have negative logs
        return static_cast<U>(sizeof(input)*8-1);
    };
    return -1; // if input is 0
}

template<typename T> class inf_int; // class definition




// MAX AND MIN, O(1) time

template <typename T>
inline constexpr T max(const T& input){
    return static_cast<T>(std::numeric_limits<T>::max());
}

template <typename T>
inline constexpr T min(const T& input){
    return static_cast<T>(std::numeric_limits<T>::min());
}


// max value of a given infinite integer
template <typename T, typename U>
inline constexpr U max(const inf_int<T>& input){
    // (base^(bit length - 1) -1 / base -1)
    // ex x^7 -1 / x-1 

    return static_cast<U>((pow(input.base(), sizeof(input.buffer)*8-1)-1)/(input.base()-1));
};




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
buffer(0),
base(2),
extra_base(nullptr)
{
    // loops while the left bit of the value is bigger than the leftmost bit in buffer
    // usually executes once
    while(LEFT_BIT(value) > sizeof(this->buffer)*8-1){
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
    // loops while the left bit of the value is bigger than the leftmost bit in buffer
    // usually executes once
    this->base = 2; // restarts the base
    while(LEFT_BIT<U>(value) > static_cast<U>(sizeof(this->buffer)*8-2)){
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