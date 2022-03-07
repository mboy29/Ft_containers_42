/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedBlackTree.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssou <youssou@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 13:43:54 by youssou           #+#    #+#             */
/*   Updated: 2021/12/01 16:38:55 by youssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDBLACKTREE_HPP
# define REDBLACKTREE_HPP

# include <cstddef>
# include <iostream>
#include "Bidirectional.hpp"
#include "Set_Iterator.hpp"
#include "Bidirectional_Reverse.hpp"
#include <cstdlib>
#include "utils.hpp"

enum color{
	black, red
};

template <class K, class V>
struct Node{
	int     				color;
	Node    				*parent;
	Node    				*left;
	Node    				*right;
	ft::pair<K,V> 			_pair;
	K      	 				key;
	V       				value;
	Node 					**root;
	int 					is_Nleaf;
};

template <class K, class V, class T = char *,  class Compare = std::less<K>, class Alloc = std::allocator<Node<K, V> > >
class RedBlackTree{
	
	public:
		typedef Node<K, V> 														Node;
		typedef	Compare															key_compare;
		typedef ft::pair<K, V>													pair;
		typedef	K																key_type;
		typedef	V																mapped_type;
		typedef Alloc	                                           				allocator_type;
		typedef	ft::pair<key_type, mapped_type>									value_type;
		typedef typename ft::condition<ft::is_integral<T>::value, ft::setIterator<const Node, const K>, ft::bidirectional<Node, K, V> >::type iterator;
		typedef typename ft::condition<ft::is_integral<T>::value, ft::setIterator<const Node, const K>, ft::bidirectional<const Node, const K, const V> >::type const_iterator;
		typedef	ft::bidirectional_reverse<iterator>								reverse_iterator;
		typedef	ft::bidirectional_reverse<const_iterator>						const_reverse_iterator;
		typedef	size_t															size_type;

 
	private:
		Node			*_root;
		Node			*_Nleaf;
		std::size_t		_size;
		Alloc			_allouageur;
		key_compare		_key_comp;
		Node 			*_End;
		Node			*deleted_nodes;
	
	public:
	
		class  value_compare : public std::binary_function<K, K, bool>
		{
			friend class RedBlackTree;
			protected:
				key_compare comp;
				value_compare(key_compare c) : comp(c) {}
			public:
				bool operator()(const K& a, const K& b) const
					{return comp(a, b);}
		};
			
		Node *next;
	
		RedBlackTree(const key_compare& comp = key_compare()) : _key_comp(comp){
			_End = this->_allouageur.allocate(1);
            _Nleaf = this->_allouageur.allocate(1);
			this->_Nleaf->color = black;
			this->_Nleaf->left = nullptr;
			this->_Nleaf->parent = nullptr; 
			this->_Nleaf->right = nullptr;
			this->_Nleaf->root = &this->_root;
			_End->root = &this->_root;
			_Nleaf->is_Nleaf = 1;
			this->_root = nullptr;
			_size = 0;
			deleted_nodes = _Nleaf;
		}

		RedBlackTree(K key, V value){
			static_cast<void>(key);	
			static_cast<void>(value);	
		}
		std::size_t max_size() const{ 
			return std::numeric_limits<std::size_t>::max() / sizeof(_allouageur.max_size());
		}
		std::size_t	getSize( void ) const{
			return (this->_size);
		};

		void desalouage(Node *tmp){
			if (tmp->is_Nleaf == 1)
				return ;
			desalouage(tmp->left);
			this->_size--;
			desalouage(tmp->right);
			_allouageur.deallocate(tmp, 1);
		};
		
		RedBlackTree(RedBlackTree &copy){
			*this = copy;
		};

		Node *copy_node(Node *dest, Node *src){
			dest->parent = nullptr;
			dest->color = src->color;
			dest->is_Nleaf = src->is_Nleaf;
			return (dest);
		}
		
		void copy_tree(Node *node, Node *parent, Node *copy){
			if (copy->is_Nleaf || node->is_Nleaf == 1)
				return ;
			if (copy->left->is_Nleaf == 0){
				node->left = _allouageur.allocate(1);
			}
			else
				node->left = this->_Nleaf;
			if (copy->right->is_Nleaf == 0){
				node->right = _allouageur.allocate(1);
			}
			else
				node->right = this->_Nleaf;
			node->parent = parent;
			node->key = copy->key;
			node->color = copy->color;
			node->value = copy->value;
			node->_pair = copy->_pair;
			node->is_Nleaf = copy->is_Nleaf;
			node->root = &this->_root;
			
			copy_tree(node->left, node, copy->left);
			copy_tree(node->right, node, copy->right);
		}
		
		RedBlackTree& operator=(const RedBlackTree &copy){
			if (copy.getSize() == 0)
			{
				this->clear();
				return (*this);
			}
			if (this->_size){
				desalouage(this->_root);	
			}

			this->_allouageur = copy._allouageur;
			this->_key_comp = copy._key_comp;
			this->_size = copy._size;
			this->_Nleaf->root = &this->_root;
			_Nleaf->is_Nleaf = 1;
			this->_root = nullptr;
			this->_root = _allouageur.allocate(1);
			copy_tree(this->_root, nullptr, copy._root);
			return (*this);
		};
		
		void free_deleted_nodes(Node *tmp){
			if (tmp->is_Nleaf == 1)
				return ;
			free_deleted_nodes(tmp->right);
			_allouageur.deallocate(tmp, 1);
		}
		
		~RedBlackTree(){
			if (deleted_nodes != _Nleaf)
				free_deleted_nodes(deleted_nodes);
			if (this->_size){
				desalouage(this->_root);	
			}
			_allouageur.deallocate(_Nleaf, 1);
			_allouageur.deallocate(_End, 1);
			
		};

		iterator begin(){
			if (this->_size){
				Node *tmp = this->_root;
				while (tmp->left != _Nleaf){
					tmp = tmp->left;
				}
				return (iterator(tmp));
			}
			return (iterator(this->_End));
		}

		const_iterator begin() const{
			if (this->_size){
				Node *tmp = this->_root;
				while (tmp->left != _Nleaf){
					tmp = tmp->left;
				}
				return (const_iterator(tmp));
			}
			return (const_iterator(this->_End));
		}

		reverse_iterator rbegin(){
			return (reverse_iterator(this->end()));
		}

		const_reverse_iterator rbegin() const{
			return (const_reverse_iterator(this->end()));
		}

		iterator end() {
			if (this->_size){
				_End->parent = nullptr;
				this->_root->parent = _End;
				_End->left = this->_root;
				return (iterator(_End));
			}
			return (iterator(_End));
		}		

		const_iterator end() const{
			if (this->_size){
				_End->parent = nullptr;
				this->_root->parent = _End;
				_End->left = this->_root;
				return (const_iterator(_End));
			}
			return (const_iterator(_End));
		}
		
		reverse_iterator rend() {
			return (reverse_iterator(this->begin()));
		}
		const_reverse_iterator rend() const{
			return (const_reverse_iterator(this->begin()));
		}

		Node *createNewNode(K key, V value){

			Node *newnode =  this->_allouageur.allocate(3);
			newnode->key = key;
			newnode->value = value;
			newnode->parent = nullptr;
			newnode->left = this->_Nleaf;
			newnode->right = this->_Nleaf;
			newnode->color = red;
			
			newnode->_pair = ft::make_pair(key, value);
			newnode->root = &this->_root;
			newnode->is_Nleaf = 0;
			return (newnode);
		}

		void rotate_right(Node *newnode){
			Node *child = newnode->left;
			newnode->left = child->right;
			if (child->right != this->_Nleaf)
				child->right->parent = newnode;
			child->parent = newnode->parent;
			if (!newnode->parent || newnode->parent == this->_End)
				this->_root = child;
			else{
				if (newnode == newnode->parent->right)
					newnode->parent->right = child;
				else
					newnode->parent->left = child;
			}
			child->right = newnode;
			newnode->parent = child;
		}

		void rotate_left(Node *newnode){
			Node *child = newnode->right;
			newnode->right = child->left;
			if (child->left != this->_Nleaf)
				child->left->parent = newnode;
			child->parent = newnode->parent;
			if (!newnode->parent || newnode->parent == this->_End)
				this->_root = child;
			else{
				if (newnode == newnode->parent->left)
					newnode->parent->left = child;
				else
					newnode->parent->right = child;
			}
			child->left = newnode;
			newnode->parent = child;
		}
		
		Node *copy_node(Node *dest, const Node *src){
			
			dest->key = src->key;
			dest->value = src->value;
			dest->parent = src->parent;
			dest->left = src->left;
			dest->right = src->right;
			dest->color = src->color;
			dest->_pair = src->_pair;
			dest->root = &this->_root;
			dest->is_Nleaf = src->is_Nleaf;

			return dest;
		}
		
		void recolor_rotate(Node *newnode){
			while (newnode->parent->color == red){
				Node *parent = newnode->parent;
				Node *grand_parent = parent->parent;
				if (parent == grand_parent->left){
					Node *uncle = grand_parent->right;
					if (uncle->color == red){
						uncle->color = black;
						parent->color = black;
						grand_parent->color = red;
						newnode = grand_parent;
					}
					else{
						if (newnode == newnode->parent->right){
							newnode = newnode->parent;
							rotate_left(newnode);
						}	
					newnode->parent->color = black;
					newnode->parent->parent->color = red;
					rotate_right(newnode->parent->parent);
					} 
				}
				else{
					if (parent == grand_parent->right){
						Node *uncle = grand_parent->left;
						if (uncle->color == red){
							uncle->color = black;
							parent->color = black;
							grand_parent->color = red;
							newnode = grand_parent;
						}
						else{	
							if (newnode == newnode->parent->left){
								newnode = newnode->parent;
								rotate_right(newnode);
							}	
							newnode->parent->color = black;
							newnode->parent->parent->color = red;
							rotate_left(newnode->parent->parent);
						} 
					}	
				}
				if (newnode == this->_root)
					break;
			}
			this->_root->color = black;
		}

		ft::pair<iterator, bool> insert(K key, V value, const Node *pos= nullptr){
			value_compare comp(this->_key_comp);
			Node *newnode = createNewNode(key, value);
			if (!this->_root){
				this->_root = newnode;
				this->_root->color = black;
				this->_size++;
			
				_End->parent = nullptr;
				this->_root->parent = _End;
				
				Node *test = static_cast<Node *>(this->_root);
				iterator toto(test);
				return (ft::make_pair(toto, true));
			}

			Node *tmp = this->_root;
			if (pos != nullptr && pos != this->_root && pos != this->_End){
				tmp = createNewNode(key, value);
				if(comp(key, pos->key)){
					if (comp(key, pos->parent->key))
						tmp = this->_root;
					else{
						tmp = copy_node(tmp, pos);
					}
				}
				else if (comp(pos->key, key)){
					if (comp(pos->parent->key, key))
						tmp = this->_root;
					else{
						tmp = copy_node(tmp, pos);
					}
				}
				else
					tmp = this->_root;
			}

			while (tmp != newnode){
				if (comp(tmp->key, key)){
					if (tmp->right == this->_Nleaf){
						newnode->parent = tmp;
						tmp->right = newnode;	
					}
					tmp = tmp->right;
				}
				else if (comp(key, tmp->key)){
					if (tmp->left == this->_Nleaf){
						newnode->parent = tmp;
						tmp->left = newnode;
					}
					tmp = tmp->left;
				}
				else{
					return (ft::make_pair(iterator(tmp), false));
				}
				
			}
			this->_size++;
			recolor_rotate(newnode);
			return (ft::make_pair(iterator(tmp), true));
		}
		
		Node *getNext(Node *node){
			Node *next;
			if (node->right == _Nleaf){
				Node *tmp = node->parent; 
				while (tmp->key <= node->key){
					if (tmp == this->_root)
						return tmp;
					tmp = tmp->parent;
				}	
				next = tmp;
				return (next);
			}
			Node *min = getMin(node->right);
			if (node == this->_Nleaf)
				return (node);
			if (min == _Nleaf){
				Node *tmp = node; 
				while (tmp->parent->key < node->key){
					tmp = tmp->parent;
				}	
				next = tmp;
			}
			else
				next = min;
			return (next);
		}

		Node *getMax(Node *node){
			while (node->right != this->_Nleaf)
				node = node->right;
			return node;
		}
		
		Node *getMin(Node *node){
			while (node->left != this->_Nleaf)
				node = node->left;
			return node;
		}

		
		void echange(Node *to_be_removed, Node *removed)
		{
			if (to_be_removed->parent == nullptr || to_be_removed->parent == this->_End)
			{
				removed->parent = this->_root->parent;
				this->_root = removed;
				return ;
			}
			if (to_be_removed == to_be_removed->parent->left)
			{
				removed->parent = to_be_removed->parent;
				to_be_removed->parent->left = removed;
			}
			else
			{
				removed->parent = to_be_removed->parent;
				to_be_removed->parent->right = removed;
			}
		}
		
		size_type erase(const K &key){
			
			size_type count = 0;
			while (search(key) != this->_End){
				deletion(key);
				count++;
			}
			return (count);
		}

		const_iterator upper_bound(const K& key) const{
			Node *tmp = this->_root;
			Node *save;
			value_compare comp(this->_key_comp);
			while (tmp != this->_Nleaf){
				save = tmp;
				if (comp(key, tmp->key))
				 	tmp = tmp->left;
				else if (comp(tmp->key, key))
				 	tmp = tmp->right;
				else
					return (++const_iterator(tmp));
			}
			tmp = save;
			if (comp(tmp->key, key))
				return (++const_iterator(tmp));
			else
				return (const_iterator(tmp));
		}

		
		iterator upper_bound(const K& key){
			Node *tmp = this->_root;
			Node *save;
			value_compare comp(this->_key_comp);
			while (tmp != this->_Nleaf){
				save = tmp;
				if (comp(key, tmp->key))
				 	tmp = tmp->left;
				else if (comp(tmp->key, key))
				 	tmp = tmp->right;
				else
					return (++iterator(tmp));
			}
			tmp = save;
			if (comp(tmp->key, key))
				return (++iterator(tmp));
			else
				return (iterator(tmp));
		}

		iterator lower_bound (const K& key){
			Node *tmp = this->_root;
			Node *save;
			value_compare comp(this->_key_comp);
			while (tmp != this->_Nleaf){
				save = tmp;
				if (comp(key, tmp->key))
				 	tmp = tmp->left;
				else if (comp(tmp->key, key))
				 	tmp = tmp->right;
				else
					return (iterator(tmp));
			}
			tmp = save;
			if (comp(tmp->key, key))
				return (++iterator(tmp));
			else
				return (iterator(tmp));
		}

		const_iterator lower_bound (const K& key) const{
			Node *tmp = this->_root;
			Node *save;
			value_compare comp(this->_key_comp);
			while (tmp != this->_Nleaf){
				save = tmp;
				if (comp(key, tmp->key))
				 	tmp = tmp->left;
				else if (comp(tmp->key, key))
				 	tmp = tmp->right;
				else
					return (const_iterator(tmp));
			}
			tmp = save;
			if (comp(tmp->key, key))
				return (++const_iterator(tmp));
			else
				return (const_iterator(tmp));
		}

		void	fill_deleted_nodes(Node *to_be_deleted){
			if (this->deleted_nodes == _Nleaf)
				this->deleted_nodes = to_be_deleted;
			else{
				Node *tmp = this->deleted_nodes;
				while (tmp != this->_Nleaf)
					tmp = tmp->right;
				tmp = to_be_deleted;
			}
			to_be_deleted->right = _Nleaf;
			to_be_deleted->left = _Nleaf;
		}

		void deletion(const K key){
			Node *to_be_removed = search(key);
			if (to_be_removed == this->_End)
				return ;
			Node *removed;
			int color = to_be_removed->color;
			if (to_be_removed->left == _Nleaf && to_be_removed->right == _Nleaf){
				removed = to_be_removed->right;
				echange(to_be_removed, to_be_removed->right);
				if (to_be_removed == this->_root){
					this->_root = _Nleaf;
				}
			}
			else if (to_be_removed->left != _Nleaf && to_be_removed->right != _Nleaf){
				Node *min = getMin(to_be_removed->right);
				color = min->color;
				removed = min->right;
				if (min->parent == to_be_removed) {
					removed->parent = min;
				} else {
					echange(min, min->right);
					min->right = to_be_removed->right;
					min->right->parent = min;
				}
				echange(to_be_removed, min);
				min->left = to_be_removed->left;
				min->left->parent = min;
				min->color = to_be_removed->color;
			}
			else{
				if(to_be_removed->left == _Nleaf){
					removed = to_be_removed->right;
					echange(to_be_removed, to_be_removed->right);	
				}
				else{
					removed = to_be_removed->left;
					echange(to_be_removed, to_be_removed->left);
				}
			}
			//fill_deleted_nodes(to_be_removed);
			if (color == black && this->_size > 1)
				remove(removed);
			this->_size--;
			_Nleaf->parent = nullptr;
		}
		
		void remove(Node *removed) 
		{
			while (removed->color == black && removed != this->_root)
			{	
				
				Node *sibling = nullptr;
				if (removed == removed->parent->left){
					sibling = removed->parent->right;
					if (sibling->color == red) 
					{
						sibling->color = black;
						removed->parent->color = red;
						rotate_left(removed->parent);
						sibling = removed->parent->right;
					}
					if (sibling->left->color == black && sibling->right->color == black) 
					{
						sibling->color = red;
						removed = removed->parent;
					}
					else 
					{
						if (sibling->right->color == black){
							sibling->left->color = black;
							sibling->color = red;
							rotate_right(sibling);
							sibling = removed->parent->right;
						}
						sibling->color = removed->parent->color;
						removed->parent->color = black;
						sibling->right->color = black;
						rotate_left(removed->parent);
						removed = this->_root;
					}
				}
				else{
					sibling = removed->parent->left;
					if (sibling->color == red) 
					{
						sibling->color = black;
						removed->parent->color = red;
						rotate_right(removed->parent);
						sibling = removed->parent->left;
					}
					if (sibling->right->color == black && sibling->left->color == black) 
					{
						sibling->color = red;
						removed = removed->parent;
					}
					else 
					{
						if (sibling->left->color == black){
							sibling->left->color = black;
							sibling->color = red;
							rotate_left(sibling);
							sibling = removed->parent->left;
						}
						sibling->color = removed->parent->color;
						removed->parent->color = black;
						sibling->left->color = black;
						rotate_right(sibling);
						removed = this->_root;
					}
				}
			}
			
			this->_root->color = black;
			removed->color = black; 
		}

		size_type count(const K key) const{
			Node *tmp = this->_root;
			value_compare comp(this->_key_comp);
			while (tmp != this->_Nleaf){
				if (comp(key, tmp->key))
					tmp = tmp->left;
				else if (comp(tmp->key, key))
					tmp = tmp->right;
				else
					return (1);
			}
			return (0);
		}

		void clear(){
			while (this->_size){
				this->erase(static_cast<K>(this->_root->key));
			}
			this->_root = nullptr;
		}

		Node *search(K key) const{
			value_compare comp(this->_key_comp);
			Node *tmp = this->_root;
			while (tmp != this->_Nleaf && tmp->key != key){
				if (comp(key, tmp->key))
					tmp = tmp->left;
				else if (comp(tmp->key, key))
					tmp = tmp->right;
			}
			if (tmp == this->_Nleaf)
				return (this->_End);
				
			return (tmp);
		}

		RedBlackTree& copy_tree( RedBlackTree & tree)
		{
			Node *root;
			Node *End;
			Node *Nleaf;
			Node *del_nodes;
			size_type size;

			root = this->_root;
			End = this->_End;
			Nleaf = this->_Nleaf;
			size = this->_size;	
			del_nodes = this->deleted_nodes;

			this->_root = tree._root;
			this->_End = tree._End;
			this->_Nleaf = tree._Nleaf;
			this->_size = tree._size;
			this->deleted_nodes = tree.deleted_nodes;
			
			tree._root = root;
			tree._End = End;
			tree._Nleaf = Nleaf;
			tree._size = size;
			tree.deleted_nodes = del_nodes;
		
			return (*this);
		}

};





#endif