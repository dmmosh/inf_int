
#ifndef __INF_INT_H__
#define __INF_INT_H__
#include <iostream> //testing purposes, remove on actual release
#include <limits>
#include <bits/stdc++.h>
#include <type_traits>
#include <bitset>
#include <memory>
#include <string>

// macros
#define BITS(x) std::bitset<sizeof(x)*8>(x) // the bit representation (debug only)
#define INT8(x) static_cast<int8_t>(x) // casts to int8 (debug only)

/* a=target variable, b=bit number to act upon 0-n */
#define BIT_SET(a,b) ((a) |= (1ULL<<(b))) // sets a bit at position b 
#define BIT_CLEAR(a,b) ((a) &= ~(1ULL<<(b))) // clears a bit at position b
#define BIT_FLIP(a,b) ((a) ^= (1ULL<<(b))) // flips a bit at position b
#define BIT_CHECK(a,b) (!!((a) & (1ULL<<(b)))) //checks if a bit is at the position, true or false

 // flags macros
#define NEGATIVE_SIGN 1 //is negative?
#define BASE (1<<1) // is base NOT 2?
#define BUFFER (1<<2) // is cross the buffer ? 
#define uT typename std::make_unsigned<T>::type // unsigned typename T
#define uU typename std::make_unsigned<U>::type // unsigned typename U


template<class T> class inf_int; // class definition
// MAX AND MIN, O(1) time


template <typename T>
inline constexpr T LEFT_BIT(const T& input){ // leftmost bit ( starting from 0)
    // ex 10 would give 3, 1010, leftmost bit is 2^3 aka 8
    if (input >0) { // if input is over 0
        return log2(input);
    } else if (input <0){ // cant have NEGATIVE_SIGN logs
        return sizeof(input)*8-1;
    };
    return -1; // if input is 0
}

inline constexpr auto log_base(const auto& val, const auto& base){
    return log2(val) / log2(base); 
}


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
    
        return static_cast<U>((std::pow(input.get_base(), sizeof(input.buffer)*8-((std::is_signed<T>()) ? 1 : 0))-1)/(input.get_base()-1));
    };
    
    
    template <typename T>
    inline constexpr T min(){
        return static_cast<T>(std::numeric_limits<T>::min());
    }

    template <class T, typename U>
    inline constexpr U min(inf_int<T>& input){
        // (base^(bit length - 1) -1 / base -1)
        // ex x^7 -1 / x-1 

        if (!std::is_signed<T>()) // if the number is unsigned
            return 0;
    
        return -(valid::max<T, U>(input))-1;
    };

}


// base conversion NOTE: data types of all have to match, make sure to CAST 
template <typename T>
constexpr T base_convert(T val, const T& base_old, const T& base_new){

    if (base_old == base_new) // base case, if bases match
        return val;
    if (val == 0) // if value is 0, return 0
        return 0;

    T out = 0; // output variable
    //ONLY BASE UP FOR NOW

   

    bool negative = false; // is negative boolean
    if (val <0){
        val = -val; // makes the value positive 
        negative = true; //makes sure to flip later 
    }

    int8_t i = LEFT_BIT(val);  // i starts at leftmost bit in the value
    
    if (base_old == 2){ // if the old base is 2 (normal number to an infinite integer)
    // old conversion (only wokrs base 2 to x)
        while(val >0 && i >= 0) {
            //std::cout << val << i 
            auto minus = std::pow(base_new, i);
            if(minus <= val){
                val-=minus;
                out += 1<< i;
            }
            i--;
        }
    } else if (base_new == 2){ // if the new base is 2 (infinite int to normal number)
        while(i>=0){ // iterates through the bits in the value (O(log(n)))
            if (BIT_CHECK(val, i)) {  // if theres a bit
                auto cur = std::pow(base_old, i); // current digit value
                if(valid::add(out, cur)){
                    out+=cur;
                }
            }
            i--;
        }

    } else { // if neither base is 2

        while(i >=0){ // iterates through the bits in the value (O(log(n)) where n is the number being input) 
            if (BIT_CHECK(val, i)) { // if theres a bit at i 
                auto cur = std::pow(base_old, i); // current digit value
                int8_t bit = static_cast<int8_t>(log_base(cur, base_new)); // bit index to insert
                std::cout << (int)i << '\t' << (int)bit << '\t' << (int)cur << '\n';
                //  log base new value's actual value at a given index
                /*
                ex.
                base 3 -> 2 with value 121
                log(121, 2) = 6 (bit index 6 aka 2^6 aka 64)
                base 2 -> with value 121
                log(121, 3) = 4 (bit index 4 aka 3^4 aka 81)
                then removes that bit from the value
                */
                if (bit < sizeof(val)*8-1){ // bit index doesnt overflow

                    while(bit >= 0 && cur >0){ //iterate backwards in the bits
                        BIT_SET(out, bit); //sets bit at current
                        cur -= std::pow(base_new, bit); //substracts from current
                        bit--; // moves bit down
                    }

                    //BIT_CLEAR(val, i); //doesnt need to
                }
                //std::cout << (int)cur << '\t' << BITS(val) << '\t' << BITS(out) <<'\n';
            }
            i--;
        }   

    }

    if (negative){
        out = -out;
    }

    return out;
};

