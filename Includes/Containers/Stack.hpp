#ifndef STACK_HPP
# define STACK_HPP
# include "Vector.hpp" // Default container

//  ---------------------------STACK CONTAINER----------------------------
// |  -> Class Template								                      |
// |  Stacks are a type of container adaptor, specifically designed to    |
// |  operate in a LIFO context (last-in first-out).                      |
// |  Thus, elements are inserted and extracted only from one end of the  |
// |  container.														  |
//  ----------------------------------------------------------------------

namespace ft
{
	template <class T, class Container = ft::vector<T> >
		class stack {

			//  ---------------------MEMBER TYPES------------------------
			
			public:
				typedef	T			value_type;
				typedef Container	container_type;
				typedef size_t		size_type;

			private:
				container_type	_container;
			
			//  --------------------MEMBER FUNCTION----------------------

			//  ---------------------CONSTRUCTOR-------------------------

			public:
				explicit stack(const container_type& ctnr = container_type()) : _container(ctnr) {}
			
			//  -----------------------OTHERS----------------------------

			public:

				//  Empty :
				bool empty(void) const { return (this->_container.empty()); }

				//  Size :
				size_type size(void) const { return (this->_container.size()); }

				//  Top & Top Const:
				value_type& top(void) { return (this->_container.back()); }
				const value_type& top() const { return (this->_container.back()); }

				//  Push :
				void push (const value_type& val) { this->_container.push_back(val); }

				//  Pop :
				void pop(void) { this->_container.pop_back(); }
			
			//  -------------RATIONAL OPERATORS FRIENDS------------------
			// |  These rational operators member function are defined   |
			// |  as "friends" in order for the actual rational          |
			// |  operators (non-member functions) to access the private |
			// |  member type _container.                    			 |
			//  ---------------------------------------------------------

			public:

				template <class Lhs, class Rhs> //  Operator== friend
					friend bool operator== (const stack<Lhs, Rhs>& lhs, const stack<Lhs, Rhs>& rhs);
			
				template <class Lhs, class Rhs> //  Operator!= friend
					friend bool operator!= (const stack<Lhs, Rhs>& lhs, const stack<Lhs, Rhs>& rhs);

				template <class Lhs, class Rhs> //  Operator< friend
					friend bool operator<  (const stack<Lhs, Rhs>& lhs, const stack<Lhs, Rhs>& rhs);

				template <class Lhs, class Rhs> //  Operator<= friend
					friend bool operator<= (const stack<Lhs, Rhs>& lhs, const stack<Lhs, Rhs>& rhs);
				
				template <class Lhs, class Rhs> //  Operator> friend
					friend bool operator>  (const stack<Lhs, Rhs>& lhs, const stack<Lhs, Rhs>& rhs);

				template <class Lhs, class Rhs> //  Operator>= friend
					friend bool operator>= (const stack<Lhs, Rhs>& lhs, const stack<Lhs, Rhs>& rhs);

		};
	
	//  -------------NON-MEMBER FUNCTIONS OVERLOADS------------------

	//  -------------------RATIONAL OPERATORS------------------------

	template <class T, class Container> //  Operator==
		bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return (lhs._container == rhs._container);
		}
	
	template <class T, class Container> //  Operator!=
		bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return (lhs._container != rhs._container);
		}

    template <class T, class Container> //  Operator<
		bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return (lhs._container < rhs._container);
		}

    template <class T, class Container> //  Operator<=
		bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return (lhs._container <= rhs._container);
		}

    template <class T, class Container> //  Operator>
		bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return (lhs._container > rhs._container);
		}

    template <class T, class Container> //  Operator>=
		bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return (lhs._container >= rhs._container);
		}
}

#endif