
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

// unsinged 
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
        if (input.base ==2) {
            return valid::max<T>();
        }

        return static_cast<U>((std::pow(input.get_base(), sizeof(input.buffer)*8-((std::is_signed<T>()) ? 1 : 0)))/(input.get_base()-1));
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


    inline constexpr auto log_base(const auto& val, const auto& base){
        return log2(val) / log2(base); 
    }

}



// base conversion NOTE: data types of all have to match, make sure to CAST 
// function has a safety option for value_safe function 
template <typename T, typename U>
constexpr T base_convert(U val, const T& base_old, const T& base_new){

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
    double divide = valid::log_base(base_new, base_old); // log base new (old), constant here
    
    while(val >0){ // iterates through the bits in the value (O(log(n)) where n is the number being input) 
            double sum = 0; // sum of inverted powers
            U curr = val; // current value
            int8_t j = i; // starts at the same index as i (highest power of value)
            while(curr){ // log(n) runtime
                sum += std::pow(base_old,j-i); //adds negative powers 
                BIT_CLEAR(curr, j); //clears the bit 
                j = LEFT_BIT(curr); // j is left bit
            }
            //std::cout << (int)i << '\t' << bit << '\n';
            BIT_SET(out, (uint8_t)((valid::log_base(sum, base_old)+i)/divide));
           
            BIT_CLEAR(val, i); //iterate
            i = LEFT_BIT(val);
    }

    if (negative){ //if negative number
        out = -out;
    }

    return out;
};


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
    //cout << ((std::is_signed<T>::value) ? input.template value<int>() : input.template value<unsigned int>());
    cout << input.template value<int>();
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


    // CONSTRUCTORS

    inf_int(); //empty (0)
    template <typename U>
    inf_int(U value); // initialized value

    template <class U>
    inf_int(inf_int<U>& init_val); // initialized with another infinite integer 




    // FUNCTIONS    

    template <typename U>
    inline U value(); // gets the value from buffer

    template <typename U>
    inline U value_safe(); // gets the value from buffer but SAFE (throws an error)

    inline std::vector<T> value(); // returns value as a vector

    template<typename U>
    inline U get_buffer(); // gets the buffer but with a data type

    inline T get_buffer(); // outs the buffer in a data type

    template<typename U>
    inline U get_base(); // gets the base but with a data type

    inline uT get_base(); // gets the base

    inline std::string info(); // prints info

    template<typename U>
    inline void base_convert(const U& base_new);



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
    friend inf_int<T> operator+(inf_int<T> out, U value) {
        if (value == 0){ //if the value is 0, nothing to add
            return out; 
        }

         uT temp_base = out.get_base();
         T temp_buffer = out.buffer;
         U temp_val = ::base_convert<U>(value,2, temp_base);
         while(!valid::add(temp_buffer, temp_val)){
             temp_base++;
             temp_buffer = ::base_convert<T>(out.buffer, out.get_base(), temp_base);
             temp_val = ::base_convert<U>(value, 2, temp_base);
        }; 
         
         for (int8_t i = LEFT_BIT((temp_buffer & temp_val)); i >= 0; i--) // fills the bits tangled before way bigger ones
         {
             BIT_SET(out.buffer, i);
         }

         out.buffer = temp_buffer | temp_val;
         out.base = temp_base; 
        
        
        return out;
    }


    template<class U>
    friend inf_int<T> operator+(inf_int<T> out, const inf_int<U>& value) { //adds another infinite integer
        if (value.buffer == 0){ // if the value is 0, nothing to add
            return out;
        }

        uT temp_base = std::max(out.get_base(), value.base);
        T temp_buffer = ::base_convert<T>(out.buffer, out.get_base(), temp_base);
        U temp_val = ::base_convert<U>(value.buffer, value.base, temp_base);

        while(!valid::add(temp_buffer, temp_val)){
            temp_base++;
            temp_buffer = ::base_convert<T>(out.buffer, out.get_base(), temp_base);
            temp_val = ::base_convert<U>(value.buffer, value.base, temp_base);
        }


        for (int8_t i = LEFT_BIT((temp_buffer & temp_val)); i >= 0; i--) // fills the bits tangled before way bigger ones
        {
            BIT_SET(out.buffer, i);
        }
        
        out.buffer = temp_buffer | temp_val;
        out.base = temp_base; 


        return out;
    }; 


    
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
    return;
};


template <class T>
template <class U>
inf_int<T>::inf_int(inf_int<U>& init_val):
buffer(init_val.get_buffer()),
base(init_val.get_base())
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
inline U inf_int<T>::get_base(){
    return static_cast<U>(this->base);
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
    
    return ::base_convert<U>(this->buffer, this->base, 2);
};

template <typename T>
template <typename U>
// convert ONLY if it's safe to do so
inline U inf_int<T>::value_safe() { // returns the value but safely


    if (this->buffer<0){
        if (-std::pow(this->base, LEFT_BIT(-this->buffer)) < valid::min<U>()){
            throw std::invalid_argument("Value underflow. Consider putting the value in a bigger data type. Value in question:" + this->info());
        } 
    } else {
        if (std::pow(this->base, LEFT_BIT(this->buffer)) > valid::max<U>()){
            throw std::invalid_argument("Value overflow. Consider putting the value in a bigger data type. Value in question:" + this->info());

        }
    }

    return ::base_convert<U>(this->buffer, this->base, 2);

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
            "\n";
};

template <class T>
template<typename U>
inline void inf_int<T>::base_convert(const U& base_new){
    this->buffer = ::base_convert<T>(this->buffer, this->base, base_new);
    this->base = static_cast<uT>(base_new);
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

    if(!value) return *this; // base case, if 0 
    
    bool negative = false;
    if (value <0 ){ // if value is negative (signed)
        negative = true;
        value = -value; // inverses twos compliment
    }


    // iterates until suitable base is found
    while(valid::log_base(value, this->base) >= sizeof(T)*8-((std::is_signed<T>()) ? 1 : 0)){
        this->base++;
    }
    this->buffer = ::base_convert<T>(value, 2, this->base);


    if (negative){ // if the buffer is tagges as negative, flips the sign
        this->buffer = -this->buffer; 
    }

    return *this;
}; 

template<class T>
template<class U>
inf_int<T>& inf_int<T>::operator=(inf_int<U>& value){
    this->base = value.get_base();
    this->buffer = value.get_buffer();
    
    //TODO: add checking to make sure the base itself isnt an inf int
    return *this;
}; 





#endif //__INF_INT_H__