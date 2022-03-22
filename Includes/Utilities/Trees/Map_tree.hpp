#ifndef	MAP_TREE_HPP
# define MAP_TREE_HPP
# include <memory> //  Allocator
# include "../Iterators/Reverse_iterator.hpp" //  Reverse iterator
# include "../Iterators/Map_iterator.hpp" //  Tree iterator
# include "./Map_node.hpp" //  Tree node


//  ----------------------------BLACK RED TREE----------------------------
//    -> Class Template
//    A RED-BLACK tree is a self-balancing binary search tree where each
//    node has an extra bit, interpreted as the colour (RED or BLACK).
//    Every RED-BLACK tree follows these 5 rules: 
//    - Every node has a colour, either RED or BLACK ;
//    - The root of the tree is always BLACK ;
//    - There are no two adjacent RED nodes (a RED node cannot have a RED
//      parent or RED child) ;
//    - Every path from a node (including root) to any of its descendants
//      NULL nodes has the same number of BLACK nodes ;
//    - All leaf nodes are BLACK nodes.
//  ----------------------------------------------------------------------

namespace ft {
	template <class Value, class Compare, class Alloc = std::allocator<Value> >
		class map_tree {

			//  ---------------------MEMBER TYPES------------------------
		
			public:
				typedef typename Value::first_type											key_type;
				typedef typename Value::second_type											mapped_type;
				typedef ft::pair<key_type, mapped_type>										value_type;
				typedef Compare																key_compare;
				typedef Alloc																allocator_type;
				typedef	ft::map_node<value_type, Alloc>										node_type;
				typedef ft::map_tree<value_type, Compare, Alloc>							tree_type;
				typedef ft::map_iterator<value_type, node_type, tree_type> 					iterator;
				typedef ft::map_iterator<const value_type, node_type, const tree_type>		const_iterator;
				typedef ft::reverse_iterator<iterator>										reverse_iterator;
				typedef ft::reverse_iterator<const_iterator>								const_reverse_iterator;
				typename Alloc::template rebind<ft::map_node<value_type, Alloc> >::other 	rebind_allocator_type;
				typedef ptrdiff_t															difference_type;
				typedef size_t																size_type;

			private:
				allocator_type		_alloc;
				key_compare			_comp;
				node_type 			*_root;
			
			
			//  -----------------PUBLIC MEMBER FUNCTION------------------
			
			public:

				//  ---------------------CONSTRUCTOR---------------------

				//  Default constructor :
				map_tree(void) : _root(NULL) {}

				//  ---------------------DESTRUCTOR----------------------
				
				~map_tree(void) {
					if (this->_root)
						this->clear();
				}

				//  ------------------------BASE-------------------------

				node_type 	*getBase(void) const { return (this->_root); }

				//  ----------------------ITERATORS----------------------

				//  Begin :
				iterator				begin(void) { return (iterator(_getInherit(this->_root), this)); }
				const_iterator			begin(void) const { return (const_iterator(_getInherit(this->_root), this)); }
				
				//  End :
				iterator				end(void) { return (iterator(NULL, this)); }
				const_iterator			end(void) const { return (const_iterator(NULL, this)); }

				//  Reverse begin :
				reverse_iterator		rbegin(void) { return (reverse_iterator(iterator(NULL, this))); };
				const_reverse_iterator	rbegin(void) const { return (const_reverse_iterator(iterator(NULL, this))); };
				
				//  Reverse end :
				reverse_iterator 		rend(void) { return (reverse_iterator(iterator(_getInherit(this->_root), this))); };
				const_reverse_iterator 	rend(void) const { return (const_reverse_iterator(iterator(_getInherit(this->_root), this))); };

				//  ----------------------CAPACITY-----------------------
			
				//  Empty :
				bool 		empty(void) const { return (!(this->_root) ? true : false); };
				
				//  Max size :
				size_type 	max_size(void) const { return (this->_alloc.max_size()); }

				//  -------------------ELEMENT ACCESS--------------------

				//  Operator[] :
				
				mapped_type&	operator[](key_type const &key) { return (*((this->insert(ft::make_pair(key ,mapped_type()))).first)).second; }
				
				//  ----------------------MODIFIERS----------------------
				
				//  Insert :
				void		insert(value_type val) {
					node_type *newNode = this->rebind_allocator_type.allocate(1);
					
					this->rebind_allocator_type.construct(newNode, val);
					this->_root = _insert(this->_root, newNode);
					_insertRebalance(this->_root, newNode);
				}

