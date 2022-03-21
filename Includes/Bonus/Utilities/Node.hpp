#ifndef MAP_NODE_HPP
# define MAP_NODE_HPP

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
	enum color {BLACK, RED};
	
	template < class value_type, class Alloc>
		struct map_node {

			//  -----------------------MEMBER TYPES-----------------------
			
			bool 		color;
			Alloc		alloc;
			value_type	*value;
			map_node	*parent, *right, *left;

			//  -----------------------CONSTRUCTORS-----------------------
			
			//  Fill constructor :
			map_node(value_type val) : color(RED), parent(NULL), right(NULL), left(NULL) {
				this->value = alloc.allocate(1);
				alloc.construct(this->value, value_type(val.first,val.second));
			}

			//  Copy constructor :
			map_node(map_node const& rhs) : color(rhs.color), parent(rhs.parent), right(rhs.right), left(rhs.left) {
				this->value = alloc.allocate(1);
				alloc.construct(this->value, rhs.value);
			}
			
			//  -----------------------DESSTRUCTOR------------------------

			~map_node(void) {
				if (this->value) {
					this->alloc.destroy(this->value);
					this->alloc.deallocate(this->value, 1);
				}
			}

			//  -------------------ASSIGNMENT OPERATOR--------------------
			
			map_node	&operator=(map_node const& rhs) {
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