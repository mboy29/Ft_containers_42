/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:31:02 by mboy              #+#    #+#             */
/*   Updated: 2022/03/23 13:31:04 by mboy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENABLE_IF_HPP
# define ENABLE_IF_HPP

//  -----------------------------ENABLE_IF-------------------------------
//    -> Class Template
//    The type T is enabled as member type enable_if::typeif Cond is
//    true. Otherwise, enable_if::type is not defined.
//  ---------------------------------------------------------------------

namespace ft
{
	//  Default struct :
	template<bool Cond, class T = void> struct enable_if {};
    
	//  True struct :
	template<class T> struct enable_if<true, T> {
		typedef T type;
	};
}

#endif
