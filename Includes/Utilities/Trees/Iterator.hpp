#ifndef TREE_ITERATOR_HPP
# define TREE_ITERATOR_HPP
# include "../Iterators/Iterator.hpp" //  Iterator

//  --------------------------------NODES---------------------------------
//    -> Class Template
//    Iterator class implented for red-black trees, aka map.
//    It inherites from the basic iterator class and is implemented as a
//    bidirectional iterator (accesses the sequence of elements in a range
//    in both directions : towards the end and towards the beginning).
//  ----------------------------------------------------------------------

namespace ft
{

	template<class It>
		class const_tree_iterator;
		
	template <class Iterator>
		class tree_iterator : public ft::iterator<ft::bidirectional_iterator_tag, Iterator> {
			
			//  ----------------------MEMBER TYPES------------------------

			private:
				typedef ft::node<Iterator>				node;
				typedef ft::node<Iterator>*				node_pointer;
			public:
				typedef bidirectional_iterator_tag  iterator_category;
				typedef Iterator                           value_type;
				typedef value_type&                 reference;
				typedef std::ptrdiff_t              difference_type;
				typedef Iterator*                          pointer;
			
			private:
				node_pointer											_node;
			
			//  ---------------------MEMBER FUNCTIONS---------------------
			
			public:
			
				//  ---------------------CONSTRUCTORS---------------------
			
				tree_iterator(void) : _node(NULL) {} //  Default Constructor
				tree_iterator(node_pointer node) : _node(node) {} //  Fill constructor
				tree_iterator(tree_iterator const &rhs) : _node(rhs._node) {} //  Copy Constructor
				
				//  ----------------------DESTRUCTOR----------------------
			
				virtual ~tree_iterator(void) {}
				
				//  -------------------------BASE-------------------------
				
				node_pointer	base(void) const { return (this->_node); }
				
				//  -------------------CONVERT TO CONST-------------------

				tree_iterator(const const_tree_iterator<const Iterator>& other) : _node(other.base()) {}

				//  -----------------DEREFERENCE OPERATOR-----------------
				
				tree_iterator& 	operator=(tree_iterator const &ref) //  Operator=
				{
					if (this != &ref)
						this->_node = ref._node;
					return (*this);
				}

				reference		operator*(void) const { return (this->_node->value); } //  Operator*

				pointer			operator->(void) const { return (&(this->_node->value)); } //  Operator->

				//  ------------------INCREMENT OPERATOR------------------

				tree_iterator &operator++(void) { //  Operator++ -> post-incrementation
					if (this->_node->parent == NULL)
						this->_node = NULL;
					if (this->_node->right != NULL) {
						this->_node = _minimum(this->_node->right);
						return (*this);
					}
					while (this->_node->parent && this->_node->parent->right == this->_node)
						this->_node = this->_node->parent;
					if (this->_node->parent)
						this->_node = this->_node->parent;
					return (*this);
				}

				tree_iterator operator++(int) { //  Operator++ -> pre-incrementation
					tree_iterator tmp = *this;
					
					++(*this);
					return (tmp);
				}

				//  ------------------DECREMENT OPERATOR------------------

				tree_iterator	&operator--(void) { //  Operator-- -> post-incrementation
					if (this->_node->left != NULL)
					{
						this->_node = _maximum(this->_node->left);
						return (*this);
					}
					while (this->_node->parent && this->_node->parent->left == this->_node)
						this->_node = this->_node->parent;
					if (this->_node->parent)
						this->_node = this->_node->parent;
					else
						this->_node = NULL;
					return(*this);
				}

				tree_iterator operator--(int) { //  Operator-- -> pre-incrementation
					tree_iterator tmp = *this;
					
					--(*this);
					return (tmp);
				}

				//  ------------IN/EQUALITY RELATIONAL OPERATOR------------

				bool operator==(tree_iterator const &lhs) { return (this->_node == lhs.base()); } //  Operator==

				bool operator==(tree_iterator<const Iterator> const &lhs) const { return (this->_node == lhs.base()); } //  Const operator==

				bool operator!=(tree_iterator const &lhs) { return (this->_node != lhs.base()); } //  Operator!=

				bool operator!=(tree_iterator<const Iterator> const &lhs) const { return (this->_node != lhs.base()); } //  Const operator!=

				//  -------------------------VALUES---------------------------

				private:
					
