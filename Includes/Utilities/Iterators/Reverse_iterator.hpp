#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

//  --------------------------REVERSE ITERATORS---------------------------
// |  -> Class Template								                      |
// |  This class reverses the direction in which a bidirectional or       |
// |  random-access iterator iterates through a range.                    |
//  ----------------------------------------------------------------------

namespace Ft
{
	template <class Iterator>
		class reverse_iterator {
	
			//  ----------------------MEMBER TYPES------------------------
		
			public:
				typedef Iterator												iterator_type;
				typedef typename Ft::iterator_traits<Iterator>::value_type							value_type;
				typedef typename Ft::iterator_traits<Iterator>::difference_type		difference_type;
				typedef typename Ft::iterator_traits<Iterator>::pointer				pointer;
				typedef typename Ft::iterator_traits<Iterator>::reference			reference;
				typedef typename Ft::iterator_traits<Iterator>::iterator_category	iterator_category;
			protected:
				pointer		_ptr;

			//  ---------------------MEMBER FUNCTIONS---------------------

			public:
				
				//  ----------------------CONSTRUCTOR---------------------
			
				reverse_iterator(void) {}
				explicit reverse_iterator (iterator_type it) : _ptr(&(*it) - 1) {}
				template <class It>
					reverse_iterator (const reverse_iterator<It>& rev_it) : _ptr(&(*rev_it.base()) - 1) {}
				
				//  -------------------------BASE-------------------------
			
				iterator_type 		base(void) const { return (iterator_type(this->_ptr + 1)); } 

				//  -----------------DEREFERENCE OPERATOR-----------------

				//  Operator*
				reference 			operator*(void) const { return (*this->_ptr); }

				//  Operator->
				pointer				operator->(void) const { return (*this->_ptr); }

				//  Operator[]
				reference			operator[](difference_type n) const { return (*(this->_ptr - n)); }


				//  ------------------INCREMENT OPERATOR------------------

				reverse_iterator&	operator++(void) { //  Operator++
					this->_ptr -= 1;
					return (*this);
				}

				reverse_iterator	operator++(int) { //  Operator++
					pointer	tmp = this->_ptr + 1;
					
					this->_ptr -= 1;
					return (reverse_iterator(tmp));
				}

				//  ------------------DECREMENT OPERATOR------------------

				reverse_iterator&	operator--(void) { //  Operator--
					this->_ptr += 1;
					return (*this);
				}
			
				reverse_iterator	operator--(int) { //  Operator--
					pointer	tmp = this->_ptr + 1;
					this->_ptr += 1;
					return (reverse_iterator(tmp));
				}
				//  -----------------ARITHMETIC OPERATOR------------------

				reverse_iterator	operator+(difference_type n) const { //  Operator+
					pointer tmp = this->_ptr - n + 1;
					return (reverse_iterator(tmp));
				}

				reverse_iterator	operator-(difference_type n) const { //  Operator-
					pointer		tmp = this->_ptr + n + 1;
					
					return (reverse_iterator(tmp));
				}

				//  -------------COMPOUND ASSIGNMENT OPERATOR--------------
			
				reverse_iterator&	operator+=(difference_type n) { //  Operator+=
					this->_ptr -= n;
					return (*this);
				}

				reverse_iterator&	operator-=(difference_type n) { //  Operator-=
					this->_ptr += n;
					return (*this);
				}

				//  ------------IN/EQUALITY RELATIONAL OPERATOR------------
			
				bool	operator==(reverse_iterator const &rhs) const { //  Operator==
					if (this->base() == rhs.base())
						return (true);
					return (false);
				}

				bool	operator==(reverse_iterator<const Iterator> &rhs) const { //  Operator==
					if (this->base() == rhs.base())
						return (true);
					return (false);
				}

				bool	operator!=(reverse_iterator const &rhs) const { //  Operator!=
					if (this->base() != rhs.base())
						return (true);
					return (false);
				}

				bool	operator!=(reverse_iterator<const Iterator> &rhs) const { //  Operator!=
					if (this->base() != rhs.base())
						return (true);
					return (false);
				}

				//  ------------INEQUALITY RELATIONAL OPERATOR------------
				
				bool	operator<(reverse_iterator const &rhs) const { //  Operator<
					if (this->base() < rhs.base())
						return (true);
					return (false);
				}

				bool	operator<(reverse_iterator<const Iterator> &rhs) const { //  Operator<
					if (this->base() < rhs.base())
						return (true);
					return (false);
				}

				bool	operator<=(reverse_iterator const &rhs) const { //  Operator<=
					if (this->base() <= rhs.base())
						return (true);
					return (false);
				}

				bool	operator<=(reverse_iterator<const Iterator> &rhs) const { //  Operator<=
					if (this->base() <= rhs.base())
						return (true);
					return (false);
				}

				bool	operator>(reverse_iterator const &rhs) const { //  Operator>
					if (this->base() > rhs.base())
						return (true);
					return (false);
				}

				bool	operator>(reverse_iterator<const Iterator> &rhs) const { //  Operator>
					if (this->base() > rhs.base())
						return (true);
					return (false);
				}

				bool	operator>=(reverse_iterator const &rhs) const { //  Operator>=
					if (this->base() >= rhs.base())
						return (true);
					return (false);
				}

				bool	operator>=(reverse_iterator<const Iterator> &rhs) const { //  Operator>=
					if (this->base() >= rhs.base())
						return (true);
					return (false);
				}
		};
				
		//  ----------------NON-MEMBER FUNCTIONS OVERLOAD-----------------

		template <class Iterator> //  Operator==
  			bool operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
				return (&(*lhs.base()) == &(*rhs.base()));
			}
		
		template <class Iterator> //  Operator!=
  			bool operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
			  return (&(*lhs.base()) != &(*rhs.base()));
			}
		
		template <class Iterator>  //  Operator<
  			bool operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
			  return (&(*lhs.base()) < &(*rhs.base()));
			}
		
		template <class Iterator> //  Operator<=
  			bool operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
			  return (&(*lhs.base()) <= &(*rhs.base()));
			}

		template <class Iterator> //  Operator>
  			bool operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
			  return (&(*lhs.base()) > &(*rhs.base()));
			}
		
		template <class Iterator> //  Operator>=
  			bool operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
				return (&(*lhs.base()) >= &(*rhs.base()));
			}
	

	//  ------------------NON-MEMBER FUNCTIONS OPERATORS------------------
	
	template <class Iterator> //  Operator+
  		reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it) {
			return (reverse_iterator<Iterator>(&(*rev_it.base()) - n));
	}

	template <class Iterator> //  Operator-
  		typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
			return (&(*rhs.base()) - &(*lhs.base()));
	}
}

#endif