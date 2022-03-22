/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 14:36:37 by sel-fadi          #+#    #+#             */
/*   Updated: 2021/12/24 13:53:40 by sel-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft {
	
	template <typename T>
	class VectorIterator
	{
		public:
			typedef T value_type;
			typedef VectorIterator<const value_type> const_iterator;
			typedef value_type* pointer;
			typedef std::random_access_iterator_tag	iterator_category;
			typedef value_type const * const_pointer;
			typedef value_type& reference;
			typedef value_type const & const_reference;
			typedef std::ptrdiff_t difference_type;
		protected:
			pointer p;
		public:
			VectorIterator() : p(0) {};
			VectorIterator(pointer ptr) : p(ptr) {};
			VectorIterator(VectorIterator const &ptr) : p(ptr.p) {};
			virtual ~VectorIterator() {};
			VectorIterator &operator=(VectorIterator const &obj) {this->p = obj.p; return (*this);}

			VectorIterator &operator+=(int value)
			{
				this->p += value;
				return (*this);
			}

			VectorIterator &operator-=(int value)
			{
				this->p -= value;
				return (*this);
			}

			VectorIterator operator+(int value) const
			{
				VectorIterator it(*this);
				return (it += value);
			}

			VectorIterator operator-(int value) const
			{
				VectorIterator it(*this);
				return (it -= value);
			}

			VectorIterator operator++()
			{
				p++;
				return *this;
			}

			VectorIterator operator++(int)
			{
				VectorIterator it(*this);
				++(*this);
				return it;
			}

			VectorIterator operator--()
			{
				p--;
				return *this;
			}

			VectorIterator operator--(int)
			{
				VectorIterator it(*this);
				--(*this);
				return it;
			}

			reference operator[](int index)
			{
				return *(p + index);
			}

			const_reference operator[](int index) const
			{
				return *(p + index);
			}

			pointer operator->()
			{
				return p;
			}

			const_pointer operator->() const
			{
				return p;
			}

			reference operator*()
			{
				return *p;
			}
			
			const_reference operator*() const
			{
				return *p;
			}

			operator const_iterator() const{
				return const_iterator(this->p);
			}
			
			difference_type operator-(VectorIterator const &obj) const
			{
				return (this->p - obj.p);
			}

			bool operator==(VectorIterator const &obj) const {
				return (this->p == obj.p);
			}

			bool operator!=(VectorIterator const &obj) const {
				return (this->p != obj.p);
			}

			bool operator<(VectorIterator const &obj) const {
				return (this->p < obj.p);
			}

			bool operator<=(VectorIterator const &obj) const {
				return (this->p <= obj.p);
			}

			bool operator>(VectorIterator const &obj) const {
				return (this->p > obj.p);
			}

			
			bool operator>=(VectorIterator const &obj) const {
				return (this->p >= obj.p);
			}

			pointer getP() const
			{
				return this->p;
			}
	};

	template < class T >
		bool operator== (const VectorIterator<T>& lhs, const VectorIterator<T>& rhs) { return lhs.getData() == rhs.getData(); }
	template < class T >
		bool operator!= (const VectorIterator<T>& lhs, const VectorIterator<T>& rhs) { return !operator==(lhs, rhs);}
	template < class T >
		bool operator<  (const VectorIterator<T>& lhs, const VectorIterator<T>& rhs) { return rhs.getData() < lhs.getData(); }
	template < class T >
		bool operator>  (const VectorIterator<T>& lhs, const VectorIterator<T>& rhs) { return !operator<=(lhs, rhs); }
	template < class T >
		bool operator<=  (const VectorIterator<T>& lhs, const VectorIterator<T>& rhs) { return !operator>(rhs, lhs); }
	template < class T >
		bool operator>=  (const VectorIterator<T>& lhs, const VectorIterator<T>& rhs) { return !operator<(lhs, rhs); }

	template <class T>
		VectorIterator<T> operator+ ( typename VectorIterator<T>::difference_type n, const VectorIterator<T>& rev_it)
		{ return VectorIterator<T>(rev_it.getP() + n);}
	
}