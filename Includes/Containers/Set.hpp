#ifndef SET_HPP
#define SET_HPP
#include <memory>						   	//  Allocator
#include <functional>					   	//  Less -> Determines whether its first argument compares less than the second
#include "../Utilities/Pair.hpp"		   	//  Pair
#include "../Utilities/Iterators/Set_iterator.hpp" 	//  Tree Iterator
#include "../Utilities/Trees/Set_node.hpp"	   	//  Tree Node
#include "../Utilities/Trees/Set_tree.hpp"	   	//  Tree

//  ----------------------------SET CONTAINER----------------------------

//  ---------------------------------------------------------------------

namespace ft  {
	
	template <class T, class Compare = std::less<T>, class Alloc = std::allocator<ft::pair<const T, T> > >
		class set {
			//  ---------------------MEMBER TYPES------------------------
			
			public:
				typedef T																key_type;
				typedef T																mapped_type;
				typedef ft::pair<const key_type, mapped_type>							value_type;
				typedef	ft::set_node<value_type, Alloc>									node_type;
				typedef ft::set_tree<ft::pair< const T, T>, Compare, Alloc>				tree_type;
				typedef Compare															key_compare;
				typedef Alloc															allocator_type;
				typedef typename allocator_type::reference								reference;
				typedef typename allocator_type::const_reference						const_reference;
				typedef typename allocator_type::pointer								pointer;
				typedef typename allocator_type::const_pointer							const_pointer;
				typedef ft::set_iterator<value_type, node_type, tree_type>				iterator;
				typedef ft::set_iterator<const value_type, node_type, const tree_type>	const_iterator;
				typedef ft::reverse_iterator<iterator>									reverse_iterator;
				typedef	ft::reverse_iterator<const_iterator>							const_reverse_iterator;
				typedef	ptrdiff_t														difference_type;
				typedef	size_t															size_type;
				
				class value_compare : public std::binary_function<value_type,value_type,bool> {   
					
					protected:
						Compare comp;
					
					public:
						typedef bool		result_type;
						typedef value_type	first_argument_type;
						typedef value_type	second_argument_type;
						
						value_compare (Compare c) : comp(c) {}
						bool operator()(const value_type& rhs, const value_type& lhs) const { return (comp(rhs.first, lhs.first)); }
				};

				private:
					tree_type	_tree;
					Compare		_comp;
					Alloc		_alloc;
					size_type	_size;
				
				//  --------------------MEMBER FUNCTION----------------------

				public:

					//  -------------------CONSTRUCTOR-----------------------

