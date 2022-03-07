#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <memory> //  Allocator
# include <stdexcept> //  length_error
# include <cstring> // memmove 

//  ---------------------------VECTOR CONTAINER---------------------------
//    -> Class Template
//    Vectors are sequence containers representing arrays that can change
//    in size.
//  ----------------------------------------------------------------------

namespace ft
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
				typedef ft::random_access_iterator<T>				iterator;
				typedef ft::random_access_iterator<const T>			const_iterator;
				typedef ft::reverse_iterator<iterator>				reverse_iterator;
				typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;				
		
			private:
				allocator_type		_alloc;
				pointer 			_ptr, _start, _end;
				size_type			_size, _capacity;
			
			//  --------------------MEMBER FUNCTION----------------------
			

			//  ---------------------CONSTRUCTOR-------------------------
			
			public:
	
				//  Default constructor :
				explicit vector(const allocator_type& alloc = allocator_type())
					: _alloc(alloc), _ptr(NULL), _start(NULL), _end(NULL), _size(0), _capacity(0) {}

				//  Fill constructor:
				explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
					: _alloc(alloc), _ptr(NULL), _start(NULL), _end(NULL), _size(n), _capacity(n) {
					if (!(this->_ptr = this->_alloc.allocate(n)))
						throw std::bad_alloc();
					for (size_type idx = 0; idx < n; idx += 1)
						this->_alloc.construct(this->_ptr + idx, val);
					this->_start = this->_ptr;
					this->_end = this->_ptr + n - 1;
				}

				//  Range constructor:
				template<class InputIterator>
        			vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename enable_if<!is_integral<InputIterator>::value, bool>::type = false)
						: _alloc(alloc), _ptr(NULL), _start(NULL), _end(NULL), _size(0), _capacity(0) {
						difference_type	size = ft::distance<InputIterator>(first, last);	
						
						if (!(this->_ptr = this->_alloc.allocate(size)))
							throw std::bad_alloc();
						for (size_type idx = 0; first != last; idx += 1)
							this->_alloc.construct(this->_ptr + idx, *first++);
						this->_start = this->_ptr;
						this->_end = this->_ptr + (size - 1);
						this->_size = size;
						this->_capacity = size;
					}
				
				//  Copy constructor:
				vector(const vector& x) : _alloc(x._alloc), _ptr(NULL), _start(NULL), _end(NULL), _size(0), _capacity(0) { *this = x; }
			
			//  ---------------------DESTRUCTOR--------------------------

			public:
	
				~vector(void) {
					this->clear();
					this->_alloc.deallocate(this->_ptr, this->capacity());
				}

			//  ----------------------OPERATOR=--------------------------

			public :

				//  Operator=
				vector& operator=(const vector& x) {
					size_type 	idx = 0;
			
					if (this == &x)
						return (*this);
					this->clear();
					this->_alloc.deallocate(this->_ptr, this->capacity());
					if (!(this->_ptr = this->_alloc.allocate(x.capacity())))
						throw std::bad_alloc();
					this->_capacity = x.capacity();
					if (!x._ptr) {
						this->_ptr = NULL;
						this->_start = NULL;
						this->_end = NULL;
						this->_size = 0;
					}
					else if (x._ptr) {
						for (const_iterator it = x.begin(); it < x.end(); it += 1)
							this->_alloc.construct(this->_ptr + idx++, *it);
						this->_start = this->_ptr;
						this->_end = this->_ptr + idx - 1;
						this->_size = x.size();
					}
					return (*this);
				}
		
			//  ----------------------ITERATORS--------------------------

			public:

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

			
			//  ----------------------CAPACITY---------------------------

			public :

				//  Size :
				size_type size(void) const { return (this->_size); } 
				
				//  Max_size :
				size_type max_size() const { return (this->_alloc.max_size()); }
				
				//  Resize :
				void resize (size_type n, value_type val = value_type()) {
					pointer			new_ptr;
					allocator_type	new_alloc;
					size_type		size = this->size();

					if (n < 0) 
						return ;
					if (n > this->capacity()) {
						if (!(new_ptr = new_alloc.allocate(n)))
							throw std::bad_alloc();
						for (size_type idx = 0; idx < size; idx += 1)
							new_alloc.construct(new_ptr + idx, this->_ptr[idx]);
						this->clear();
						this->_alloc.deallocate(this->_ptr, this->capacity());
						this->_size = n;
						this->_capacity = n;
						this->_ptr = new_ptr;
						this->_start = this->_ptr;
						this->_end = this->_ptr + (this->size() - 1);
					}
					if (n > size) {
						for (size_type idx = size; idx < n; idx += 1)
							this->_alloc.construct(this->_ptr + idx, val);
						this->_size = n;
					}
					else if (n < size) {
						for (size_type idx = size - n; idx < size; idx += 1)
							this->_alloc.destroy(this->_start + idx);
						this->_size -= (size - n);
						this->_end = this->_ptr + (this->size() - 1);	
					}
				}

				//  Capacity :
				size_type capacity() const { return (this->_capacity); } 

				//  Empty() :
				bool empty() const {
					if (this->size() == 0)
						return (true);
					return (false);
				}

				//  Reserve() :
				void reserve (size_type n) {
					pointer			new_ptr;
					allocator_type	new_alloc;
					size_type		size = this->size();
		
					if (n > this->capacity()) {
						if (!(new_ptr = new_alloc.allocate(n)))
							throw std::bad_alloc();
						for (size_type idx = 0; idx < size; idx += 1)
							new_alloc.construct(new_ptr + idx, this->_ptr[idx]);
						this->clear();
						this->_alloc.deallocate(this->_ptr, this->capacity());
						this->_size = size;
						this->_capacity = n;
						this->_ptr = new_ptr;
						this->_start = this->_ptr;
						this->_end = this->_ptr + (this->size() - 1);
					}
					else if (n > this->max_size())
						throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
				}


			//  --------------------ELEMENT ACCESS-----------------------

			public:

				//  Operator[] :
				reference operator[](size_type n) { return (*(this->_ptr + n)); }

				const_reference operator[] (size_type n) const { return (*(this->_ptr + n)); }

				//  At :
				reference at(size_type n) {
					if (n >= this->size())
						throw std::out_of_range("vector");
					return ((*this)[n]);
				}

				const_reference at(size_type n) const {
					if (n >= this->size())
						throw std::out_of_range("vector");
					return ((*this)[n]);
				}

				//  Front :
				reference front(void) { return ((*this)[0]); }
				const_reference front(void) const { return ((*this)[0]); }

				//  Back :
				reference back(void) { return ((*this)[this->size() - 1]); }
				const_reference back() const { return ((*this)[this->size() - 1]); }


			//  -----------------------MODIFIERS-------------------------

			public:

				//  Assign - Range :
				template <class InputIterator> //  Range :
					void assign (InputIterator first, InputIterator last, typename enable_if<!is_integral<InputIterator>::value,bool>::type = false) {
						size_type 		capacity = this->capacity();
						difference_type new_dst = ft::distance<InputIterator>(first, last);

						this->clear();
						this->_capacity = capacity;
						this->_size = new_dst;
						if (static_cast<long long>(capacity) < static_cast<long long>(new_dst)) {
							if (!(this->_ptr = this->_alloc.allocate(new_dst)))
								throw std::bad_alloc();
							this->_capacity = new_dst;
						}
						for (size_type idx = 0; first != last; idx += 1)
							this->_alloc.construct(this->_ptr + idx, *first++);
						this->_start = this->_ptr;
						this->_end = this->_ptr + (new_dst - 1);
					}
				
				//  Assign - Fill :
				void assign (size_type n, const value_type& val) { //  Fill :
					pointer			new_ptr;
					allocator_type	new_alloc;

					this->clear();
					if (n > this->capacity()) {
						if (!(new_ptr = new_alloc.allocate(n)))
							throw std::bad_alloc();
						this->clear();
						this->_alloc.deallocate(this->_ptr, this->capacity());
						this->_capacity = n;
						this->_ptr = new_ptr;
						this->_start = this->_ptr;
					}
					for (size_type idx = 0; idx < n; idx += 1)
						this->_alloc.construct(this->_ptr + idx, val);
					this->_size += n;
					this->_end = this->_ptr + (this->size() - 1);
				}

				//  Push_back :
				void push_back (const value_type& val) {
					pointer			new_ptr;
					allocator_type	new_alloc;
					size_type		new_capacity = this->capacity(), capacity = this->capacity(), size = this->size();

					if ((size + 1) > new_capacity) {
						new_capacity *= 2;
						new_capacity = (new_capacity <= 0 ? 1 : new_capacity);
						while (size + 1 > new_capacity)
							new_capacity *= 2;
						if (!(new_ptr = new_alloc.allocate(new_capacity)))
							throw std::bad_alloc();
						for (size_type idx = 0; idx < size; idx += 1)
							new_alloc.construct(new_ptr + idx, this->_ptr[idx]);
						new_alloc.construct(new_ptr + size, val);
						this->clear();
						this->_alloc.deallocate(this->_ptr, capacity);
						this->_capacity = new_capacity;
						this->_ptr = new_ptr;
						this->_start = this->_ptr;
					}
					else
						this->_alloc.construct(this->_ptr + size, val);
					this->_end = this->_ptr + size;
					this->_size = size + 1;
				}
				
				//  Pop_back :
				void pop_back(void) {
					if (this->_end) {
						this->_alloc.destroy(this->_end);
						this->_size -= 1;
						this->_end = this->_ptr + (this->size() - 1);
					}
				}

				//  Insert - Single element :
				iterator insert(iterator position, const value_type& val) {
					pointer			new_ptr;
					allocator_type	new_alloc;
					size_type		new_size = this->size(), new_capacity = this->capacity();
					difference_type	new_dst = ft::distance(this->begin(), position);
				
					if (new_size >= new_capacity) {
						new_capacity *= 2;
						new_capacity = (new_capacity <= 0 ? 1 : new_capacity);
						while (new_size + 1 > new_capacity)
							new_capacity *= 2;
						if (!(new_ptr = new_alloc.allocate(new_capacity)))
							throw std::bad_alloc();
						for (size_type idx = 0; idx < new_size; idx += 1)
							new_alloc.construct(new_ptr + idx, this->_ptr[idx]);
						new_alloc.construct(new_ptr + new_size, val);
						this->clear();
						this->_alloc.deallocate(this->_ptr, new_capacity);
						this->_ptr = new_ptr;
						this->_size = new_size;
						this->_capacity = new_capacity;
						this->_start = this->_ptr;
						this->_end = this->_ptr + (this->size() - 1);
						
					}
					this->_alloc.construct(this->_ptr + this->size(), val);
					this->_size += 1;
					this->_end = this->_start + (this->size() - 1);
					for (iterator it = this->end() - 1; it != (this->begin() + new_dst - 1); it -= 1) {
						if ((it - 1) != (this->begin() - 1))
							*it = *(it - 1);
					}
					*(this->begin() + new_dst) = val;
					return (iterator(this->_start + new_dst));
				}

				//  Insert - Fill :
				void insert(iterator position, size_type n, const value_type& val) {
					for (size_type idx = 0; idx < n; idx += 1)
						position = this->insert(position, val);
				}

				//  Insert - Range :
				template <class InputIterator>
					void insert (iterator position, InputIterator first, InputIterator last, typename enable_if<!is_integral<InputIterator>::value,bool>::type = false) {
						vector<value_type> tmp;

						for (InputIterator it = first; it != last; it++) 
							tmp.push_back(*it);
						while (tmp.size() != 0) {
							position = this->insert(position, tmp[tmp.size() - 1]);
							tmp.pop_back();
						}
					}

				//  Erase - One element :
				iterator erase(iterator position) {
					difference_type	new_dst = ft::distance(this->begin(), position);
					
					std::memmove(this->_start + new_dst, this->_start + new_dst + 1, ((this->size() - new_dst - 1) * sizeof(value_type)));
					this->_alloc.destroy(this->_start + this->_size);
					this->_size -= 1;
					this->_end -= 1;
					return (iterator(this->_start + new_dst));
				}

				//  Erase - Multiple consecutive elements :
				iterator erase (iterator first, iterator last) {
					difference_type	diff = last.base() - first.base();

					std::memmove(first.base(), last.base(), ((this->size() - diff) * sizeof(value_type)));
					for (size_type idx = this->size() - diff; idx < this->size(); idx += 1)
						this->_alloc.destroy(this->_start + idx);
					this->_size -= diff;
					this->_end -= diff;
					return (last - diff);
				}

				//  Swap :
				void swap(vector& x) {
					allocator_type	tmp_alloc = this->_alloc;
					pointer			tmp_ptr = this->_ptr, tmp_start = this->_start, tmp_end = this->_end;
					size_type		tmp_size = this->size(), tmp_capacity = this->capacity();

					this->_alloc = x._alloc;
					this->_ptr = x._ptr;
					this->_start = x._start;
					this->_end = x._end;
					this->_size = x.size();
					this->_capacity = x.capacity();
					x._alloc = tmp_alloc;
					x._ptr = tmp_ptr;
					x._start = tmp_start;
					x._end = tmp_end;
					x._size = tmp_size;
					x._capacity = tmp_capacity;
				}

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

			public:
	
				//  Get_allocator :
				allocator_type get_allocator(void) const{
					return (this->_alloc);
				}

		};

	//  ---------------NON-MEMBER FUNCTIONS OVERLOADS---------------------

	//  ---------------------RATIONAL OPERATORS---------------------------

	template <class T, class Alloc> //  Operator==
		bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			if (lhs.size() == rhs.size())
				return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
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
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		}
	
	template <class T, class Alloc> //  Operator<=
		bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			if (lhs == rhs || lhs < rhs)
				return (true);
			return (false);  	
		}
	
	template <class T, class Alloc> //  Operator>
		bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			if (!(lhs < rhs) && lhs != rhs)
				return (true);
			return (false);
		}
	
	template <class T, class Alloc> //  Operator>=
		bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			if (lhs > rhs || lhs == rhs)
				return (true);
			return (false);
		}
	
	//  ---------------------------SWAP------------------------------
	
	template <class T, class Alloc> //  Swap
		void swap(vector<T, Alloc> &x, vector<T, Alloc> &y) { x.swap(y); }
}	

#endif