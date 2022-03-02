#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include "iterator.hpp"

namespace ft
{
    template <class T>
    class random_access_iterator : public iterator<random_access_iterator_tag, T>
    {
        public: //다른 클래스에서도 이 클래스 변수 받아서 typedef로 별칭을 정하기 때문에 public으로 넣음
        
            typedef	typename ft::iterator<random_access_iterator_tag, T>::iterator_category	iterator_category;
	        typedef	typename ft::iterator<random_access_iterator_tag, T>::pointer			pointer;
	        typedef	typename ft::iterator<random_access_iterator_tag, T>::reference			reference;
	        typedef	typename ft::iterator<random_access_iterator_tag, T>::value_type		value_type;
	        typedef	typename ft::iterator<random_access_iterator_tag, T>::difference_type	difference_type;

            random_access_iterator() : ptr(0) {}
            random_access_iterator(const random_access_iterator& src) : ptr(src.ptr) {}
            random_access_iterator(pointer _ptr) : ptr(_ptr) {}
            virtual ~random_access_iterator() {}

            pointer		base() const { return (ptr); } //왜 pointer형으로 리턴해야하는지 random말고

            random_access_iterator &operator= (const random_access_iterator<const value_type> &src)
            {
                if (this != &src)
                    this->ptr = src.ptr;
                return (*this);
            }
            random_access_iterator& operator++ () // Prefix increment operator.
            {
                this->ptr += 1;
                return (*this);
            }
            random_access_iterator operator++ (int) // Postfix increment operator.
            {
                random_access_iterator tmp(*this);
                this->ptr += 1;
                return (tmp);
            }
            random_access_iterator& operator-- ()
            {
                this->ptr -= 1;
                return (*this);
            }
            random_access_iterator operator-- (int)
            {
                random_access_iterator tmp(*this);
                this->ptr -= 1;
                return (tmp);
            }
            random_access_iterator operator+ (difference_type n)
            {
                random_access_iterator tmp(*this);
                tmp.ptr += n;
                return (tmp);
            }
            random_access_iterator& operator+= (difference_type n)
            {
                ptr += n;
                return (*this);
            }
            random_access_iterator operator- (difference_type n)
            {
                random_access_iterator tmp(*this);
                tmp.ptr -= n;
                return (tmp);
            }
            random_access_iterator& operator-= (difference_type n)
            {
                ptr -= n;
                return (*this);
            }
            bool operator== (const random_access_iterator<const value_type>& rhs) const //const 정리
            {
                if (this->ptr == rhs.base())
                    return (true);
                return (false);
            }
            bool operator!= (const random_access_iterator<const value_type>& rhs) const
            {
                if (this->ptr != rhs.base())
                    return (true);
                return (false);
            }
            bool operator< (const random_access_iterator<const value_type>& rhs) const
            {
                if (this->ptr < rhs.base())
                    return (true);
                return (false);
            }
            bool operator> (const random_access_iterator<const value_type>& rhs) const
            {
                if (this->ptr > rhs.base())
                    return (true);
                return (false);
            }
            bool operator<= (const random_access_iterator<const value_type>& rhs) const
            {
                if (this->ptr <= rhs.base())
                    return (true);
                return (false);
            }
            bool operator>= (const random_access_iterator<const value_type>& rhs) const
            {
                if (this->ptr >= rhs.base())
                    return (true);
                return (false);
            }
            reference operator*() {return (*ptr);}
            const reference operator*() const {return (*ptr);}
            pointer operator->() {return (ptr);}
            reference operator[](int n) {return (*(ptr + n));}
            const reference operator[](int n) const {return (*(ptr + n));}

	operator random_access_iterator<const T> () const { return (random_access_iterator<const T>(this->ptr)); }
    
        private:

            pointer     ptr;
    };
    template<typename T>
	random_access_iterator<T>
		operator +	(typename random_access_iterator<T>::difference_type n, const random_access_iterator<T>& iterator)
		{ random_access_iterator<T> itr = iterator; return (itr + n); } //외부 함수로 만든 이유? : 이걸 안에 만들면 원래 lhs변수 포함 세개의 인자를 받으려고 함

    template<typename iter>
	typename ft::random_access_iterator<iter>::difference_type
		operator -	(const random_access_iterator<iter>& lhs, const random_access_iterator<iter>& rhs) { return (lhs.base() - rhs.base()); }
template<typename iter1, typename iter2>
	typename ft::random_access_iterator<iter1>::difference_type
		operator -	(const random_access_iterator<iter1>& lhs, const random_access_iterator<iter2>& rhs) { return (lhs.base() - rhs.base()); }
}


#endif