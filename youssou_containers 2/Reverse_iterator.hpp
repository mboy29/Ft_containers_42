/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssou <youssou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:10:26 by youssou           #+#    #+#             */
/*   Updated: 2021/11/28 14:58:50 by youssou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR
#define REVERSE_ITERATOR

#include "Iterator_traits.hpp"

namespace ft{


		template <class Iterator>
		class reverse_iterator{
			
			public:
				typedef Iterator                                                             iterator_type;
				typedef typename ft::iterator_traits<Iterator>::iterator_category            iterator_category;
				typedef typename ft::iterator_traits<Iterator>::value_type                   value_type;
				typedef typename ft::iterator_traits<Iterator>::difference_type              difference_type;
				typedef typename ft::iterator_traits<Iterator>::pointer                      pointer;
				typedef typename ft::iterator_traits<Iterator>::reference                    reference;
				
				reverse_iterator() : _iterator(0){ }
				
				explicit reverse_iterator (const iterator_type it) : _iterator(it - 1){
				}
				
				template <class Iter>
				reverse_iterator (const reverse_iterator<Iter>& rev_it) : _iterator(rev_it.base() - 1) {
					
				}

				reverse_iterator &operator=(const reverse_iterator &rhs){
					if (*this != rhs)
						this->_iterator = rhs._iterator;
					return (*this);
				}
			
				iterator_type base() const{
					return (this->_iterator + 1);
				}
				
				reference operator*() const{
					iterator_type le_K = this->_iterator;
					return (*(le_K));
				}

				reverse_iterator operator+ (difference_type n) const{
					reverse_iterator temp(base() - n);
					return (temp);
				}

				reverse_iterator& operator++(){
					this->_iterator--;
					return (*this);
				}
 
				reverse_iterator  operator++(int){
					reverse_iterator temp = *this;
					++(*this);
					return temp;
				}

				reverse_iterator& operator+= (difference_type n){
					this->_iterator = _iterator - n;
					return (*this); 
				}

				reverse_iterator operator- (difference_type n) const{
					reverse_iterator temp(base() + n);
					return (temp); 
				}

				reverse_iterator& operator--(){
					this->_iterator++;
					return (*this);
				}
 
				reverse_iterator  operator--(int){
					reverse_iterator temp = *this;
					--(*this);
					return temp;
				}
				
				reverse_iterator& operator-= (difference_type n){
					this->_iterator = _iterator + n;
					return (*this); 
				}

				pointer operator->() const{
					return (_iterator.operator->());
				}

				reference operator[] (difference_type n) const{
					return (*(this->_iterator - n));
				}

			private:
				iterator_type    _iterator;
		};
		
		template <class Iterator>
		reverse_iterator<Iterator> operator- (const reverse_iterator<Iterator>& rev_it, typename reverse_iterator<Iterator>::difference_type n){
			return (reverse_iterator<Iterator>(rev_it.base() + n));
		}
		
		template <class Iterator>
		reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it){
			return (reverse_iterator<Iterator>(rev_it.base() - n));
		}

		template <class Iterator, class T>
		typename reverse_iterator<Iterator>::difference_type operator- (const reverse_iterator<Iterator>& lhs, const reverse_iterator<T>& rhs){
			return (rhs.base() - lhs.base());
		}

		template <class Iterator, class T>
		bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<T>& rhs){
			return (lhs.base() == rhs.base());
		}

		template <class Iterator, class T>
		bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<T>& rhs){
			return (lhs.base() != rhs.base());
		}

		template <class Iterator, class T>
		bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<T>& rhs){
			return (lhs.base() >= rhs.base());
		}

		template <class Iterator, class T>
		bool operator>  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<T>& rhs){
			return (lhs.base() < rhs.base());
		}

		template <class Iterator, class T>
		bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<T>& rhs){
			return (lhs.base() <= rhs.base());
		}
		
		template <class Iterator, class T>
		bool operator< (const reverse_iterator<Iterator>& lhs, const reverse_iterator<T>& rhs){
			return (lhs.base() > rhs.base());
		}
	
}





#endif