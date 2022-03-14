/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcadmin <mcadmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 23:08:20 by sel-fadi          #+#    #+#             */
/*   Updated: 2022/01/11 02:50:17 by mcadmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>
# include <stdlib.h>
# include <string>

namespace ft
{
	template < class T1, class T2 > struct pair {
		public:
			typedef T1 first_type;	
			typedef T2 second_type;
			
			pair() : first(), second() {};
			
			pair ( const first_type &a, const second_type &b ) : first(a), second(b) {};
			
			template<class U, class V> 
			pair ( const pair<U, V>& pai ) : first(pai.first), second(pai.second) {};
			
			pair& operator= ( const pair& pai )
			{
				if (this != &pai)
				{
					this->first = pai.first;
					this->second = pai.second;
				}
				return *this;
			}
			~pair() {}

			first_type first;
			second_type second;
	};


	template <class T1,class T2>
	ft::pair<T1,T2> make_pair (T1 x, T2 y)
	{
		return ( ft::pair<T1,T2>(x,y) );
	}
	
	template <class T1, class T2>
	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return lhs.first==rhs.first && lhs.second==rhs.second; }

	template <class T1, class T2>
	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(lhs==rhs); }

	template <class T1, class T2>
	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

	template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(rhs<lhs); }

	template <class T1, class T2>
	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return rhs<lhs; }

	template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(lhs<rhs); }
}