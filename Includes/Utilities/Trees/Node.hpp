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
	
	template < class value_type, class Alloc>
		struct RedBlackNode {
			Alloc	_alloc;
			value_type *data;
			RedBlackNode *parent;    
			RedBlackNode *right;    
			RedBlackNode *left;
			bool color;

			RedBlackNode(value_type val)
			{
				this->data = _alloc.allocate(1);
				_alloc.construct(this->data, value_type(val.first,val.second));
				left = right = parent = NULL;
				this->color = RED;
			}
			
			RedBlackNode	&operator=(RedBlackNode const& src)
			{
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
				this->data = _alloc.allocate(1);
				_alloc.construct(this->data, src.data);
				this->parent = src.parent;
				this->right = src.right;
				this->left = src.left;
				this->color = src.color;
			}
			
			~RedBlackNode()
			{
				if (data)
				{
					_alloc.destroy(data);
					_alloc.deallocate(data, 1);
				}
			}
			
		};
};

#endif