#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "random_access_iterator.hpp"

namespace ft
{
	template <class Iterator>
	class reverse_iterator
	{
		protected:
			Iterator current;
		public:
			typedef Iterator                                                        iterator_type;
			typedef	typename	ft::iterator_traits<Iterator>::iterator_category	iterator_category;
	        typedef	typename	ft::iterator_traits<Iterator>::value_type			value_type;
	        typedef	typename	ft::iterator_traits<Iterator>::difference_type		difference_type;
	        typedef	typename	ft::iterator_traits<Iterator>::pointer				pointer;
	        typedef	typename	ft::iterator_traits<Iterator>::reference			reference;

			reverse_iterator() : current() {}
            template <typename U>
			reverse_iterator(const reverse_iterator<U>& other) : current(other.base()) {}
			explicit reverse_iterator(iterator_type x) : current(x) {}
			virtual ~reverse_iterator() {}

			template< class U > 
			reverse_iterator& operator=(const reverse_iterator<U>& other ) { current = other.base(); return (*this);}
			iterator_type base() const { return (current);}
			
			/* reverse_iterator */
            reverse_iterator& operator++ ()
            {
                current--;
                return (*this);
            }
            reverse_iterator operator++ (int)
            {
                reverse_iterator tmp(*this);
                current--;
                return (tmp);
            }
            reverse_iterator& operator-- ()
            {
                current++;
                return (*this);
            }
            reverse_iterator operator-- (int)
            {
                reverse_iterator tmp(*this);
                current++;
                return (tmp);
            }
            reverse_iterator operator+ (difference_type n) const
            {
                reverse_iterator tmp(*this);
                tmp.current -= n;
                return (tmp);
            }
            reverse_iterator& operator+= (difference_type n)
            {
                current -= n;
                return (*this);
            }
            reverse_iterator operator- (difference_type n) const
            {
                reverse_iterator tmp(*this);
                tmp.current += n;
                return (tmp);
            }
            reverse_iterator& operator-= (difference_type n)
            {
                current += n;
                return (*this);
            }
            difference_type		operator-(reverse_iterator	other)		{ return (other.current - current); }
            reference operator[](int n) {return (*(current - n - 1));} //지정된 상대 위치의 요소에 대한 참조를 반환
            const reference operator[](int n) const {return (*(current - n - 1));}
			reference operator*() { iterator_type tmp = current; return *(--tmp); }
			const reference operator*() const { iterator_type tmp = current; return *(--tmp); }
			pointer	operator->() const { iterator_type tmp = current; return &(*(--tmp)); }

	};
template <typename iter1, typename iter2>
	bool operator ==	(const reverse_iterator<iter1>& lhs, const reverse_iterator<iter2>& rhs) { return (lhs.base() == rhs.base()); }
template <typename iter1, typename iter2>
	bool operator !=	(const reverse_iterator<iter1>& lhs, const reverse_iterator<iter2>& rhs) { return !(lhs == rhs); }
template <typename iter1, typename iter2>
	bool operator <		(const reverse_iterator<iter1>& lhs, const reverse_iterator<iter2>& rhs) { return (lhs.base() > rhs.base()); }
template <typename iter1, typename iter2>
	bool operator <=	(const reverse_iterator<iter1>& lhs, const reverse_iterator<iter2>& rhs) { return !(lhs > rhs); }
template <typename iter1, typename iter2>
	bool operator >		(const reverse_iterator<iter1>& lhs, const reverse_iterator<iter2>& rhs) { return (rhs < lhs); }
template <typename iter1, typename iter2>
	bool operator >=	(const reverse_iterator<iter1>& lhs, const reverse_iterator<iter2>& rhs) { return !(lhs < rhs); }

template <typename iter>
	reverse_iterator<iter> operator +(typename reverse_iterator<iter>::difference_type n, const reverse_iterator<iter>& rev_it) { return (rev_it + n); }
template <typename iter>
	typename reverse_iterator<iter>::difference_type
	operator -	(const reverse_iterator<iter>& lhs, const reverse_iterator<iter>& rhs) { return (rhs - lhs); }
}
#endif