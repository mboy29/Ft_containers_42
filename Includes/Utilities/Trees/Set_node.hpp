#ifndef SET_NODE_HPP
# define SET_NODE_HPP

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
	enum set_color { SBLACK, SRED};
	
	template < class value_type, class Alloc>
		struct set_node {

			//  -----------------------MEMBER TYPES-----------------------
			
			bool 		color;
			Alloc		alloc;
			value_type	*value;
			set_node	*parent, *right, *left;

			//  ---------------------MEMBER FUNCTIONS---------------------

			//  -----------------------CONSTRUCTORS-----------------------
			
			//  Fill constructor :
			set_node(value_type val) : color(SRED), parent(NULL), right(NULL), left(NULL) {
				this->value = alloc.allocate(1);
				alloc.construct(this->value, value_type(val));
			}

			//  Copy constructor :
			set_node(set_node const& rhs) : color(rhs.color), parent(rhs.parent), right(rhs.right), left(rhs.left) {
				if (this->value) {
					this->alloc.destroy(this->value);
					this->alloc.deallocate(this->value, 1);
				}
				this->value = alloc.allocate(1);
				alloc.construct(this->value, rhs.value);
			}
			
			//  -----------------------DESSTRUCTOR------------------------

			~set_node(void) {
				if (this->value) {
					this->alloc.destroy(this->value);
					this->alloc.deallocate(this->value, 1);
				}
			}

			//  -------------------ASSIGNMENT OPERATOR--------------------
			
			set_node	&operator=(set_node const& rhs) {
				if (this != rhs) {
					if (this->value) {
						this->alloc.destroy(this->value);
						this->alloc.deallocate(this->value, 1);
					}
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