// // base conversion NOTE: data types of all have to match, make sure to CAST 
// template <typename T>
// constexpr T base_convert(T val, const T& base_cur, const T& base_new){

//     if (base_cur == base_new) // base case, if bases match
//         return val;

//     T out = 0;
//     //ONLY BASE UP FOR NOW

//     int8_t i = LEFT_BIT(val); // length of the bits


//     while(val >0 && i >= 0) {
//         //std::cout << val << i;
//         auto minus = std::pow(base_new, i);
//         if(minus <= val){
//             val-=minus;
//             out += 1<< i;
//         }
//         i--;
//     }

//     return out;
// };

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
    return;
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
    if((BIT_CHECK(this->flags_arr, NEGATIVE_SIGN))){ // if buffer is negative & output data type is signed
        if (std::is_signed<U>())
            out-= valid::max<T,U>(*this)+1;
        i--;
    } 

    while (i >= 0) { // while i is 0 or more
        

        if ((1<<i) & this->buffer) {
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
            "\nMIN:\t" + std::to_string(valid::min<T, long long>(*this)) + 
            "\n" + this->flags() + "\n";
};

template <class T>
inline std::string inf_int<T>::flags(){ // prints flags
    return  std::string("The number is: [ ") + 
            (BIT_CHECK(this->flags_arr, NEGATIVE_SIGN) ? "NEGATIVE, " : "POSITIVE, ") +
            (BIT_CHECK(this->flags_arr, BASE) ? "BASE_UP, " : "BASE_FINE, ") + 
            (BIT_CHECK(this->flags_arr, BUFFER) ? "BUFFER_UP ]" : "BUFFER_FINE ]" );

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
        BIT_SET(this->flags_arr, NEGATIVE_SIGN);
        //value ^= (1<<sizeof(value)*8-1);
        value = -value; // inverses twos compliment
    }

    // iterates until a base that can hold the number is found
    U max_val = valid::max<T, U>(*this); // temp max val variable
    while(max_val < value && max_val >0) { // keep iterating until a base that can hold the value is found or max val overflows
        BIT_SET(this->flags_arr, BASE); // flips the base bit
        BIT_SET(this->flags_arr, BUFFER); // flips the buffer bit
        this->base++; // increases the base
        max_val = valid::max<T, U>(*this); // makes new max val (with  new base)
    }


    this->buffer = base_convert<U>(value, 2, this->get_base()); // makes the buffer
    if (BIT_CHECK(this->flags_arr, NEGATIVE_SIGN)) { // if the sign is negative
        this->buffer = -this->buffer;
        //this->buffer |= sizeof(this->buffer)*8-1;
    } 



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