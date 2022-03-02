#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory> //allocator
# include "utils.hpp"
# include "random_access_iterator.hpp"
# include "reverse_iterator.hpp"

namespace ft
{
	template<typename T, typename Allocator = std::allocator<T> >
	class vector
	{
		public:
			typedef	T														value_type;
			typedef	Allocator												allocator_type;
			typedef	typename allocator_type::reference						reference;
			typedef	typename allocator_type::const_reference				const_reference;
			typedef	typename allocator_type::pointer						pointer;
			typedef	typename allocator_type::const_pointer					const_pointer;
			typedef	typename allocator_type::size_type						size_type;
			typedef	ft::random_access_iterator<value_type>					iterator;
			typedef	ft::random_access_iterator<const value_type>			const_iterator;
			typedef	ft::reverse_iterator<iterator>							reverse_iterator;
			typedef	ft::reverse_iterator<const_iterator>					const_reverse_iterator;
			typedef	typename ft::iterator_traits<iterator>::difference_type	difference_type;

		protected:
			allocator_type		_alloc;
			pointer				_begin;
			pointer				_end;
			pointer				_end_capa;

		public:
			// (1) empty container constructor (default constructor)
			explicit vector( const allocator_type& alloc = allocator_type())
				: _alloc(alloc), _begin(0), _end(0), _end_capa(0)
			{}
			// (2) fill constructor
			explicit vector( size_type count, const T& value = T(), const allocator_type& alloc = allocator_type())
				: _alloc(alloc), _begin(0), _end(0), _end_capa(0)
			{
				_begin = _alloc.allocate(count);
				_end_capa = _begin + count;
				_end = _begin;
				while (count--)
				{
					_alloc.construct(_end, value);
					_end++;
				}
			}
			// (3) range constructor
			template< class InputIterator >
			vector (InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
				: _alloc(alloc), _begin(0), _end(0), _end_capa(0)
			{
				insert(_begin, first, last);
			}
			// (4) copy constructor
			vector( const vector& other )
				: _alloc(other._alloc), _begin(0), _end(0), _end_capa(0)
			{
				insert(_begin, other.begin(), other.end());
			}
			~vector()
			{
				this->clear();
				_alloc.deallocate(_begin, this->capacity());
			}

			vector& operator= (const vector& vec)
			{
				if(this == &vec)
					return (*this);
				this->clear();
				insert(_begin, vec.begin(), vec.end());
				return (*this);
			}

			//Iterators
			iterator begin() { return (_begin); }
			const_iterator begin() const { return (_begin); }
			iterator end() { return (_end); }
			const_iterator end() const { return (_end); }
			reverse_iterator rbegin() { return (reverse_iterator(_end)); }
			const_reverse_iterator rbegin() const { return (reverse_iterator(_end)); }
			reverse_iterator rend() { return (reverse_iterator(_begin)); }
			const_reverse_iterator rend() const { return (reverse_iterator(_begin)); }

			//Capacity
			size_type size() const { return (_end - _begin); }
			size_type max_size() const { return (_alloc.max_size()); }
			void resize (size_type n, value_type val = value_type()) 
			{
				size_type	range = ft::distance(_begin, _end);
				size_t size = n - range;
				if (capacity() < n)
				{
					if(n < capacity() * 2)
						reserve(capacity() * 2);
					else
						reserve(n);
					for (size_t i = 0; i < size; i++)
						_alloc.construct(_end++, val);
				}
				else if (n < range)
				{
					_end = _begin + n;
					_end_capa = _end;
				}
			}
			size_type capacity() const { return (_end_capa - _begin); }
			bool empty() const { return (_end == _begin); }
			void reserve (size_type n)
			{
				if (this->capacity() < n)
				{
					pointer prev = _begin;
					pointer prev_end = _end;
					size_type capa = capacity();
					_begin = _alloc.allocate(n);
					_end_capa = _begin + n;
					_end = _begin;
					for ( ; prev != prev_end; prev++)
					{
						_alloc.construct(_end, *prev);
						_alloc.destroy(prev);
						_end++;
					}
					_alloc.deallocate(prev_end - size(), capa);
				}
			}
			
			//Element access
			reference operator[] (size_type n) { return (*(_begin + n)); }
			const_reference operator[] (size_type n) const { return (*(_begin + n)); }
			reference at (size_type n)
			{
				if (n >= this->size())
					throw std::out_of_range("vector::at");
				return ((*this)[n]);
			}
			const_reference		at (size_type n) const
			{
				if (n >= this->size())
					throw std::out_of_range("vector::at");
				return ((*this)[n]);
			}
			reference		front() { return (*(_begin)); }
			const_reference	front() const { return (*(_begin)); }
			reference		back() { return (*(_end - 1)); }
			const_reference	back() const { return (*(_end - 1)); }

			//Modifier
			template <class InputIterator>
			void assign (InputIterator first, InputIterator last, // range version
				typename ft::enable_if<!is_integral<InputIterator>::value>::type* = 0)
			{
				size_t capa = this->capacity();
				size_type	range = ft::distance(first, last);
				this->clear();
				_alloc.deallocate(_begin, capacity());
				if (capa < range)
				{
					_begin = _alloc.allocate(range);
					_end_capa = _begin + range;
				}
				else
				{
					_begin = _alloc.allocate(capa);
					_end_capa = _begin + capa;
				}
				for (size_t i = 0; i < range; i++)
					_alloc.construct(_begin + i, *(&*first++));
				_end = _begin + range;
			}
			void assign (size_type n, const value_type& val) // fill version
			{
				size_t capa = this->capacity();
				this->clear();
				_alloc.deallocate(_begin, capa);
				if (capa < n)
				{
					_begin = _alloc.allocate(n);
					_end_capa = _begin + n;
				}
				else
				{
					_begin = _alloc.allocate(capa);
					_end_capa = _begin + capa;
				}
				for (size_t i = 0; i < n; i++)
					_alloc.construct(_begin + i, val);
				_end = _begin + n;
			}
			void push_back (const value_type& val)
			{
				if (_end == _end_capa)
				{
					if (size() == 0)
						reserve(1);
					else
						reserve(size() * 2);
				}
				_alloc.construct(_end++, val);
			}
			void pop_back()
			{
				if (!empty())
					_alloc.destroy(_end - 1);
				_end--;
			}
			// single element
			iterator insert (iterator position, const value_type& val)
			{

				size_type	pos = &(*position) - _begin;
				insert(position, 1, val);
				// return (iterator(position)); 왜 이렇게는 안될까..? 궁금 아 insert하면서 begin 주소가 바뀌기 때문인듯!!!!
				return (iterator(_begin + pos));
			}
			// fill
    		void insert (iterator position, size_type n, const value_type& val)
			{
				pointer n_end = _end;
				pointer n_begin = _begin;
				size_t capa = capacity();
				size_t size = _end - _begin;
				
				if(capacity() * 2 < size + n)
				{
					n_begin = _alloc.allocate(size + n);
					_end_capa = n_begin + size + n;
					n_end = n_begin;
				}
				else
				{
					n_begin = _alloc.allocate(capacity() * 2);
					_end_capa = n_begin + capacity() * 2;
					n_end = n_begin;
				}
				for (int i = 0; _begin + i < &*position; i++)
					_alloc.construct(&*n_end++, *(_begin + i)); //position 전까지 복사
				for (size_t i = 0; i < n; i++)
					_alloc.construct(&*n_end++, val);
				for (int i = 0; &*position + i < _end; i++)
					_alloc.construct(&*n_end++, *(position + i));
				for (int i = 0; _begin + i < _end; i++)
					_alloc.destroy(_begin + i);
				_alloc.deallocate(_begin, capa);
				_begin = n_begin;
				_end = n_end;
			}
			// range
			template <class InputIterator>
    		void insert (iterator position, InputIterator first, InputIterator last,
				typename ft::enable_if<!is_integral<InputIterator>::value>::type* = 0)
			{
				pointer n_end = _end;
				pointer n_begin = _begin;
				size_t capa = capacity();
				size_t size = _end - _begin;
				size_type	n_size = ft::distance(first, last);
				//reserve는 새로운게 만들어지는게 아닌데...!!
				if(capa * 2 < size + n_size)
				{
					n_begin = _alloc.allocate(size + n_size);
					_end_capa = n_begin + size + n_size;
					n_end = n_begin;
				}
				else
				{
					n_begin = _alloc.allocate(capa * 2);
					_end_capa = n_begin + capa * 2;
					n_end = n_begin;
				}
				for (int i = 0; _begin + i < &*position; i++)
					_alloc.construct(&*n_end++, *(_begin + i));
				for (; &*first != &*last; first++)
					_alloc.construct(&*n_end++, *(&*first));
				for (int i = 0; &*position + i < _end; i++)
					_alloc.construct(&*n_end++, *(position + i));
				for (int i = 0; _begin + i < _end; i++)
					_alloc.destroy(_begin + i);
				_alloc.deallocate(_begin, capa);
				_begin = n_begin;
				_end = n_end;
			}

			iterator erase (iterator position)
			{
				return(erase(position, position + 1));
			}
			iterator erase (iterator first, iterator last)
			{
				for (int i = 0; first + i != last; i++)
					_alloc.destroy(&*first);
				for (int i = 0; last + i != _end; i++)
				{
					_alloc.construct(&*first + i, *(last + i));
					_alloc.destroy(&*last + i);
				}
				_end -= &*last - &*first;
				return (first);
			}
			void swap (vector& x)
			{
				pointer tmp = x._begin;
				pointer tmp_end = x._end;
				pointer tmp_capa = x._end_capa;
				allocator_type tmp_alloc = x._alloc;

				x._begin = _begin;
				x._end = _end;
				x._end_capa = _end_capa;
				x._alloc = _alloc;
				_begin = tmp;
				_end = tmp_end;
				_end_capa = tmp_capa;
				_alloc = tmp_alloc;
			}
			void clear()
			{
				for (int i = 0; _begin + i < _end; i++)
					_alloc.destroy(_begin + i);
				_end = _begin;
			}

			//Allocator
			allocator_type get_allocator() const
			{
				return (allocator_type());
			}
	};
	//non-member function
	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) //equal을 사용해봐야겠다
	{
		if (lhs.size() != rhs.size())
			return false;
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <class T, class Alloc>
		bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return !(lhs == rhs); }
	template <class T, class Alloc>
		bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return ft::lexicographical_compare(lhs.begin(), lhs.end(),rhs.begin(), rhs.end());
		}
	template <class T, class Alloc>
		bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return !(rhs < lhs); }
	template <class T, class Alloc>
		bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (rhs < lhs); }
	template <class T, class Alloc>
		bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return !(lhs < rhs); }
	//== 과 < 를 equal과 lexicographical_compare로 구현하여 나머지도 ==나 <를 사용한다
	template <class T, class Alloc>
		void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
		{
			x.swap(y);
		}
}


#endif