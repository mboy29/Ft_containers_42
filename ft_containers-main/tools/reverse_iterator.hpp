/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcadmin <mcadmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:43:04 by sel-fadi          #+#    #+#             */
/*   Updated: 2022/01/10 00:55:07 by mcadmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <string>
#include "iterator_traits.hpp"
#include "../Vector/iterator.hpp"
#include "../Map/mapIterator.hpp"

namespace ft {
	
	template <class Iterator>
	class reverse_iterator {
		public:
			typedef Iterator iterator_type;
			typedef typename  Iterator_traits<Iterator>::iterator_category iterator_category;
			typedef typename  Iterator_traits<Iterator>::value_type value_type;
			typedef typename  Iterator_traits<Iterator>::difference_type difference_type;
			typedef typename  Iterator_traits<Iterator>::pointer pointer;
			typedef typename  Iterator_traits<Iterator>::pointer const *const_pointer;
			typedef typename  Iterator_traits<Iterator>::reference reference;
			typedef typename  Iterator_traits<Iterator>::reference const &const_reference;
			
		protected:
			iterator_type _iterator;
		public:
		
		reverse_iterator() : _iterator(iterator_type()) {};

		explicit reverse_iterator (iterator_type it) { this->_iterator = --it; };

		template< class U >
            reverse_iterator(const reverse_iterator<U>& rev_it) : _iterator(rev_it.getIter()) {}
		template< class U >
			reverse_iterator	&operator=(const reverse_iterator<U>& other) { _iterator = other.getIter(); return *this; }

		iterator_type base() const { iterator_type tmp = _iterator ; return ++tmp; }
		
		virtual ~reverse_iterator(){};
		
		iterator_type getIter() const
		{
			return this->_iterator;	
		}

		reference operator*() {return *this->_iterator;}
		
		const_pointer operator*() const  {return *this->_iterator;}

		reverse_iterator operator+(difference_type n) const {return(reverse_iterator(_iterator - n + 1));}

		reverse_iterator operator-(difference_type n) const {return(reverse_iterator(_iterator + n + 1));}
		
		reverse_iterator &operator++() {--_iterator; return *this;}

		reverse_iterator operator++(int) {reverse_iterator tmp = *this ; --_iterator; return tmp;}

		reverse_iterator &operator--() {++_iterator; return *this;}

		reverse_iterator operator--(int) {reverse_iterator tmp = *this ; ++_iterator; return tmp;}
		
		reverse_iterator &operator+=(difference_type  value) {_iterator -= value; return (*this);}
		
		reverse_iterator &operator-=(difference_type  value)	{ _iterator += value; return (*this);}

		pointer operator->() {return &*_iterator;}

		const_pointer operator->() const {return &*_iterator;}

		reference operator[](int index)	{return *(this->_iterator + index);}

		const_reference operator[](int index) const	{return *(this->_iterator + index);}

		operator reverse_iterator<const iterator_type>() const {
                return (reverse_iterator<const iterator_type>(_iterator));
            }
	};
	
	template < class T >
		bool operator== (const reverse_iterator<T>& lhs, const reverse_iterator<T>& rhs) { return lhs.base() == rhs.base(); }
	template < class T >
		bool operator!= (const reverse_iterator<T>& lhs, const reverse_iterator<T>& rhs) { return !operator==(lhs, rhs); }
	template < class T >
		bool operator<  (const reverse_iterator<T>& lhs, const reverse_iterator<T>& rhs) { return lhs.base() > rhs.base(); }
	template < class T >
		bool operator>  (const reverse_iterator<T>& lhs, const reverse_iterator<T>& rhs) { return lhs.base() < rhs.base(); }
	template < class T >
		bool operator<=  (const reverse_iterator<T>& lhs, const reverse_iterator<T>& rhs) { return lhs.base() >= rhs.base(); }
	template < class T >
		bool operator>=  (const reverse_iterator<T>& lhs, const reverse_iterator<T>& rhs) { return lhs.base() <= rhs.base(); }
	
	template <class Iterator>
		reverse_iterator<Iterator> operator+ ( typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
		{ return (rev_it + n);	}
		
	template <class Iterator>
		typename reverse_iterator<Iterator>::difference_type operator- ( const reverse_iterator<Iterator>& lhs,  const reverse_iterator<Iterator>& rhs)
		{return (rhs.base() - lhs.base()); }
}