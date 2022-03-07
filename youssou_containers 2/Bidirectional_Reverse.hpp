/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bidirectional_Reverse.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssou <youssou@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 16:20:57 by youssou           #+#    #+#             */
/*   Updated: 2021/12/14 10:09:05 by youssou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIDIRECTIONAL_REVERSE_HPP
#define BIDIRECTIONAL_REVERSE_HPP

#include <stddef.h>
#include <iostream>
#include "RedBlackTree.hpp"
#include "Iterator_traits.hpp"

namespace ft
{
	template <class Iterator>
	class bidirectional_reverse {

		public:
		
			typedef Iterator                                                             iterator_type;
			typedef typename ft::iterator_traits<Iterator>::iterator_category            iterator_category;
			typedef typename ft::iterator_traits<Iterator>::value_type                   value_type;
			typedef typename ft::iterator_traits<Iterator>::pointer                      pointer;
			typedef typename ft::iterator_traits<Iterator>::reference                    reference;

			
			bidirectional_reverse() : _iterator(0){ }
			
			explicit bidirectional_reverse (const iterator_type it){
				_iterator = it;
				_base = it;
			}

			bidirectional_reverse &operator=(const bidirectional_reverse &rhs){
				this->_iterator = rhs._iterator;
				return (*this);
			}

			~bidirectional_reverse(){ return; }
			
			template <class Iter>
			bidirectional_reverse (const bidirectional_reverse<Iter>& rev_it)  {
				_iterator = rev_it.base();
			}
			
			operator bidirectional_reverse<const Iterator>() const {
				bidirectional_reverse<const Iterator> temp(this->_ptr_t);
				return (temp);
			}
			
			bidirectional_reverse(const bidirectional_reverse &copy){
				*this = copy;
			}
		

			bidirectional_reverse& operator++(){
				this->_iterator--;
				return (*this);
			}
		
			bidirectional_reverse  operator++(int){
				bidirectional_reverse temp = *this;
				++(*this);
				return (temp);
			}
			
			bidirectional_reverse &operator++() const {
				(*this)++;
				return (*this);
			}

			bidirectional_reverse& operator--(){
				this->_iterator++;
				return (*this);
			}

			bidirectional_reverse  operator--(int){
				bidirectional_reverse temp = *this;
				--(*this);
				return temp;
			}

			typename Iterator::pair_value *operator->() const{
				return ((_iterator - 1).operator->());
			}

			typename Iterator::pair_value &operator*() const{
                return (*(this->operator->()));
            }
			
			Iterator base() const{
				return (_iterator);
			}

			private:
				iterator_type    _iterator;
				iterator_type    _base;
	};

   template <class Iterator, class T>
	bool operator== (const bidirectional_reverse<Iterator>& lhs, const bidirectional_reverse<T>& rhs){
		return (lhs.base() == rhs.base());
	}

	template <class Iterator, class T>
	bool operator!= (const bidirectional_reverse<Iterator>& lhs, const bidirectional_reverse<T>& rhs){
		return (lhs.base() != rhs.base());
	}

}





#endif