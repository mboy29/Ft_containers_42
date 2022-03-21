#ifndef set_HPP
#define set_HPP
#include <memory>						   	//  Allocator
#include <functional>					   	//  Less -> Determines whether its first argument compares less than the second
#include "../Utilities/Pair.hpp"		   	//  Pair
#include "../Utilities/Trees/Node.hpp"	   	//  Tree Node
#include "../Utilities/Trees/Iterator.hpp" 	//  Tree Iterator
#include "../Utilities/Trees/Tree.hpp"	   	//  Tree

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
	 	 template < class T,                        // set::key_type/value_type
           class Compare = std::less<T>,        // set::key_compare/value_compare
           class Alloc = std::allocator<T>      // set::allocator_type
           >
	class set
	{
		
		public:
			typedef T			value_type;
			typedef Compare		key_compare;
			typedef Alloc		allocator_type;
			typedef	ft::tree_node<value_type, Alloc>	RedBlack;
			typedef ft::tree<value_type, Compare, Alloc> rbt;
			typedef typename    allocator_type::reference           reference;
			typedef typename    allocator_type::const_reference     const_reference;
			typedef typename    allocator_type::pointer             pointer;
			typedef typename    allocator_type::const_pointer       const_pointer;
			
			typedef ft::tree_iterator<value_type, RedBlack, rbt > iterator;
			typedef ft::tree_iterator<const value_type, RedBlack, const rbt > const_iterator;
			
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef	ft::reverse_iterator<const_iterator> const_reverse_iterator;
			
			typedef	ptrdiff_t	difference_type;
			typedef	size_t		size_type;
				class value_compare : public std::binary_function<value_type,value_type,bool>
				{   
					protected:
						Compare comp;
					public:
						value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
						typedef bool result_type;
						typedef value_type first_argument_type;
						typedef value_type second_argument_type;
						bool operator() (const value_type& x, const value_type& y) const
						{
							return comp(x, y);
						}
				};
			
            explicit set (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _cmp(comp), _alloc(alloc), _size(0) {}
            
            template <class InputIterator>
				set (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _cmp(comp), _alloc(alloc), _size(0)
				{
					while (first != last)
					{
						this->insert(*first);
						first++;
					}
				}
            
            set (const set& x) { *this = x; }
			
			set& operator= (const set& x)
			{
				this->clear();
				this->insert(x.begin(),x.end());
				this->_cmp = x._cmp;
				this->_alloc = x._alloc;
				this->_size = x._size;
				return *this;
			}
			
			~set()
			{
			}
			
			iterator begin() { return this->_rbt.begin(); }
            const_iterator begin() const { return this->_rbt.begin(); }
            iterator end() { return this->_rbt.end(); }
            const_iterator end() const { return this->_rbt.end(); }
			
			reverse_iterator rbegin() { return this->_rbt.rbegin(); }
            const_reverse_iterator rbegin() const { return this->_rbt.rbegin(); }
            reverse_iterator rend() { return this->_rbt.rend(); }
            const_reverse_iterator rend() const { return this->_rbt.rend(); }

			bool empty() const { return this->_rbt.empty(); }
            size_type size() const { return this->_size; }
            size_type max_size() const { return this->_rbt.max_size(); }

			
			// insert
			pair<iterator,bool> insert (const value_type& val)
			{
				RedBlack *tmp = this->_rbt.search(val);
				bool found = false;
				if (tmp == NULL)
				{
					found = true;
					this->_rbt.insertion(val);
					tmp = this->_rbt.search(val);
					this->_size++;
				}
				return ft::make_pair(iterator(tmp, &this->_rbt), found);
			}
			
			iterator insert (iterator position, const value_type& val)
			{
				(void)position;
				return (this->insert(val));
			}
			template <class InputIterator>
  				void insert (InputIterator first, InputIterator last)
				{
					while (first != last)
					{
						this->insert(*first);
						++first;
					}
				}
				
			// erase
			void erase (iterator position)
			{
				this->_rbt.deleteByVal(*position);
					this->_size--;
			}
			
			size_type erase (const value_type& k)
			{
				if (this->_rbt.deleteByVal(k))
				{
					this->_size--;
					return 1;
				}
				return 0;
			}
			void erase (iterator first, iterator last)
			{
				std::vector<value_type> tmp;
				
				while (first != last)
				{
					tmp.push_back(first->first);
					++first;
				}
				for (size_type i = 0; i < tmp.size(); i++)
				{
					this->erase(tmp[i]);
				}
			}
			
			void	swap (set& x)
			{
				std::swap(_size, x._size);
				std::swap(_alloc, x._alloc);
				std::swap(_cmp, x._cmp);
				this->_rbt.swap(x._rbt);
			}
			
			void clear()
			{
				this->_rbt.clear();
				this->_size = 0;
			}

			key_compare key_comp() const
			{
				return this->_cmp;
			}
			value_compare value_comp() const
			{
				return value_compare(_cmp);
			}

			iterator find (const value_type& k)
			{
				return this->_rbt.find(k);
			}
			const_iterator find (const value_type& k) const
			{
				return this->_rbt.find(k);
			}

			size_type count (const value_type& k) const
			{
				return this->_rbt.count(k);
			}

			iterator lower_bound (const value_type& k)
			{
				return this->_rbt.lower_bound(k);
			}
			 const_iterator lower_bound (const value_type& k) const
			{
				return this->_rbt.lower_bound(k);
			}

			iterator upper_bound (const value_type& k)
			{
				return this->_rbt.upper_bound(k);
			}
			const_iterator upper_bound (const value_type& k) const
			{
				return this->_rbt.upper_bound(k);
			}

			pair<iterator,iterator>             equal_range (const value_type& k)
			{
				return (ft::make_pair<iterator, iterator>(lower_bound(k), upper_bound(k)));
			}
			pair<const_iterator,const_iterator> equal_range (const value_type& k) const
			{
				return (ft::make_pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k)));
			}

			allocator_type get_allocator() const
			{
				return this->_alloc;
			}
			private:
				rbt _rbt;
				Compare _cmp;
				Alloc _alloc;
				size_type _size;
	};

	template <class InputIterator1, class InputIterator2>
	bool map_equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
	{
		while (first1!=last1) {
			if (!(*first1 == *first2))   // or: if (!pred(*first1,*first2)), for version 2
			return false;
			++first1; ++first2;
		}
		return true;
	}

	template <class InputIterator1, class InputIterator2>
	bool map_lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
									InputIterator2 first2, InputIterator2 last2)
	{
		while (first1!=last1)
		{
			if (first2==last2 || *first2<*first1) return false;
			else if (*first1<*first2) return true;
			++first1; ++first2;
		}
		return (first2!=last2);
	}
	
	template <class T, class Compare, class Alloc>
		void swap (set<T,Compare,Alloc>& x, set<T,Compare,Alloc>& y)
		{ x.swap(y); }
	
	template <class T, class Compare, class Alloc>
		bool operator== ( const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs )
			{ return ((lhs.size() == rhs.size()) && ft::map_equal(lhs.begin(), lhs.end(), rhs.begin()));}
	template <class T, class Compare, class Alloc>
		bool operator!= ( const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs )
		{ return !(lhs == rhs); }
	template <class T, class Compare, class Alloc>
		bool operator<  ( const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs )
		{ return ft::map_lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }
	template <class T, class Compare, class Alloc>
		bool operator<= ( const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs )
		{ return !(rhs < lhs); }
	template <class T, class Compare, class Alloc>
		bool operator>  ( const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs )
		{ return (rhs < lhs); }
	template <class T, class Compare, class Alloc>
		bool operator>= ( const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs )
		{ return !(lhs < rhs); }
};

#endif