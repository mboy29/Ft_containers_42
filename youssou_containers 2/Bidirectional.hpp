/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bidirectional.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssou <youssou@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 10:49:02 by youssou           #+#    #+#             */
/*   Updated: 2021/12/01 16:33:52 by youssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIDIRECTIONAL_HPP
#define BIDIRECTIONAL_HPP

#include <stddef.h>
#include <iostream>
#include "RedBlackTree.hpp"
#include "utils.hpp"

namespace ft
{
    template <class T, class K, class V, class Pointer = T*, class Reference = T&>
    class bidirectional {

        public:
            typedef T                                   value_type;
            typedef ptrdiff_t                           difference_type;
            typedef Pointer                             pointer;
            typedef Reference                           reference;
            typedef std::bidirectional_iterator_tag     iterator_category;
            typedef ft::pair<K, V>                      pair_value;
            
            bidirectional(const value_type val) : _ptr_t(&val) {
                return;
            }

            bidirectional(const pointer ptr_t) : _ptr_t(ptr_t) { return; }
            
            bidirectional(K key, V value){
                static_cast<void>(key);
                static_cast<void>(value);
            };

            bidirectional() : _ptr_t(nullptr){ return; }
            ~bidirectional(){ return; }
            bidirectional(const bidirectional &copy){
                *this = copy;
            }
        
            bidirectional &operator=(const bidirectional &rhs){
                if (*this != rhs)
                    this->_ptr_t = rhs._ptr_t;
                return (*this);
            }

            operator bidirectional<const T, const K, const V>() const {
                    bidirectional<const T, const K, const V> temp(this->_ptr_t);
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
                if (node->left->is_Nleaf == 1){
                    pointer tmp = node->parent; 
                    pointer root = *(node->root); 
                    while (tmp->key >= node->key){
                        if (tmp == root)
                            return tmp;
                        tmp = tmp->parent;
                    }
                    next = tmp;
                    return (next);
                }
                
                pointer min = getMax(node->left); 
                if (node->is_Nleaf == 1)
                    return (node);
                if (min->is_Nleaf == 1){
                    pointer tmp = node; 
                    while (tmp->parent->key > node->key){
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
            
            bidirectional& operator++(){
                _ptr_t = getNext(_ptr_t);
                return (*this);
            }
        
            bidirectional  operator++(int){
                bidirectional temp = *this;
                ++(*this);
                return (temp);
            }
            
            bidirectional &operator++() const {
                (*this)++;
                return (*this);
            }
            
            bidirectional& operator--(){
                _ptr_t = getPrev(_ptr_t);
                return (*this);
            }

            bidirectional  operator--(int){
                bidirectional temp = *this;
                --(*this);
                return temp;
            }

            pair_value *operator->() const{
                pair_value *a = (pair_value *)&(_ptr_t->_pair);
                return (a);
            }

            pair_value &operator*() const{
                return (*(this->operator->()));
            }
            
            pointer base() const{
                return (this->_ptr_t);
            }

           bool operator!= (const bidirectional &rhs){
                return (rhs._ptr_t != this->_ptr_t);
            }

           bool operator== (const bidirectional &rhs){
                return (rhs._ptr_t == this->_ptr_t);
            }
            
            bidirectional operator+ (difference_type n) const{
                static_cast<void>(n);
                bidirectional temp(getNext(_ptr_t));
                return (temp);
            }
            
            bidirectional operator- (difference_type n) const{
                static_cast<void>(n);
                bidirectional temp(getPrev(_ptr_t));
                return (temp);
            }
            
        protected:
            pointer  _ptr_t;
    };

    template <class T, class K, class V>
    std::ostream& operator<<(std::ostream& os, const ft::bidirectional<T, K, V>& rhs){
        os << *rhs.base() ;
        return (os);
    }

    template <class T, class L, class K, class V>
    bool operator!= (const bidirectional<T, K, V>& lhs, const bidirectional<L, K, V>& rhs){
        return (lhs.base() != rhs.base());
    }
    
    template <class T, class L, class K, class V>
    bool operator==(const bidirectional<T, K, V>& lhs, const bidirectional<L, K, V>& rhs){
        return (lhs.base() == rhs.base());
    }

}


/*
182, le N unused :what: on est sur de l'histoire là ?
idem 188, N unused
*/


#endif