#ifndef UTILS_HPP
# define UTILS_HPP

#include "iterator.hpp"
namespace ft
{
    /* enable_if */
    template<bool B, class T = void>
    struct enable_if {};

    template<class T>
    struct enable_if<true, T> { typedef T type; };

    /* is_integral */
    template<class T>
    struct is_integral
    {
        static const bool value = false; //static const만 class 선언과 동시에 초기화될 수 있다.
    };

    template <> //템플릿 특수화를 통해 integral에 맞는 타입인지 value를 true와 false로 정할 수 있다.
    struct is_integral<bool> {static const bool value = true;};

    template <>
    struct is_integral<char> {static const bool value = true;};

    template <>
    struct is_integral<signed char> {static const bool value = true;};

    template <>
    struct is_integral<short int> {static const bool value = true;};

    template <>
    struct is_integral<int> {static const bool value = true;};

    template <>
    struct is_integral<long int> {static const bool value = true;};

    template <>
    struct is_integral<long long int> {static const bool value = true;};

    template <>
    struct is_integral<unsigned char> {static const bool value = true;};

    template <>
    struct is_integral<unsigned short int> {static const bool value = true;};

    template <>
    struct is_integral<unsigned int> {static const bool value = true;};

    template <>
    struct is_integral<unsigned long int> {static const bool value = true;};

    template <>
    struct is_integral<unsigned long long int> {static const bool value = true;};

    /* distance random iterator말고 다른 iterator가 들어왔을 때*/
    template < typename InputIt >
	typename ft::iterator_traits<InputIt>::difference_type	distance(InputIt first, InputIt last)
	{
		typename ft::iterator_traits<InputIt>::difference_type	dist = 0;
		while (first != last)
        {
			++first;
			++dist;
		}
		return dist;
	}
    
    /* equal */
    template<class InputIt1, class InputIt2>
    bool equal(InputIt1 first1, InputIt1 last1, 
            InputIt2 first2)
    {
        for (; first1 != last1; ++first1, ++first2) {
            if (!(*first1 == *first2)) {
                return false;
            }
        }
        return true;
    }
    template<class InputIt1, class InputIt2, class BinaryPredicate>
    bool equal(InputIt1 first1, InputIt1 last1, 
            InputIt2 first2, BinaryPredicate p)
    {
        for (; first1 != last1; ++first1, ++first2) {
            if (!p(*first1, *first2)) {
                return false;
            }
        }
        return true;
    }

    /* lexicographical_compare */
    template<class InputIt1, class InputIt2>
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                                InputIt2 first2, InputIt2 last2)
    {
        for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
            if (*first1 < *first2) return true;
            if (*first2 < *first1) return false;
        }
        return (first1 == last1) && (first2 != last2);
    }
    template<class InputIt1, class InputIt2, class Compare>
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                                InputIt2 first2, InputIt2 last2,
                                Compare comp)
    {
        for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
            if (comp(*first1, *first2)) return true;
            if (comp(*first2, *first1)) return false;
        }
        return (first1 == last1) && (first2 != last2);
    }

    /* pair */
    template< class T1, class T2 >
    struct pair
    {
        public:
            typedef T1 first_type;
            typedef T2 second_type;

            T1 first;
            T2 second;
        
            pair() : first(), second() {}
            pair( const T1& x, const T2& y ) : first(x), second(y) {}
            template< class U1, class U2 >
            pair( const pair<U1, U2>& p ) : first(p.first), second(p.second) {}
            pair& operator= (const pair& pr) { first = pr.first; second = pr.second; return (*this); }
    };
    template <class T1, class T2>
    pair<T1,T2> make_pair (T1 x, T2 y)  { return ( pair<T1,T2>(x,y) ); }

    template <class T1, class T2>
    bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return (lhs.first == rhs.first && lhs.second == rhs.second); }

    template <class T1, class T2>
    bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return !(lhs == rhs); }

    template <class T1, class T2>
    bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second)); }

    template <class T1, class T2>
    bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return !(rhs < lhs); }

    template <class T1, class T2>
    bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return (rhs < lhs); }

    template <class T1, class T2>
    bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    { return !(lhs < rhs); }

    enum Color
    {
        RED,
        BLACK,
        DBLACK
    };
}



#endif