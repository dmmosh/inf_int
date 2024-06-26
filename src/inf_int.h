
#ifndef __INF_INT_H__
#define __INF_INT_H__
//#include <iostream> //testing purposes, remove on actual release
#include <limits>
#include <bits/stdc++.h>
#include <type_traits>
#include <bitset>
#include <memory>
#include <string>

// macros
#define BITS(x) std::bitset<sizeof(x)*8>(x)
#define INT8(x) static_cast<int8_t>(x)

 // flags macros
#define SIGN 1
#define BASE (1<<1)
#define BUFFER (1<<2)
#define uT typename std::make_unsigned<T>::type
#define uU typename std::make_unsigned<U>::type


template<class T> class inf_int; // class definition
// MAX AND MIN, O(1) time


template <typename T>
inline constexpr T LEFT_BIT(const T& input){ // leftmost bit ( starting from 0)
    // ex 10 would give 3, 1010, leftmost bit is 2^3 aka 8
    if (input >0) { // if input is over 0
        return log2(input);
    } else if (input <0){ // cant have SIGN logs
        return sizeof(input)*8-1;
    };
    return -1; // if input is 0
}



// base conversion NOTE: data types of all have to match, make sure to CAST 
template <typename T>
constexpr T base_convert(T val, const T& base_cur, const T& base_new){

    if (base_cur == base_new) // base case, if bases match
        return val;

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
        auto minus = std::pow(base_new, i);
        if(minus <= val){
            val-=minus;
            out += 1<< i;
        }
        i--;
    }

    return out;
};

namespace valid{ // bound checking
    template<typename T, typename U>
    inline constexpr bool add( T to, U from ) {
        if (LEFT_BIT(from) > sizeof(T)*8-1) return false;
        if( from > 0 && to > std::numeric_limits<T>::max() - from ) return false;
        if( from < 0 && to < std::numeric_limits<T>::min() - from ) return false;

        return true;
    }

    // valid subtract note: from has to be unsigned to substract, otherwise would be - - aka + 
    template<typename T, typename U>
    inline constexpr bool subtract( T to, U from ) {
        if (LEFT_BIT(from) > sizeof(T)*8-1) return false;
      if ((from < 0) && (to > std::numeric_limits<T>::max() + from)) return false;
      if ((from > 0) && (to < std::numeric_limits<T>::min() + from)) return false;

      return true;
    }

    template<typename T>
    inline constexpr bool pow(const T& base, const T& power){ // checks if the power is valid
        return ((power * std::log(base) < std::log(std::numeric_limits<T>::max())) ?  true : false);
    }
    

    template <typename T>
    inline constexpr T max(){
        return static_cast<T>(std::numeric_limits<T>::max());
    }

    
    // max value of a given infinite integer
    template <class T, typename U>
    inline constexpr U max(inf_int<T>& input){
        // (base^(bit length - 1) -1 / base -1)
        // ex x^7 -1 / x-1 
    
        return static_cast<U>((std::pow(input.get_base(), sizeof(input.buffer)*8-1)-1)/(input.get_base()-1));
    };
    
    
    template <typename T>
    inline constexpr T min(){
        return static_cast<T>(std::numeric_limits<T>::min());
    }

}
// FUNCTION DECLARATIONS
// if theres another template other than T, then dont use friend keyword

template <typename T>
uT testing(T num){
    uT out = static_cast<uT>(num);
    return out;

};

// prints the values
template<class T>
std::ostream& operator<<(std::ostream& cout, inf_int<T>& input){
    cout << ((std::is_signed<T>::value) ? input.template value<int>() : input.template value<unsigned int>());
    return cout;
};


template<class T>
class inf_int{
    public: 
    T buffer; // the buffer 

    // unsigned T (macro)
    uT base; // the base, starting 0 , NEVER CALL RAW
    // why ?
    // possibility the base itself will overflow , hence shifting to extra base 
    // always use base() function when dealing with the base

