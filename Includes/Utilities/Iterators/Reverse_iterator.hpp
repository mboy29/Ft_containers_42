/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:31:43 by mboy              #+#    #+#             */
/*   Updated: 2022/03/23 13:31:53 by mboy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

//  --------------------------REVERSE ITERATORS---------------------------
//    -> Class Template
//    This class reverses the direction in which a bidirectional or
//    random-access iterator iterates through a range.
//  ----------------------------------------------------------------------

//  --------------------------INTERNAL LIBRARIES-------------------------

# include "Iterator.hpp"  //  Iterator

namespace ft
{
	template <class Iterator>
		class reverse_iterator {
	
			//  ----------------------MEMBER TYPES------------------------
		
			public:
				typedef Iterator													iterator_type;
				typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
				typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
				typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
				typedef typename ft::iterator_traits<Iterator>::reference			reference;
				typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
			protected:
				Iterator		_iterator;

			//  ---------------------MEMBER FUNCTIONS---------------------

			public:
				
				//  ----------------------CONSTRUCTOR---------------------
				
				reverse_iterator(void) : _iterator() {}
				explicit reverse_iterator (iterator_type const it) : _iterator(it) {}
				template <class It>
					reverse_iterator (reverse_iterator<It> const &rev_it) : _iterator(rev_it.base()) {}
				
				//  ----------------------DESTRUCTOR----------------------

				virtual ~reverse_iterator() {}

				//  -------------------------BASE-------------------------
			
				iterator_type 		base(void) const { return (this->_iterator); } 
				
				//  -------------------CONVERT TO CONST-------------------

				operator reverse_iterator<const Iterator>(void) const {
					reverse_iterator<const Iterator>	tmp(this->_iterator);
					return (tmp);
				}

				//  ------------------ASSIGNMENT OPERATOR-----------------

				//  Operator=
				template<class It> 
					reverse_iterator	&operator=(reverse_iterator<It> const &rhs) {
						if (*this != rhs)
							this->_iterator = rhs.base();
						return (*this);
					}

				//  -----------------DEREFERENCE OPERATOR-----------------

				//  Operator*
				reference operator*(void) {
					iterator_type tmp = this->_iterator;
					return *(--tmp);
				}
				
				const reference operator*(void) const {
					iterator_type tmp = this->_iterator;
					return *(--tmp);
				}

				//  Operator->
				pointer				operator->(void) const { 
					iterator_type	tmp = this->_iterator;
					return &(*(--tmp));
				}

				//  Operator[] :
				reference			operator[](difference_type n) { return (*(this->_iterator - n - 1)); }
				const reference		operator[](difference_type n) const { return (*(this->_iterator - n - 1)); }
				

				//  ------------------INCREMENT OPERATOR------------------

				reverse_iterator&	operator++(void) { //  Operator++ -> post-incrementatio,
					this->_iterator--;
					return (*this);
				}

				reverse_iterator	operator++(int) { //  Operator++ -> pre-incrementatio
					reverse_iterator	tmp(*this);
					this->_iterator--;
					return (tmp);
				}

				//  ------------------DECREMENT OPERATOR------------------

				reverse_iterator&	operator--(void) { //  Operator-- -> post-incrementation
					this->_iterator++;
					return (*this);
				}
			
				reverse_iterator	operator--(int) { //  Operator-- -> pre-incrementation
					reverse_iterator	tmp(*this);
					this->_iterator++;
					return (tmp);
				}

				//  -----------------ARITHMETIC OPERATOR------------------

				reverse_iterator	operator+(difference_type n) const { //  Operator+
					reverse_iterator	tmp(*this);
					tmp._iterator -= n;
					return (tmp);
				}

				reverse_iterator	operator-(difference_type n) const { //  Operator-
					reverse_iterator	tmp(*this);
					tmp._iterator += n;
					return (tmp);
				}

				difference_type		operator-(reverse_iterator rhs) { return (rhs._iterator - this->_iterator); } //  For operator[]  

				//  -------------COMPOUND ASSIGNMENT OPERATOR--------------
			
				reverse_iterator&	operator+=(difference_type n) { //  Operator+=
					this->_iterator -= n;
					return (*this);
				}

				reverse_iterator&	operator-=(difference_type n) { //  Operator-=
					this->_iterator += n;
					return (*this);
				}

		};
				
		//  ----------------NON-MEMBER FUNCTIONS OVERLOAD-----------------

		template <class Iterator1, class Iterator2> //  Operator==
			bool operator==(reverse_iterator<Iterator1> const &lhs, reverse_iterator <Iterator2> const &rhs) {
				return (lhs.base() == rhs.base());
			}

		template <class Iterator1, class Iterator2> //  Operator!=
			bool operator!=(reverse_iterator<Iterator1> const &lhs, reverse_iterator <Iterator2> const &rhs) {
				return (!(lhs == rhs));
			}

		template <class Iterator1, class Iterator2> //  Operator<
			bool operator<(reverse_iterator<Iterator1>const &lhs, reverse_iterator <Iterator2> const &rhs) {
				return (lhs.base() > rhs.base());
			}

		template <class Iterator1, class Iterator2> //  Operator<=
			bool operator<=(reverse_iterator<Iterator1> const &lhs, reverse_iterator <Iterator2> const &rhs) {
				return (!(lhs > rhs));
			}

		template <class Iterator1, class Iterator2> //  Operator>
			bool operator> (reverse_iterator<Iterator1> const &lhs, reverse_iterator <Iterator2> const &rhs) {
				return (rhs < lhs);
			}

		template <class Iterator1, class Iterator2> //  Operator>=
			bool operator>=(reverse_iterator<Iterator1> const &lhs, reverse_iterator <Iterator2> const &rhs) {
				return (!(lhs < rhs));
			}
		
		

		//  ------------------NON-MEMBER FUNCTIONS OPERATORS------------------
		
		template <typename Iterator> //  Operator+ -> rit + rit
			reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it) { return (rev_it + n); }
		
		template <typename Iterator> //  Operator- -> rit - rit
			typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (rhs - lhs); }

}

#endif
