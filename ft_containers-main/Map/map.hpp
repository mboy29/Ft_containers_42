/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 16:08:09 by sel-fadi          #+#    #+#             */
/*   Updated: 2022/02/01 16:39:58 by sel-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <vector>
#include "redBlackTree.hpp"
#include "pair.hpp"
#include "mapIterator.hpp"
#include "../tools/reverse_iterator.hpp"

namespace ft  {
	
	 template < class Key,                                     // map::key_type
			class T,                                       // map::mapped_type
			class Compare = std::less<Key>,                     // map::key_compare
			class Alloc = std::allocator<ft::pair<const Key, T> >    // map::allocator_type
			>
	class Map
	{
		
		public:
			typedef Key			key_type;
			typedef T			mapped_type;
			typedef ft::pair<const key_type,mapped_type> value_type;
			typedef Compare		key_compare;
			typedef Alloc		allocator_type;
			typedef	RedBlackNode<value_type, Alloc>	RedBlack;
			typedef RedBlackTree<ft::pair< const Key, T>, Compare, Alloc> rbt;
			typedef typename    allocator_type::reference           reference;
			typedef typename    allocator_type::const_reference     const_reference;
			typedef typename    allocator_type::pointer             pointer;
			typedef typename    allocator_type::const_pointer       const_pointer;
			
			typedef ft::MapIterator<value_type, RedBlack, rbt > iterator;
			typedef ft::MapIterator<const value_type, RedBlack, const rbt > const_iterator;
			
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
							return comp(x.first, y.first);
						}
				};
			
            explicit Map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _cmp(comp), _alloc(alloc), _size(0) {}
            
            template <class InputIterator>
				Map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _cmp(comp), _alloc(alloc), _size(0)
				{
					while (first != last)
					{
						this->insert(*first);
						first++;
					}
				}
            
            Map (const Map& x) { *this = x; }
			
			Map& operator= (const Map& x)
			{
				this->clear();
				this->insert(x.begin(),x.end());
				this->_cmp = x._cmp;
				this->_alloc = x._alloc;
				this->_size = x._size;
				return *this;
			}
			
			~Map()
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

			mapped_type& operator[] (const key_type& k) { return (*((this->insert(ft::make_pair(k,mapped_type()))).first)).second; }
			
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
				return (this->insert(val)).first;
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
			
			size_type erase (const key_type& k)
			{
				if (this->_rbt.deleteByVal(ft::make_pair(k, mapped_type())))
				{
					this->_size--;
					return 1;
				}
				return 0;
			}
			void erase (iterator first, iterator last)
			{
				std::vector<key_type> tmp;
				
				while (first != last)
				{
					tmp.push_back(first->first);
					++first;
				}
				for (size_type i = 0; i < tmp.size(); i++)
					this->erase(tmp[i]);
			}
			
			void	swap (Map& x)
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

			iterator find (const key_type& k)
			{
				value_type val = ft::make_pair(k, mapped_type());
				return this->_rbt.find(val);
			}
			const_iterator find (const key_type& k) const
			{
				value_type val = ft::make_pair(k, mapped_type());
				return this->_rbt.find(val);
			}

			size_type count (const key_type& k) const
			{
				return this->_rbt.count(k);
			}

			iterator lower_bound (const key_type& k)
			{
				return this->_rbt.lower_bound(k);
			}
			 const_iterator lower_bound (const key_type& k) const
			{
				return this->_rbt.lower_bound(k);
			}

			iterator upper_bound (const key_type& k)
			{
				return this->_rbt.upper_bound(k);
			}
			const_iterator upper_bound (const key_type& k) const
			{
				return this->_rbt.upper_bound(k);
			}

			pair<iterator,iterator>             equal_range (const key_type& k)
			{
				return (ft::make_pair<iterator, iterator>(lower_bound(k), upper_bound(k)));
			}
			pair<const_iterator,const_iterator> equal_range (const key_type& k) const
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
	
	template <class Key, class T, class Compare, class Alloc>
		void swap (Map<Key,T,Compare,Alloc>& x, Map<Key,T,Compare,Alloc>& y)
		{ x.swap(y); }
	
	template <class Key, class T, class Compare, class Alloc>
		bool operator== ( const Map<Key,T,Compare,Alloc>& lhs, const Map<Key,T,Compare,Alloc>& rhs )
			{ return ((lhs.size() == rhs.size()) && ft::map_equal(lhs.begin(), lhs.end(), rhs.begin()));}
	template <class Key, class T, class Compare, class Alloc>
		bool operator!= ( const Map<Key,T,Compare,Alloc>& lhs, const Map<Key,T,Compare,Alloc>& rhs )
		{ return !(lhs == rhs); }
	template <class Key, class T, class Compare, class Alloc>
		bool operator<  ( const Map<Key,T,Compare,Alloc>& lhs, const Map<Key,T,Compare,Alloc>& rhs )
		{ return ft::map_lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }
	template <class Key, class T, class Compare, class Alloc>
		bool operator<= ( const Map<Key,T,Compare,Alloc>& lhs, const Map<Key,T,Compare,Alloc>& rhs )
		{ return !(rhs < lhs); }
	template <class Key, class T, class Compare, class Alloc>
		bool operator>  ( const Map<Key,T,Compare,Alloc>& lhs, const Map<Key,T,Compare,Alloc>& rhs )
		{ return (rhs < lhs); }
	template <class Key, class T, class Compare, class Alloc>
		bool operator>= ( const Map<Key,T,Compare,Alloc>& lhs, const Map<Key,T,Compare,Alloc>& rhs )
		{ return !(lhs < rhs); }
	
};