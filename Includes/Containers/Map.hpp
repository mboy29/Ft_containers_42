#ifndef MAP_HPP
#define MAP_HPP
#include <memory>						   	//  Allocator
#include <functional>					   	//  Less -> Determines whether its first argument compares less than the second
#include "../Utilities/Pair.hpp"		   	//  Pair
#include "../Utilities/Trees/Node.hpp"	   	//  Tree Node
#include "../Utilities/Trees/Iterator.hpp" 	//  Tree Iterator
#include "../Utilities/Trees/Tree.hpp"	   	//  Tree

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
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
		class map
		{

		//  ------------------------MEMBER TYPES-------------------------

		public:
			typedef Key									 		key_type;
			typedef T 											mapped_type;
			typedef ft::pair<const key_type, mapped_type>	 	value_type;
			typedef Compare										key_compare;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference 			reference;
			typedef typename allocator_type::const_reference 	const_reference;
			typedef typename allocator_type::pointer 			pointer;
			typedef typename allocator_type::const_pointer 		const_pointer;
			typedef ft::tree_iterator<value_type> 				iterator;
			typedef ft::const_tree_iterator<value_type>			const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
			typedef std::ptrdiff_t								difference_type;
			typedef std::size_t									size_type;
			
			//  ----------------------VALUE COMPARE----------------------
			//  -> Class template
			//  Map container member type : map::value_compare.
			//  Returns a comparison object that can be used to compare 2
			//  elements in order to identify whether the key of the first one
			//  goes before the second.
			//  https://www.cplusplus.com/reference/map/map/value_comp/
			//  ---------------------------------------------------------

			class value_compare : public std::binary_function<value_type, value_type, bool> { 
				friend class map;
				protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {}
				public:
					typedef bool 		result_type;
					typedef value_type 	first_argument_type;
					typedef value_type 	second_argument_type;
					bool operator() (const value_type& x, const value_type& y) const { return comp(x.first, y.first); }
			};

			private:
				typedef tree<value_type, value_compare, allocator_type>  _tree_type;
				_tree_type												 _tree;
			
			//  ---------------------MEMBER FUNCTIONS---------------------

			public:
			
				//  ---------------------CONSTRUCTORS---------------------

				//  Construct empty map :
				explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
					: _tree(value_compare(comp), alloc) {};
				
				//  Construct map based on a range :
				template <class InputIterator>
					map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) 
						: _tree(value_compare(comp), alloc) { this->insert(first, last); };
				
				//  Construct Copy :
				map (map const &rhs) : _tree(rhs._tree) {}
				
				//  ---------------------DESTRUCTORS----------------------
				
				~map(void) {};


				//  -------------------ASSIGN OPERATOR--------------------

				//  Operator= :
				map		&operator=(const map &x) {
					if (this != &x)
						this->_tree = x._tree;
					return (*this);
				}

				//  ----------------------ITERATORS-----------------------
			
				
				//  Begin/tree::begin :
				iterator				begin(void) { return (this->_tree.begin()); }
				const_iterator			begin(void) const { return (this->_tree.begin()); }
				
				//  End/tree::end :
				iterator				end(void) { return (this->_tree.end()); }
				const_iterator			end(void) const { return (this->_tree.end()); }
				
				//  Reverse begin/tree::rbegin :
				reverse_iterator		rbegin(void) { return (this->_tree.rbegin()); }
				const_reverse_iterator	rbegin(void) const { return (this->_tree.rbegin()); }
				
				//  Reverse end/tree::rend :
				reverse_iterator		rend(void) { return (this->_tree.rend()); }
				const_reverse_iterator	rend(void) const { return (this->_tree.rend()); }
				
				//  -----------------------CAPACITY-----------------------
				
				//  Empty/tree::empty :
				bool		empty(void) const { return (this->_tree.empty()); }
				
				//  Size/tree::size :
				size_type	size(void) const { return (this->_tree.size()); }
				
				//  Max_size :
				size_type	max_size(void) const {
					return (std::numeric_limits<difference_type>::max() / sizeof(map));
				}
				
				//  --------------------ELEMENT ACCESS--------------------

				//  Operator[] :
					mapped_type& operator[] (const key_type& k) { return (this->insert(ft::make_pair(k, mapped_type())).first->second); }
				
				//  ----------------------MODIFIERS-----------------------
				
				
				//  Insert/tree::insert single element (empty tree) :
				pair<iterator, bool>	insert(const value_type& val) { return (this->_tree.insert(val)); }
				
				//  Insert/tree::insert "hint" :
				iterator 				insert(iterator position, const value_type& val) { return (this->_tree.insert(position, val)); }
			
				//  Insert/tree::insert rang :
				template <class InputIterator>
					void 				insert(InputIterator first, InputIterator last) {	return (this->_tree.insert(first, last)); }

				//  Clear :
				void 					clear(void) { return (this->_tree.clear()); }

				//  ----------------------OBSERVERS-----------------------

				//  Key compare :
				key_compare		key_comp(void) const { return (key_compare()); }
				
				//  Value compare :
				value_compare	value_comp(void) const { return (value_compare(key_compare())); }

				//  ----------------------OPERATIONS----------------------

				//  Lower bound/Tree::lower_bound :
				iterator 		lower_bound(const key_type& k) { return (iterator(this->_tree.lower_bound(ft::make_pair(k, mapped_type())))); }
				const_iterator 	lower_bound(const key_type& k) const { return (const_iterator(this->_tree.lower_bound(ft::make_pair(k, mapped_type())))); }
				
				//  Upper bound/Tree::upper_bound :
				iterator 		upper_bound(const key_type& k) { return (iterator(this->_tree.upper_bound(ft::make_pair(k, mapped_type())))); }
				const_iterator 	upper_bound(const key_type& k) const { return (const_iterator(this->_tree.upper_bound(ft::make_pair(k, mapped_type())))); }

				//  Equal range :
				pair<iterator,iterator>	equal_range (const key_type& k) { return (ft::make_pair(this->lower_bound(k), this->upper_bound(k))); }
				pair<const_iterator,const_iterator> equal_range(const key_type& k) const { return (ft::make_pair(this->lower_bound(k), this->upper_bound(k))); }
				
				//  --------------FRIEND RATIONAL OPERATORS---------------
				
				//  Operator== :
				template < class _Key, class _Map, class _Compare, class _Alloc >
					friend bool operator==(const ft::map<_Key, _Map, _Compare, _Alloc> &lhs, const ft::map<_Key, _Map, _Compare, _Alloc> &rhs);
				
				//  Operato< :
				template < class _Key, class _Map, class _Compare, class _Alloc >
					friend bool operator<(const ft::map<_Key,_Map,_Compare,_Alloc> &lhs, const ft::map<_Key,_Map,_Compare,_Alloc> &rhs);
		};

		//  ----------------NON-MEMBER FUNCTIONS OVERLOADS----------------

		//  ----------------------RATIONAL OPERATORS----------------------
			
		//  Operator== :
		template <class Key, class Map, class Compare, class Alloc>
			bool operator==(const ft::map<Key, Map, Compare, Alloc> &lhs, const ft::map<Key, Map, Compare, Alloc> &rhs) {
				if (lhs.size() != rhs.size())
					return (false);
				return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
			}
		
		//  Operator!= :
		template <class Key, class Map, class Compare, class Alloc>
			bool operator!=(const ft::map<Key, Map, Compare, Alloc> &lhs, const ft::map<Key, Map, Compare, Alloc> &rhs) { return (!(lhs == rhs)); }
		
		
		//  Operator< :
		template < class Key, class Map, class Compare, class Alloc>
			bool operator<(const ft::map<Key, Map, Compare, Alloc> &lhs, const ft::map<Key, Map, Compare, Alloc> &rhs) { return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }
		
		//  Operator> :
		template <class Key, class Map, class Compare, class Alloc>
			bool operator>(const ft::map<Key, Map, Compare, Alloc> &lhs, const ft::map<Key, Map, Compare, Alloc> &rhs) { return (rhs < lhs); }
		
		//  OperatorÒ<= :
		template <class Key, class Map, class Compare, class Alloc>
			bool operator<=(const ft::map<Key, Map, Compare, Alloc> &lhs, const ft::map<Key, Map, Compare, Alloc> &rhs) { return(!(rhs < lhs)); }
		
		//  Operator>= :
		template <class Key, class Map, class Compare, class Alloc>
			bool operator>=(const ft::map<Key, Map, Compare, Alloc> &lhs, const ft::map<Key, Map, Compare, Alloc> &rhs) { return (!(lhs < rhs)); }
}

#endif