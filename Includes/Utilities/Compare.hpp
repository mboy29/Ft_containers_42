/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Compare.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:30:59 by mboy              #+#    #+#             */
/*   Updated: 2022/03/23 13:31:00 by mboy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPARE_HPP
# define COMPARE_HPP

//  -----------------------COMPARE RE-IMPLATATION------------------------
//    -> Function Template
//    Returns true if the range [first1,last1) compares
//    lexicographically less than the range [first2, last2).
//  ---------------------------------------------------------------------

namespace ft
{
	//  Default lexicographical compare :
	template <class It1, class It2>
		bool lexicographical_compare(It1 first1, It1 last1, It2 first2, It2 last2) {
			while (first1 != last1) {
				if (first2 == last2 || *first2 < *first1)
					return (false);
				else if (*first1 < *first2)
					return (true);
				++first1;
				++first2;
			}
			return (first2!=last2);
		}

	//  Lexicographical compare with compare value:
	template <class It1, class It2, class Compare>
		bool lexicographical_compare(It1 first1, It1 last1, It2 first2, It2 last2, Compare comp) {
			while (first1 != last1) {
				if (first2 == last2 || comp(*first2, *first1))
					return (false);
				else if (comp(*first1, *first2))
					return (true);
				++first1;
				++first2;
			}
			return (first2 != last2);
		};
}


#endif
