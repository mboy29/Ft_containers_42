#ifndef SET_HPP
#define SET_HPP
#include <memory>						   	//  Allocator
#include <functional>					   	//  Less -> Determines whether its first argument compares less than the second
#include "../../Utilities/Trees/Node.hpp"	   	//  Tree Node
#include "../../Utilities/Trees/Iterator.hpp" 	//  Tree Iterator
#include "../../Utilities/Trees/Tree.hpp"	   	//  Tree

//  ----------------------------set CONTAINER----------------------------
//    -> Class Template
//    Associative containers that store elements in a specific order
//    formed by a combination of a key (used to sort and uniquely
//    identify the elements) and a setped value (stores the content
//    associated to this key).
//    Warning :
//     	- The values are grouped together in member type, aka a pair ;
//      - The types of key and setped value may differ ;
//      - Typically implemented as binary search trees.
//  ---------------------------------------------------------------------

namespace ft
{
	template < class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
		class set {

		//  ------------------------MEMBER TYPES-------------------------

		public:
			typedef T											key_type;
			typedef T											value_type;
			typedef Compare										key_compare;
			typedef Compare										value_compare;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			poiner;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef ft::const_tree_iterator<value_type>				iterator;
			typedef ft::const_tree_iterator<value_type>			const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
			typedef std::ptrdiff_t								difference_type;
			typedef std::size_t									size_type;
			


			private:
				typedef ft::node<value_type>								_node;
				typedef typename Alloc::template rebind<_node>::other 		_rebind;
				typedef tree<value_type, value_compare, _rebind>			_tree_type;
				_tree_type												 	_tree;
			
			//  ---------------------MEMBER FUNCTIONS---------------------

			public:
			
				//  ---------------------CONSTRUCTORS---------------------

				//  Construct empty set :
				explicit set(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
					: _tree(value_compare(comp), alloc) {};
				
				//  Construct set based on a range :
				template <class InputIterator>
					set(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) 
						: _tree(value_compare(comp), alloc) { this->insert(first, last); };
				
				//  Construct Copy :
				set (set const &rhs) : _tree(rhs._tree) {}
				
				//  ---------------------DESTRUCTORS----------------------
				
				~set(void) {};


				//  -------------------ASSIGN OPERATOR--------------------

				//  Operator= :
				set		&operator=(const set &x) {
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
					return (this->_tree.max_size());
				}
				
				//  ----------------------MODIFIERS-----------------------
				
				
				//  Insert/tree::insert :
				ft::pair<iterator, bool>	insert(const value_type& val) { return (this->_tree.insert(val)); } //  Single element
				iterator 					insert(iterator position, const value_type& val) { (void)position; return (this->_tree.insert(val).first); } //  By hint
				template <class InputIterator>
					void 					insert(InputIterator first, InputIterator last) {	return (this->_tree.insert(first, last)); } //  By range

				//  Erase/tree::erase :
				void 					erase (iterator position) { return (this->_tree.erase(position)); }
				size_type 				erase (const value_type& val) { return (this->_tree.erase(val)); }
				void 					erase (iterator first, iterator last) { return (this->_tree.erase(first, last)); }

				//  Swap :
				void 					swap(set& x) { return (this->_tree.swap(x._tree)); }
				//  Clear :
				void 					clear(void) { return (this->_tree.clear()); }

				//  ----------------------OBSERVERS-----------------------

				//  Key compare :
				key_compare		key_comp(void) const { return (key_compare()); }
				
				//  Value compare :
				value_compare	value_comp(void) const { return (value_compare(key_compare())); }

				//  ----------------------OPERATIONS----------------------

				//  Find/tree::find :
				iterator		find (const value_type& val) { return (iterator(this->_tree.find(val))); }
				const_iterator	find (const value_type& val) const { return (const_iterator(this->_tree.find(val))); }
				
				//  Count/tree::count :
				size_type		count (const value_type& val) const { return (this->_tree.count(val)); }

				//  Lower bound/Tree::lower_bound :
				iterator		lower_bound (const value_type& val) { return (iterator(this->_tree.lower_bound(val))); }
				const_iterator	lower_bound (const value_type& val) const {	return (const_iterator(_tree.lower_bound(val))); }
				
				//  Upper bound/Tree::upper_bound :
				iterator		upper_bound (const value_type& val) { return (iterator(_tree.upper_bound(val))); }
				const_iterator	upper_bound (const value_type& val) const {	return (const_iterator(_tree.upper_bound(val))); }

				//  Equal range :
				ft::pair<iterator, iterator> 			equal_range (const value_type& val){ return (ft::make_pair(this->lower_bound(val), this->upper_bound(val))); }
				ft::pair<const_iterator,const_iterator>	equal_range( const value_type& val) const { return (ft::make_pair(this->lower_bound(val), this->upper_bound(val))); }
				
				//  --------------FRIEND RATIONAL OPERATORS---------------
				
				//  Operator== :
				template < class _T, class _Compare, class _Alloc >
					friend bool operator==( const ft::set<_T,_Compare,_Alloc>& lhs, const ft::set<_T,_Compare,_Alloc>& rhs );
				
				//  Operato< :
				template < class _T, class _Compare, class _Alloc >
					friend bool operator<( const ft::set<_T,_Compare,_Alloc>& lhs, const ft::set<_T,_Compare,_Alloc>& rhs );
		};

		//  ----------------NON-MEMBER FUNCTIONS OVERLOADS----------------

		//  ----------------------RATIONAL OPERATORS----------------------
			
		//  Operator== :
		template < class T, class Compare, class Alloc >
			bool operator==( const ft::set<T,Compare,Alloc>& lhs, const ft::set<T,Compare,Alloc>& rhs ) {
				if (lhs.size() != rhs.size())
					return (false);
				return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
			}
		
		//  Operator!= :
		template < class T, class Compare, class Alloc >
			bool operator!=( const ft::set<T,Compare,Alloc>& lhs, const ft::set<T,Compare,Alloc>& rhs ) { return (!(lhs == rhs)); }
		
		//  Operator< :
		template < class T, class Compare, class Alloc >
			bool operator<( const ft::set<T,Compare,Alloc>& lhs, const ft::set<T,Compare,Alloc>& rhs ) { return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }
		
		//  Operator> :
		template < class T, class Compare, class Alloc >
			bool operator>( const ft::set<T,Compare,Alloc>& lhs, const ft::set<T,Compare,Alloc>& rhs ) { return (rhs < lhs); }
		
		//  Operator<= :
		template < class T, class Compare, class Alloc >
			bool operator<=( const ft::set<T,Compare,Alloc>& lhs, const ft::set<T,Compare,Alloc>& rhs ) { return(!(rhs < lhs)); }
		
		//  Operator>= :
		template < class T, class Compare, class Alloc >
			bool operator>=( const ft::set<T,Compare,Alloc>& lhs, const ft::set<T,Compare,Alloc>& rhs ) { return (!(lhs < rhs)); }
};

#endif