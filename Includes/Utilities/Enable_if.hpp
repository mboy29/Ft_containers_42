#ifndef ENABLE_IF_HPP
# define ENABLE_IF_HPP

//  -----------------------------ENABLE_IF-------------------------------
//    -> Class Template
//    The type T is enabled as member type enable_if::typeif Cond is
//    true. Otherwise, enable_if::type is not defined.
//  ---------------------------------------------------------------------

namespace ft
{
	template<bool Cond, class T = void> struct enable_if {};
    template<class T> struct enable_if<true, T> {
		typedef T type;
	};
}

#endif