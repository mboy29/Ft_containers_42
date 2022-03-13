#ifndef	TREE_HPP
# define TREE_HPP
# include <memory> //  Allocator
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
	template <class Pair, class Compare = std::less<Pair>, class Alloc = std::allocator<Pair> >
		class tree {

			//  ----------------------MEMBER TYPES------------------------

			public:
				typedef tree												tree_type;
				typedef ft::node<Pair>										node_type;
				typedef ft::node<Pair>*										node_pointer;
				typedef	Pair												value_type;
				typedef	Compare												value_compare;
				typedef	Alloc												allocator_type;
				typedef std::allocator<node_type>							node_allocator_type;
				typedef	typename allocator_type::reference					reference;
				typedef	typename allocator_type::const_reference			const_reference;
				typedef	typename allocator_type::pointer					pointer;
				typedef	typename allocator_type::const_pointer				const_pointer;
				typedef	ft::tree_iterator<value_type>						iterator;
				typedef	ft::const_tree_iterator<value_type>					const_iterator;
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

				//  Fill constructor (used when constrocting a map container) :
				tree(value_compare const &comp, allocator_type const &alloc, node_allocator_type const &node_alloc = node_allocator_type())
					: _comp(comp), _alloc(alloc), _node_alloc(node_alloc), _node(NULL), _size(0) {
					this->_node = _node_alloc.allocate(1);
					this->_node_alloc.construct(this->_node, node_type());
				}

				//  Copy constructor :
				tree(tree const &rhs) : _comp(rhs._comp), _alloc(rhs._alloc), _node_alloc(rhs._node_alloc), _node(NULL), _size(0) {
					this->_node = this->_node_alloc.allocate(1);
					this->_node_alloc.construct(this->_node, node_type());
					_copy(rhs.getRoot());
				}

			//  -----------------------DESTRUCTOR------------------------

			public:

				~tree(void) {
					this->clear();
				}
			
			//  ---------------------ASSIGN OPERATOR---------------------
			
			public:

				//  Operator= :
				tree&		operator=(tree const &rhs) {
					if (this != &rhs) {
						this->clear();
						this->_comp = rhs._comp;
						this->_alloc = rhs._alloc;
						this->_node_alloc = rhs._alloc;
						_copy(rhs.getRoot());
						this->_size = rhs._size;
					}
					return (*this);
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
				
				color			getColor(node_pointer node) const { //  Other
					if (!node) //  Leaf always black
						return (BLACK);
					return (node->color);
				}

				void			setColor(color c) { if (this->_node != NULL) this->_node->color = c; } //  This
				void			setColor(node_pointer node, color c) { if (node != NULL) node->color = c; } //  Other
				
				//  Get parent :
				node_pointer	getParent(void) const { //  This
					if (!this->_node || this->_node->parent == this->_node)
						return (NULL);
					return (this->_node->parent);
				}

				node_pointer	getParent(node_pointer node) const { //  Other
					if (!node || (node && node->parent == this->_node))
						return (NULL);
					return (node->parent);
				}
				//  Get grandparent :
				node_pointer	getGrandParent(void) const { //  This
					node_pointer	parent = this->getParent();

					if (parent)
						return (parent->getParent());
					return (NULL);
				}

				node_pointer	getGrandParent(node_pointer node) const {  //  Other
					node_pointer	parent = getParent(node);
					
					if (parent)
						return (getParent(parent));
					return (NULL);
				}

				//  Get sibling:
				node_pointer	getSibling(void) const { //  This 
					node_pointer	parent = this->getParent();

					if (parent && this->_node == parent->left)
						return (parent->right);
					else if (parent)
						return (parent->left);
					return (NULL);
				}

				node_pointer	getSibling(node_pointer node) const {  //  Other
					node_pointer	parent = getParent(node);

					if (parent && node == parent->left)
						return (parent->right);
					else if (parent)
						return (parent->right);
					return (NULL);
				}
				//  Get uncle:
				node_pointer	getUncle(void) const { //  This
					node_pointer	parent = this->getParent();
					
					if (parent)
						return (parent->getSibling());
					return (NULL);
				}

				node_pointer	getUncle(node_pointer node) const {  //  Other
					node_pointer	parent = getParent(node);

					if (parent)
						return (getSibling(parent));
					return (NULL);
				}

			//  ------------------------ITERATORS------------------------

			public:

				//  Begin :
				iterator				begin(void) { return (iterator(_minimum(this->_node))); }
				const_iterator			begin(void) const { return (const_iterator(_minimum(this->_node))); }
				
				//  End :
				iterator				end(void) { return (iterator(this->_node)); }
				const_iterator			end(void) const { return (const_iterator(this->_node)); }

				//  Reverse begin :
				reverse_iterator		rbegin(void) { return (reverse_iterator(this->end())); }
				const_reverse_iterator	rbegin(void) const { return (const_reverse_iterator(this->end())); }

				//  Reverse end :
				reverse_iterator		rend(void) { return (reverse_iterator(this->begin())); }
				const_reverse_iterator	rend(void) const { return (const_reverse_iterator(this->begin())); }

			//  ------------------------CAPACITY-------------------------

			public:

				// Empty :
				bool		empty(void) const {
					if (this->size() == 0)
						return (true);
					return (false);
				}

				//  Size :
				size_type	size(void) const { return (this->_size); }

				//  Maximum siwe :
				size_type	max_size(void) const { return (this->_alloc.max_size()); }
			
			//  ------------------------MODIFIERS------------------------

			public:

				//  Insert/map::insert single element (empty tree) :
				pair<iterator, bool>	insert(const value_type& val) { return (_insertValue(val));	}

				//  Insert/map::insert "hint" :
				iterator 				insert(iterator position, const value_type& val) {
					(void)position;
					return (_insertValue(val).first);
				}

				//  Insert/map::insert rang :
				template<class InputIterator>
					void 				insert(InputIterator first, InputIterator last) {
						while (first != last) {
							this->insert(*first);
							++first;
						}
					}

				//  Erase/map::erase by position :
				void 		erase(const_iterator position) { _eraseValue(*position); }
				
				//  Erase/map::erase by value :
				size_type	erase(value_type const &val) { return (_eraseValue(val)); }

				//  Erase/map::erase by range :
				void 		erase(const_iterator first, const_iterator last) {
					
					for (const_iterator it = first; it != last; it++) {
						
					}
				}

				//  Swap :
				void		swap(tree &rhs) {
					value_compare		comp = rhs._comp;
					allocator_type		alloc = rhs._alloc;
					node_allocator_type	node_alloc = rhs._node_alloc;
					node_pointer		node = rhs._node;
					size_type			size = rhs._size;

					rhs._comp = this->_comp;
					rhs._alloc = this->_alloc;
					rhs._node_alloc = this->_alloc;
					rhs._node = this->_node;
					rhs._size = this->_size;
					this->_comp = comp;
					this->_alloc = alloc;
					this->_node_alloc = node_alloc;
					this->_node = node;
					this->_size = size;
				}

				//  Clear Tree :
				void		clear(void) {
					_delete(this->getRoot());
					this->setRoot(NULL);
					this->_size = 0;
				}
			
			//  -----------------------OPERATIONS------------------------

			public:

				//  Find/map::find :
				node_pointer	find(value_type const &val) const {
					node_pointer	tmp = getRoot();
					
					while (tmp) {
						if (!(_comp(tmp->value, val)) && !(_comp(val, tmp->value)))
							break ;
						else if (_comp(tmp->value, val))
							tmp = tmp->right;
						else
							tmp = tmp->left;
					}
					if (!tmp)
						return (this->_node);
					return (tmp);
				}

				//  Count/map::count :
				size_type		count(value_type const &val) const {
					const_iterator	tmp = find(val);

					if (tmp == this->end())
						return (0);
					return (1);
				}

				//  Lower bound/Map::lower_bound :
				iterator		lower_bound(const value_type& k) {
					iterator	begin = this->begin();

					while (begin != this->end()) {
						if (_comp(*begin, k) ==  false)
							break;
						++begin;
					}
					return (begin);
				}
				
				//  Const lower bound/Map::lower_bound (const):
				const_iterator	lower_bound(const value_type& k) const {
					const_iterator	begin = this->begin();

					while (begin != this->end()) {
						if (_comp(*begin, k) == false)
							break;
						++begin;
					}
					return (begin);
				}

				//  Upper bound/Map::upper_bound :
				iterator		upper_bound(const value_type& k) {
					iterator	begin = this->begin();

					while (begin != this->end()) {
						if (_comp(k, *begin) == true)
							break;
						++begin;
					}
					return (begin);
				}
				
				//  Const upper bound/Map::upper_bound (const):
				const_iterator	upper_bound(const value_type& k) const {
					const_iterator	begin = this->begin();

					while (begin != this->end()) {
						if (_comp(k, *begin) == true)
							break;
						++begin;
					}
					return (begin);
				}
				
			//  -------------------------INSERT--------------------------
			
			
			private:
				

				//  Insert :
				void		 			_insert(node_pointer node) {
					node_pointer	parent, grandparent, uncle;

					while (node != this->getRoot() && getColor(node) == RED && getColor(getParent(node)) == RED) {
						parent = getParent(node);
						grandparent = getGrandParent(node);
						uncle = getUncle(node);
						if (getColor(uncle) == RED)
							_insertRecolor(node);
						else if (parent == grandparent->left)
							(node == parent->right) ? _insertRotate(node, parent) : _insertSwap(node, parent, grandparent);
						else if (parent == grandparent->right)
							(node == parent->left) ? _insertRotate(node, parent) : _insertSwap(node, parent, grandparent);
					}
					setColor(this->getRoot(), BLACK);
				}

				//  Insert node :
				pair<iterator, bool>	_insertNode(node_pointer node) {
					node_pointer	tmp = this->getRoot(), parent;

					if (!tmp) {
						this->setRoot(node);
						return (ft::make_pair(iterator(node), true));
					}
					while (tmp) {
						if (_comp(tmp->value, node->value)) {
							parent = tmp;
							tmp = tmp->right;
						}
						else if (_comp(node->value, tmp->value)) {
							parent = tmp;
							tmp = tmp->left;
						}
						else
							return (ft::make_pair(iterator(tmp), false));
					}
					if (_comp(parent->value, node->value))
						parent->right = node;
					else
						parent->left = node;
					node->parent = parent;
					return (ft::make_pair(iterator(node), true));
				}
				
				//  Insert value :
				pair<iterator, bool>	_insertValue(const value_type &val) {
					node_pointer				node = this->_node_alloc.allocate(1);
					this->_node_alloc.construct(node, node_type(val));
					ft::pair<iterator, bool>	tmp = _insertNode(node);

					if (tmp.second == false) {
						this->_node_alloc.destroy(node);
						this->_node_alloc.deallocate(node, 1);
					}
					else {
						this->_size += 1;
						_insert(node);
					}
					return (tmp);
				}

			//  --------------------------ERASE--------------------------
// for (const_iterator it = this->begin(); it != this->end(); it++)
// 						std::cout << it->first << " " << it->second << std::endl;
			private:

				//  Erase :
				void			_erase(node_pointer node) {
					node_pointer ptr = NULL, parent = NULL, tmp = NULL;
					
					if (node == NULL) 
						return ;
					if (node == this->getRoot())
						return (_eraseRoot(node));
					if (getColor(node) == RED || getColor(node->left) == RED || getColor(node->right) == RED)
						return (_eraseRed(node));
					tmp = node;
					setColor(tmp, UNDEFINED);
					std::cout << "==> 5" << std::endl;
					while (tmp != this->getRoot() && getColor(tmp) == UNDEFINED) {
						parent = tmp->parent;
						if (tmp == parent->left || !parent->left)
							ptr = parent->right;
						else
							ptr = parent->left;
						// ptr = (tmp == parent->left) ? parent->right : parent->left;
						if (getColor(ptr) == RED)
							_eraseRotate1(ptr, parent);
						else if (getColor(ptr->left) == BLACK && getColor(ptr->right) == BLACK)
							_eraseRecolor(ptr, parent, tmp);
						else {
							if ((tmp == parent->left && getColor(ptr->right) == BLACK)
								|| (tmp == parent->right && getColor(ptr->left) == BLACK))
								_eraseRotate2(ptr, parent);
							_eraseRotate3(ptr, parent);
							break;
						}
					}
					for (const_iterator it = this->begin(); it != this->end(); it++)
						std::cout << "----------" << it->first << " " << it->second << std::endl;
					std::cout << "=> " << node->value.second << std::endl; //->value.first << " " << node->value.second << std::endl;
					std::cout << "=> " << node->parent->left<< std::endl;
					std::cout << "=> " << node->parent->right->value.second << std::endl ; //<< " " << node->parent->left->value.second << std::endl;
					//std::cout << "=> " << node->parent->right->value.first << " " << node->parent->right->value.second << std::endl;
					if (node == node->parent->right)
						node->parent->right = NULL;
					else
						node->parent->left = NULL;
					for (const_iterator it = this->begin(); it != this->end(); it++)
						std::cout << "--------------" << it->first << " " << it->second << std::endl;
					this->_node_alloc.destroy(node);
					this->_node_alloc.deallocate(node, 1);
					setColor(this->getRoot(), BLACK);
				}

				//  Erase node :
				node_pointer	_eraseNode(node_pointer node, value_type const &val) {
					if (node == NULL)
						return (node);
					if (_comp(node->value, val)) // 삭제하고자하는 위치 찾기
						return (_eraseNode(node->right, val));
					if (_comp(val, node->value))
						return (_eraseNode(node->left, val));
					if (node->left == NULL || node->right == NULL)
						return (node);
					node_pointer tmp = _minimum(node->right);
					if (tmp->parent == node) //tmp left가 null
					{
						if (node->parent && node->parent->left == node)
							node->parent->left = tmp;
						if (node->parent && node->parent->right == node)
							node->parent->right = tmp;
						tmp->left = node->left;
						node->left->parent = tmp;
						node->left = NULL; // 529번째줄로 return하기 위한 조건
						tmp->parent = node->parent;
						node->parent = tmp;
						node->right = tmp->right;
						tmp->right = node;
						std::swap(tmp->color, node->color);
					}
					else
					{
						if (node->parent && node->parent->left == node)
							node->parent->left = tmp;
						if (node->parent && node->parent->right == node)
							node->parent->right = tmp;
						if (tmp->parent->left == tmp)
							tmp->parent->left = node;
						if (tmp->parent->right == tmp)
							tmp->parent->right = node;
						node_pointer tmp2 = tmp->parent;
						node->right->parent = tmp;
						tmp->parent = node->parent;
						node->parent = tmp2;
						tmp->left = node->left;
						node->left->parent = tmp;
						node->left = NULL;
						node_pointer tmp3 = tmp->right;
						tmp->right = node->right;
						node->right = tmp3;
						std::swap(tmp->color, node->color);
					}
					return (_eraseNode(tmp->right, val));
				}

				//  Erase value:
				size_type	_eraseValue(value_type const &val) {
					node_pointer	tmp;
					
					if (!(tmp = _eraseNode(this->getRoot(), val)))
						return (0);
					_erase(tmp);
					this->_size -= 1;
					return (1);
				}

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

				//  Copy Tree :
				void	_copy(node_pointer node) {
					if (node != NULL) {
						_insertValue(node->value);
						_copy(node->left);
						_copy(node->right);
					}
				}

				//  Minimum node value:
				node_pointer	_minimum(node_pointer node) const {
					if (node != NULL) {
						while (node->left != NULL)
							node = node->left;
					}
					return (node);
				}

				//  Rotate left :
				void	_rotateLeft(node_pointer node) {
					node_pointer	right = node->right;

					if (right) {
						if ((node->right = right->left))
							node->right->parent = node;
						right->parent = node->parent;
						if (!getParent(node))
							setRoot(right);
						else if (node == node->parent->left)
							node->parent->left = right;
						else
							node->parent->right = right;
						right->left = node;
						node->parent = right;
					}
				}

				//  Rotate right :
				void	_rotateRight(node_pointer node) {
					node_pointer	left = node->left;

					if (left) {
						if ((node->left = left->right))
							node->left->parent = node;
						left->parent = node->parent;
						if (!getParent(node))
							setRoot(left);
						else if (node != node->parent->left)
							node->parent->right = left;
						else
							node->parent->left = left;
						left->right = node;
						node->parent = left;
					}
				}

				//  Recolor (_insert) :
				void	_insertRecolor(node_pointer &node) {
					setColor(getParent(node), BLACK);
					setColor(getGrandParent(node), RED);
					setColor(getUncle(node), BLACK);
					node = getGrandParent(node);
				}

				//  Rotate (_insert) :
				void	_insertRotate(node_pointer &node, node_pointer &parent) {
					if (parent == getGrandParent(node)->left)
						_rotateLeft(parent);
					else if (parent == getGrandParent(node)->right)
						_rotateRight(parent);
					node = parent;
					parent = getParent(node);
				}

				//  Swap (_insert) :
				void	_insertSwap(node_pointer &node, node_pointer parent, node_pointer grandparent) {
					if (parent == grandparent->left)
						_rotateRight(grandparent);
					else if (parent == grandparent->right)
						_rotateLeft(grandparent);
					std::swap(parent->color, grandparent->color);
					node = parent;
				}

				//  Erase root (_erase) :
				void	_eraseRoot(node_pointer root) {
					if (root->right)
						setRoot(root->right);
					else
						setRoot(root->left);
					this->_node_alloc.destroy(root);
					this->_node_alloc.deallocate(root, 1);
					setColor(this->getRoot(), BLACK);
				}

				//  Erase red (_erase) :
				void	_eraseRed(node_pointer &node) {
					node_pointer	tmp;

					if (node->left)
						tmp = node->left;
					else
						tmp = node->right;
					if (node == node->parent->left)
						node->parent->left = tmp;
					else
						node->parent->right = tmp;
					if (tmp)
						tmp->parent = node->parent;
					setColor(tmp, BLACK);
					this->_node_alloc.destroy(node);
					this->_node_alloc.deallocate(node, 1);
				}

				//  Erase rotate 1 (_erase) :
				void	_eraseRotate1(node_pointer &ptr, node_pointer &parent) {
					if (ptr == parent->right)
						_rotateLeft(parent);
					if (ptr == parent->left)
						_rotateRight(parent);
					setColor(ptr, BLACK);
					setColor(parent, RED);
				}

				//  Erase rotate 2 (_erase) :
				void	_eraseRotate2(node_pointer &ptr, node_pointer &parent) {
					if (ptr == parent->right) {
						_rotateRight(ptr);
						setColor(ptr->left, BLACK);
						setColor(ptr, RED);
						ptr = parent->right;
					}
					if (ptr == parent->left) {
						_rotateLeft(ptr);
						setColor(ptr->right, BLACK);
						setColor(ptr, RED);
						ptr = parent->left;
					}
				}

				//  Erase rotate 3 (_erase) :
				void	_eraseRotate3(node_pointer &ptr, node_pointer &parent) {
					if (ptr == parent->right) {
						_rotateLeft(parent);
						setColor(ptr, getColor(parent));
						setColor(parent, BLACK);
						setColor(ptr->right, BLACK);
					}
					if (ptr == parent->left) {
						_rotateRight(parent);
						setColor(ptr, getColor(parent));
						setColor(parent, BLACK);
						setColor(ptr->left, BLACK);
					}
				}

				//  Erase recolor (_erase) :
				void	_eraseRecolor(node_pointer ptr, node_pointer parent, node_pointer node) {
					setColor(ptr, RED);
					if (getColor(parent) == RED)
						setColor(parent, BLACK);
					else
						setColor(parent, UNDEFINED);
					node = parent;
				}

			

		};
};

#endif