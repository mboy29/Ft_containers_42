/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:30:55 by mboy              #+#    #+#             */
/*   Updated: 2022/03/23 13:30:56 by mboy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP

//  ---------------------------EQUAL ALGORITHM-------------------------------
//    -> Function template
//    Compares the elements in the range [first1,last1) with those in
//    the range beginning at first2, and returns true if all of the
//    elements in both ranges match.
//  -------------------------------------------------------------------------

namespace ft
{
	//  ----------------------------EQUALITY---------------------------------

	template <class It1, class It2>
		bool equal(It1 first1, It1 last1, It2 first2) {
			while (first1 != last1) {
				if (!(*first1++ == *first2++))
					return (false);
			}
			return (true);
		}

	//  ----------------------------PRETICATE---------------------------------
	//    -> Function template
	//    Pret is a binary function pointer or oject that accepts two
	//    elements and returns a  value convertible to bool.
	//    The value returned indicates whether the elements are considered to
	//    match in the context of this function.
	//  ----------------------------------------------------------------------

	template <class It1, class It2, class BinaryPredicate>
		bool equal (It1 first1, It1 last1, It2 first2, BinaryPredicate pred) {
			while (first1 != last1) {
				if (!pred(*first1++, *first2++))
					return (false);
			}
			return (true);
		}
}

#endif
