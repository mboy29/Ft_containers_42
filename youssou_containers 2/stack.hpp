/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssou <youssou@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 13:57:36 by youssou           #+#    #+#             */
/*   Updated: 2021/11/30 19:48:39 by youssou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"
#include <iostream>

namespace ft{
    
    template <class T, class Container = ft::vector<T> >
    class stack{

        public:
        template <class LHS_T , class RHS_C>
        friend bool operator== (const stack<LHS_T, RHS_C>& lhs, const stack<LHS_T, RHS_C>& rhs);
        
        template <class LHS_T , class RHS_C>
        friend bool operator!= (const stack<LHS_T, RHS_C>& lhs, const stack<LHS_T, RHS_C>& rhs);

        template <class LHS_T , class RHS_C>
        friend bool operator< (const stack<LHS_T, RHS_C>& lhs, const stack<LHS_T, RHS_C>& rhs);

        template <class LHS_T , class RHS_C>
        friend bool operator<= (const stack<LHS_T, RHS_C>& lhs, const stack<LHS_T, RHS_C>& rhs);

        template <class LHS_T , class RHS_C>
        friend bool operator>  (const stack<LHS_T, RHS_C>& lhs, const stack<LHS_T, RHS_C>& rhs);
        
        template <class LHS_T , class RHS_C>
        friend bool operator>= (const stack<LHS_T, RHS_C>& lhs, const stack<LHS_T, RHS_C>& rhs);
    
        typedef T                           value_type;
        typedef Container                   container_type;
        typedef size_t                      size_type;
        
        explicit stack (const container_type& ctnr = container_type()) : c(ctnr){};

        bool empty() const{
            return (c.empty());
        }

        size_type size() const{
            return (c.size());
        }

        value_type& top(){
            return (c.back());
        }
        const value_type& top() const{
            return (c.back());
        }

        void push (const value_type& val){
            c.push_back(val);
        }

        void pop(){
            c.pop_back();
        }

        protected:
            container_type c;
    };

    template <class T, class Container>
    bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs){

        return (lhs.c == rhs.c);
    }

    template <class T, class Container>
    bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
        return (lhs.c != rhs.c);
    }

    template <class T, class Container>
    bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
        return (lhs.c < rhs.c);
    }

    template <class T, class Container>
    bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
        return (lhs.c <= rhs.c);
    }

    template <class T, class Container>
    bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
        return (lhs.c > rhs.c);
    }

    template <class T, class Container>
    bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
        return (lhs.c >= rhs.c);
    }
}
#endif