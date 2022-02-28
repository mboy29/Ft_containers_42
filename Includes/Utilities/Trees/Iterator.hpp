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
	template <class Iterator>
		class tree_iterator : public ft::iterator<ft::bidirectional_iterator_tag, Iterator> {
			
			//  ----------------------MEMBER TYPES------------------------
		
			protected:
				typedef iterator<random_access_iterator_tag, Iterator>	iterator;
			
			public:
				typedef typename iterator::value_type			value_type;
				typedef typename iterator::difference_type		difference_type;
				typedef typename iterator::pointer				pointer;
				typedef typename iterator::reference			reference;
				typedef typename iterator::iterator_category	iterator_category;
				typedef	ft::node<Iterator>						node;
				typedef ft::node<Iterator>						*node_ptr;
			
			private:
				node_ptr						_node;
			
			//  ---------------------MEMBER FUNCTIONS---------------------
			
			public:
			
				//  ---------------------CONSTRUCTORS---------------------
			
			
				tree_iterator(void): _node(NULL) {} //  Default Constructor
				tree_iterator(node_ptr node) : _node(node) {} //  Fill constructor
				tree_iterator(tree_iterator const &rhs) : _node(rhs._node) {} //  Copy Constructor
			
				//  ----------------------DESTRUCTOR----------------------
			
				virtual ~tree_iterator(void) {}
				
				//  -------------------------BASE-------------------------
				
				node_ptr	baseNode(void) const { return (this->_node); }
				
				//  -------------------CONVERT TO CONST-------------------

				operator tree_iterator<const Iterator> (void) {
					return (tree_iterator<const Iterator> (this->_ptr));
				};

				//  -----------------DEREFERENCE OPERATOR-----------------
				
				tree_iterator& operator=(const tree_iterator& ref)
				{
					if (this != &ref)
						this->_node = ref._node;
					return (*this);
				}

				reference	operator*(void) const { //  Operator*
					return (*(this->_ptr));
				}

				pointer		operator->(void) const { //  Operator->
					return (this->_ptr);
				}

				//  ------------------INCREMENT OPERATOR------------------

				tree_iterator &operator++(void) { //  Operator++ -> a++
					if (this->_node->parent == NULL)
						this->_node = NULL;
					if (this->_node->right != NULL)
					{
						this->_node = _minimum(this->_node->right);
						return (*this);
					}
					while (this->_node->parent && this->_node->parent->right == this->_node)
						this->_node = this->_node->parent;
					if (this->_node->parent)
						this->_node = this->_node->parent;
					return (*this);
				}

				tree_iterator operator++(int) { //  Operator++ -> ++a
					tree_iterator tmp = *this;
					
					++(*this);
					return (tmp);
				}

				//  ------------------DECREMENT OPERATOR------------------

				tree_iterator	&operator--(void) { //  Operator-- -> a--
					if (this->_node->left != NULL)
					{
						this->_node = _maximum(this->_node->left);
						return (*this);
					}
					while (this->_node->parent && this->_node->parent->left == this->_node)
						this->_node =this->_node->parent;
					if (this->_node->parent)
						this->_node = this->_node->parent;
					else
						this->_node = NULL;
					return(*this);
				}

				tree_iterator operator--(int) { //  Operator-- -> --a
					tree_iterator tmp = *this;
					
					--(*this);
					return (tmp);
				}

				//  ------------IN/EQUALITY RELATIONAL OPERATOR------------

				bool operator==(tree_iterator const &lhs) const { return (this->baseNode() == lhs._node); } //  Operator==

				bool operator==(tree_iterator<const Iterator> const &lhs) const { return (this->baseNode() == lhs._node); } //  Const operator==

				bool operator!=(tree_iterator const &lhs) const { return (this->baseNode() != lhs._node); } //  Operator!=

				bool operator!=(tree_iterator<const Iterator> const &lhs) const { return (this->baseNode() != lhs._node); } //  Const operator!=

				//  -------------------------VALUES---------------------------

				private:
					
					//  Get minimum value (left) :
					node_ptr	_minimum(node_ptr node)
					{
						while (node->left != NULL)
							node = node->left;
						return (node);
					}

					//  Get maximum value (right) :
					node_ptr	_maximum(node_ptr node)
					{
						while (node->right != NULL)
							node = node->right;
						return (node);
					}
			
		};
};

#endif
