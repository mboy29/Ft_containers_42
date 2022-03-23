/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:31:34 by mboy              #+#    #+#             */
/*   Updated: 2022/03/23 13:31:36 by mboy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define  RANDOM_ACCESS_ITERATOR_HPP

//  -----------------------RANDOM ACCESS ITERATORS------------------------
//    -> Class Template
//    This class are iterators that can be used to access elements at an
//    arbitrary offset position relative to the element they point to 
//    (they offer the same functionality as pointers.
//  ----------------------------------------------------------------------

namespace ft
{
	template <class Iterator>
		class random_access_iterator : public iterator<random_access_iterator_tag, Iterator> {
		
			//  ----------------------MEMBER TYPES------------------------
		
			protected:
				typedef iterator<random_access_iterator_tag, Iterator>	iterator;
			
			public:
				typedef typename iterator::value_type			value_type;
				typedef typename iterator::difference_type		difference_type;
				typedef typename iterator::pointer				pointer;
				typedef typename iterator::reference			reference;
				typedef typename iterator::iterator_category	iterator_category;
			
			//  ---------------------MEMBER FUNCTIONS---------------------

			public:
				
				//  ----------------------CONSTRUCTOR---------------------
			
				random_access_iterator(void) { this->_ptr = NULL; }
				random_access_iterator(pointer ptr) { this->_ptr = ptr; };
				random_access_iterator(random_access_iterator const &rhs) { *this = rhs; };
			
				//  -------------------------BASE-------------------------
			
				pointer 		base(void) const { return (this->_ptr); } 
				
				//  -------------------CONVERT TO CONST-------------------

				operator random_access_iterator<const Iterator> (void) {
					return (random_access_iterator<const Iterator> (this->_ptr));
				}
				
				//  -----------------DEREFERENCE OPERATOR-----------------

				random_access_iterator&	operator=(random_access_iterator const &rhs) {
					if (this != &rhs)
						this->_ptr = rhs._ptr;
					return (*this);
				}

				reference	operator*(void) const { //  Operator*
					return (*(this->_ptr));
				}

				pointer		operator->(void) const { //  Operator->
					return (this->_ptr);
				}

				reference	operator[](difference_type n) const { //  Operator[]
					return (*(this->_ptr + n));
				}
				
				//  ------------------INCREMENT OPERATOR------------------
				
				random_access_iterator&	operator++(void) { //  Operator++ -> a++
					this->_ptr += 1;
					return (*this);
				}

				random_access_iterator	operator++(int) { //  Operator++ -> ++a
					random_access_iterator	tmp = this->_ptr;

					this->_ptr += 1;
					return (tmp);
				}


				//  ------------------DECREMENT OPERATOR------------------

				random_access_iterator&	operator--(void) { //  Operator-- -> a--
					this->_ptr -= 1;
					return (*this);
				}

				random_access_iterator	operator--(int) { //  Operator-- -> --a
					random_access_iterator	tmp = this->_ptr;

					this->_ptr -= 1;
					return (tmp);
				}
	
				
				//  -----------------ARITHMETIC OPERATOR------------------
					
				random_access_iterator	operator-(difference_type n) const { return (this->_ptr - n); };
				random_access_iterator	operator+(difference_type n) const { return (this->_ptr + n); };
				
				template <class It>
				friend random_access_iterator<It> operator+(
					typename random_access_iterator<It>::difference_type n,
					random_access_iterator<It> const & rhs);

				template <class It>
				friend random_access_iterator<It> operator-(
					typename random_access_iterator<It>::difference_type n,
					random_access_iterator<It> const & rhs);

				
				//  -------------COMPOUND ASSIGNMENT OPERATOR--------------

				random_access_iterator	operator+=(difference_type n) { //  Operator+=
					this->_ptr += n;
					return (*this);
				}

				random_access_iterator	operator-=(difference_type n) { //  Operator-=
					this->_ptr -= n;
					return (*this);
				}

				//  ------------IN/EQUALITY RELATIONAL OPERATOR------------
			
				bool	operator==(random_access_iterator const &rhs) const { //  Operator==
					if (this->base() == rhs._ptr)
						return (true);
					return (false);
				}

				bool	operator==(random_access_iterator<const Iterator> &rhs) const { //  Const operator==
					if (this->base() == rhs.base())
						return (true);
					return (false);
				}

				bool	operator!=(random_access_iterator const &rhs) const { //  Operator!=
					if (this->base() != rhs._ptr)
						return (true);
					return (false);
				}

				bool	operator!=(random_access_iterator<const Iterator> &rhs) const { //  Const operator!=
					if (this->base() != rhs.base())
						return (true);
					return (false);
				}

				//  ------------INEQUALITY RELATIONAL OPERATOR------------
				
				bool	operator<(random_access_iterator const &rhs) const { //  Operator<
					if (this->base() < rhs._ptr)
						return (true);
					return (false);
				}

				bool	operator<(random_access_iterator<const Iterator> &rhs) const { //  Operator<
					if (this->base() < rhs.base())
						return (true);
					return (false);
				}

				bool	operator<=(random_access_iterator const &rhs) const { //  Operator<=
					if (this->base() <= rhs._ptr)
						return (true);
					return (false);
				}

				bool	operator<=(random_access_iterator<const Iterator> &rhs) const { //  Operator<=
					if (this->base() <= rhs.base())
						return (true);
					return (false);
				}

				bool	operator>(random_access_iterator const &rhs) const { //  Operator>
					if (this->base() > rhs._ptr)
						return (true);
					return (false);
				}

				bool	operator>(random_access_iterator<const Iterator> &rhs) const { //  Operator>
					if (this->base() > rhs.base())
						return (true);
					return (false);
				}

				bool	operator>=(random_access_iterator const &rhs) const { //  Operator>=
					if (this->base() >= rhs._ptr)
						return (true);
					return (false);
				}

				bool	operator>=(random_access_iterator<const Iterator> &rhs) const { //  Operator>=
					if (this->base() >= rhs.base())
						return (true);
					return (false);
				}

		};

		//  ----------------NON-MEMBER FUNCTIONS OVERLOAD-----------------
		
		template <class Iterator1, class Iterator2> //  Operator=
			bool operator==(const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs) {
				if (lhs.base() == rhs.base())
					return (true);
				return (false);
			}

		template <class Iterator1, class Iterator2> //  Operator!=
			bool operator!=(const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs) {
				if (lhs.base() != rhs.base())
					return (true);
				return (false);
			}

		template <class Iterator1, class Iterator2> //  Operator<
			bool operator<(const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs) {
				if (lhs.base() < rhs.base())
					return (true);
				return (false);
			}

		template <class Iterator1, class Iterator2> //  Operator<=
			bool operator<=(const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs) {
				if (lhs.base() <= rhs.base())
					return (true);
				return (false);
			}
	
		template <class Iterator1, class Iterator2> //  Operator>
			bool operator>(const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs) {
				if (lhs.base() > rhs.base())
					return (true);
				return (false);
			}
	
		template <class Iterator1, class Iterator2> //  Operator>=
			bool operator>=(const random_access_iterator<Iterator1>& lhs, const random_access_iterator<Iterator2>& rhs) {
				if (lhs.base() >= rhs.base())
					return (true);
				return (false);
			}
		
		//  ----------------NON-MEMBER FUNCTIONS OPERATORS----------------
		
		template <class Iterator> //  Operator+
			ft::random_access_iterator<Iterator>	operator+(typename ft::random_access_iterator<Iterator>::difference_type n, ft::random_access_iterator<Iterator> const &rhs) {
					return (rhs._ptr + n);
			}
		
		template <class Iterator> //  Operator- -> it - n
			ft::random_access_iterator<Iterator>	operator-(typename ft::random_access_iterator<Iterator>::difference_type n, ft::random_access_iterator<Iterator> const &rhs) {
					return (rhs._ptr - n);
			}
		
		template <class Iterator1, class Iterator2> //  perator- -> it - it
			typename ft::random_access_iterator<Iterator1>::difference_type operator+(random_access_iterator<Iterator1> const &lhs, random_access_iterator<Iterator2> const &rhs) {
				return (lhs.base() + rhs.base());
			}

		template <class Iterator1, class Iterator2> //  perator- -> it - it
			typename ft::random_access_iterator<Iterator1>::difference_type operator-(random_access_iterator<Iterator1> const &lhs, random_access_iterator<Iterator2> const &rhs) {
				return (lhs.base() - rhs.base());
			}
}

#endif