				//  erase :
				size_type	erase(value_type val) {
					node_type *tmp = NULL;

					if (!this->_root || !(tmp = search(val)))
						return (0);
					_erase(tmp);
					return (1);
				}

				//  Swap :
				void		swap(map_tree &rhs) {
					std::swap(this->_root, rhs._root);
					std::swap(this->_alloc, rhs._alloc);
					std::swap(this->_comp, rhs._comp);
					std::swap(this->rebind_allocator_type, rhs.rebind_allocator_type);
				}

				//  Clear :
				void	 	clear(void) {
					_clear(this->_root);
					this->_root = NULL;
				}
				
				//  ---------------------OPERATIONS----------------------


				//  Find :
				iterator		find(value_type const &key) {
					node_type *tmp = NULL;
					
					if (!(tmp = search(key)))
						return (iterator(NULL, this));
					return (iterator(tmp, this));
				}

				//  Const find :
				const_iterator	find(value_type const &key) const {
					node_type *tmp = NULL;
					
					if (!(tmp = search(key)))
						return (const_iterator(NULL, this));
					return (const_iterator(tmp, this));
				}

				//  Count :
				size_type		count(key_type const &key) const {
					node_type *tmp = NULL;
					
					if (!(tmp = search(ft::make_pair(key, mapped_type()))))
						return (0);
					return (1);
				}
			
				//  Lower bound :
				iterator		lower_bound(key_type const &key){
					node_type *ptr = NULL, *tmp = NULL;
				
					if (!(tmp = _search(key ,this->_root, &ptr)))
						return (iterator(ptr, this));
					return (iterator(tmp, this));
				}

				//  Const lower bound :
				const_iterator	lower_bound(key_type const &key) const {
					node_type *ptr = NULL, *tmp = NULL;
					
					if (!(tmp = _search(key, this->_root, &ptr)))
						return (const_iterator(ptr, this));
					return (const_iterator(tmp, this));
				}

				//  Upper bound :
				iterator		upper_bound(key_type const &key) {
					node_type *ptr = NULL, *tmp = NULL;
					
					if (!(tmp = _search(key, this->_root, &ptr)))
						return (iterator(ptr,this));
					return (++iterator(tmp,this));
				}

				//  Const upper bound :
				const_iterator	upper_bound(key_type const &key) const {
					node_type *ptr = NULL, *tmp = NULL;
					
					if (!(tmp = _search(key, this->_root, &ptr)))
						return (const_iterator(ptr,this));
					return (++const_iterator(tmp,this));
				}
				
				//  Bound :
				node_type	*bound(key_type const &key) const {
					node_type rhs = this->_root, lhs = rhs;
					
					while (rhs) {
						if (_comp(key, rhs->value->first)) {
							lhs = rhs;
							rhs = rhs->left;
						}
						else if (_comp(rhs->value->first, key))
							rhs = rhs->right;
						else 
							return (rhs);
					}
					return (lhs);
				}

				// Search :
				node_type	*search(value_type val) const {
					node_type *tmp = this->_root;
					
					while (1) {
						if (!tmp)
							return (NULL);
						if (val.first == tmp->value->first)
							return (tmp);
						if (_comp(val.first, tmp->value->first))
							tmp = tmp->left;
						else
							tmp = tmp->right;
					}
					return (tmp);
				}
				//  ----------------------ROTATIONS----------------------

				//  Left rotation :
				void 		rotateLeft(node_type *&root, node_type *&node) {
					node_type	*tmp = node->right;
				
					if ((node->right = tmp->left))
						node->right->parent = node;
					tmp->parent = node->parent;
					if (!node->parent)
						root = tmp;
					else if (node == node->parent->left)
						node->parent->left = tmp;
					else
						node->parent->right = tmp;
					tmp->left = node;
					node->parent = tmp;
				}

				//  Right rotation :
				void		rotateRight(node_type *&root, node_type *&node) {
					node_type *tmp = node->left;
				
					if ((node->left = tmp->right))
						node->left->parent = node;
					tmp->parent = node->parent;
					if (node->parent == NULL)
						root = tmp;
					else if (node == node->parent->left)
						node->parent->left = tmp;
					else
						node->parent->right = tmp;
					tmp->right = node;
					node->parent = tmp;
				}
				
			//  -----------------PRIVATE MEMBER FUNCTION-----------------

			private :

				//  ------------------INSERT MODIFIER--------------------
		