					//  Default constructor :
					explicit set(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _comp(comp), _alloc(alloc), _size(0) {}

					//  Fill constructor :
					template <class InputIterator>
						set(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _comp(comp), _alloc(alloc), _size(0) {
							while (first != last)
								this->insert(*first++);
						}

					//  Copy construcotr
					set (const set& rhs) { *this = rhs; }

					//  -------------------DESTRUCTOR------------------------

					~set(void) {}

					//  --------------------OPERATOR=------------------------

					//  Operator= :
					set&	operator=(const set& rhs) {
						if (this != &rhs) {
							this->clear();
							this->insert(rhs.begin(),rhs.end());
							this->_comp = rhs._comp;
							this->_alloc = rhs._alloc;
							this->_size = rhs._size;
						}
						return (*this);
					}

					//  --------------------ITERATORS------------------------
				
					//  Begin :
					iterator				begin(void) { return (this->_tree.begin()); }
					const_iterator			begin(void) const { return (this->_tree.begin()); }

					//  End :
					iterator				end(void) { return (this->_tree.end()); }
					const_iterator			end(void) const { return (this->_tree.end()); }

					//  Reverse begin :
					reverse_iterator		rbegin(void) { return (this->_tree.rbegin()); }
					const_reverse_iterator	rbegin(void) const { return (this->_tree.rbegin()); }
					
					//  Reverse end :
					reverse_iterator		rend(void) { return (this->_tree.rend()); }
					const_reverse_iterator	rend(void) const { return (this->_tree.rend()); }

					//  --------------------CAPACITY-------------------------
				
					//  Empty :
					bool		empty(void) const { return (this->_tree.empty()); }

					//  Size :
					size_type	size(void) const { return (this->_size); }

					//  Max size :
					size_type	max_size(void) const { return (this->_tree.max_size()); }

					//  ---------------------MODIFIERS-----------------------
					
					// Insert (single element):
					pair<iterator,bool>	insert(const value_type& val) {
						bool idx = false;
						node_type *tmp = NULL;
						
						if (!(tmp = this->_tree.search(val))) {
							idx = true;
							this->_tree.insert(val);
							tmp = this->_tree.search(val);
							this->_size += 1;
						}
						return (ft::make_pair(iterator(tmp, &this->_tree), idx));
					}

					//  Insert (with hint) :
					iterator			insert(iterator position, const value_type& val) {
						(void)position;
						return ((this->insert(val)).first);
					}
				
					//  Insert (range) :
					template <class InputIterator>
						void insert (InputIterator first, InputIterator last) {
							while (first != last)
								this->insert(*first++);
						}
					
					//  Erase (element erase not returned) :
					void erase (iterator position) {
						this->_tree.erase(*position);
						this->_size -= 1;
					}

					//  Erase (element erase returned) :
					size_type	erase(const key_type& k) {
						if (this->_tree.erase(ft::make_pair(k, mapped_type()))) {
							this->_size -= 1;
							return (1);
						}
						return (0);
					}

					//  Erase (range) :
					void		erase(iterator first, iterator last) {
						ft::vector<key_type> tmp;
						
						while (first != last) {
							tmp.push_back(first->first);
							++first;
						}
						for (size_type idx = 0; idx < tmp.size(); idx += 1)
							this->erase(tmp[idx]);
					}

					//  Swap :
					void		swap(set& x) {
						std::swap(this->_size, x._size);
						std::swap(this->_alloc, x._alloc);
						std::swap(this->_comp, x._comp);
						this->_tree.swap(x._tree);
					}

					//  Clear :
					void 		clear(void) {
						this->_tree.clear();
						this->_size = 0;
					}

					//  ---------------------OBSERVERS-----------------------

					//  Key compare :
					key_compare		key_comp(void) const { return (this->_comp); }

					//  Value compaire :
					value_compare	value_comp(void) const { return (value_compare(this->_comp)); }

					//  ---------------------OPERATIONS----------------------
					
					//  Find :
					iterator		find(const key_type& key) { return (this->_tree.find(ft::make_pair(key, mapped_type()))); }

					//  Const find
					const_iterator	find(const key_type& key) const { return (this->_tree.find(ft::make_pair(key, mapped_type()))); }

					//  Count :
					size_type		count(const key_type& key) const { return (this->_tree.count(key)); }

					//  Lower bound :
					iterator		lower_bound(const key_type& key) { return (this->_tree.lower_bound(key)); }
					const_iterator	lower_bound(const key_type& key) const { return (this->_tree.lower_bound(key)); }

					//  Upper bound :
					iterator		upper_bound(const key_type& key) { return (this->_tree.upper_bound(key)); }
					const_iterator	upper_bound(const key_type& key) const { return (this->_tree.upper_bound(key)); }

					//  Equal range :
					pair<iterator,iterator>					equal_range(const key_type& key) { return (ft::make_pair<iterator, iterator>(lower_bound(key), upper_bound(key))); }
					pair<const_iterator, const_iterator>	equal_range(const key_type& key) const { return (ft::make_pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key))); }

					//  ----------------------ALLOCATOR----------------------
					
					//  Get allocator
					allocator_type	get_allocator(void) const { return (this->_alloc); }
			};

		
		//  ------------------NON-MEMBER FUNCTIONS OVERLOADS-----------------
		
			//  ---------------------RATIONAL OPERATORS----------------------
		
			//  Operator== :
			template <class T, class Compare, class Alloc>
				bool operator==(const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs) {
					return ((lhs.size() == rhs.size()) && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
				}
			
			//  Operator!= :
			template <class T, class Compare, class Alloc>
				bool operator!=(const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs) {
					return !(lhs == rhs);
				}
			
			//  Operator< :
			template <class T, class Compare, class Alloc>
				bool operator<(const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs) {
					return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
				}
			
			//  Operator> :
			template <class T, class Compare, class Alloc>
				bool operator>( const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs) {
					return (rhs < lhs);
				}
			
			//  Operator<= :
			template <class T, class Compare, class Alloc>
				bool operator<=(const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs) {
					return !(rhs < lhs);
				}
			
			//  Operator>= :
			template <class T, class Compare, class Alloc>
				bool operator>=(const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs) {
					return !(lhs < rhs);
				}

			//  ----------------------------SWAP-----------------------------
			
			template <class T, class Compare, class Alloc>
				void swap(set<T, Compare, Alloc>& rhs, set<T, Compare, Alloc>& lhs) { rhs.swap(lhs); }

};

#endif