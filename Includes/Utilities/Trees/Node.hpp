/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:32:50 by mboy              #+#    #+#             */
/*   Updated: 2022/03/23 13:32:51 by mboy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
# define NODE_HPP

//  --------------------------------NODES---------------------------------
//    -> Struct Template
//    A binary tree is made of nodes, where each node contains a "left"
//    reference, a "right" reference, and a data element.
//    The topmost node in the tree is called the root.
//    Every node (excluding a root) in a tree is connected by a directed
//    edge from exactly one other node.
//  ----------------------------------------------------------------------

namespace ft
{
	enum color { BLACK, RED};
	
	template < class value_type, class Alloc>
		struct node {

			//  -----------------------MEMBER TYPES-----------------------
			
			bool 		color;
			Alloc		alloc;
			value_type	*value;
			node	*parent, *right, *left;

			//  ---------------------MEMBER FUNCTIONS---------------------

			//  -----------------------CONSTRUCTORS-----------------------
			
			//  Fill constructor :
			node(value_type val) : color(RED), parent(NULL), right(NULL), left(NULL) {
				this->value = alloc.allocate(1);
				alloc.construct(this->value, value_type(val.first, val.second));
			}

			//  Copy constructor :
			node(node const& rhs) : color(rhs.color), parent(rhs.parent), right(rhs.right), left(rhs.left) {
				this->value = alloc.allocate(1);
				alloc.construct(this->value, rhs.value);
			}
			
			//  -----------------------DESSTRUCTOR------------------------

			//  Destructor :
			~node(void) {
				if (this->value) {
					this->alloc.destroy(this->value);
					this->alloc.deallocate(this->value, 1);
				}
			}

			//  -------------------ASSIGNMENT OPERATOR--------------------
			
			node	&operator=(node const& rhs) {
				if (this != rhs) {
					this->value = alloc.allocate(1);
					alloc.construct(this->value, rhs.value);
					this->left = rhs.left;
					this->right = rhs.right;
					this->parent = rhs.parent;
					this->color = rhs.color;
				}
				return (*this);
			}		
		};
};

#endif
