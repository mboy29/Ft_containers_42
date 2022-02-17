#ifndef INTEGRAL_HPP
# define INTEGRAL_HPP

//  -----------------------------IS INTEGRAL---------------------------------
//    -> Class template
//    Trait class that identifies whether T is an integral type.
//    Inherits from integral_constant as being either true_type or
//    false_type
//  -------------------------------------------------------------------------

namespace ft 
{
	//  ------------------------INTEGRAL CONSTANT----------------------------
	//    -> Class template
	//    Provides compile-time constants as types
	//  ---------------------------------------------------------------------

	template <class T, bool val>
		struct integral_constant {
			static const	bool 									value = val;
			typedef 		T										value_type;
			typedef 		integral_constant<value_type, value>	type;
			operator 		value_type(void) { return (value); }
		};
	
	//  ---------------------------IS INTEGRAL-------------------------------
	
	template <class T>  //  False_type :
		struct is_integral : public integral_constant<T, false> {};
	
	template <class T> //  True_type :
		struct is_integral<const T> : is_integral<T> {};
	
	
	template <> //  Bool - true :
		struct is_integral<bool> : public integral_constant<bool, true> {};
	
	template <> //  Char - true :
		struct is_integral<char> : public integral_constant<char, true> {};
	
	template <> //  Wchar_t - true :
		struct is_integral<wchar_t> : public integral_constant<wchar_t, true> {};
	
	template <> //  Signed char - true :
		struct is_integral<signed char> : public integral_constant<signed char, true> {};
	
	template <> //  Short int - true :
		struct is_integral<short int> : public integral_constant<short int, true> {};
	
	template <> //  Int - true :
		struct is_integral<int> : public integral_constant<int, true> {};
	
	template <> //  Long int - true :
		struct is_integral<long int> : public integral_constant<long int, true> {};
	
	template <> //  Long long int - true :
		struct is_integral<long long int> : public integral_constant<long long int, true> {};
	
	template <> //  Unsigned char - true :
		struct is_integral<unsigned char> : public integral_constant<unsigned char, true> {};
	
	template <> //  Unsigned short int - true :
		struct is_integral<unsigned short int> : public integral_constant<unsigned short int, true> {};
	
	template <> //  Unsigned int - true :
		struct is_integral<unsigned int> : public integral_constant<unsigned int, true> {};
	
	template <> //  Unsigned long int - true :
		struct is_integral<unsigned long int> : public integral_constant<unsigned long int, true> {};
	
	template <> //  Unsigned long long int - true :
		struct is_integral<unsigned long long int> : public integral_constant<unsigned long long int, true> {};
}

#endif