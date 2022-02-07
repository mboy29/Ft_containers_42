#ifndef FORWARD_ITERATOR_HPP
# define FORWARD_ITERATOR_HPP

//  --------------------------FORWARD ITERATORS---------------------------
// |  -> Class Template								                      |
// |  These can be used to access the sequence of elements in a range in  |
// |  the direction that goes from its beginning towards its end.         |
//  ----------------------------------------------------------------------

namespace Ft
{
	template<class Iterator>
		class forward_iterator {
			
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
			
				forward_iterator(void) { this->_ptr = NULL; }
				forward_iterator(pointer ptr) { this->_ptr = ptr; };
				forward_iterator(forward_iterator const &rhs) { *this = rhs; };

				//  -----------------------DESTRUCTOR---------------------
				
				~forward_iterator(void);

				//  -------------------------BASE-------------------------
			
				pointer 		base(void) const { return (this->_ptr); } 

				//  -----------------DEREFERENCE OPERATOR-----------------

				forward_iterator&	operator=(forward_iterator const &rhs) {
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
				
				forward_iterator&	operator++(void) { //  Operator++ -> a++
					this->_ptr += 1;
					return (*this);
				}

				forward_iterator	operator++(int) { //  Operator++ -> ++a
					forward_iterator	tmp = this->_ptr;

					this->_ptr += 1;
					return (tmp);
				}

				//  ------------IN/EQUALITY RELATIONAL OPERATOR------------
			
				bool	operator==(forward_iterator const &rhs) const { //  Operator==
					if (this->base() == rhs.base())
						return (true);
					return (false);
				}

				bool	operator==(forward_iterator<const Iterator> &rhs) const { //  Operator==
					if (this->base() == rhs.base())
						return (true);
					return (false);
				}

				bool	operator!=(forward_iterator const &rhs) const { //  Operator!=
					if (this->base() != rhs.base())
						return (true);
					return (false);
				}

				bool	operator!=(forward_iterator<const Iterator> &rhs) const { //  Operator!=
					if (this->base() != rhs.base())
						return (true);
					return (false);
				}
		};

		//  ----------------NON-MEMBER FUNCTIONS OVERLOAD-----------------
		
		template<class Iterator> //  Operator==
			bool	operator==(const Ft::forward_iterator<Iterator> &lhs, const Ft::forward_iterator<Iterator> &rhs) {
				return (&(*lhs.base()) == &(*rhs.base()));
			}
		
		template<class Iterator> //  Operator!=
			bool	operator!=(const Ft::forward_iterator<Iterator> &lhs, const Ft::forward_iterator<Iterator> &rhs) {
				return (&(*lhs.base()) != &(*rhs.base()));
			}
};

#endif