				//  Insert :
				node_type		*_insert(node_type *rhs , node_type *lhs) {
					if (rhs) {
						if (_comp(lhs->value->first, rhs->value->first)) {
							rhs->left = _insert(rhs->left, lhs);
							rhs->left->parent = rhs;
						}
						else {
							rhs->right = _insert(rhs->right, lhs);
							rhs->right->parent = rhs;
						}
						return (rhs);
					}
					return (lhs);
				}

				//  Insert recolor :
				void	_insertRecolor(node_type *&node, node_type *parent, node_type *grand, node_type *uncle) {
					grand->color = MRED;
					parent->color = MBLACK;
					uncle->color = MBLACK;
					node = grand;
				}

				//  Insert rotate left (parent of node is left child of grand of node) :
				void	_insertRotateLeftL(node_type *&root, node_type *& node, node_type *parent) {
					rotateLeft(root, parent);
					node = parent;
					parent = node->parent;
				}

				//  Insert rotate right (parent of node is left child of grand of node):
				void	_insertRotateRightL(node_type *&root, node_type *&node, node_type *parent, node_type *grand) {
					rotateRight(root, grand);
					std::swap(parent->color, grand->color);
					node = parent;
				}
				
				//  Insert rotate left (parent of node is right child of grand of node):
				void	_insertRotateLeftR(node_type *&root, node_type *& node, node_type *parent, node_type *grand) {
					rotateLeft(root, grand);
					std::swap(parent->color, grand->color);
					node = parent;
				}

				//  Insert rotate Right (parent of node is right child of grand of node):
				void	_insertRotateRightR(node_type *&root, node_type *& node, node_type *parent) {
					rotateRight(root, parent);
					node = parent;
					parent = node->parent;
				}

				//  Insert rebalance :
				void	_insertRebalance(node_type *&root, node_type *&node)
				{
					node_type *parent = NULL, *grand = NULL;

					while ((node != root) && (node->color != MBLACK) && (node->parent->color == MRED))
					{
						parent = node->parent;
						grand = node->parent->parent;
						if (parent == grand->left) {
							if (grand->right != NULL && grand->right->color == MRED) 
								_insertRecolor(node, parent, grand, grand->right);
							else {
								if (node == parent->right) 
									_insertRotateLeftL(root, node, parent);
								_insertRotateRightL(root, node, parent, grand);
							}
						}
						else {
							if ((grand->left != NULL) && (grand->left->color == MRED))
								_insertRecolor(node, parent, grand, grand->left);
							else {
								if (node == parent->left)
									_insertRotateRightR(root, node, parent);
								_insertRotateLeftR(root, node, parent, grand);
							}
						}
					}
					root->color = MBLACK;
				}

				//  -------------------ERASE MODIFIER--------------------

				//  Erase leaf :
				void	_eraseLeaf(node_type *&rhs, node_type *parent, bool isBlack) {
					node_type	*tmp = NULL;

					if (isBlack)
						_eraseRebalance(rhs);
					else if ((tmp = _getSibling(rhs)))
						tmp->color = MRED;
					if (_isLeft(rhs))
						parent->left = NULL;
					else
						parent->right = NULL;
				}
				//  Erase detach :
				void	_eraseDetach(node_type *&rhs, node_type *node, node_type *parent, bool isBlack) {
					if (_isLeft(rhs))
						parent->left = node;
					else
						parent->right = node;
					rebind_allocator_type.destroy(rhs);
					rebind_allocator_type.deallocate(rhs, 1);
					node->parent = parent;
					if (isBlack)
						_eraseRebalance(node);
					else
						node->color = MBLACK;
				}
	
				//  Erase :
				void	_erase(node_type *&rhs) {
					node_type *node = _replace(rhs), *parent = rhs->parent;

					bool isBlack = ((node == NULL || node->color == MBLACK) && (rhs->color == MBLACK));
					if (!node) {
						if (rhs == this->_root)
							this->_root = NULL;
						else
							_eraseLeaf(rhs, parent, isBlack);
						rebind_allocator_type.destroy(rhs);
						rebind_allocator_type.deallocate(rhs, 1);
						return;
					}
					if (!rhs->left || !rhs->right) {
						if (rhs == this->_root) {
							std::swap(rhs->value, node->value);
							rhs->left = rhs->right = NULL;
							rebind_allocator_type.destroy(node);
							rebind_allocator_type.deallocate(node, 1);
						}
						else
							_eraseDetach(rhs, node, parent, isBlack);
						return;
					}
					_swap(node, rhs);
					_erase(node);
				}

