#ifndef	TREE_HPP
# define TREE_HPP
# include "../Iterators/Reverse_iterator.hpp" //  Reverse iterator

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


				
		};
};

#endif