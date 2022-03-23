/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:31:13 by mboy              #+#    #+#             */
/*   Updated: 2022/03/23 13:31:14 by mboy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

//  -------------------------PAIR RE-IMPLATATION-------------------------
//    -> Class Template
//    A pair couples together a pair of values, which may be of
//    different types (First and Second). The individual values can be
//    accessed through its public members first and second.
//  ---------------------------------------------------------------------

namespace ft 
{
	//  ---------------------------CLASS---------------------------------
	
	template <class First, class Second>
		struct pair {

			//  ---------------------MEMBER TYPES------------------------
			
			typedef First	first_type;
			typedef Second	second_type;

			first_type		first;
			second_type		second;

			//  --------------------MEMBER FUNCTION----------------------

			//  ---------------------CONSTRUCTOR-------------------------

			//  Default constructor :
			pair(void) : first(), second() {};

			//  Copy constructor:
			template <class U, class V>
				pair(const pair<U, V> &rhs) : first(rhs.first), second(rhs.second){};

			//  Fill constructor:
			pair(const first_type &rhs, const second_type &lhs) : first(rhs), second(lhs){};
			
			//  -------------------ASSIGN OPERATOR-------------------

			//  Operator= :
			pair &operator=(pair const &rhs)  {
				if (this != &rhs) {
					this->first = rhs.first;
					this->second = rhs.second;
				}
				return (*this);
			}
		};

	//  ----------------NON-MEMBER FUNCTIONS OVERLOADS---------------
		
		//  -------------------RATIONAL OPERATORS--------------------
		
		//  Operator== :
		template <class First, class Second>
			bool operator==(pair<First, Second> const &rhs, pair<First, Second> const &lhs) {
				return (rhs.first == lhs.first && rhs.second == lhs.second);
			}

		//  Operator!= :
		template <class First, class Second>
			bool operator!=(pair<First, Second> const &rhs, pair<First, Second> const &lhs) {
				return (!(rhs == lhs));
			}

		//  Operator< :
		template <class First, class Second>
			bool operator<(pair<First, Second> const &rhs, pair<First, Second> const &lhs) {
				return (rhs.first < lhs.first || (!(lhs.first < rhs.first) && rhs.second < lhs.second));
			}

		//  Operator<= :
		template <class First, class Second>
		bool operator<=(pair<First, Second> const &rhs, pair<First, Second> const &lhs) {
			return (!(lhs < rhs));
		}

		//  Operator> :
		template <class First, class Second>
		bool operator>(pair<First, Second> const &rhs, pair<First, Second> const &lhs) {
			return (lhs < rhs);
		}

		//  Operator>= :
		template <class First, class Second>
		bool operator>=(pair<First, Second> const &rhs, pair<First, Second> const &lhs) {
			return (!(rhs < lhs));
		}

		//  ------------------------MAKE PAIR------------------------

		//  Make pair :
		template <class First, class Second>
		pair<First, Second> make_pair(First rhs, Second lhs) { return (pair<First, Second>(rhs, lhs)); }

}

#endif
