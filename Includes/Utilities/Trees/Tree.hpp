#ifndef	TREE_HPP
# define TREE_HPP
# include <memory> //  Allocator
# include "../Iterators/Reverse_iterator.hpp" //  Reverse iterator
# include "./Node.hpp" //  Tree node
# include "./Iterator.hpp" //  Tree iterator

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
		class tree
		{
			//  ---------------------MEMBER TYPES------------------------
		
			public:
				typedef typename Value::first_type											key_type;
				typedef typename Value::second_type											mapped_type;
				typedef ft::pair<key_type, mapped_type>										value_type;
				typedef Compare																key_compare;
				typedef Alloc																allocator_type;
				typedef ptrdiff_t															difference_type;
				typedef size_t																size_type;
				typedef	ft::tree_node<value_type, Alloc>									node_type;
				typedef ft::tree<value_type, Compare, Alloc>								tree_type;
				typedef ft::tree_iterator<value_type, node_type, tree_type> 				iterator;
				typedef ft::tree_iterator<const value_type, node_type, const tree_type>		const_iterator;
				typedef ft::reverse_iterator<iterator>										reverse_iterator;
				typedef ft::reverse_iterator<const_iterator>								const_reverse_iterator;
				
				typename Alloc::template rebind<ft::tree_node<value_type, Alloc> >::other 	rebind_allocator_type;


			private:
				allocator_type		_alloc;
				key_compare			_comp;
				node_type 			*_root;
			
			
			//  -----------------PUBLIC MEMBER FUNCTION------------------
			
			public:

				//  ---------------------CONSTRUCTOR---------------------

				//  Default constructor :
				tree(void) : _root(NULL) {}

				//  ---------------------DESTRUCTOR----------------------
				
				~tree(void) {
					if (this->_root)
						this->clear();
				}

				//  ----------------------ITERATORS----------------------

				//  Begin :
				iterator				begin(void) { return (iterator(successor(this->_root), this)); }
				const_iterator			begin(void) const { return (const_iterator(successor(this->_root), this)); }
				
				//  End :
				iterator				end(void) { return (iterator(NULL, this)); }
				const_iterator			end(void) const { return (const_iterator(NULL, this)); }

				//  Reverse begin
				reverse_iterator		rbegin(void) { return (reverse_iterator(iterator(NULL, this))); };
				const_reverse_iterator	rbegin(void) const { return (const_reverse_iterator(iterator(NULL, this))); };
				
				//  Reverse end :
				reverse_iterator 		rend(void) { return (reverse_iterator(iterator(successor(this->_root), this))); };
				const_reverse_iterator 	rend(void) const { return (const_reverse_iterator(iterator(successor(this->_root), this))); };

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
					node_type *targetNode = NULL;

					if (!this->_root || !(targetNode = search(val)))
						return (0);
					_erase(targetNode);
					return (1);
				}

				//  Swap :
				void		swap(tree &rhs) {
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
				iterator 	find(value_type const &key) {
					node_type *tmp = search(key);
					
					if (!tmp)
						return iterator(NULL, this);
					return iterator(tmp, this);
				}

				//  Const find :
				const_iterator find (value_type const &key) const 
				{
					node_type *tmp = search(key);
					if (!tmp)
						return const_iterator(NULL, this);
					return const_iterator(tmp, this);
				}

				//  Count :
				size_type count (const key_type& k) const 
				{
					value_type val = ft::make_pair(k, mapped_type());
					node_type *tmp = search(val);
					if (!tmp)
						return 0;
					else
						return 1;
				}
			
				//  Lower bound :
				iterator lower_bound (const key_type& k)
				{
					node_type *p = NULL;
					node_type *tmp = found(k,this->_root,&p);
					if (!tmp)
						return iterator(p,this);
					return iterator(tmp,this);
				}

				//  Const lower bound :
				const_iterator lower_bound (const key_type& k) const
				{
					node_type *p = NULL;
					node_type *tmp = found(k,this->_root,&p);
					if (!tmp)
						return const_iterator(p,this);
					return const_iterator(tmp,this);
				}

				//  Upper bound :
				iterator upper_bound (const key_type& k)
				{
					node_type *p = NULL;
					node_type *tmp = found(k,this->_root,&p);
					if (!tmp)
						return iterator(p,this);
					return ++iterator(tmp,this);
				}

				//  Const upper bound :
				const_iterator upper_bound (const key_type& k) const
				{
					node_type *p = NULL;
					node_type *tmp = found(k,this->_root,&p);
					if (!tmp)
						return const_iterator(p,this);
					return ++const_iterator(tmp,this);
				}
				

				node_type	*bound(const key_type& k) const
				{
					node_type src = _root;
					node_type tmp = src;
					while (src != NULL && src != NULL)
					{
						if (_comp(k, src->value->first))
						{
							tmp = src;
							src = src->left;
						}
						else if (_comp(src->value->first, k))
							src = src->right;
						else 
							return src;
					}
					return tmp;
				}

				//  ----------------------ROTATIONS----------------------

				void 	rotateLeft(node_type *&root, node_type *&node) {
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
				
				void	rotateRight(node_type *&root, node_type *&node) {
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

				// searches for given value
				// if found returns the node (used for erase)
				// else returns the last node while traversing (used in insert)
				node_type *search(value_type val) const
				{
					node_type *tmp = _root;
					while (1)
					{
						if (tmp == NULL)
							return NULL;
						if (val.first == tmp->value->first)
							return tmp;
						if (_comp(val.first, tmp->value->first))
							tmp = tmp->left;
						else
							tmp = tmp->right;
					}
					return tmp;
				}

				node_type *found(key_type index,node_type *root,node_type **p)  const
				{
					if (!root)
						return root;
					if (_comp(index, root->value->first))
					{   
						*p = root;
						return found(index,root->left,p);
					}
					else if (_comp(root->value->first,index))
						return found(index,root->right,p);
					else 
						return root;
				}

				// find node that do not have a left child
				// in the subtree of the given node
				node_type *successor(node_type *x) const
				{
					node_type *temp = x;
				
					if (temp == NULL)
						return NULL;
					while (temp->left != NULL)
						temp = temp->left;
				
					return temp;
				}
				
				// check if node is left child of parent
				bool isOnLeft(node_type *node)
				{
					if (node == NULL)
						return false;
					return (node == node->parent->left);
				}
				
				bool hasRedChild(node_type *node)
				{
					return (node->left != NULL && node->left->color == RED) ||
						(node->right != NULL && node->right->color == RED);
				}
				
				// returns pointer to sibling
				node_type *sibling(node_type *nodeTarget)
				{
					node_type *node = nodeTarget;
					// sibling null if no parent
					if (node->parent == NULL)
						return NULL;
					if (isOnLeft(node))
						return node->parent->right;
					return node->parent->left;
				}
				
				void fixDoubleBlack(node_type *targetNode)
				{
					if (targetNode == _root)
					// Reached root
						return;
				
					node_type *sib = sibling(targetNode);
					node_type *parent = targetNode->parent;
					if (sib == NULL)
					{
						// No sibiling, double black pushed up
						fixDoubleBlack(parent);
					}
					else
					{
						if (sib->color == RED)
						{
							// sib red
							parent->color = RED;
							sib->color = BLACK;
							if (isOnLeft(sib))
							{
								// left case
								rotateRight(_root, parent);
							}
							else
							{
								// right case
								rotateLeft(_root, parent);
							}
							fixDoubleBlack(targetNode);
						}
						else
						{
							// Sibling black
							if (hasRedChild(sib))
							{
								// at least 1 red children
								if (sib->left != NULL && sib->left->color == RED)
								{
									if (isOnLeft(sib))
									{
										// left left
										sib->left->color = sib->color;
										sib->color = parent->color;
										rotateRight(_root, parent);
									}
									else
									{
										// right left
										sib->left->color = parent->color;
										rotateRight(_root, sib);
										rotateLeft(_root, parent);
									}
								}
								else
								{
									if (isOnLeft(sib))
									{
										// left right
										sib->right->color = parent->color;
										rotateLeft(_root, sib);
										rotateRight(_root, parent);
									}
									else
									{
										// right right
										sib->right->color = sib->color;
										sib->color = parent->color;
										rotateLeft(_root, parent);
									}
								}
								parent->color = BLACK;
							}
							else
							{
								// 2 black children
								sib->color = RED;
								if (parent->color == BLACK)
									fixDoubleBlack(parent);
								else
									parent->color = BLACK;
							}
						}
					}
				}

				// find node that replaces a erased node in BST
				node_type *BSTreplace(node_type *&targetNode)
				{
					// when node have 2 children
					if (targetNode->left != NULL && targetNode->right != NULL)
						return successor(targetNode->right);
				
					// when leaf
					if (targetNode->left == NULL && targetNode->right == NULL)
						return NULL;
				
					// when single child
					if (targetNode->left != NULL)
						return targetNode->left;
					else
						return targetNode->right;
				}
				
				void swapValues(node_type *u, node_type *v)
				{
					value_type *tmp;
					tmp = u->value;
					u->value = v->value;
					v->value = tmp;
				}
			

				node_type * getRoot() const { return this->_root; }
				
			//  -----------------PRIVATE MEMBER FUNCTION-----------------

			private :

				//  ----------------------MODIFIERS----------------------

				//  Insert :
				node_type		*_insert(node_type *src , node_type *newNode) {
					/* If the tree is empty, return a new node */
					if (src) {
						/* Otherwise, recur down the tree */
						if (_comp(newNode->value->first, src->value->first)) {
							src->left  = _insert(src->left, newNode);
							src->left->parent = src;
						}
						else {
							src->right = _insert(src->right, newNode);
							src->right->parent = src;
						}
						/* return the (unchanged) node pointer */
						return (src);
					}
					return (newNode);
				}

				//  Insert rebalance :
				void _insertRebalance(node_type *&root, node_type *&newNode)
				{
					node_type *parent_newNode = NULL;
					node_type *grand_parent_newNode = NULL;

					while ((newNode != root) && (newNode->color != BLACK) && (newNode->parent->color == RED))
					{
						parent_newNode = newNode->parent;
						grand_parent_newNode = newNode->parent->parent;

						/*  Case : A ---> Parent of newNode is left child of Grand-parent of newNode */
						if (parent_newNode == grand_parent_newNode->left)
						{
							node_type *uncle_newNode = grand_parent_newNode->right;
							/* Case : 1  The uncle of newNode is also red Only Recoloring required */
							if (uncle_newNode != NULL && uncle_newNode->color == RED)
							{
								grand_parent_newNode->color = RED;
								parent_newNode->color = BLACK;
								uncle_newNode->color = BLACK;
								newNode = grand_parent_newNode;
							}
							else
							{
								/* Case : 2  newNode is right child of its parent  Left-rotation required */
								if (newNode == parent_newNode->right)
								{
									rotateLeft(root, parent_newNode);
									newNode = parent_newNode;
									parent_newNode = newNode->parent;
								}
								/* Case : 3  newNode is left child of its parent Right-rotation required */
								rotateRight(root, grand_parent_newNode);
								std::swap(parent_newNode->color, grand_parent_newNode->color);
								newNode = parent_newNode;
							}
						}

						/* Case : B  Parent of newNode is right child of Grand-parent of newNode */
						else
						{
							node_type *uncle_newNode = grand_parent_newNode->left;
							
							
							/*  Case : 1 The uncle of newNode is also red Only Recoloring required */
							if ((uncle_newNode != NULL) && (uncle_newNode->color == RED))
							{
								grand_parent_newNode->color = RED;
								parent_newNode->color = BLACK;
								uncle_newNode->color = BLACK;
								newNode = grand_parent_newNode;
							}
							else
							{
								/* Case : 2 newNode is left child of its parent Right-rotation required */
								if (newNode == parent_newNode->left)
								{
									rotateRight(root, parent_newNode);
									newNode = parent_newNode;
									parent_newNode = newNode->parent;
								}
				
								/* Case : 3 newNode is right child of its parent Left-rotation required */
								rotateLeft(root, grand_parent_newNode);
								std::swap(parent_newNode->color, grand_parent_newNode->color);
								newNode = parent_newNode;
							}
						}
					}
					root->color = BLACK;
				}
						
				
				//  Erase :
				void _erase(node_type *&targetNode) {
					node_type *nodeReplaceTarget = BSTreplace(targetNode); // looking here debug
				
					// True when u and v are both black
					bool rtBlack = ((nodeReplaceTarget == NULL || nodeReplaceTarget->color == BLACK) && (targetNode->color == BLACK));
					node_type *parentTarget = targetNode->parent;
				
					if (nodeReplaceTarget == NULL) 
					{
						// nodeReplaceTarget is NULL therefore targetNode is leaf
						if (targetNode == _root)
						{
							// targetNode is root, making root null
							_root = NULL;
						}
						else
						{
							if (rtBlack)
							{
								// u and targetNode both black
								// targetNode is leaf, fix double black at targetNode
								fixDoubleBlack(targetNode);
							}
							else
							{
								node_type *tmp = sibling(targetNode);
								// u or targetNode is red
								if (tmp != NULL)
									// sibling is not null, make it red"
									tmp->color = RED;
							}
							// erase targetNode from the tree
							if (isOnLeft(targetNode))
								parentTarget->left = NULL;
							else
								parentTarget->right = NULL;
						}
						rebind_allocator_type.destroy(targetNode);
						rebind_allocator_type.deallocate(targetNode, 1);
						return;
					}
				
					if (targetNode->left == NULL || targetNode->right == NULL)
					{
						// targetNode has 1 child
						if (targetNode == _root)
						{
							std::swap(targetNode->value, nodeReplaceTarget->value);
							targetNode->left = targetNode->right = NULL;
							rebind_allocator_type.destroy(nodeReplaceTarget);
							rebind_allocator_type.deallocate(nodeReplaceTarget, 1);
						}
						else
						{
							// Detach targetNode from tree and motargetNodee u up
							if (isOnLeft(targetNode))
								parentTarget->left = nodeReplaceTarget;
							else
								parentTarget->right = nodeReplaceTarget;
							rebind_allocator_type.destroy(targetNode);
							rebind_allocator_type.deallocate(targetNode, 1);
							nodeReplaceTarget->parent = parentTarget;
							if (rtBlack)
								// u and v both black, fix double black at u
								fixDoubleBlack(nodeReplaceTarget);
							else
								// u or v red, color u black
								nodeReplaceTarget->color = BLACK;
						}
						return;
					}
					// v has 2 children, swap values with successor and recurse
					swapValues(nodeReplaceTarget, targetNode);
					_erase(nodeReplaceTarget);
				}
				//  Clear :
				void	_clear(node_type *rhs)
				{
					if (rhs == NULL)
						return ;
					_clear(rhs->left);
					_clear(rhs->right);
					_alloc.deallocate(rhs->value, 1);
					rebind_allocator_type.deallocate(rhs, 1);
				}
				
		};
}

#endif