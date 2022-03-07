/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssou <youssou@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 11:12:46 by youssou           #+#    #+#             */
/*   Updated: 2021/12/01 16:31:51 by youssou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft{

    
    /**      Lexicographic compare       **/
    template <class InputIterator1, class InputIterator2>
    bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2){
        while (first1 != last1){
            if (first2 == last2 || *first2 < *first1)
                return (false);
            else if (*first1 < *first2) 
                return (true);
            ++first1; ++first2;
        }
        return (first2 != last2);
    }

    /**    Enable_if     **/
    template<bool, class T = void>
    struct enable_if {};

    template<class T>
    struct enable_if<true, T> { typedef T type; };

    /**    Is integral    **/
    template <class T, T v>
    struct integral_constant {
    static const T value = v;
        typedef T value_type;
        typedef integral_constant<T,v> type;
        operator T() { return v; }
    };

    typedef integral_constant<bool, true>  true_type;
    typedef integral_constant<bool, false> false_type;

    template <class T> 
    struct is_integral : false_type {};
    
    template <> 
    struct is_integral<int> : true_type {};
    
    template <> 
    struct is_integral<bool> : true_type {};

    template <> 
    struct is_integral<char16_t> : true_type {};

    template <> 
    struct is_integral<char32_t> : true_type {};

    template <> 
    struct is_integral<wchar_t> : true_type {};

    template <> 
    struct is_integral<signed char> : true_type {};

    template <> 
    struct is_integral<short int> : true_type {};

    template <> 
    struct is_integral<long int> : true_type {};

    template <> 
    struct is_integral<long long int> : true_type {};

    template <> 
    struct is_integral<unsigned char> : true_type {};
    
    template <> 
    struct is_integral<unsigned short int> : true_type {};

    template <> 
    struct is_integral<unsigned int> : true_type {};

    template <> 
    struct is_integral<unsigned long int> : true_type {};

    template <> 
    struct is_integral<unsigned long long int> : true_type {};

    /** Pair **/
    template <class T1, class T2>
    struct pair{
        
        public:
            typedef T1              first_type;
            typedef	T2              second_type;

            pair(){}

            template<class U, class V> 
            pair (const pair<U,V>& pr) : first(pr.first), second(pr.second) {}
            
            pair (const first_type& a, const second_type& b) : first(a), second(b){}
                

            pair& operator= (const pair& pr){
                this->first = pr.first;
                this->second = pr.second;
                return (*this);
            }
            

        public:
            first_type  first;
            second_type second;
    };
    
    template<class T1, class T2>
    ft::pair<T1, T2> make_pair(T1 arg1, T2 arg2){
        ft::pair<T1, T2> _pair(arg1, arg2);
        return (_pair);
    }
    
    template <class T1, class T2>
    bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs){ 
        return (lhs.first == rhs.first && lhs.second == rhs.second);
    }

    template <class T1, class T2>
    bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs){ 
        return (!(lhs == rhs)); 
    }

    template <class T1, class T2>
    bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs){ 
        if (lhs.first > rhs.first)
            return (false);
        return (lhs.first < rhs.first || lhs.second < rhs.second);
    }

    template <class T1, class T2>
    bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs){ 
        return (lhs < rhs || rhs == lhs);
    }

    template <class T1, class T2>
    bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs){ 
        return (!(lhs < rhs) && rhs == lhs); 
    }

    template <class T1, class T2>
    bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs){ 
        return (!(lhs < rhs) || rhs == lhs);
    }


    /**    Enable_if     **/
    template<bool, class T = void, class B = void>
    struct condition {};

    template<class T, class B>
    struct condition<true, T, B> { typedef T type; };

    template<class T, class B>
    struct condition<false, T, B> { typedef B type; };


}



#endif