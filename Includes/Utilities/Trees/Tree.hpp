#ifndef	TREE_HPP
# define TREE_HPP
# include "../Iterators/Reverse_iterator.hpp" //  Reverse iterator
# include "./Node.hpp" //  Tree node
# include "./Iterator.hpp" //  Tree iterator

//  ----------------------------BLACK RED TREE----------------------------
//    -> Class Template
//    A red-black tree is a self-balancing binary search tree where each
//    node has an extra bit, interpreted as the colour (red or black).
//    Every red-black tree follows these 5 rules: 
//    - Every node has a colour, either red or black ;
//    - The root of the tree is always black ;
//    - There are no two adjacent red nodes (a red node cannot have a red
//      parent or red child) ;
//    - Every path from a node (including root) to any of its descendants
//      NULL nodes has the same number of black nodes ;
//    - All leaf nodes are black nodes.
//  ----------------------------------------------------------------------

namespace ft
{
	template <class Pair, class Compare, class Alloc = std::allocator<Pair> >
		class tree {

			//  ----------------------MEMBER TYPES------------------------

			public:
				typedef ft::node<Pair>										node_type;
				typedef ft::node<Pair>										*node_pointer;
				typedef std::allocator<node_type>							node_allocator_type;
				typedef	Pair												value_type;
				typedef	Compare												value_compare;
				typedef	Alloc												allocator_type;
				typedef	typename allocator_type::reference					reference;
				typedef	typename allocator_type::const_reference			const_reference;
				typedef	typename allocator_type::pointer					pointer;
				typedef	typename allocator_type::const_pointer				const_pointer;
				typedef	ft::tree_iterator<value_type>						iterator;
				typedef	ft::tree_iterator<const value_type>					const_iterator;
				typedef	ft::reverse_iterator<iterator>						reverse_iterator;
				typedef	ft::reverse_iterator<const_iterator>				const_reverse_iterator;
				typedef	std::size_t											size_type;
				typedef	std::ptrdiff_t										difference_type;
			
			private:
				value_compare		_comp;
				allocator_type		_alloc;
				node_allocator_type	_node_alloc;
				node_pointer		_node;
				size_type			_size;
			
			//  --------------------MEMBER FUNCTION----------------------
			

			//  ---------------------CONSTRUCTOR-------------------------
			
			public:

				//  Fill constructor :
				tree(value_compare const &comp, allocator_type const &alloc, node_allocator_type const &node_alloc = node_allocator_type()) : _comp(comp), _alloc(alloc), _node_alloc(node_alloc), _node(NULL), _size(0) {
					this->_node = this->_node_alloc.allocate(1);
					this->_node_alloc.construct(this->_node, node_type());
				}

				//  Copy constructor :
				tree(tree const &rhs) : _comp(rhs._comp), _alloc(rhs._alloc), _node_alloc(rhs._node_alloc), _node(NULL), _size(0) {
					this->_node = this->_node_alloc.allocate(1);
					this->_node_alloc.construct(this->_node, node_type());
				}

			//  ---------------------CONSTRUCTOR-------------------------

			public:

				~tree(void) {
					this->_clear();
				}
			
			//  ---------------------ASSIGN OPERATOR---------------------
			
			public:

				//  Operator= :
				tree&		operator=(tree const &rhs) {
					if (this != &rhs) {
						this->_clear();
						this->_comp = rhs._comp;
						this->_alloc = rhs._alloc;
						this->_node_alloc = rhs._alloc;
						this->_size = rhs.size();
						_copy(rhs.getRoot());
						return (*this);
					}
				}

			//  -------------------------GET/SET-------------------------
		
			public:
				//  Get node (this) :
				node_pointer	getNode(void) const { return (this->_node); }
				
				//  Get & set root :
				node_pointer	getRoot(void) const { return (this->_node->left); } //  This
				node_pointer	getRoot(node_pointer node) const { return (node->getRoot()); } //  Other
				
