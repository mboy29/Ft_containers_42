/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 00:27:49 by mcadmin           #+#    #+#             */
/*   Updated: 2022/02/01 16:37:41 by sel-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../vector/vector.hpp"
namespace ft{

	template <class T, class Container = ft::Vector<T> >
	class Stack
	{
		public:
			typedef				Container					container_type;
			typedef				T							value_type;
			typedef	typename	Container::size_type		size_type;
			typedef	typename	Container::reference		reference;
			typedef	typename	Container::const_reference	const_reference;

			explicit Stack ( const container_type& ctnr = container_type()) : _container(ctnr) {}

			Stack ( const Stack &other ) { operator=(other); }

			~Stack() {}
			
			Stack &operator= ( const Stack& other )
			{
				if (this != &other)
					this->_container = other._container;
				return *this;
			}

			bool	empty() const {
				return (this->_container.empty());
			}

			size_type	size() const {
				return (this->_container.size());
			}

			value_type& top() {
				return (this->_container.back());
			}
			const value_type& top() const {
				return (this->_container.back());
			}

			void	push(const value_type& val){
				this->_container.push_back(val);
			}

			void	pop(){
				this->_container.pop_back();
			}

			template <class U, class Ct>
			friend	bool	operator== (const Stack< U, Ct>& lhs, const Stack< U, Ct>& rhs){
				return (lhs._container == rhs._container); 
			}

			template <class U, class Ct>
			friend	bool	operator!= (const Stack< U, Ct>& lhs, const Stack< U, Ct>& rhs){
				return (lhs._container != rhs._container); 
			}

			template <class U, class Ct>
			friend	bool	operator< (const Stack< U, Ct>& lhs, const Stack< U, Ct>& rhs){
				return (lhs._container < rhs._container); 
			}

			template <class U, class Ct>
			friend	bool	operator<= (const Stack< U, Ct>& lhs, const Stack< U, Ct>& rhs){
				return (lhs._container <= rhs._container); 
			}

			template <class U, class Ct>
			friend	bool	operator> (const Stack< U, Ct>& lhs, const Stack< U, Ct>& rhs){
				return (lhs._container > rhs._container); 
			}

			template <class U, class Ct>
			friend	bool	operator>= (const Stack< U, Ct>& lhs, const Stack< U, Ct>& rhs){
				return (lhs._container >= rhs._container); 
			}
			protected:
				container_type	_container;
	};

}