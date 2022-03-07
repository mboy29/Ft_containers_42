/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssou <youssou@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:18:57 by youssou           #+#    #+#             */
/*   Updated: 2021/11/14 16:15:36 by youssou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS
#define ITERATOR_TRAITS
#include <iostream>
#include <stddef.h>

namespace ft{

    template <class Iterator>
    class iterator_traits{
        public:
            typedef typename Iterator::difference_type                   difference_type;
            typedef typename Iterator::value_type                        value_type;
            typedef typename Iterator::pointer                           pointer;
            typedef typename Iterator::reference                         reference;
            typedef	typename Iterator::iterator_category                 iterator_category;
    };
    
    template <class T>
    class iterator_traits<T*>{
        public:
            typedef ptrdiff_t                                       difference_type;
            typedef T                                               value_type;
            typedef T*                                              pointer;
            typedef T&                                              reference;
            typedef	std::random_access_iterator_tag                 iterator_category;
    };
    
    template <class T>
    class iterator_traits<const T*>{
        public:
            typedef ptrdiff_t                                       difference_type;
            typedef T                                               value_type;
            typedef const T*                                              pointer;
            typedef const T&                                              reference;
            typedef	std::random_access_iterator_tag                 iterator_category;
    }; 

}

#endif