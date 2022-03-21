#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP
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
    template <class T, class Node, class Tree>
		class map_iterator : public iterator<bidirectional_iterator_tag, T> {

			//  -----------------------MEMBER TYPES-----------------------

			protected:
				Node 													*_node;
				const Tree 												*_tree;
				typedef iterator<bidirectional_iterator_tag, T>			iterator;
		
			public:
				typedef typename iterator::value_type 					value_type;
				typedef typename iterator::pointer						pointer;
				typedef typename iterator::reference					reference;
				typedef typename iterator::difference_type				difference_type;
				typedef typename iterator::iterator_category			iterator_category;
			
			//  ---------------------MEMBER FUNCTIONS---------------------

			public :

				//  ---------------------CONSTRUCTORS---------------------

				//  Default constructor :
				map_iterator(void) : _node(), _tree() {}
				
				//  Fill constructor :
				map_iterator(Node *node, const Tree *tree) : _node(node), _tree(tree) {}
				
				//  Copy constructor :
				map_iterator(const map_iterator& rhs) { *this = rhs; }
			
				//  ---------------------DESSTRUCTOR----------------------	
			
				//  Destructor :
				virtual ~map_iterator(void) {}
			
				//  -------------------------BASE-------------------------

				Node *base(void) const { return (this->_node); }

				//  -------------------CONVERT TO CONST-------------------
				
				operator	map_iterator<const T, Node, const Tree>(void) const {
					return (map_iterator<const T, Node, const Tree>(this->_node, this->_tree));
				}
				
				//  -----------------ASSIGNMENT OPERATOR------------------
			

				//  Operator= :
				map_iterator& operator=(const map_iterator& rhs) {
					if (this != &rhs) {
						this->_node = rhs._node;
						this->_tree = rhs._tree;
					}
					return (*this);
				}
			
				//  -----------------DEREFERENCE OPERATOR-----------------
			
				//  Operator* :
				reference operator*(void) const { return (*this->_node->value); }
				
				//  Operator-> :
				pointer   operator->(void) const { return (this->_node->value); }

			
				//  ------------------INCREMENT OPERATOR------------------


				//  Operator++ -> post-incrementation :
				map_iterator	&operator++(void) {
					Node *tmp = NULL;
					
					if (!this->_node) {
						if (!(this->_node = this->_tree->getBase()) || !(this->_node))
							return (*this);
						while (this->_node->left) //  Move to smallest tree value
							this->_node = this->_node->left;
					}
					else {
						if (this->_node->right) {
							this->_node = this->_node->right;
							while (this->_node->left)
								this->_node = this->_node->left;
						}
						else {
							for (tmp = this->_node->parent; tmp && this->_node == tmp->right; tmp = tmp->parent)
								this->_node = tmp;
							this->_node = tmp;
						}
					}
					return (*this);
				}

				//  Operator++ -> pre-incrementation :
				map_iterator	operator++(int) {
					map_iterator tmp(*this);
					++(*this);
					return (tmp);
				}
			
				//  ------------------DECREMENT OPERATOR-----------------
			

				//  Operator-- -> post-incrementation :
				map_iterator	&operator--(void) {
					Node *tmp =  NULL;
					
					if (!this->_node) {
						if (!(_node = _tree->getBase())) //  Check for an empty tree
							return (*this);
						while (this->_node->right) //  Move to smallest tree value
							this->_node = this->_node->right;
					}
					else {
						if (this->_node->left) {
							this->_node = this->_node->left;
							while (this->_node->right)
								this->_node = this->_node->right;
						}
						else {
							for (tmp = this->_node->parent; tmp && this->_node == tmp->left; tmp = tmp->parent)
								this->_node = tmp;
							this->_node = tmp;
						}
					}
					return (*this);
				}
				
				//  Operator-- -> pre-incrementation :
				map_iterator	operator--(int) {
					map_iterator tmp(*this);
					--(*this);
					return (tmp);
				}

				//  --------------FRIEND COMPARAISON OPERATOR-------------
				
				friend bool operator==(map_iterator const& lhs, map_iterator const& rhs) { return (lhs.base() == rhs.base()); }
				friend bool operator!=(map_iterator const& lhs, map_iterator const& rhs) { return (!operator == (lhs, rhs)); }
		};
};

#endif