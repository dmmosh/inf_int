
#ifndef __INF_INT_H__
#define __INF_INT_H__
//#include <iostream> //testing purposes, remove on actual release
#include <limits>
#include <bits/stdc++.h>
#include <bitset>
#include <memory>
#include <string>
#define N '\n'

// macros
#define BITS(x) std::bitset<sizeof(x)*8>(x)
#define INT8(x) static_cast<int8_t>(x)

template<class T> class inf_int; // class definition
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
template <class T, typename U>
inline constexpr U max(inf_int<T>& input){
    // (base^(bit length - 1) -1 / base -1)
    // ex x^7 -1 / x-1 

    return static_cast<U>((pow(input.get_base(), sizeof(input.buffer)*8-1)-1)/(input.get_base()-1));
};


template <typename T>
inline constexpr T LEFT_BIT(const T& input){ // leftmost bit ( starting from 0)
    // ex 10 would give 3, 1010, leftmost bit is 2^3 aka 8
    if (input >0) { // if input is over 0
        return log2(input);
    } else if (input <0){ // cant have negative logs
        return sizeof(input)*8-1;
    };
    return -1; // if input is 0
}

// checks if theres been an overflow
template <typename T, typename U>
inline constexpr bool overflow(T to, U from){
    if ((to+from > max(to)) || 
        (to > 0 && from > 0 && to+from <0) || 
        (to < 0 && from < 0 && to+from > 0)){
        return true;
    } 


    return false;
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


// FUNCTION DECLARATIONS
// if theres another template other than T, then dont use friend keyword

void test();


template<class T>
class inf_int{
    public: 
    T buffer; // the buffer 
    T base; // the base, starting 0 , NEVER CALL RAW
    // why ?
    // possibility the base itself will overflow , hence shifting to extra base 
    // always use base() function when dealing with the base
    bool base_breach; // if base has been overflowed itself
    // TODO: change some code to utilize base breach for true super duper infinity and beyond
    //constructors
    inf_int();

    template <typename U>
    inf_int(U value);

    template <class U>
    inf_int(inf_int<U> init_val);

    // FUNCTIONS    
    void bound_check();
    inline void base_up(); // moves bases up
    inline void base_down();  // moves bases down

    template <typename U>
    inline U value();

    inline T get_buffer(); // outs the buffer in a data type

    // never call base raw
    inline T get_base(); // outs the base in a data type

    inline std::string info();

    // OPERATOR OVERLOADING

    template<typename U>
    inf_int<T>& operator+=(U& add); 
    template<class U>
    inf_int<T>& operator+=(inf_int<U>& add);


    template<typename U>
    inf_int<T>& operator+(U& value); 
    template<class U>
    inf_int<T>& operator+(inf_int<U>& value);


    template<typename U>
    inf_int<T>& operator=(U& value); 
    template<class U>
    inf_int<T>& operator=(inf_int<U>& value); 
    
};  



// template class implementations (all of them)
template <class T>
inf_int<T>::inf_int():
buffer(0),
base(2)
{
    return;
};

template <class T> 
template <typename U> 
inf_int<T>::inf_int(U value):
buffer(0),
base(2)
{
    if(!value) return;

    *this = value;
};


template <class T>
template <class U>
inf_int<T>::inf_int(inf_int<U> init_val):
buffer(init_val.get_buffer()),
base(init_val.get_base())
{   
    *this = init_val;
    return;
};



// FUNCTIONS

template <class T>
inline void inf_int<T>::base_up() {
    this->buffer = base_convert(this->buffer, this->base, this->base+1);
    this->base++;
};

template <class T>
inline void inf_int<T>::base_down() {
    if (this->base >2) {
        this->buffer = base_convert(this->buffer, this->base, this->base-1);
        this->base--;
    };
};


template <class T>
inline T inf_int<T>::get_buffer(){
    return static_cast<T>(this->buffer);
};


// NEVER CALL BASE RAW
template <class T>
inline T inf_int<T>::get_base() {
    return static_cast<T>(this->base);
};

template <typename T>
template <typename U>
inline U inf_int<T>::value() {
    if (!this->buffer) return 0; // base case

    U out = 0; //output number
    int i = LEFT_BIT(this->buffer); // i iterate over bits

    while (i >= 0) { // while i is 0 or more
        if ((1<<i) & this->buffer) 
            out+= static_cast<U>(pow(this->get_base(), i)); //adds the power
        i--;
    }

    return out;

};

template <class T>
inline std::string inf_int<T>::info(){
    return  "\nVAL:\t" + std::to_string(this->value<long long>()) +
            "\nBITS:\t" + BITS(this->get_buffer()).to_string() + 
            "\nBASE:\t" + std::to_string(this->get_base()) +
            "\nMAX:\t" + std::to_string(max<T, long long>(*this)) + 
            "\n";
};



template<class T>
std::ostream& operator<<(std::ostream& cout, const inf_int<T>& inf){
    if (inf.get_base() == 2){
        cout << inf.buffer;
        return cout;
    }

};

template<class T>
template<typename U>
inf_int<T>& inf_int<T>::operator+=( U& add){

    return *this + add;
}; 

template<class T>
template<class U>
inf_int<T>& inf_int<T>::operator+=( inf_int<U>& add){

    return *this + add;
}; 

template<class T> 
template<typename U>
inf_int<T>& inf_int<T>::operator+(U& value) {
    inf_int<T> out = *this;
    
    if(overflow<T, U>(out.buffer, value)) { // if theres an overflow, move bases up
        out.buffer = base_convert<T>(out.buffer, out.get_base(), out.get_base()+1);
        out.base++;
    }

    if (out.get_base() != 2) // if the base ISNT 2, convert
        out.buffer+= base_convert<U>(value, 2, out.get_base());
    else 
        out.buffer += value;

    return out;
}; 


template<class T>
template<class U>
inf_int<T>& inf_int<T>::operator+(inf_int<U>& value) {
    inf_int<T> out = *this;
    
    if(overflow<T>(out.buffer, value.buffer)) { // if theres an overflow, move bases up
        out.buffer = base_convert<T>(out.buffer, out.get_base(), out.get_base()+1);
        //value = base_convert<U>(value, this->get_base(), this->get_base()+1);
        out.base++;
    }
    
    if(out.get_base() != value.get_base()) // if the bases dont match, convert
        out.buffer += base_convert<U>(value.buffer, value.get_base(), out.get_base());
    else 
        out.buffer += value.buffer; //add the bases

    return out;
}; 


template<class T> template<typename U>
inf_int<T>& inf_int<T>::operator=(U& value) {
    // loops while the left bit of the value is bigger than the leftmost bit in buffer
    // usually executes once
    
    this->buffer = 0;
    this->base = 2; // restarts the base

    if(!value) return *this; // base case, if 0 

    // iterates until a base that can hold the number is found
    U max_val = max<T, U>(*this); // temp max val variable
    while(max_val < value && max_val >0) { // keep iterating until a base that can hold the value is found or max val overflows
        this->base++; // increases the base
        max_val = max<T, U>(*this); // makes new max val
    }

    this->buffer = base_convert<U>(value, 2, this->get_base()); // makes the buffer


    // while(LEFT_BIT<U>(value) > static_cast<U>(sizeof(this->buffer)*8-2)){
    //     value = base_convert(value, static_cast<U>(this->base), static_cast<U>(this->base+1));
    //     this->base++;
    // }
    //this->buffer = value; 

    return *this;
}; 

template<class T>
template<class U>
inf_int<T>& inf_int<T>::operator=(inf_int<U>& value){
    this->base = value.get_base();
    this->buffer = value.get_buffer();
    this->base_breach = value.base_breach;
    
    //TODO: add checking to make sure the base itself isnt an inf int
    return *this;
}; 





#endif //__INF_INT_H__