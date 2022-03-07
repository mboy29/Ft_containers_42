/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssou <youssou@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 20:42:34 by youssou           #+#    #+#             */
/*   Updated: 2021/12/18 08:56:56 by youssou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <functional>
#include "RedBlackTree.hpp"
#include "Bidirectional.hpp"
#include "Bidirectional_Reverse.hpp"
#include "utils.hpp"

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > > 
	class map
	{
		private:
			typedef Node<Key, T> 													Node;
			typedef typename Alloc::template rebind<Node>::other 					rebind;
			typedef RedBlackTree<Key, T,char *, Compare, rebind>              		RBtree;
			typedef typename RBtree::mapped_type									RB_mapped_type;
			
		public:
			typedef	Key																key_type;
			typedef	T																mapped_type;
			typedef Alloc	                                           				allocator_type;
			typedef	ft::pair<key_type, mapped_type>									value_type;	
			typedef	Compare															key_compare;
			typedef	typename allocator_type::reference								reference;
			typedef	typename allocator_type::const_reference						const_reference; 
			typedef	typename allocator_type::pointer								pointer;
			typedef	typename allocator_type::const_pointer							const_pointer;	 
			typedef typename RBtree::iterator										iterator;
			typedef typename RBtree::const_iterator									const_iterator;
			typedef typename RBtree::reverse_iterator								reverse_iterator;
			typedef typename RBtree::const_reverse_iterator							const_reverse_iterator;
			typedef	size_t															size_type;
			typedef	typename ft::iterator_traits<iterator>::difference_type			difference_type;	 
			
			
			class  value_compare : public std::binary_function<value_type, value_type, bool>
			{
				friend class map<Key, T, Compare, Alloc>;
				protected:
					key_compare comp;
					value_compare(key_compare c) : comp(c) {}
				public:

					bool operator()(const value_type& a, const value_type& b) const
						{return comp(a.first, b.first);}
			};
		
		private:
			size_type               	_size;
			key_compare					_key_comp;
			allocator_type         		_allocator;
			RBtree						_tree;

			
		public:
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _key_comp(comp), _allocator(alloc){
			}
			
			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _key_comp(comp), _allocator(alloc){; 
				this->insert(first, last);
			}

			map (const map& x){
				if (*this != x){
					this->_key_comp = x.key_comp();
					this->_allocator = x.get_allocator();
					this->_tree = x._tree;
					this->_size = x.size();
				}	
			}
			
			~map(){
				
			}

			map& operator= (const map& x){
				if (*this != x){
					this->_key_comp = x.key_comp();
					this->_allocator = x.get_allocator();
					this->_tree = x._tree;
					this->_size = x.size();
				}
				return (*this);
			}
			
			iterator begin(){
				return (this->_tree.begin());
			}
			
			const_iterator begin() const{
				return (this->_tree.begin());
			}

			iterator end(){
				return (this->_tree.end());
			}
			
			const_iterator end() const{
				return (this->_tree.end());
			}
			
			reverse_iterator rbegin(){
				return (this->_tree.rbegin());
			}
			const_reverse_iterator rbegin() const{
				return (this->_tree.rbegin());
			}

			reverse_iterator rend(){
				return (this->_tree.rend());
			}
			
			const_reverse_iterator rend() const{
				return (this->_tree.rend());
			}

			bool empty() const{
				return (this->_tree.getSize() == 0);
			}

			size_type size() const{
				return (this->_tree.getSize());
			}

			size_type max_size() const{ 
				return std::numeric_limits<std::size_t>::max() / (sizeof(map));
			}

			RB_mapped_type& operator[] (const key_type& k){
				return(this->_tree.insert(k, mapped_type()).first->second);
			}

			ft::pair<iterator,bool> insert (const value_type& val){
				return (this->_tree.insert(val.first, val.second));
			}

			iterator insert (iterator position, const value_type& val){
				ft::pair<iterator,bool> ret = this->_tree.insert(val.first, val.second, position.base());
				return (ret.first);

			}

			template <class InputIterator>
			void insert (InputIterator first, InputIterator last){
				while (first != last){
					this->_tree.insert(first->first, first->second);
					first++;
				}
			}

			void erase (iterator position){
				this->_tree.erase(static_cast<typename RBtree::key_type>(position->first));
			}

			size_type erase (const key_type& k){
				return (this->_tree.erase(k));
			}
 
			void erase (iterator first, iterator last){
				while (first != last)
					erase(first++);
			}

			void swap (map& x){
				this->_tree.copy_tree(x._tree);
			}

			void clear(){
				this->_tree.clear();
			}

			key_compare key_comp() const{
				return (this->_key_comp);
			}

			value_compare value_comp() const{
				return (value_compare(this->_key_comp));
			}

			iterator find (const key_type& k){
				return (iterator(this->_tree.search(k)));
			}
			const_iterator find (const key_type& k) const{
				return (const_iterator(this->_tree.search(k)));
			}

			size_type count (const key_type& k) const{
				return (this->_tree.count(k));
			}
			
			iterator lower_bound (const key_type& k){
				return (this->_tree.lower_bound(k));
			}
			
			const_iterator lower_bound (const key_type& k) const{
				return (this->_tree.lower_bound(k));
			}

			iterator upper_bound (const key_type& k){
				return (this->_tree.upper_bound(k)); 
			}
			const_iterator upper_bound (const key_type& k) const{
				return (this->_tree.upper_bound(k)); 
			}

			ft::pair<const_iterator,const_iterator> equal_range (const key_type& k) const{
				ft::pair<const_iterator, const_iterator> ret(this->lower_bound(k), this->upper_bound(k));
				return (ret);
			}
			
			ft::pair<iterator,iterator> equal_range (const key_type& k){
				ft::pair<iterator, iterator> ret(this->lower_bound(k), this->upper_bound(k));
				return (ret);
			}

			allocator_type get_allocator() const{
				return (this->_allocator);
			}
	};
	
	template< class Key, class T, class Compare, class Alloc >
	bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ){
		if (lhs.size() != rhs.size())
			return (false);
		typename ft::map<Key,T,Compare,Alloc>::const_iterator beg1 = lhs.begin();
		typename ft::map<Key,T,Compare,Alloc>::const_iterator beg2 = rhs.begin();
		typename ft::map<Key,T,Compare,Alloc>::const_iterator end1 = lhs.end();
		typename ft::map<Key,T,Compare,Alloc>::const_iterator end2 = rhs.end();
		
		while (beg1 != end1){
			if (*beg1 != *beg2)
				return false;
			beg1++;
			beg2++;	
		}
		return (true);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ){
		return (!(lhs == rhs));
	}
	
	template <class Key, class T, class Compare, class Alloc>
  	bool operator<  ( const map<Key,T,Compare,Alloc>& lhs,  const map<Key,T,Compare,Alloc>& rhs ){
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));	  
	}

	template <class Key, class T, class Compare, class Alloc>
  	bool operator<= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ){
		return (!(rhs < lhs));	  
	}
	template <class Key, class T, class Compare, class Alloc>
  	bool operator>  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ){
		return (rhs < lhs);	  
	}

	template <class Key, class T, class Compare, class Alloc>
  	bool operator>= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ){
		return (!(lhs < rhs));  
	}

	template <class Key, class T, class Compare, class Alloc>
  	void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y){
		x.swap(y);	  
	}
	
} 


#endif