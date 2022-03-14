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
    template <class T, class Node, class Tree>
		class tree_iterator {

			//  -----------------------MEMBER TYPES-----------------------

			protected:
				Node 			*_node;
				const Tree 		*_tree;
		
			public:
				typedef iterator_traits< iterator<std::bidirectional_iterator_tag, T> >	iterator_traits;
				typedef typename iterator_traits::value_type 							value_type;
				typedef typename iterator_traits::pointer								pointer;
				typedef typename iterator_traits::reference								reference;
				typedef typename iterator_traits::difference_type						difference_type;
				typedef typename iterator_traits::iterator_category						iterator_category;
			
			//  ---------------------MEMBER FUNCTIONS---------------------

			public :

				//  ---------------------CONSTRUCTORS---------------------

				//  Default constructor :
				tree_iterator(void) : _node(), _tree() {}
				
				//  Fill constructor :
				tree_iterator(Node *node, const Tree *tree) : _node(node), _tree(tree) {}
				
				//  Copy constructor :
				tree_iterator(const tree_iterator& rhs) { *this = rhs; }
			
				//  ---------------------DESSTRUCTOR----------------------	
			
				//  Destructor :
				virtual ~tree_iterator(void) {}
			
				//  -------------------------BASE-------------------------

				Node *base(void) const { return (this->_node); }

				//  -------------------CONVERT TO CONST-------------------
				
				operator	tree_iterator<const T, Node, const Tree>(void) const {
					return (tree_iterator<const T, Node, const Tree>(this->_node, this->_tree));
				}
				
				//  -----------------ASSIGNMENT OPERATOR------------------
			

				//  Operator= :
				tree_iterator& operator=(const tree_iterator& rhs) {
					if (this != &rhs) {
						this->_node = rhs._node;
						this->_tree = rhs._tree;
					}
					return (*this);
				}
			
				//  -----------------DEREFERENCE OPERATOR-----------------
			
				//  Operator* :
				reference operator*(void) const { return (*this->_node->data); }
				
				//  Operator-> :
				pointer   operator->(void) const { return (this->_node->data); }

			
				//  ------------------INCREMENT OPERATOR------------------


				//  Operator++ -> post-incrementation :
				tree_iterator	&operator++(void) {
					Node *tmp = NULL;
					
					if (!this->_node) {
						if (!(this->_node = this->_tree->getRoot()))
							return (*this);
						else if (!this->_node) //  Check for an empty tree
							throw "mmmmkkk";
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
							tmp = this->_node->parent;
							while (tmp && this->_node == tmp->right) {
								this->_node = tmp;
								tmp = tmp->parent;
							}
							this->_node = tmp;
						}
					}
					return (*this);
				}

				//  Operator++ -> pre-incrementation :
				tree_iterator	operator++(int) {
					tree_iterator tmp(*this);
					++(*this);
					return (tmp);
				}
			
				//  ------------------DECREMENT OPERATOR------------------
				//  --------------FRIEND COMPARAISON OPERATOR-------------
			

				//  Operator-- -> post-incrementation :
				tree_iterator	&operator-- (void) {
					Node *tmp =  NULL;
					
					if (!this->_node) {
						if (!(_node = _tree->getRoot())) //  Check for an empty tree
							throw "mmmmkkk"; 
						while (this->_node->right) //  Move to smallest tree value
							this->_node = this->_node->right;
					}
					else
						if (this->_node->left) {
							this->_node = this->_node->left;
							while (this->_node->right)
								this->_node = this->_node->right;
						}
						else {
							tmp = this->_node->parent;
							while (tmp && this->_node == tmp->left) {
								this->_node = tmp;
								tmp = tmp->parent;
							}
							this->_node = tmp;
						}
					return (*this);
				}
				
				//  Operator-- -> pre-incrementation :
				tree_iterator	operator--(int) {
					tree_iterator tmp(*this);
					--(*this);
					return (tmp);
				}

				
				friend bool operator== (const tree_iterator& lhs, const tree_iterator& rhs) { return lhs.base() == rhs.base(); }
				friend bool operator!= (const tree_iterator& lhs, const tree_iterator& rhs) { return !operator==(lhs, rhs); }
		};
};

