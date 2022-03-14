/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SetRBT.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcadmin <mcadmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:22:33 by sel-fadi          #+#    #+#             */
/*   Updated: 2022/01/30 01:07:53 by mcadmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <utility>
#include "../Map/pair.hpp"
#include "setIterator.hpp"
#include "../tools/reverse_iterator.hpp"


namespace ft {

	enum Color {BLACK, RED};
	template < class value_type, class Alloc>
	struct RedBlackNode
	{
		Alloc	_alloc;
		value_type *data;
		RedBlackNode *parent;    
		RedBlackNode *right;    
		RedBlackNode *left;
		bool color;

		RedBlackNode(value_type *val)
		{
			this->data = _alloc.allocate(1);
			_alloc.construct(this->data, val);
			left = right = parent = NULL;
			this->color = RED;
		}
		
		RedBlackNode	&operator=(RedBlackNode const& src)
		{
			if (data)
			{
				_alloc.destroy(data);
				_alloc.deallocate(data, 1);
			}
			this->data = _alloc.allocate(1);
			_alloc.construct(this->data, src.data);
			this->left = src.left;
			this->right = src.right;
			this->parent = src.parent;
			this->color = src.color;
			return *this;
		}

		RedBlackNode(const RedBlackNode& src)
        {
			if (data)
			{
				_alloc.destroy(data);
				_alloc.deallocate(data, 1);
			}
            this->data = _alloc.allocate(1);
            _alloc.construct(this->data, src.data);
            this->parent = src.parent;
            this->right = src.right;
            this->left = src.left;
            this->color = src.color;
        }
		
		~RedBlackNode()
		{
			// if (data)
			// {
			// 	_alloc.destroy(data);
			// 	_alloc.deallocate(data, 1);
			// }
		}
		
	};
	template < class T,                                     // map::key_type
           class Compare,                     // map::key_compare
           class Alloc = std::allocator<T>    // map::allocator_type
           >
	class RedBlackTree
	{
		public:
			typedef T value_type;
			typedef Compare     key_compare;
            typedef Alloc       allocator_type;
            typedef ptrdiff_t   difference_type;
            typedef size_t      size_type;
			
			typedef	RedBlackNode<value_type, Alloc>	RedBlack;
			typedef RedBlackTree<value_type, Compare, Alloc> rbt;
			
			typedef ft::SetIterator<value_type, RedBlack, rbt > iterator;
			typedef ft::SetIterator<const value_type, RedBlack, const rbt > const_iterator;
			
			typedef ft::reverse_iterator<iterator > reverse_iterator;
			typedef ft::reverse_iterator<const_iterator > const_reverse_iterator;
			
			typename Alloc::template rebind<RedBlackNode<value_type, Alloc> >::other _allocRebind;


		private:
			allocator_type _alloc;
			key_compare _cmp;
			RedBlack *root;
		
		public:

			RedBlackTree()
			{
				this->root = NULL;
			}

			~RedBlackTree()
			{
				// this->clear();
			}
			
			void rotateLeft(RedBlack *&root, RedBlack *&node)
			{
				RedBlack *node_right = node->right;
			
				node->right = node_right->left;
			
				if (node->right != NULL)
					node->right->parent = node;
			
				node_right->parent = node->parent;
			
				if (node->parent == NULL)
					root = node_right;
				else if (node == node->parent->left)
					node->parent->left = node_right;
				else
					node->parent->right = node_right;
			
				node_right->left = node;
				node->parent = node_right;
			}
			
			void rotateRight(RedBlack *&root, RedBlack *&node)
			{
				RedBlack *node_left = node->left;
			
				node->left = node_left->right;
			
				if (node->left != NULL)
					node->left->parent = node;
			
				node_left->parent = node->parent;
			
				if (node->parent == NULL)
					root = node_left;
				else if (node == node->parent->left)
					node->parent->left = node_left;
				else
					node->parent->right = node_left;
			
				node_left->right = node;
				node->parent = node_left;
			}

			void fixViolation(RedBlack *&root, RedBlack *&newNode)
			{
				RedBlack *parent_newNode = NULL;
				RedBlack *grand_parent_newNode = NULL;

				while ((newNode != root) && (newNode->color != BLACK) && (newNode->parent->color == RED))
				{
					parent_newNode = newNode->parent;
					grand_parent_newNode = newNode->parent->parent;

					/*  Case : A ---> Parent of newNode is left child of Grand-parent of newNode */
					if (parent_newNode == grand_parent_newNode->left)
					{
						RedBlack *uncle_newNode = grand_parent_newNode->right;
						/* Case : 1  The uncle of newNode is also red Only Recoloring required */
						if (uncle_newNode != NULL && uncle_newNode->color == RED)
						{
							grand_parent_newNode->color = RED;
							parent_newNode->color = BLACK;
							uncle_newNode->color = BLACK;
							newNode = grand_parent_newNode;
						}
						else
						{
							/* Case : 2  newNode is right child of its parent  Left-rotation required */
							if (newNode == parent_newNode->right)
							{
								rotateLeft(root, parent_newNode);
								newNode = parent_newNode;
								parent_newNode = newNode->parent;
							}
							/* Case : 3  newNode is left child of its parent Right-rotation required */
							rotateRight(root, grand_parent_newNode);
							std::swap(parent_newNode->color, grand_parent_newNode->color);
							newNode = parent_newNode;
						}
					}

					/* Case : B  Parent of newNode is right child of Grand-parent of newNode */
					else
					{
						RedBlack *uncle_newNode = grand_parent_newNode->left;
						
						
						/*  Case : 1 The uncle of newNode is also red Only Recoloring required */
						if ((uncle_newNode != NULL) && (uncle_newNode->color == RED))
						{
							grand_parent_newNode->color = RED;
							parent_newNode->color = BLACK;
							uncle_newNode->color = BLACK;
							newNode = grand_parent_newNode;
						}
						else
						{
							/* Case : 2 newNode is left child of its parent Right-rotation required */
							if (newNode == parent_newNode->left)
							{
								rotateRight(root, parent_newNode);
								newNode = parent_newNode;
								parent_newNode = newNode->parent;
							}
			
							/* Case : 3 newNode is right child of its parent Left-rotation required */
							rotateLeft(root, grand_parent_newNode);
							std::swap(parent_newNode->color, grand_parent_newNode->color);
							newNode = parent_newNode;
						}
					}
				}
				root->color = BLACK;
			}
			
			RedBlack *insertionBST(RedBlack *src , RedBlack *newNode)
			{
				/* If the tree is empty, return a new node */
				if (src == NULL)
					return newNode;
				/* Otherwise, recur down the tree */
				if (_cmp(newNode->data, src->data))
				{
					src->left  = insertionBST(src->left, newNode);
					src->left->parent = src;
				}
				else
				{
					src->right = insertionBST(src->right, newNode);
					src->right->parent = src;
				}
				/* return the (unchanged) node pointer */
				return src;
			}
			
			void insertion(value_type *val)
			{
				RedBlack *newNode = _allocRebind.allocate(1);
				_allocRebind.construct(newNode, val);

				// Do a normal BST insert
				root = insertionBST(root, newNode);
				
				// fix Red Black Tree violations
				fixViolation(root, newNode);
			}

			// find node that do not have a left child
			// in the subtree of the given node
			RedBlack *successor(RedBlack *x) const
			{
				RedBlack *temp = x;
			
				if (temp == NULL)
					return NULL;
				while (temp->left != NULL)
					temp = temp->left;
			
				return temp;
			}
			
			// check if node is left child of parent
			bool isOnLeft(RedBlack *node)
			{
				if (node == NULL)
					return false;
				return (node == node->parent->left);
			}
			
			bool hasRedChild(RedBlack *node)
			{
				return (node->left != NULL && node->left->color == RED) ||
					(node->right != NULL && node->right->color == RED);
			}
			
			// returns pointer to sibling
			RedBlack *sibling(RedBlack *nodeTarget)
			{
				RedBlack *node = nodeTarget;
				// sibling null if no parent
				if (node->parent == NULL)
					return NULL;
				if (isOnLeft(node))
					return node->parent->right;
				return node->parent->left;
			}
			
			void fixDoubleBlack(RedBlack *targetNode)
			{
				if (targetNode == root)
				// Reached root
					return;
			
				RedBlack *sib = sibling(targetNode);
				RedBlack *parent = targetNode->parent;
				if (sib == NULL)
				{
					// No sibiling, double black pushed up
					fixDoubleBlack(parent);
				}
				else
				{
					if (sib->color == RED)
					{
						// sib red
						parent->color = RED;
						sib->color = BLACK;
						if (isOnLeft(sib))
						{
							// left case
							rotateRight(root, parent);
						}
						else
						{
							// right case
							rotateLeft(root, parent);
						}
						fixDoubleBlack(targetNode);
					}
					else
					{
						// Sibling black
						if (hasRedChild(sib))
						{
							// at least 1 red children
							if (sib->left != NULL && sib->left->color == RED)
							{
								if (isOnLeft(sib))
								{
									// left left
									sib->left->color = sib->color;
									sib->color = parent->color;
									rotateRight(root, parent);
								}
								else
								{
									// right left
									sib->left->color = parent->color;
									rotateRight(root, sib);
									rotateLeft(root, parent);
								}
							}
							else
							{
								if (isOnLeft(sib))
								{
									// left right
									sib->right->color = parent->color;
									rotateLeft(root, sib);
									rotateRight(root, parent);
								}
								else
								{
									// right right
									sib->right->color = sib->color;
									sib->color = parent->color;
									rotateLeft(root, parent);
								}
							}
							parent->color = BLACK;
						}
						else
						{
							// 2 black children
							sib->color = RED;
							if (parent->color == BLACK)
								fixDoubleBlack(parent);
							else
								parent->color = BLACK;
						}
					}
				}
			}

			// find node that replaces a deleted node in BST
			RedBlack *BSTreplace(RedBlack *&targetNode)
			{
				// when node have 2 children
				if (targetNode->left != NULL && targetNode->right != NULL)
					return successor(targetNode->right);
			
				// when leaf
				if (targetNode->left == NULL && targetNode->right == NULL)
					return NULL;
			
				// when single child
				if (targetNode->left != NULL)
					return targetNode->left;
				else
					return targetNode->right;
			}
			
			void swapValues(RedBlack *u, RedBlack *v)
			{
				value_type *tmp;
				tmp = u->data;
				u->data = v->data;
				v->data = tmp;
			}
			
			// deletes the given node
			void deleteNode(RedBlack *&targetNode)
			{
				RedBlack *nodeReplaceTarget = BSTreplace(targetNode);
			
				// True when u and v are both black
				bool rtBlack = ((nodeReplaceTarget == NULL || nodeReplaceTarget->color == BLACK) && (targetNode->color == BLACK));
				RedBlack *parentTarget = targetNode->parent;
			
				if (nodeReplaceTarget == NULL) 
				{
					// nodeReplaceTarget is NULL therefore targetNode is leaf
					if (targetNode == root)
					{
						// targetNode is root, making root null
						root = NULL;
					}
					else
					{
						if (rtBlack)
						{
							// u and targetNode both black
							// targetNode is leaf, fix double black at targetNode
							fixDoubleBlack(targetNode);
						}
						else
						{
							RedBlack *tmp = sibling(targetNode);
							// u or targetNode is red
							if (tmp != NULL)
								// sibling is not null, make it red"
								tmp->color = RED;
						}
						// delete targetNode from the tree
						if (isOnLeft(targetNode))
							parentTarget->left = NULL;
						else
							parentTarget->right = NULL;
					}
					_allocRebind.destroy(targetNode);
					_allocRebind.deallocate(targetNode, 1);
					// delete targetNode;
					return;
				}
			
				if (targetNode->left == NULL || targetNode->right == NULL)
				{
					// targetNode has 1 child
					if (targetNode == root)
					{
						// targetNode is root, assign the value of u to targetNode, and delete u
						targetNode->data = nodeReplaceTarget->data;
						targetNode->left = targetNode->right = NULL;
						_allocRebind.destroy(nodeReplaceTarget);
						_allocRebind.deallocate(nodeReplaceTarget, 1);
						// delete nodeReplaceTarget;
					}
					else
					{
						// Detach targetNode from tree and motargetNodee u up
						if (isOnLeft(targetNode))
							parentTarget->left = nodeReplaceTarget;
						else
							parentTarget->right = nodeReplaceTarget;
						_allocRebind.destroy(targetNode);
						_allocRebind.deallocate(targetNode, 1);
						// delete targetNode;
						nodeReplaceTarget->parent = parentTarget;
						if (rtBlack)
							// u and v both black, fix double black at u
							fixDoubleBlack(nodeReplaceTarget);
						else
							// u or v red, color u black
							nodeReplaceTarget->color = BLACK;
					}
					return;
				}
				// v has 2 children, swap values with successor and recurse
				swapValues(nodeReplaceTarget, targetNode);
				deleteNode(nodeReplaceTarget);
			}

			
			// searches for given value
			// if found returns the node (used for delete)
			// else returns the last node while traversing (used in insert)
			RedBlack *search(value_type *val) const
			{
				RedBlack *tmp = root;
				while (1)
				{
					if (tmp == NULL)
						return NULL;
					if (val == tmp->data)
						return tmp;
					if (_cmp(val, tmp->data))
						tmp = tmp->left;
					else
						tmp = tmp->right;
				}
				return tmp;
			}
			
			size_type deleteByVal(value_type *val)
			{
				// Tree is empty
				if (root == NULL)
					return 0;
			
				RedBlack *targetNode = search(val);
				if (targetNode == NULL)
					return 0;
				deleteNode(targetNode);
				return 1;
			}

			RedBlack * getRoot() const { return this->root; }

			iterator begin() { return iterator(successor(this->root), this); }
			const_iterator begin() const { return const_iterator(successor(this->root),this); }
			iterator end() { return iterator(NULL, this); }
			const_iterator end() const { return const_iterator(NULL, this); }

			reverse_iterator rbegin() { return reverse_iterator(iterator(NULL,this)); };
			const_reverse_iterator rbegin() const { return const_reverse_iterator(iterator(NULL,this)); };
			reverse_iterator rend() { return reverse_iterator(iterator(successor(this->root),this)); };
			const_reverse_iterator rend() const { return const_reverse_iterator(iterator(successor(this->root),this)); };

			bool empty() const { return this->root == NULL; };
			size_type max_size() const { return this->_alloc.max_size(); }

			void	clear_help(RedBlack *src)
			{
				if (src == NULL)
					return ;
				clear_help(src->left);
				clear_help(src->right);
				_alloc.deallocate(src->data, 1);
				_allocRebind.deallocate(src, 1);
			}
			
			void clear()
			{
				clear_help(root);
				this->root = NULL;
			}
			
			void	swap (RedBlackTree &src)
			{
				std::swap(root, src.root);
				std::swap(_alloc, src._alloc);
				std::swap(_cmp, src._cmp);
				std::swap(_allocRebind, src._allocRebind);
			}
			
			iterator find (const value_type& k)
			{
				RedBlack *tmp = search(k);
				if (!tmp)
					return iterator(NULL, this);
				return iterator(tmp, this);
			}
			const_iterator find (const value_type& k) const 
			{
				RedBlack *tmp = search(k);
				if (!tmp)
					return const_iterator(NULL, this);
				return const_iterator(tmp, this);
			}

			size_type count (const value_type& k) const 
			{
				RedBlack *tmp = search(k);
				if (!tmp)
					return 0;
				else
					return 1;
			}
			
			RedBlack *found(value_type *index,RedBlack *root,RedBlack **p)  const
			{
				if (!root)
					return root;
				if (_cmp(index, root->data))
				{   
					*p = root;
					return found(index,root->left,p);
				}
				else if (_cmp(root->data,index))
					return found(index,root->right,p);
				else 
					return root;
			}
			
			iterator lower_bound (const value_type& k)
			{
				RedBlack *p = NULL;
				RedBlack *tmp = found(k,this->root,&p);
				if (!tmp)
					return iterator(p,this);
				return iterator(tmp,this);
			}
			const_iterator lower_bound (const value_type& k) const
			{
				RedBlack *p = NULL;
				RedBlack *tmp = found(k,this->root,&p);
				if (!tmp)
					return const_iterator(p,this);
				return const_iterator(tmp,this);
			}
			iterator upper_bound (const value_type& k)
			{
				RedBlack *p = NULL;
				RedBlack *tmp = found(k,this->root,&p);
				if (!tmp)
					return iterator(p,this);
				return ++iterator(tmp,this);
			}
			const_iterator upper_bound (const value_type& k) const
			{
				RedBlack *p = NULL;
				RedBlack *tmp = found(k,this->root,&p);
				if (!tmp)
					return const_iterator(p,this);
				return ++const_iterator(tmp,this);
			}
			
			RedBlack	*bound(const value_type& k) const
			{
				RedBlack src = root;
				RedBlack tmp = src;
				while (src != NULL && src != NULL)
				{
					if (_cmp(k, src->data))
					{
						tmp = src;
						src = src->left;
					}
					else if (_cmp(src->data, k))
						src = src->right;
					else 
						return src;
				}
				return tmp;
			}
			
	};
}

