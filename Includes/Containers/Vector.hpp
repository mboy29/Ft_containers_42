#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <memory> //  Allocator

//  ---------------------------VECTOR CONTAINER---------------------------
// |  -> Class Template								                      |
// |  Vectors are sequence containers representing arrays that can change |
// |  in size.															  |
//  ----------------------------------------------------------------------

namespace Ft
{

	template < class T, class Alloc = std::allocator<T> >
		class vector {
			
			//  ---------------------MEMBER TYPES------------------------
			public:
				typedef T											value_type;
				typedef Alloc										allocator_type;
				typedef typename allocator_type::reference			reference;
				typedef typename allocator_type::const_reference	const_reference;
				typedef typename allocator_type::pointer			pointer;
				typedef typename allocator_type::const_pointer		const_pointer;
				typedef typename allocator_type::difference_type	difference_type;
				typedef typename allocator_type::size_type 			size_type;
				typedef Ft::random_access_iterator<T>				iterator;
				typedef Ft::random_access_iterator<const T>			const_iterator;
				typedef Ft::reverse_iterator<T>						reverse_iterator;
				typedef Ft::reverse_iterator<const T>				const_reverse_iterator;				
		
			private:
				allocator_type		_alloc;
				pointer 			_ptr, _start, _end;
				size_type			_size, _capacity;
			
			//  --------------------MEMBER FUNCTION----------------------
			//  ---------------------CONSTRUCTOR-------------------------

			public:
				
				//  Default constructor :
				explicit vector(const allocator_type& alloc = allocator_type()) {
					this->_alloc = alloc;
					this->_ptr = NULL;
					this->_start = NULL;
					this->_end = NULL;
					this->_size = 0;
					this->_capacity = 0;
				}

				//  Fill constructor:
				explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) {
					this->_alloc = alloc;
					if (!(this->_ptr = this->_alloc.allocate(n)))
						throw std::bad_alloc();
					for (size_type idx = 0; idx < n; idx += 1)
						this->_alloc.construct(this->_ptr + idx, val);
					this->_start = this->_ptr;
					this->_end = this->_ptr + n - 1;
					this->_size = n;
					this->_capacity = n;
				}

				//  Range constructor:
				template<class InputIterator>
        			vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename enable_if<!is_integral<InputIterator>::value, bool>::type = false) {
						difference_type	n = Ft::distance<InputIterator>(first, last);	
						
						this->_alloc = alloc;
						if (!(this->_ptr = this->_alloc.allocate(n)))
							throw std::bad_alloc();
						for (size_type idx = 0; first != last; idx += 1)
							this->_alloc.construct(this->_ptr + idx, *first++);
						this->_start = this->_ptr;
						this->_end = this->_ptr + (n - 1);
						this->_size = n;
						this->_capacity = n;
					}
				
				//  Copy constructor:
				vector(const vector& x) {
					this->_alloc = x._alloc;
					this->_ptr = NULL;
					this->_start = NULL;
					this->_end = NULL;
					this->_size = 0;
					this->_capacity = 0;
					*this = x;
				}
			
			//  ---------------------DESTRUCTOR--------------------------

			public:
				~vector(void) {
					this->clear();
					this->_alloc.deallocate(this->_ptr, this->capacity());
				}

			//  ----------------------OPERATOR=--------------------------

			vector& operator= (const vector& x) {
				size_type 	idx = 0;
		
				if (this != &x) {
					this->clear();
					this->_alloc.deallocate(this->_ptr, this->capacity());
					if (!(this->_ptr = this->_alloc.allocate(x.capacity())))
						throw std::bad_alloc();
					this->_capacity = x.capacity();
					if (x._ptr == NULL) {
						this->_ptr = NULL;
						this->_start = NULL;
						this->_end = NULL;
						this->_size = 0;
					}
					else if (x._ptr != NULL) {
						for (const_iterator it = x.begin(); it < x.end(); it += 1)
							this->_alloc.construct(this->_ptr + idx++, *it);
						this->_start = this->_ptr;
						this->_end = this->_ptr + idx - 1;
						this->_size = x.size();
					}
				}
				return (*this);

			}
		
			//  ----------------------ITERATORS--------------------------

			//  Begin :
			iterator begin() { return (iterator(this->_start)); }
			const_iterator begin() const { return (const_iterator(this->_start)); }

			//  End :
			iterator end() { return (iterator(this->_end + 1)); }
			const_iterator end() const { return (const_iterator(this->_end + 1)); }

			//  Reverse begin :
			reverse_iterator rbegin() { return (reverse_iterator(this->end())); }
			const_reverse_iterator rbegin() const { return (const_reverse_iterator(this->end())); }

			//  Reverse end :
			reverse_iterator rend() { return (reverse_iterator(this->begin())); }
			const_reverse_iterator rend() const { return (const_reverse_iterator(this->begin())); }

			//  Const begin :
			const_iterator cbegin() const { return (const_iterator(this->begin())); }

			//  Const end :
			const_iterator cend() const { return (const_iterator(this->end())); }

			//  Const reverse begin :
			const_reverse_iterator crbegin() const { return (const_reverse_iterator(this->rbegin())); }

			//  Const reverse end :
			const_reverse_iterator crend() const { return (const_reverse_iterator(this->rend())); }


			
			//  ----------------------CAPACITY---------------------------

			size_type size(void) const { return (this->_size); } //  Size()
			
			size_type max_size() const { return (this->_alloc.max_size()); } //  Max_size()

			//void resize (size_type n, value_type val = value_type());

			size_type capacity() const { return (this->_capacity); } //  Capacity();

			bool empty() const { //  Empty()
				if (this->size() == 0)
					return (true);
				return (false);
			}

			// void reserve (size_type n);
			// void shrink_to_fit();


			//  --------------------ELEMENT ACCESS-----------------------


			//  -----------------------MODIFIERS-------------------------

			//  Clear :
			void clear(void) {
				size_type	size = this->size();
				
				if (!this->empty()) {
					for (size_type idx = 0; idx < size; idx += 1)
						this->_alloc.destroy(this->_ptr + idx);
					this->_start = this->_ptr;
					this->_end = this->_ptr - 1;
					this->_size = 0;
					this->_capacity = 0;
				}

			}
			//  ----------------------ALLOCATOR--------------------------
		
		};

		
		//  -------------NON-MEMBER FUNCTIONS OVERLOADS------------------

		//  -------------------RATIONAL OPERATORS------------------------

		template <class T, class Alloc> //  Operator==
  			bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
				if (lhs.size() == rhs.size())
					return (Ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
				return (false);
			}
		
		template <class T, class Alloc> //  Operator!=
  			bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
				if (lhs == rhs)
					return (false);
				return (true);	  
			}
		
		template <class T, class Alloc> //  Operator<
  			bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
				return (Ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
			}
		
		template <class T, class Alloc> //  Operator<=
  			bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
				if (lhs == rhs || lhs < rhs)
					return (true);
				return (false);  	
			}
		
		template <class T, class Alloc> //  Operator>
 			bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
				if (lhs <= rhs)
					return (false);
				return (true);
			}
		template <class T, class Alloc> //  Operator>=
  			bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
				if (lhs > rhs || lhs == rhs)
				  	return (true);
				return (false);
			}
		
		//  ------------------TEMPLATE SPECIALIZATION--------------------
}

#endif