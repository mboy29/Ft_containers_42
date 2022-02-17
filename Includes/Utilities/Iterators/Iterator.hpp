#ifndef ITERATOR_HPP
# define ITERATOR_HPP
# include <cstddef> // ptrdiff_t -> Signed integer type of the result of subtracting two pointers

//  ---------------------ITERATOR RE-IMPLATATION-------------------------
// |  -> Header           								                 |
// |  Object that, pointing to some element in a range of elements       |
// |  (array or container), has the ability to iterate through the       |
// |  elements of that range using a set of operators.                   |                            |
//  ---------------------------------------------------------------------

namespace ft
{
	//  -----------------------ITERATOR BASS CLASS------------------------
	// |  -> Bass Class           						                  |
	// |  Can be used to derive iterator classes from it. Not an iterator |
	// |  class and does not provide any of the functionality an iterator |
	// |  is expected to have. 											  |
	//  ------------------------------------------------------------------
	
	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
		class iterator {
			public:
				typedef T			value_type;
				typedef Distance	difference_type;
				typedef Pointer		pointer;
				typedef Reference	reference;
				typedef Category	iterator_category;
				
			protected:
				pointer				_ptr;
		};
	
	//  ----------------------ITERATOR CATEGORY TAG-----------------------
	// |  -> Struct											              |
	// |  Iterators are classified into five categories depending on the  |
	// |  functionality they implement.    								  |
	//  ------------------------------------------------------------------
	
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag {};
	struct bidirectional_iterator_tag {};
	struct random_access_iterator_tag {};

	//  -------------------------ITERATOR TRAITS--------------------------
	// |  -> Struct											              |
	// |  Traits class defining properties of iterators.                  |
	//  ------------------------------------------------------------------
	
	template <class Iterator>
		struct iterator_traits {
			typedef typename Iterator::value_type			value_type;
			typedef typename Iterator::difference_type		difference_type;
			typedef typename Iterator::pointer				pointer;
			typedef typename Iterator::reference			reference;
			typedef typename Iterator::iterator_category	iterator_category;
		};

	template<class Iterator>
		struct iterator_traits<Iterator*> {
			typedef Iterator						value_type;
			typedef ptrdiff_t						difference_type;
			typedef Iterator*						pointer;
			typedef Iterator&						reference;
			typedef random_access_iterator_tag		iterator_category;		
		};
	
	template<class Iterator>
		struct iterator_traits<const Iterator*> {
			typedef Iterator						value_type;
			typedef ptrdiff_t						difference_type;
			typedef const Iterator*					pointer;
			typedef const Iterator&					reference;
			typedef random_access_iterator_tag	iterator_category;		
		};
	
	//  -----------------ITERATOR OPERATION FUNCTION------------------

		template<class InputIterator>
			typename iterator_traits<InputIterator>::difference_type distance (InputIterator first, InputIterator last) {
				typename iterator_traits<InputIterator>::difference_type size = 0;

				while (first++ != last)
					size += 1;
				return (size);
			};
}

#endif