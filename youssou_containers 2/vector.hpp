/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssou <youssou@student.42nice.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 13:43:54 by youssou           #+#    #+#             */
/*   Updated: 2021/12/01 16:21:23 by youssou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "Reverse_iterator.hpp"
#include "Iterator.hpp"
#include <iostream>
#include <string>
#include <type_traits>
#include "utils.hpp"

namespace ft{


    template < class T, class Allocator = std::allocator<T> >
    class vector
    {

        public:
            /*** Define ***/
            typedef T                                                   value_type;
            typedef Allocator                                           allocator_type;
            typedef size_t                                              size_type;
            typedef std::ptrdiff_t                                      difference_type;
            typedef value_type&                                         reference;
            typedef const value_type&                                   const_reference;
            typedef ft::iterator<value_type>                            iterator;
            typedef ft::iterator<const value_type>                      const_iterator;
            typedef ft::reverse_iterator<iterator>                      reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>                const_reverse_iterator;
            typedef typename allocator_type::pointer                    pointer;
            typedef typename allocator_type::const_pointer              const_pointer;

 
            /*** Constructors ***/
            explicit vector (const allocator_type& alloc = allocator_type()) : _begin(nullptr), _end(nullptr), _size(0), _capacity(0), _allocator(alloc){
            }

            explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _size(n), _capacity(n), _allocator(alloc) {
                this->_begin = _allocator.allocate(n);
                for (size_type i = 0 ; i < n ; i++)
                    _allocator.construct(this->_begin + i, val);
                this->_end = this->_begin + this->_size;
            }

            ~vector(){
               // this->clear();
               // _allocator.deallocate(this->_begin, this->_capacity);
            }

            template <class InputIterator>
            vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type *enable = nullptr) : _size(0), _capacity(0), _allocator(alloc) {
                this->assign(first, last);
                (void)enable;
            }

            vector (const vector& x) : _begin(nullptr), _end(nullptr),  _size(0), _capacity(0), _allocator(allocator_type()){
                this->clear();
                this->_allocator = x._allocator;
                this->_capacity = x._capacity;
                this->_size = x._size;
                this->_begin = _allocator.allocate(this->_capacity);
                for (size_type i = 0 ; i < this->_size ; i++)
                {
                    _allocator.construct(this->_begin + i, x[i]);
                }
                this->_end = this->_begin + this->_size;
            }

            vector& operator=(const vector& x){
                if (x == *this)
                    return (*this);
                this->clear();
                this->_allocator = x._allocator;
                this->_capacity = x._capacity;
                this->_size = x._size;
                this->_begin = _allocator.allocate(this->_capacity);
                for (size_type i = 0 ; i < this->_size ; i++)
                    _allocator.construct(this->_begin + i, x[i]);
                this->_end = this->_begin + this->_size;
                return (*this);
            }

            /*** Iterators ***/
            iterator begin(){
                return (iterator(this->_begin));
            }
            const_iterator begin() const{
                return (const_iterator(this->_begin));
            }
            iterator end(){
                return (iterator(this->_end));
            }
            const_iterator end() const{
                 return (const_iterator(this->_end));
            }
            
            reverse_iterator rbegin(){
                return (reverse_iterator(this->end()));
            }

            const_reverse_iterator rbegin() const{
                return (const_reverse_iterator(this->end()));
            }

            reverse_iterator rend(){
                return (reverse_iterator(this->begin()));
            }

            const_reverse_iterator rend() const{
                return (const_reverse_iterator(this->begin()));
            }
            
            /* return actual used size for the container */
            size_type size() const{
                return (this->_size);
            }
            /* return maximum size possible to allocate */
            size_type max_size() const{
                return (std::numeric_limits<std::size_t>::max() / sizeof(T));
            }
            /* resize the container capacity to n, does nothing if equal, shrink if size > n, does not deallocate */
            void resize (size_type n, value_type val = value_type()){
                if (n < this->_size){
                    while (this->_size > n){
                    // std::cout << "*******HERE*******" << _size << "\n";
                       //this->_allocator.destroy(this->_begin + _size);
                        this->_end--;
                        this->_size--;
                    }
                    // this->_end = this->_begin + this->_size;
                }
                else if (n > this->_capacity){
                    if (this->_capacity == 0)
                        this->_capacity++;
                    pointer temp;
                    if (this->_capacity * 2 > n){
                        temp = _allocator.allocate(this->_capacity * 2);
                        this->_capacity *= 2;
                    }
                    else{
                        temp = _allocator.allocate(n); 
                        this->_capacity = n;
                    }
                    for(size_type i=0; i < this->_size; i++){
                        _allocator.construct(temp + i, *(this->_begin + i));
                        _allocator.destroy(this->_begin + i);
                    }
                    _allocator.deallocate(this->_begin, this->_capacity);
                    for(unsigned long int i = this->_size; i < n; i++){
                        _allocator.construct(temp + i, val);
                    }
                    this->_size = n;
                    this->_begin = temp;
                    this->_end = temp + n;
                    
                }
                else if (n > this->_size && n < this->_capacity){
                    for (size_t i = this->_size; i < n; i++){
                        this->_allocator.construct(this->_begin + i, val);
                        this->_end++;
                        this->_size++;
                    } 
                }
            }
            
            /* return total container capacity */
            size_type capacity() const{
                return (this->_capacity);
            }
            /* return bool if container empty or not */
            bool empty() const{
                return (this->_size == 0);
            }
            /* Le vrai lance une bad_alloc mais pas le notre en cas de n == max_size */
            void reserve (size_type n){
                if (n > this->_capacity){
                    if (n >= this->max_size()){
                        throw  std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
                    }
                    int diff = n;
                    if (n > this->_size)
                        diff = this->_size;
                    /**/
                    if (n < this->_capacity){
                        while (this->_size > n){
                            this->_allocator.destroy(this->_end);
                            this->_end--;
                            this->_size--;
                        }
                    }
                    else if (n > this->_capacity){
                        pointer temp = _allocator.allocate(n);
                        for(size_type i = 0; i < this->_size; i++){
                            _allocator.construct(temp + i, *(this->_begin + i));
                            _allocator.destroy(this->_begin + i);
                        }
                        _allocator.deallocate(this->_begin, this->_capacity);
                        this->_size = n;
                        this->_begin = temp;
                        this->_end = temp + n;
                        this->_capacity = n;
                    }
                    /**/
                    this->_size = diff;
                    this->_end = this->_begin + diff;
                }
            }

            template <class InputIterator>
            typename iterator::difference_type getDistance(InputIterator first, InputIterator last){
                difference_type i = 0;
                for(i = 0; first != last; i++){
                    first++;
                }
                return (i);
            }
            
            /*** Element access ***/
            reference operator[] (size_type n){
                return (*(this->_begin + n));
            }
            const_reference operator[] (size_type n) const{
                return (*(this->_begin + n));
            }
            reference at (size_type n){
                if (n < 0 || n >= this->_size)
                    throw std::out_of_range("vector");
                return (*(this->_begin + n));
            }
            const_reference at (size_type n) const{
                if (n < 0 || n >= this->_size)
                    throw std::out_of_range("vector");
                return (*(this->_begin + n));
            }
            reference front(){
                return (*this->_begin);
            }
            const_reference front() const{
                return (*this->_begin);
            }
            reference back(){
                return (*(this->_end - 1));
            }
            const_reference back() const{
                return (*(this->_end - 1));
            }

            /*** Modifiers ***/
            template <class InputIterator> 
            void assign (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type *enable = nullptr){
                static_cast<void>(enable);
                if (this->_size)
                    this->clear();
                difference_type capacity = getDistance(first, last);
                if (static_cast<unsigned int>(capacity) > this->_capacity)
                    this->_capacity = capacity;
                this->_begin = _allocator.allocate(this->_capacity);
                int i;
                for(i=0; first != last; i++){
                    _allocator.construct(this->_begin + i, *(first++));
                }
                this->_end = this->_begin + i;
                this->_size = i;
            }

            void assign (size_type n, const value_type& val){
                if (this->_size)
                    this->clear();
                if (n <= this->_capacity){
                        for (size_type y = 0; y < n; y++){
                            _allocator.construct(this->_begin + y, val);
                        }
                        this->_end = this->_begin + n;
                    }
                    else {
                        _allocator.deallocate(this->_begin, this->_capacity);
                        this->_begin = _allocator.allocate(n);
                        this->_capacity = n;
                        for (unsigned long int i = 0; i < this->_capacity; i++){
                            _allocator.construct(this->_begin + i, val);
                        }
                        this->_end = this->_begin + n;
                    }
                    this->_size = n;
            }
            
            void push_back (const value_type& val){
                if (this->_size >= this->_capacity){
                    if (this->capacity() > 0)
                        this->reserve(this->_capacity * 2);
                    else
                        this->reserve(1);
                    _allocator.construct(this->_end, val);
                    this->_end++;
                }
                else{
                    _allocator.construct(this->_end, val);
                    this->_end++;
                }
                this->_size++;
            }
            
            void pop_back(){
                if (this->_size != 0){
                    _allocator.destroy(this->_end - 1);
                    this->_end--;
                    this->_size--;
                }

            }
            iterator insert (iterator position, const value_type& val){
                size_type index = position - this->begin();
                if (this->_size >= this->_capacity){ 
                    if (this->_capacity == 0)
                        this->_capacity++;
                    pointer temp = _allocator.allocate(this->_capacity * 2);
                    for(size_type i = 0 ; i < index ; i++){
                        _allocator.construct(temp + i, *(this->_begin + i));
                    }
                    _allocator.construct(temp + index, val);
                    for(size_type j = index + 1; j <= this->_size ; j++){
                        _allocator.construct(temp + j, *(this->_begin + (j - 1)));
                    }
                    for(size_type i=0; i < this->_size ; i++){
                        _allocator.destroy(this->_begin + i);
                    }
                    _allocator.deallocate(this->_begin, this->_capacity);
                    this->_begin = temp;
                    this->_capacity *= 2;
                    this->_size++;
                     this->_end = temp + this->_size;
                    return (this->_begin + index);
                } else {
                   
                   if (this->_size == 0)
                        _allocator.construct(this->_begin + this->_size, val);
                    for(size_type i = this->_size; i > index ; i--){
                        _allocator.construct(_begin + i, _begin[i - 1]);
                    }
                    this->_begin[index] = val;
                }
                this->_end++;
                this->_size++;
                return(this->_begin + index);
            }
            
            void insert (iterator position, size_type n, const value_type& val){
                size_type index = position - this->begin();
                if (this->_capacity > this->_size + n){
                // std::cout << "***************3\n";
                    ft::vector<T>temp(position, this->end()); //faire une copie des elements seulement needed; (ceux de la fin)
                    for (unsigned long int y = 0; y < n; y++){
                        this->_begin[index + y] = val;
                    }
                    for (size_type w = 0; w < n; w++){
                        this->_begin[index + n + w] = temp._begin[index + w];
                    }
                    this->_end = (this->_end + n);
                    this->_size += n;
                } else if (this->_capacity <= this->_size + n) {
                    if (this->_capacity == 0)
                        this->_capacity++;
                    pointer temp = _allocator.allocate((this->_capacity + n) * 2);
                    for (size_type i = 0; i < index; i++){
                        _allocator.construct(temp + i, *(this->_begin + i));
                    }
                    for (size_type y = index; y < index + n; y++){
                        _allocator.construct(temp + y, val);
                    }
                    for (size_type w = 0; w < this->_size - index; w++){
                        _allocator.construct(temp + index + n + w, *(this->_begin + index + w));
                    }
                    for(size_type i=0; i < this->_size ; i++){
                        _allocator.destroy(this->_begin + i);
                    }
                    _allocator.deallocate(this->_begin, this->_capacity);
                    this->_begin = temp;
                    this->_size += n;
                    this->_end = temp + this->_size;
                    this->_capacity = (this->_capacity + n) * 2;
                }
            }

            template <class InputIterator>
            void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type *enable = nullptr){
                difference_type diff = 0;
                static_cast<void>(enable);
                diff = getDistance(first, last);
                if (this->_size <= this->_capacity){
                    difference_type diff_begin = position - this->begin(); 
                    this->reserve(this->_size + diff);
                    position = this->begin() + diff_begin;
                }
                for (int i = 0; i < diff; i++){
                    position = this->insert(position + ((i == 0) ? 0 : 1), *(first++));
                }
            }
            
            iterator erase (iterator position){
                difference_type i = position.base() - this->_begin;
                std::memmove(this->_begin + i, this->_begin + i + 1, (this->_size - i - 1) * sizeof(value_type));
                _allocator.destroy(this->_begin + this->_size);
                this->_size--;
                this->_end--;
                return (iterator(this->_begin + i));
            }

            iterator erase (iterator first, iterator last){
                difference_type diff = last.base() - first.base();
                std::memmove(first.base(), last.base(), (this->_size - diff) * sizeof(value_type));
 
                for(size_type i = this->_size - diff; i < this->_size ; i++){
                    _allocator.destroy(this->_begin + i);
                }

                this->_size -= diff;
                this->_end -= diff;
                return (last - diff);
            }
            
            void swap (vector& x){
                pointer begin_temp = this->_begin;
                pointer end_temp = this->_end;
                size_type size_temp = this->_size;
                size_type capacity_temp = this->_capacity;
                allocator_type  alloc_temp = this->_allocator;
                
                this->_begin = x._begin;
                this->_end = x._end;
                this->_size = x._size;
                this->_capacity = x._capacity;
                this->_allocator = x._allocator;
                
                x._begin = begin_temp;
                x._end = end_temp;
                x._size = size_temp;
                x._capacity = capacity_temp;
                x._allocator = alloc_temp;
            }
            
            void clear(){
                if (this->_size != 0){
                    for (unsigned long int i = 0; i < this->_size; i++){
                        this->_end--;
                        _allocator.destroy(this->_begin + i);
                    }
                    this->_size = 0;
                }
            }

            /***  Allocator ***/
            allocator_type get_allocator() const{
                return (this->_allocator);
            }

        private:
            pointer                 _begin;
            pointer                 _end;
            size_type               _size;
            size_type               _capacity;
            allocator_type          _allocator;
            
    };

    template <class T, class Alloc>
    bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
        if (lhs.size() != rhs.size())
            return (false);

        for(std::size_t i=0; i < lhs.size(); i++){
            if (*(lhs.begin() + i) != *(rhs.begin() + i))
                return (false);
        } 
        return (true);
    }

    template <class T, class Alloc>
    bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
        return (!(lhs == rhs));
    }

    template <class T, class Alloc>
    bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }

    template <class T, class Alloc>
    bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
        if (lhs < rhs || lhs == rhs)
            return (true);
        return (false);
    }

    template <class T, class Alloc>
    bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
        if (!(lhs < rhs) && lhs != rhs)
            return (true);
        return (false);
    }

    template <class T, class Alloc>
    bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
        if (lhs > rhs || lhs == rhs)
            return (true);
        return (false);
    }

    template <class T, class Alloc>
    void swap (vector<T,Alloc>& x, vector<T,Alloc>& y){
        x.swap(y);
    }
   
}
#endif