				void			setRoot(node_pointer node) { //  This 
					this->_node->left = node;
					this->_node->right = node;
					if (node != NULL)
						node->parent = this->_node;
				}

				void			setRoot(node_pointer root, node_pointer node) { root->setRoot(node); } //  Other

				//  Get & set color :
				color			getColor(void) const { return (this->_node->color); } //  This		
				color			getColor(node_pointer node) const { return (node->getColor()); } //  Other
				void			setColor(color c) { if (this->_node != NULL) this->_node->color = c; } //  This
				void			setColor(node_pointer node, color c) { if (node != NULL) node->color = c; } //  Other
				
				//  Get parent :
				node_pointer	getParent(void) const { //  This
					if (!this->_node || this->_node->parent == this->_node)
						return (NULL);
					return (this->_node->parent);
				}

				node_pointer	getParent(node_pointer node) const { return (node->getParent()); } //  Other

				//  Get grandparent :
				node_pointer	getGrandParent(void) const { //  This
					node_pointer	tmp = this->getParent();

					if (tmp)
						return (tmp->getParent());
					return (NULL);
				}

				node_pointer	getGrandParent(node_pointer node) const { return (node->getGrandParent()); }  //  Other

				//  Get sibling:
				node_pointer	getSibling(void) const { //  This 
					node_pointer	tmp = this->getParent();

					if (tmp && this->_node == tmp->left)
						return (tmp->right);
					else if (tmp)
						return (tmp->left);
					return (NULL);
				}

				node_pointer	getSibling(node_pointer node) const { return (node->getSibling()); } //  Other
				
				//  Get uncle:
				node_pointer	getUncle(void) const { //  This
					node_pointer	tmp = this->getParent();
					
					if (tmp)
						return (tmp->getSibling());
					return (NULL);
				}

				node_pointer	getUncle(node_pointer node) const { return (node->getUncle()); } //  Other

			//  ------------------------ITERATORS------------------------

			public:

				//  Begin :
				iterator				begin(void) { return (iterator(_minimum(this->_node))); }
				const_iterator			begin(void) const { return (const_iterator(_minimum(this->_node))); }
				
				//  End :
				iterator				end(void) { return (iterator(this->_node)); }
				const_iterator			end(void) const { return (iterator(this->_node)); }

				//  Reverse begin :
				reverse_iterator		rbegin(void) { return (reverse_iterator(this->end())); }
				const_reverse_iterator	rbegin(void) const { return (reverse_iterator(this->end())); }

				//  Reverse end :
				reverse_iterator		rend(void) { return (reverse_iterator(this->begin())); }
				const_reverse_iterator	rend(void) const { return (reverse_iterator(this->begin())); }

			//  ------------------------ITERATORS------------------------

			public:

				// Empty :
				bool		empty(void) const {
					if (this->size() == 0)
						return (true);
					return (false);
				}

				//  Size :
				size_type	size(void) const { return (this->_size()); }

				//  Maximum siwe :
				size_type	max_size(void) const { return (this->_node_alloc.max_size()); }

			
			//  -------------------------OTHERS--------------------------

			private:

				//  Delete Tree :
				void		_delete(node_pointer	node) {
					if (node != NULL) {
						_delete(node->left);
						_delete(node->right);
						this->_node_alloc.destroy(node);
						this->_node_alloc.deallocate(node, 1);
					}
				}

				//  Clear Tree :
				void		_clear(void) {
					_delete(this->getRoot());
					this->setRoot(NULL);
					this->_size = 0;
				}

				//  Copy Tree :
				void	_copy(node_pointer node) {
					if (node != NULL) {
						(node->value);
						_copy(node->left);
						_copy(node->right);
					}
				}

				//  Minimum Node value:
				node_pointer	_minimum(node_pointer node) const {
					if (node != NULL) {
						while (node->left != NULL)
							node = node->left;
					}
					return (node);
				}
			

		};
};

#endif