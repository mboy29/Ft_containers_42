#ifndef MAP_HPP
# define MAP_HPP
# include <memory> //  Allocator
# include <functional> //  Less -> Determines whether its first argument compares less than the second
# include <../Utilities/Pair.hpp> //  Pair

//  ----------------------------MAP CONTAINER----------------------------
//    -> Class Template
//    Associative containers that store elements in a specific order 
//    formed by a combination of a key (used to sort and uniquely
//    identify the elements) and a mapped value (stores the content
//    associated to this key).
//    Warning :
//     	- The values are grouped together in member type, aka a pair ;
//      - The types of key and mapped value may differ ;
//      - Typically implemented as binary search trees.
//  ---------------------------------------------------------------------

namespace ft
{
	template<class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
		class map {
			
			//  ---------------------MEMBER TYPES------------------------

			public:
				typedef Key												key_type;
				typedef T												mapped_type;
				typedef	ft::pair<key_type, mapped_type>					value_type;
				typedef Compare											key_compare;
				typedef Alloc											allocator_type;
				typedef typename allocator_type::reference				reference;
				typedef typename allocator_type::const_reference		const_reference;
				typedef typename allocator_type::pointer				pointer;
				typedef typename allocator_type::const_pointer			const_pointer;
				typedef ft::bidirectional_iterator<value_type>			iterator;
				typedef ft::bidirectional_iterator<const value_type>	const_iterator;
				typedef ft::reverser_iterator<value_type>				reverse_iterator;
				typedef ft::reverser_iterator<const value_type>			const_reverse_iterator;
				typedef ft::iterator_traits<iterator>::difference_type	difference_type;
				typedef size_t											size_type;
		}
}

#endif