					//  Get minimum value (left) :
					node_pointer	_minimum(node_pointer node) {
						while (node->left != NULL)
							node = node->left;
						return (node);
					}

					//  Get maximum value (right) :
					node_pointer	_maximum(node_pointer node) {
						while (node->right != NULL)
							node = node->right;
						return (node);
					}
			
		};

	template <class Iterator>
		class const_tree_iterator : public ft::iterator<ft::bidirectional_iterator_tag, const Iterator> {
			
			//  ----------------------MEMBER TYPES------------------------

			private:
				typedef ft::node<Iterator>               node;
				typedef ft::node<Iterator>*              node_pointer;

			public:
				typedef bidirectional_iterator_tag  iterator_category;
				typedef const Iterator                           value_type;
				typedef const value_type&           reference;
				typedef std::ptrdiff_t              difference_type;
				typedef const Iterator*                    pointer;

				
			private:
				node_pointer											_node;

			//  ---------------------MEMBER FUNCTIONS---------------------
			
			public:
			
				//  ---------------------CONSTRUCTORS---------------------
				
				const_tree_iterator(void): _node(NULL) {} //  //  Default Constructor
				const_tree_iterator(const_tree_iterator const &ref) : _node(ref._node) {} //  Fill constructor
				const_tree_iterator(node_pointer node) : _node(node) {} //  Copy Constructor
				
				//  ----------------------DESTRUCTOR----------------------
				
				virtual ~const_tree_iterator(void) {}
				
				//  -------------------------BASE-------------------------
				
				node_pointer 	base(void) const { return (this->_node); }

				//  -----------------CONVERT TO NON-CONST-----------------

				const_tree_iterator(const tree_iterator<Iterator>& other) : _node(other.base()) {}
				
				//  -----------------DEREFERENCE OPERATOR-----------------

				
				const_tree_iterator& operator=(const_tree_iterator const &ref) { //  Operator=
					if (this != &ref)
						this->_node = ref._node;
					return (*this);
				}

				reference 			operator*(void) const { return (this->_node->value); } //  Operator*

				pointer 			operator->(void) const { return (&(this->_node->value)); } //  Operator->

				//  ------------------INCREMENT OPERATOR------------------
				
				const_tree_iterator&	operator++(void) { //  Operator++ -> post-incrementation
					if (this->_node->parent == NULL) 
						this->_node = NULL;
					if (this->_node->right != NULL) {
						this->_node = _minimum(this->_node->right);
						return (*this);
					}
					while (this->_node->parent && this->_node->parent->right == this->_node)
						this->_node = this->_node->parent;
					if (this->_node->parent)
						this->_node = this->_node->parent;
					return (*this);
				}

				const_tree_iterator operator++(int) { //  Operator++ -> pre-incrementation
					const_tree_iterator tmp = *this;
					
					++(*this);
					return (tmp);
				}

				//  ------------------DECREMENT OPERATOR------------------

				const_tree_iterator&	operator--(void) { //  Operator-- -> post-incrementation
					if (this->_node->left != NULL) {
						this->_node = _maximum(this->_node->left);
						return (*this);
					}
					while (this->_node->parent && this->_node->parent->left == this->_node)
						this->_node = this->_node->parent;
					if (this->_node->parent)
						this->_node = this->_node->parent;
					else
						this->_node = NULL;
					return (*this);
				}

				const_tree_iterator operator--(int) { //  Operator-- -> pre-incrementation
					const_tree_iterator tmp = *this;
					
					--(*this);
					return (tmp);
				}

				//  ------------IN/EQUALITY RELATIONAL OPERATOR------------

				bool operator==(const_tree_iterator const &lhs) { return (this->_node == lhs.base()); } //  Operator==

				bool operator==(tree_iterator<Iterator> const &lhs) { return (this->_node == lhs.base()); } //  Operator==

				bool operator!=(const_tree_iterator const& lhs) { return (this->_node !=lhs.base()); } //  Operator!=

				bool operator!=(tree_iterator<Iterator> const &lhs) { return (this->_node != lhs.base()); } //  Operator!=
				
				//  -------------------------VALUES---------------------------
				
				//  Get minimum value (left) :
				node_pointer	_minimum(node_pointer node) {
					while (node->left != NULL)
						node = node->left;
					return (node);
				}

				//  Get maximum value (right) :
				node_pointer	_maximum(node_pointer node)
				{
					while (node->right != NULL)
						node = node->right;
					return (node);
				}
		};
};

#endif