    int8_t flags_arr; // flags array, each bit acts as a boolean, 3 filled so far

    // CONSTRUCTORS

    inf_int();

    template <typename U>
    inf_int(U value);

    template <class U>
    inf_int(inf_int<U>& init_val);




    // FUNCTIONS    

    template <typename U>
    inline U value(); // gets the value from buffer

    template <typename U>
    inline U value_safe(); // gets the value from buffer but SAFE (throws an error)

    inline std::vector<T> value(); // returns value as a vector

    template<typename U>
    inline U get_buffer();

    inline T get_buffer(); // outs the buffer in a data type

    template<typename U>
    inline uU get_base(); // gets the base

    inline uT get_base(); // gets the base

    inline std::string info(); // prints info

    inline std::string flags(); // prints flags




    // OPERATOR OVERLOADING

    template<typename U>
    inf_int<T>& operator+=(const U& add);  // overloads += operator with value

    template<class U>
    inf_int<T>& operator+=(const inf_int<U>& add);  // overloads += operator with another inf int

    template<typename U>
    inf_int<T>& operator=(U value);  // overloads = operator with another inf int

    template<class U>
    inf_int<T>& operator=(inf_int<U>& value);  // overloads = operator with another inf int

    // friend functions w templates cant be declared and defined later 

    template<typename U>
    friend inf_int<T> operator+(inf_int<T> out, const U& value) {

        U add = base_convert<U>(value, 2, out.get_base()); // converts bases from 2 to inf int's

        while (!valid::add<T,U>(out.buffer, add) && LEFT_BIT(add) > sizeof(out.buffer)*8-1){
            add = base_convert<U>(add, out.get_base(), out.get_base()+1);
            out.buffer = base_convert<T>(out.buffer, out.get_base(), out.get_base()+1);
            out.base++;
            
        }
 
        out.buffer += add;
        return out;
    }; 

    template<class U>
    friend inf_int<T> operator+(inf_int<T> out, const inf_int<U>& value) {


        U add = base_convert<U>(value.buffer, value.base, out.base); // converts bases from 2 to inf int's

        while (!valid::add<T,U>(out.buffer, add) && LEFT_BIT(add) > sizeof(out.buffer)*8-1){
            add = base_convert<U>(add, out.get_base(), out.get_base()+1);
            out.buffer = base_convert<T>(out.buffer, out.get_base(), out.get_base()+1);
            out.base++;
            
        }

        out.buffer += add;

        return out;
    }; 
    
};  



// template class implementations (all of them)
template <class T>
inf_int<T>::inf_int():
buffer(0),
base(2),
flags_arr(0)
{
    return;
};

template <class T> 
template <typename U> 
inf_int<T>::inf_int(U value):
buffer(0),
base(2),
flags_arr(0)
{
    if(!value) return;

    *this = value;
};


template <class T>
template <class U>
inf_int<T>::inf_int(inf_int<U>& init_val):
buffer(init_val.get_buffer()),
base(init_val.get_base()),
flags_arr(init_val.flags_arr)
{   
    return;
};


// FUNCTIONS

template <class T>
template<typename U>
inline U inf_int<T>::get_buffer(){
    return static_cast<U>(this->buffer);
};

template <class T>
inline T inf_int<T>::get_buffer(){
    return this->get_buffer<T>();
};

template <class T>
template<typename U>
inline uU inf_int<T>::get_base(){
    return static_cast<uU>(this->base);
}; 

// NEVER CALL BASE RAW
// todo: change some stuff here
template <class T>
inline uT inf_int<T>::get_base() {
    return this->get_base<T>();
};

