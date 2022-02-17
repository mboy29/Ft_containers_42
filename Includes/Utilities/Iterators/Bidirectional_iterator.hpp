#ifndef	BIDIRECTIONAL_ITERATOR_HPP
# define BIDIRECTIONAL_ITERATOR_HPP

//  -----------------------BIDIRECTIONAL ITERATORS------------------------
// |  -> Class Template								                      |
// |  These iterators are iterators that can be used to access the        |
// |  sequence of elements in a range in both directions.                 |
// |  They can towards the end and towards the beginning.				  |
//  ----------------------------------------------------------------------

namespace ft
{
	template <class Iterator>
	class bidirectional_iterator : public iterator<bidirectional_iterator_tag, Iterator>
	{
		//  ----------------------MEMBER TYPES------------------------

		protected:
			typedef iterator<bidirectional_iterator_tag, Iterator>	iterator;
		public:
			typedef typename iterator::value_type					value_type;
			typedef typename iterator::difference_type				difference_type;
			typedef typename iterator::iterator_category			iterator_category;
			typedef typename iterator::pointer						pointer;
			typedef typename iterator::reference 					reference;
		
		//  ---------------------MEMBER FUNCTIONS---------------------
		
		public:
			
			//  ----------------------CONSTRUCTOR---------------------
			
			bidirectional_iterator (void) { this->_ptr = NULL; }
			bidirectional_iterator (pointer ptr) { this->_ptr = ptr; }
			bidirectional_iterator (bidirectional_iterator const &rhs) { *this = rhs; }

			//  -------------------------BASE-------------------------
			
			pointer base(void) const { return (this->_ptr); };

			//  -------------------CONVERT TO CONST-------------------

				operator bidirectional_iterator<const Iterator> () {
					return (bidirectional_iterator<const Iterator> (this->_ptr));
				};
			
			//  -----------------DEREFERENCE OPERATOR-----------------

			bidirectional_iterator & operator=(bidirectional_iterator const & rhs) { //  Operator=
				if (this != &rhs)
					this->_ptr = rhs._ptr;
				return (*this);
			}

			reference operator*(void) const {  //  Operator*
				return (*(this->_ptr));
			}
			
			pointer operator->(void) { //  Operator->
				return (this->_ptr);
			}
			
			//  ------------------INCREMENT OPERATOR------------------
		
			bidirectional_iterator & operator++(void) { //  Operator++ -> a++
				this->_ptr += 1;
				return (*this);
			}

			bidirectional_iterator operator++(int) { //  Operator++ -> ++a
				bidirectional_iterator tmp = this->_ptr;
			
				this->_ptr += 1;
				return (tmp);
			}

			//  ------------------DECREMENT OPERATOR------------------

			bidirectional_iterator & operator--(void) { //  Operator-- -> a--
				this->_ptr -= 1;
				return (*this);
			}

			bidirectional_iterator operator--(int) { //  Operator-- -> --a
				bidirectional_iterator tmp = this->_ptr;
	
				this->_ptr -= 1;
				return (tmp);
			}

			//  ------------IN/EQUALITY RELATIONAL OPERATOR------------
	
			bool operator==(bidirectional_iterator const & rhs) const { //  Operator==
				if (this->base() == rhs._ptr)
					return (true);
				return (false);
			}

			bool operator==(bidirectional_iterator<const Iterator> & rhs) const { //  Operator==
				if (this->base() == rhs.base())
					return (true);
				return (false);
			}

			bool operator!=(bidirectional_iterator const & rhs) const { //  Operator!=
				if (this->base() != rhs._ptr)
					return (true);
				return (false);
			}

			bool operator!=(bidirectional_iterator<const Iterator> & rhs) const { //  Operator!=
				if (this->base() != rhs.base())
					return (true);
				return (false);
			}

			
	};

	//  ----------------NON-MEMBER FUNCTIONS OVERLOAD-----------------
	
	template <class Iterator, class Iterator_> //  Operator==
		bool operator==(const bidirectional_iterator<Iterator>& lhs, const bidirectional_iterator<Iterator_>& rhs) {
			return (&(*lhs.base()) == &(*rhs.base()));
		}

	template <class Iterator, class Iterator_> //  Operator!=
		bool operator!=(const bidirectional_iterator<Iterator>& lhs, const bidirectional_iterator<Iterator_>& rhs) {
			return (&(*lhs.base()) != &(*rhs.base()));
		};
}

#endif