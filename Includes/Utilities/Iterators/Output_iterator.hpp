#ifndef OUTPUT_ITERATOR_HPP
# define OUTPUT_ITERATOR_HPP

//  --------------------------OUTPUT ITERATORS----------------------------
// |  -> Class Template								                      |
// |  These can be used in sequential output operations, where each       |
// |  element pointed by the iterator is written a value only once and    |
// |  then the iterator is incremented.
//  ----------------------------------------------------------------------

namespace Ft
{
	template<class Iterator>
		class output_iterator {
			
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
			
				output_iterator(pointer ptr) { this->_ptr = ptr; };
				output_iterator(output_iterator const &rhs) { *this = rhs; };

				//  -----------------------DESTRUCTOR---------------------
				
				~output_iterator(void);

				//  -----------------DEREFERENCE OPERATOR-----------------

				output_iterator&	operator=(output_iterator const &rhs) {
					if (this != &rhs)
						this->_ptr = rhs->_ptr;
					return (*this);
				}

				reference	operator*(void) const { //  Operator*
					return (*this->_ptr);
				}

				
				//  ------------------INCREMENT OPERATOR------------------
				
				output_iterator&	operator++(void) { //  Operator++ -> a++
					this->_ptr += 1;
					return (*this);
				}

				output_iterator	operator++(int) { //  Operator++ -> ++a
					output_iterator	tmp = this->_ptr;

					this->_ptr += 1;
					return (tmp);
				}
		};
};

#endif