template <typename T>
template <typename U>
inline U inf_int<T>::value() {
    if (!this->get_buffer()) return 0; // base case
    if (this->get_base<U>() == 2) return this->get_buffer<U>();

    int8_t i = LEFT_BIT(this->get_buffer()); // i iterate over bits

    U out = 0; //output number

    if(this->get_buffer() < 0){ // if buffer is negative
        U tmp = static_cast<U>(std::pow(this->get_base(), sizeof(this->get_buffer())*8-2)) +1;
        if (!valid::subtract(out, tmp))
            return valid::min<U>();
        out-=tmp;
        i--; 
    } 



    while (i >= 0) { // while i is 0 or more
        

        if (((1<<i) & this->buffer)) {
            U tmp = static_cast<U>(std::pow(this->get_base(), i));
            if (!valid::add(out, tmp)) // if adding overflows, return the max value
                return valid::max<U>();
            
            
            out+= tmp; //adds the std::power
        }
        i--;
    }
    return out;
};

template <typename T>
template <typename U>
inline U inf_int<T>::value_safe() { // returns the value but safely
    if (!this->get_buffer()) return 0; // base case
    if (this->get_base<U>() == 2) return this->get_buffer<U>();

    int8_t i = LEFT_BIT(this->get_buffer()); // i iterate over bits

    U out = 0; //output number

    while (i >= 0) { // while i is 0 or more
        

        if (((1<<i) & this->buffer)) {
            U tmp = static_cast<U>(std::pow(this->get_base(), i));
            if (!valid::add(out, tmp)) // if adding overflows, return the max value
                throw std::invalid_argument("Value overflow. Consider increasing the returning value size or changing the function to the other version.");

            
            out+= tmp; //adds the std::power
        }
        i--;
    }
    return out;
};


template <typename T>
inline std::vector<T> inf_int<T>::value() {
    std::vector<T> out; 


    return out;
}; 



template <class T>
inline std::string inf_int<T>::info(){
    return  "\nVAL:\t" + std::to_string(this->value<long long>()) +
            "\nBITS:\t" + BITS(this->get_buffer()).to_string() + 
            "\nBASE:\t" + std::to_string(this->get_base()) +
            "\nMAX:\t" + std::to_string(valid::max<T, long long>(*this)) +
            "\nMIN:\t" + std::to_string(-(valid::max<T, long long>(*this) +1)) + 
            "\n" + this->flags() + "\n";
};

template <class T>
inline std::string inf_int<T>::flags(){ // prints flags
    return  std::string("The number is: [ ") + 
            ((SIGN & this->flags_arr) ? "NEGATIVE, " : "POSITIVE, ") +
            ((BASE & this->flags_arr) ? "BASE_UP, " : "BASE_FINE, ") + 
            ((BUFFER & this->flags_arr) ? "BUFFER_UP ]" : "BUFFER_FINE ]" );

}; 


template<class T>
template<typename U>
inf_int<T>& inf_int<T>::operator+=(const U& add){
    *this = *this + add;
    return *this;
}; 

template<class T>
template<class U>
inf_int<T>& inf_int<T>::operator+=(const inf_int<U>& add){
    *this = *this + add;    
    return *this;
}; 



template<class T> 
template<typename U>
inf_int<T>& inf_int<T>::operator=(U value) {
    // loops while the left bit of the value is bigger than the leftmost bit in buffer
    // usually executes once
    
    this->buffer = 0;
    this->base = 2; // restarts the base
    this->flags_arr = 0;

    if(!value) return *this; // base case, if 0 
    
    if (value <0 ){ // if value is negative (signed)
        this->flags_arr |= SIGN; // flip the sign, number is now negative
        value -= valid::min<U>();
    }

    // iterates until a base that can hold the number is found
    U max_val = valid::max<T, U>(*this); // temp max val variable
    while(max_val < value && max_val >0) { // keep iterating until a base that can hold the value is found or max val overflows
        this->flags_arr |= BASE; // flips the base up bit
        this->flags_arr |= BUFFER; // flips the buffer up bit
        this->base++; // increases the base
        max_val = valid::max<T, U>(*this); // makes new max val (with  new base)
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
    this->flags_arr = value.flags_arr; 
    
    //TODO: add checking to make sure the base itself isnt an inf int
    return *this;
}; 





#endif //__INF_INT_H__