// namespace ft
// {

	
// 	template <typename iterator>
// 	class map_reverse_iterator
// 	{
// 	public:
// 		iterator _tree;

// 	public:
// 		map_reverse_iterator() : _tree(nullptr) {}
// 		template <class T1>
// 		map_reverse_iterator(const map_reverse_iterator<iterator> &it) : _tree(it.base()) {}
// 		explicit map_reverse_iterator(iterator node) : _tree(node) {}
// 		typedef typename iterator::value_type pair;

// 		iterator base() const
// 		{
// 			return _tree;
// 		}

// 		pair &operator*() const
// 		{
// 			return (*--base());
// 		}

// 		pair *operator->()
// 		{
// 			return &(operator*());
// 		}

// 		pair &get_pair()
// 		{
// 			return (_tree.get_pair());
// 		}

// 		map_reverse_iterator &operator++()
// 		{
// 			--_tree;
// 			return (*this);
// 		}

// 		map_reverse_iterator operator++(int)
// 		{
// 			map_reverse_iterator temp = *this;
// 			_tree--;
// 			return temp;
// 		}

// 		map_reverse_iterator &operator--()
// 		{
// 			++_tree;
// 			return (*this);
// 		}

// 		map_reverse_iterator operator--(int)
// 		{
// 			map_reverse_iterator temp = *this;
// 			_tree++;
// 			return temp;
// 		}

// 		bool operator!()
// 		{
// 			if (_tree == nullptr)
// 				return true;
// 			return false;
// 		}

// 		bool operator==(map_reverse_iterator const &rhs)
// 		{
// 			if (_tree == rhs._tree)
// 				return true;
// 			return false;
// 		}

// 		bool operator!=(map_reverse_iterator const &rhs)
// 		{
// 			if (_tree != rhs._tree)
// 				return true;
// 			return false;
// 		}

// 		bool empty() const
// 		{
// 			if (_tree)
// 				return true;
// 			return false;
// 		}
// 	};

// 	template <class pair, typename NodPtr>
// 	class MapIterator
// 	{
// 	public:
// 		NodPtr _tree;
// 		typedef pair value_type;

// 	public:
// 		MapIterator() : _tree(nullptr) {}
// 		template <class T1>
// 		MapIterator(const MapIterator<T1, NodPtr> &it) : _tree(it.base()) {}
// 		explicit MapIterator(NodPtr node) : _tree(node) {}
// 		NodPtr base() const
// 		{
// 			return this->_tree;
// 		}

// 		pair &operator*() const
// 		{
// 			return (_tree)->pair;
// 		}

// 		pair *operator->()
// 		{
// 			return &(_tree->pair);
// 		}

// 		pair &get_pair()
// 		{
// 			return (_tree->pair);
// 		}

// 		MapIterator &operator++()
// 		{
// 			_tree = get_next(_tree);
// 			return (*this);
// 		}

// 		MapIterator operator++(int)
// 		{
// 			MapIterator temp = *this;
// 			_tree = get_next(_tree);

// 			return temp;
// 		}

// 		MapIterator &operator--()
// 		{
// 			_tree = get_precedent(_tree);
// 			return (*this);
// 		}

// 		MapIterator operator--(int)
// 		{
// 			MapIterator temp = *this;
// 			_tree = get_precedent(_tree);

// 			return temp;
// 		}

// 		bool operator!()
// 		{
// 			if (_tree == nullptr)
// 				return true;
// 			return false;
// 		}

// 		bool operator==(MapIterator const &rhs)
// 		{
// 			if (_tree == rhs._tree)
// 				return true;
// 			return false;
// 		}

// 		bool operator!=(MapIterator const &rhs)
// 		{
// 			if (_tree != rhs._tree)
// 				return true;
// 			return false;
// 		}

// 		bool empty() const
// 		{
// 			if (_tree)
// 				return true;
// 			return false;
// 		}
// 	};

// };

#endif
