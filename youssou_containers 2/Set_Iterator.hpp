/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Set_Iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssou <youssou@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 10:49:02 by youssou           #+#    #+#             */
/*   Updated: 2021/12/01 16:37:21 by youssou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_ITERATOR_HPP
#define SET_ITERATOR_HPP

#include <stddef.h>
#include <iostream>
#include "RedBlackTree.hpp"
#include "utils.hpp"

namespace ft
{
    template <class T, class V, class Pointer = T*, class Reference = T&>
    class setIterator {

        public:
            typedef T                                   value_type;
            typedef ptrdiff_t                           difference_type;
            typedef Pointer                             pointer;
            typedef Reference                           reference;
            typedef std::bidirectional_iterator_tag     iterator_category;
            typedef ft::pair<V, V>                      pair_value_;
            typedef const V                          pair_value;

            
            setIterator(const value_type val) : _ptr_t(&val) {
                return;
            }

            setIterator(const pointer ptr_t) : _ptr_t(ptr_t) { return; }
            
            setIterator(V key, V value){
                static_cast<void>(key);
                static_cast<void>(value);
            };

            setIterator() : _ptr_t(nullptr){ return; }
            ~setIterator(){ return; }
            setIterator(const setIterator &copy){
                *this = copy;
            }
        
            setIterator &operator=(const setIterator &rhs){
                if (*this != rhs)
                    this->_ptr_t = rhs._ptr_t;
                return (*this);
            }

            operator setIterator<const T, const V>() const {
                    setIterator<const T, const V> temp(this->_ptr_t);
                return (temp);
            }

            pointer getNext(pointer node) const{
                pointer next;
                if (node->right->is_Nleaf == 1){
                    pointer tmp = node; 
                    pointer root = *(node->root);
                    while (tmp == tmp->parent->right && tmp->parent != root->parent){
                        tmp = tmp->parent;
                    }
                    next = tmp;
                    return (next->parent);
                }
                pointer min = getMin(node->right); 
                if (node->is_Nleaf == 1)
                    return (node);
                if (min->is_Nleaf == 1){
                    pointer tmp = node; 
                    while (tmp->parent->key < node->key){
                        tmp = tmp->parent;
                    }	
                    next = tmp;
                }
                else
                    next = min;                
                return (next);
		    }

            pointer getPrev(pointer node) const {
                pointer next;
                if (node == (*(node->root))->parent)
                    return (getMax(node->left));
                if (node->left->is_Nleaf == 1){
                    pointer tmp = node->parent; 
                    pointer root = *(node->root);
                    while (!(tmp->key < node->key) || tmp->key == node->key){
                        if (tmp == root)
                            return tmp;
                        tmp = tmp->parent;
                    }
                    next = tmp;
                    return (next);
                }
                
                pointer min = getMax(node->left); 
                if (node->is_Nleaf == 1){
                    return (node);
                }
                if (min->is_Nleaf == 1){
                    pointer tmp = node; 
                    while (!(tmp->parent->key < node->key)){
                        tmp = tmp->parent;
                    }	
                    next = tmp;
                }
                else
                    next = min;
                return (next);
            }

            pointer getMin(pointer node) const{
                while (node->left->is_Nleaf == 0){
                    node = node->left;
                }
                return (node);
            }    
            pointer getMax(pointer node) const{
                while (node->right->is_Nleaf == 0){
                    node = node->right;
                }
                return (node);
            }  

        
            setIterator& operator++(){
                _ptr_t = getNext(_ptr_t);
                return (*this);
            }
        
            setIterator  operator++(int){
                setIterator temp = *this;
                ++(*this);
                return (temp);
            }
            
            setIterator &operator++() const {
                (*this)++;
                return (*this);
            }
            
            setIterator& operator--(){
                _ptr_t = getPrev(this->base());
                return (*this);
            }

            setIterator  operator--(int){
                setIterator temp = *this;
                --(*this);
                return temp;
            }

            const V *operator->() const{
                pair_value_ *a = (pair_value_ *)&(_ptr_t->_pair);
                return (&(a->first));
            }

            const V &operator*() const{
                return (*(this->operator->()));
            }
            
            pointer base() const{
                return (this->_ptr_t);
            }

           bool operator!= (const setIterator &rhs){
                return (rhs._ptr_t != this->_ptr_t);
            }

           bool operator== (const setIterator &rhs){
                return (rhs._ptr_t == this->_ptr_t);
            }
            
            setIterator operator+ (difference_type n) const{
                static_cast<void>(n);
                setIterator temp(getNext(_ptr_t));
                return (temp);
            }
            
            setIterator operator- (difference_type n) const{
                static_cast<void>(n);
                setIterator temp(getPrev(_ptr_t));
                return (temp);
            }
            
        protected:
            pointer  _ptr_t;
    };

    template <class T, class V>
    std::ostream& operator<<(std::ostream& os, const ft::setIterator<T, V>& rhs){
        os << *rhs.base() ;
        return (os);
    }

    template <class T, class L,  class V>
    bool operator!= (const setIterator<T, V>& lhs, const setIterator<L, V>& rhs){
        return (lhs.base() != rhs.base());
    }
    
    template <class T, class L,  class V>
    bool operator==(const setIterator<T, V>& lhs, const setIterator<L, V>& rhs){
        return (lhs.base() == rhs.base());
    }

}

/*
on est sur pour le N unused, 188 193 ?
*/

#endif