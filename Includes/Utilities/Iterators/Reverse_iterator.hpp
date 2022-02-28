#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP
# include "Iterator.hpp"

//  --------------------------REVERSE ITERATORS---------------------------
//    -> Class Template
//    This class reverses the direction in which a bidirectional or
//    random-access iterator iterates through a range.
//  ----------------------------------------------------------------------

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
				iterator_type		_iterator;

			//  ---------------------MEMBER FUNCTIONS---------------------

			public:
				
				//  ----------------------CONSTRUCTOR---------------------
			
				reverse_iterator(void) : _iterator(NULL) {}
				explicit reverse_iterator (iterator_type const it) : _iterator(it - 1) {}
				template <class It>
					reverse_iterator (reverse_iterator<It> const &rev_it) : _iterator(rev_it.base() - 1) {}
				
				//  -------------------------BASE-------------------------
			
				iterator_type 		base(void) const { return (this->_iterator + 1); } 
				
				//  -------------------CONVERT TO CONST-------------------

				operator reverse_iterator<const Iterator>(void) const {
					reverse_iterator<const Iterator>	tmp(this->_iterator);
					return (tmp);
				}

				//  ------------------ASSIGNMENT OPERATOR-----------------

				//  Operator=
				reverse_iterator	&operator=(reverse_iterator const &rhs) {
					if (*this != rhs)
						this->_iterator = rhs._iterator;
					return (*this);
				}

				//  -----------------DEREFERENCE OPERATOR-----------------

				//  Operator*
				reference 			operator*(void) const {
					iterator_type	tmp = this->_iterator;
					return (*(tmp));
				}

				//  Operator->
				pointer				operator->(void) const { return (this->_iterator.operator->()); }

				//  Operator[]
				reference			operator[](difference_type n) const { return (*(this->_iterator - n)); }
				

				//  ------------------INCREMENT OPERATOR------------------

				reverse_iterator&	operator++(void) { //  Operator++
					this->_iterator -= 1;
					return (*this);
				}

				reverse_iterator	operator++(int) { //  Operator++
					reverse_iterator	tmp = *this;
					++(*this);
					return (tmp);
				}

				//  ------------------DECREMENT OPERATOR------------------

				reverse_iterator&	operator--(void) { //  Operator--
					this->_iterator += 1;
					return (*this);
				}
			
				reverse_iterator	operator--(int) { //  Operator--
					reverse_iterator	tmp = *this;
					--(*this);
					return (tmp);
				}
				//  -----------------ARITHMETIC OPERATOR------------------

				reverse_iterator	operator+(difference_type n) const { //  Operator+
					reverse_iterator	tmp(this->base() - n);
					return (tmp);
				}

				reverse_iterator	operator-(difference_type n) const { //  Operator-
					reverse_iterator	tmp(this->base() + n);
					return (tmp);
				}

				//  -------------COMPOUND ASSIGNMENT OPERATOR--------------
			
				reverse_iterator&	operator+=(difference_type n) { //  Operator+=
					this->_iterator = this->_iterator - n;
					return (*this);
				}

				reverse_iterator&	operator-=(difference_type n) { //  Operator-=
					this->_iterator = this->_iterator + n;
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
				return (lhs.base() != rhs.base());
			}

		template <class Iterator1, class Iterator2> //  Operator<
			bool operator<(reverse_iterator<Iterator1>const &lhs, reverse_iterator <Iterator2> const &rhs) {
				return (lhs.base() > rhs.base());
			}

		template <class Iterator1, class Iterator2> //  Operator<=
			bool operator<=(reverse_iterator<Iterator1> const &lhs, reverse_iterator <Iterator2> const &rhs) {
				return (lhs.base() >= rhs.base());
			}

		template <class Iterator1, class Iterator2> //  Operator>
			bool operator> (reverse_iterator<Iterator1> const &lhs, reverse_iterator <Iterator2> const &rhs) {
				return (lhs.base() < rhs.base());
			}

		template <class Iterator1, class Iterator2> //  Operator>=
			bool operator>=(reverse_iterator<Iterator1> const &lhs, reverse_iterator <Iterator2> const &rhs) {
				return (lhs.base() <= rhs.base());
			}
		
		

		//  ------------------NON-MEMBER FUNCTIONS OPERATORS------------------
		
		template <class Iterator> //  Operator+ > it + n
			reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, reverse_iterator<Iterator> const &rev_it) {
				return (reverse_iterator<Iterator>(rev_it.base() - n));
		}

		template <class Iterator> //  Operator- -> it - n
			reverse_iterator<Iterator>	operator-(typename reverse_iterator<Iterator>::difference_type n, reverse_iterator<Iterator> const &rhs){
					return (reverse_iterator<Iterator>(rhs.base() + n));
			}

		template <class Iterator, class Iterator2>   //  Operator+ -> it - it
			typename reverse_iterator<Iterator>::difference_type operator+(reverse_iterator<Iterator> const &lhs, reverse_iterator<Iterator2> const &rhs) {
				return (rhs.base() + lhs.base());
			}
		
		template <class Iterator, class Iterator2>  //  Operator- -> it - it
			typename reverse_iterator<Iterator>::difference_type operator-(reverse_iterator<Iterator> const &lhs, reverse_iterator<Iterator2> const &rhs) {
				return (rhs.base() - lhs.base());
			}
}

#endif