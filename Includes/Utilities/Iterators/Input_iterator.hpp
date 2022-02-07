#ifndef INPUT_ITERATOR_HPP
# define INPUT_ITERATOR_HPP

//  ---------------------------INPUT ITERATORS----------------------------
// |  -> Class Template								                      |
// |  These can can be used in sequential input operations, where each    |
// |  value pointed by the iterator is read only once and then the        |
// |  iterator is incremented.
//  ----------------------------------------------------------------------

namespace Ft
{
	template<class Iterator>
		class input_iterator {
			
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
			
				input_iterator(pointer ptr) { this->_ptr = ptr; };
				input_iterator(input_iterator const &rhs) { *this = rhs; };

				//  -----------------------DESTRUCTOR---------------------
				
				~input_iterator(void);

				//  -------------------------BASE-------------------------
			
				pointer 		base(void) const { return (this->_ptr); } 
				
				//  -----------------DEREFERENCE OPERATOR-----------------

				input_iterator&	operator=(input_iterator const &rhs) {
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
				
				input_iterator&	operator++(void) { //  Operator++ -> a++
					this->_ptr += 1;
					return (*this);
				}

				input_iterator	operator++(int) { //  Operator++ -> ++a
					input_iterator	tmp = this->_ptr;

					this->_ptr += 1;
					return (tmp);
				}

				//  ------------IN/EQUALITY RELATIONAL OPERATOR------------
			
				bool	operator==(input_iterator const &rhs) const { //  Operator==
					if (this->base() == rhs.base())
						return (true);
					return (false);
				}

				bool	operator==(input_iterator<const Iterator> &rhs) const { //  Operator==
					if (this->base() == rhs.base())
						return (true);
					return (false);
				}

				bool	operator!=(input_iterator const &rhs) const { //  Operator!=
					if (this->base() != rhs.base())
						return (true);
					return (false);
				}

				bool	operator!=(input_iterator<const Iterator> &rhs) const { //  Operator!=
					if (this->base() != rhs.base())
						return (true);
					return (false);
				}
		};

		//  ----------------NON-MEMBER FUNCTIONS OVERLOAD-----------------
		
		template<class Iterator> //  Operator==
			bool	operator==(const Ft::input_iterator<Iterator> &lhs, const Ft::input_iterator<Iterator> &rhs) {
				return (&(*lhs.base()) == &(*rhs.base()));
			}
		
		template<class Iterator> //  Operator!=
			bool	operator!=(const Ft::input_iterator<Iterator> &lhs, const Ft::input_iterator<Iterator> &rhs) {
				return (&(*lhs.base()) != &(*rhs.base()));
			}
};

#endif