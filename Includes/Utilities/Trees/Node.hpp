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
	enum color {BLACK, RED};

	//  ----------------------------BASIC NODE----------------------------

	template<class Value>
		struct node {

			//  -----------------------MEMBER TYPES-----------------------

			typedef Value	value_type;
			typedef	color	color_type;

			value_type		value;
			color_type		color;
			node			*parent, *left, *right;

			//  -----------------------CONSTRUCTORS-----------------------
			
			//  Default constructor :
			node(void) : value(), color(RED), parent(NULL), left(NULL), right(NULL) {}
			
			//  Fill constructor :
			node(value_type const& value, color_type color = RED ,node *parent = NULL, node *left = NULL, node *right = NULL)
				: value(value), color(color), parent(parent), left(left), right(right) {}

			//  Copy constructor :
			node(node const& rhs) : value(rhs.value), color(rhs.color), parent(rhs.parent), left(rhs.left), right(rhs.right) {}
		
			//  -----------------------DESSTRUCTOR------------------------

			virtual ~node(void) {};

			//  -------------------ASSIGNMENT OPERATOR--------------------
		
			node	&operator=(node const &rhs) {
				if (this != &rhs) {
					this->value = rhs.value;
					this->color = rhs.color;
					this->parent = rhs.parent;
					this->left = rhs.left;
					this->right = rhs.right;
				}
				return (*this);
			}

			//  -------------IN/EQUALITY RELATIONAL OPERATOR--------------

			//  Equality :
			bool	operator==(node const& rhs) {
				if (this->value == rhs.value)
					return (true);
				return (false);
			}

			//  Inequality :
			bool	operator!=(node const& rhs) {
				if (this->value != rhs.value)
					return (true);
				return (false);
			}
		};

	//  -------------------------BLACK & RED NODE-------------------------
	
	template < class value_type, class Alloc>
		struct tree_node {

			//  -----------------------MEMBER TYPES-----------------------
			
			bool 		color;
			Alloc		alloc;
			value_type	*value;
			tree_node	*parent, *right, *left;

			//  -----------------------CONSTRUCTORS-----------------------
			
			//  Fill constructor :
			tree_node(value_type val) : color(RED), parent(NULL), right(NULL), left(NULL) {
				this->value = alloc.allocate(1);
				alloc.construct(this->value, value_type(val.first,val.second));
			}

			//  Copy constructor :
			tree_node(tree_node const& rhs) : color(rhs.color), parent(rhs.parent), right(rhs.right), left(rhs.left) {
				this->value = alloc.allocate(1);
				alloc.construct(this->value, rhs.value);
			}
			
			//  -----------------------DESSTRUCTOR------------------------

			~tree_node(void) {
				if (this->value) {
					this->alloc.destroy(this->value);
					this->alloc.deallocate(this->value, 1);
				}
			}

			//  -------------------ASSIGNMENT OPERATOR--------------------
			
			tree_node	&operator=(tree_node const& rhs) {
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