				//  Erase MRED sibling :
				void	_eraseRedSibling(node_type *rhs, node_type *sibling, node_type *parent) {
					parent->color = MRED;
					sibling->color = MBLACK;
					if (_isLeft(sibling))
						rotateRight(this->_root, parent);
					else
						rotateLeft(this->_root, parent);
					_eraseRebalance(rhs);
				}

				//  Erase black sibling's left child : 
				void	_eraseBlackSiblingL(node_type *sibling, node_type *parent) {
					if (_isLeft(sibling)) {
						sibling->left->color = sibling->color;
						sibling->color = parent->color;
						rotateRight(this->_root, parent);
					}
					else {
						sibling->left->color = parent->color;
						rotateRight(this->_root, sibling);
						rotateLeft(this->_root, parent);
					}
				}

				//  Erase sibling's right child : 
				void	_eraseBlackSiblingR(node_type *sibling, node_type *parent) {
					if (_isLeft(sibling)) {
						sibling->right->color = parent->color;
						rotateLeft(this->_root, sibling);
						rotateRight(this->_root, parent);
					}
					else {
						sibling->right->color = sibling->color;
						sibling->color = parent->color;
						rotateLeft(this->_root, parent);
					}
				}

				//  Erase rebalance :
				void	_eraseRebalance(node_type *rhs) {
					node_type *sibling = NULL, *parent = rhs->parent;
					
					if (rhs != this->_root && !(sibling = _getSibling(rhs)))
						return (_eraseRebalance(parent));
					else if (rhs != this->_root) {
						if (sibling->color == MRED)
							return (_eraseRedSibling(rhs, sibling, parent));
						else if (_isRedChild(sibling)) {
							if (sibling->left != NULL && sibling->left->color == MRED)
								_eraseBlackSiblingL(sibling, parent);
							else
								_eraseBlackSiblingR(sibling, parent);
							parent->color = MBLACK;
						}
						else {
							sibling->color = MRED;
							if (parent->color == MBLACK)
								_eraseRebalance(parent);
							else
								parent->color = MBLACK;
						}
					}
				}
				
				//  -------------------OTHER MODIFIERS-------------------

				//  Swap :
				void		_swap(node_type *rhs, node_type *lhs) {
					value_type *tmp = rhs->value;
					
					rhs->value = lhs->value;
					lhs->value = tmp;
				}

				//  Clear :
				void		_clear(node_type *rhs)
				{
					if (rhs == NULL)
						return ;
					_clear(rhs->left);
					_clear(rhs->right);
					_alloc.deallocate(rhs->value, 1);
					rebind_allocator_type.deallocate(rhs, 1);
				}

				// 	Replace :
				node_type	*_replace(node_type *&rhs) {
					if (rhs->left != NULL && rhs->right != NULL)
						return (_getInherit(rhs->right));
					if (rhs->left == NULL && rhs->right == NULL)
						return (NULL);
					if (rhs->left != NULL)
						return (rhs->left);
					return (rhs->right);
				}

				//  ---------------------OPERATIONS----------------------
				
				//  Find :
				node_type	*_search(key_type idx, node_type *root, node_type **ptr) const {
					if (root) {
						if (_comp(idx, root->value->first)) {   
							*ptr = root;
							return (_search(idx, root->left, ptr));
						}
						else if (_comp(root->value->first, idx))
							return (_search(idx, root->right, ptr));
					}
					return (root);
				}

				//  -----------------OTHERS (GET/IS/SET)-----------------
				
				// Is left :
				bool		_isLeft(node_type *rhs) {
					if (rhs == NULL)
						return (false);
					return (rhs == rhs->parent->left);
				}
				
				//  Is red child :
				bool	_isRedChild(node_type *rhs) {
					return (rhs->left != NULL && rhs->left->color == MRED) ||
						(rhs->right != NULL && rhs->right->color == MRED);
				}
				
				//  Get inheritor :
				node_type	*_getInherit(node_type *rhs) const {
					node_type *tmp = NULL;
				
					if ((tmp = rhs)) {
						while (tmp->left != NULL)
							tmp = tmp->left;
						return (tmp);
					}
					return (NULL);
				}

				//  Get sibling :
				node_type	*_getSibling(node_type *rhs) {
					node_type *tmp = rhs;

					if (tmp->parent) {
						if (_isLeft(tmp))
							return (tmp->parent->right);
						return (tmp->parent->left);
					}
					return (NULL);
				}
		
		};
}

#endif