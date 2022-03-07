/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssou <youssou@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 13:30:34 by youssou           #+#    #+#             */
/*   Updated: 2021/11/26 17:05:30 by youssou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <stddef.h>
#include <iostream>

namespace ft{

    template <class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
    class iterator {
        
        public:
            typedef T         value_type;
            typedef Distance  difference_type;
            typedef Pointer   pointer;
            typedef Reference reference;
            typedef std::random_access_iterator_tag  iterator_category;
            
            iterator(pointer ptr_t) : _ptr_t(ptr_t) {  return; }
            iterator() : _ptr_t(nullptr){ return; }
            ~iterator(){ return; }
            iterator(const iterator &copy){
                *this = copy;
            }
            
            iterator &operator=(const iterator &rhs){
                if (*this != rhs)
                    this->_ptr_t = rhs._ptr_t;
                return (*this);
            }
            operator iterator<const T>() const {
                    iterator<const T> temp(this->_ptr_t);
                return (temp);
            }

            iterator& operator++(){
                this->_ptr_t++;
                return (*this);
            }

            iterator  operator++(int){
                iterator temp = *this;
                ++(*this);
                return temp;
            }
            
            iterator &operator++() const {
                (*this)++;
                return (*this);
            }
            
            iterator& operator--(){
                this->_ptr_t--;
                return (*this);
            }

            iterator  operator--(int){
                iterator temp = *this;
                --(*this);
                return temp;
            }
            
           iterator operator- (difference_type n) const{
                iterator temp(this->_ptr_t - n);
                return (temp);
            }
            
 
            iterator& operator+= (difference_type n){
                *this = *this + n;
                return (*this);
            }
            
            iterator& operator-= (difference_type n){
                *this = *this - n;
                return (*this);
            }
            
            iterator operator+ (difference_type n) const{
                iterator temp(this->_ptr_t + n);
                return (temp);
            }

            pointer operator->() const{
                return (this->_ptr_t);
            }

            reference operator[] (difference_type n) const{
                return (*(this->_ptr_t + n));
            }
            
            reference operator*() const{
                return (*this->_ptr_t);
            }
            
            pointer base() const{
                return (this->_ptr_t);
            }
        
        protected:
            pointer  _ptr_t;
    };

        template <class T>
        std::ostream& operator<<(std::ostream& os, const ft::iterator<T>& rhs){
            os << *rhs.base() ;
            return (os);
        }
        
        template <typename T, typename R>
        typename iterator<T>::difference_type operator-(const iterator<T> lhs, const iterator<R> rhs){
            return (lhs.base() - rhs.base());
        }
        
        template <class T, class R>
        typename iterator<T>::difference_type operator+(const iterator<T> lhs, const iterator<R> rhs){
            return (lhs.base() + rhs.base());
        }

        template <typename T>
        iterator<T> operator+(typename iterator<T>::difference_type n, const iterator<T> lhs){
            return (n + lhs.base());
        }

        template <typename T>
        iterator<T> operator- (typename iterator<T>::difference_type n, const iterator<T> lhs){
            return (n - lhs.base());
        }
        
        template <class T, class L>
        bool operator!= (const iterator<T>& lhs, const iterator<L>& rhs){
            return (lhs.base() != rhs.base());
        }

        template <class T, class L>
        bool operator>= (const iterator<T>& lhs, const iterator<L>& rhs){
            return (lhs.base() >= rhs.base());
        }

        template <class T, class L>
        bool operator> (const iterator<T>& lhs, const iterator<L>& rhs){
            return (lhs.base() > rhs.base());
        }

        template <class T, class L>
        bool operator<= (const iterator<T>& lhs, const iterator<L>& rhs){
            return (lhs.base() <= rhs.base());
        }
        
        template <class T, class L>
        bool operator< (const iterator<T>& lhs, const iterator<L>& rhs){
            return (lhs.base() < rhs.base());
        }
        
        template <class T, class L>
        bool operator==(const iterator<T>& lhs, const iterator<L>& rhs){
            return (lhs.base() == rhs.base());
        }
    }




#endif