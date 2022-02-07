#ifndef BIDIRECTIONAL_ITERATOR_HPP
# define BIDIRECTIONAL_ITERATOR_HPP

//  -----------------------BIDIRECTIONAL ITERATORS------------------------
// |  -> Class Template								                      |
// |  These can be used to access the sequence of elements in a range in  |
// |  both directions (towards the end and towards the beginning).        |
//  ----------------------------------------------------------------------

namespace Ft
{
	template<class Iterator>
		class bidirectional_iterator {
			
			//  ----------------------MEMBER TYPES------------------------
		
			public:
				typedef Iterator												iterator_type;
				typedef typename iterator_traits<Iterator>::value_type			value_type;
				typedef typename iterator_traits<Iterator>::difference_type		difference_type;
				typedef typename iterator_traits<Iterator>::pointer				pointer;
				typedef typename iterator_traits<Iterator>::reference			reference;
				typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
			protected:
				pointer		_ptr;

			//  ---------------------MEMBER FUNCTIONS---------------------

			public:
				
				//  ----------------------CONSTRUCTOR---------------------
			
				bidirectional_iterator(void) { this->_ptr = NULL; }
				bidirectional_iterator(pointer ptr) { this->_ptr = ptr; };
				bidirectional_iterator(bidirectional_iterator const &rhs) { *this = rhs; };

				//  -----------------------DESTRUCTOR---------------------
				
				~bidirectional_iterator(void);

				//  -------------------------BASE-------------------------
			
				pointer 		base(void) const { return (this->_ptr); } 

				//  -----------------DEREFERENCE OPERATOR-----------------

				bidirectional_iterator&	operator=(bidirectional_iterator const &rhs) {
					if (this != &rhs)
						this->_ptr = rhs->_ptr;
					return (*this);
				}

				reference	operator*(void) const { //  Operator*
					return (*this->_ptr);
				}

				pointer		operator->(void) const { //  Operator->
					return (this->_ptr);
				}

				
				//  ------------------INCREMENT OPERATOR------------------
				
				bidirectional_iterator&	operator++(void) { //  Operator++ -> a++
					this->_ptr += 1;
					return (*this);
				}

				bidirectional_iterator	operator++(int) { //  Operator++ -> ++a
					bidirectional_iterator	tmp = this->_ptr;

					this->_ptr += 1;
					return (tmp);
				}


				//  ------------------DECREMENT OPERATOR------------------

				bidirectional_iterator&	operator--(void) { //  Operator-- -> a--
					this->_ptr -= 1;
					return (*this);
				}

				bidirectional_iterator	operator--(int) { //  Operator-- -> --a
					bidirectional_iterator	tmp = this->_ptr;

					this->_ptr -= 1;
					return (tmp);
				}

				//  ------------IN/EQUALITY RELATIONAL OPERATOR------------
			
				bool	operator==(bidirectional_iterator const &rhs) const { //  Operator==
					if (this->base() == rhs.base())
						return (true);
					return (false);
				}

				bool	operator==(bidirectional_iterator<const Iterator> &rhs) const { //  Operator==
					if (this->base() == rhs.base())
						return (true);
					return (false);
				}

				bool	operator!=(bidirectional_iterator const &rhs) const { //  Operator!=
					if (this->base() != rhs.base())
						return (true);
					return (false);
				}

				bool	operator!=(bidirectional_iterator<const Iterator> &rhs) const { //  Operator!=
					if (this->base() != rhs.base())
						return (true);
					return (false);
				}
		};

		//  ----------------NON-MEMBER FUNCTIONS OVERLOAD-----------------
		
		template<class Iterator> //  Operator==
			bool	operator==(const Ft::bidirectional_iterator<Iterator> &lhs, const Ft::bidirectional_iterator<Iterator> &rhs) {
				return (&(*lhs.base()) == &(*rhs.base()));
			}
		
		template<class Iterator> //  Operator!=
			bool	operator!=(const Ft::bidirectional_iterator<Iterator> &lhs, const Ft::bidirectional_iterator<Iterator> &rhs) {
				return (&(*lhs.base()) != &(*rhs.base()));
			}
};

#endif