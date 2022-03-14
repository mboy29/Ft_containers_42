/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapIterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 17:29:15 by sel-fadi          #+#    #+#             */
/*   Updated: 2022/02/01 16:38:33 by sel-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "../tools/reverse_iterator.hpp"

namespace ft
{
    template < class T, class Node, class Tree >
    class mapIterator
    {
        protected:
            Node *_node;
            const Tree *_rbt;
        public:
			typedef Iterator_traits< iterator<std::bidirectional_iterator_tag, T> > iterator_traits;
			typedef typename iterator_traits::value_type value_type;
			typedef typename iterator_traits::pointer pointer;
			typedef typename iterator_traits::reference reference;
			typedef typename iterator_traits::difference_type difference_type;
			typedef typename iterator_traits::iterator_category iterator_category;
        
            mapIterator() : _node(), _rbt() {};
            mapIterator( Node *node, const Tree *rbt ) : _node(node), _rbt(rbt) {};
            mapIterator( const mapIterator& rhs ) { *this = rhs; }
            mapIterator& operator= ( const mapIterator& rhs ) { this->_node = rhs._node; this->_rbt = rhs._rbt; return *this; }
            virtual ~mapIterator() {};

            reference operator*() const { return *this->_node->data; }
            pointer   operator->() const { return this->_node->data; }

            mapIterator &operator++ ()
            {
                Node *p;
                if (_node == NULL)
                {
                    _node = _rbt->getRoot();
                    if (_node == NULL)
                        return *this;
                    
                    // error! ++ requested for an empty _rbt
                    if (_node == NULL)
                        throw "mmmmkkk";
                    
                    // move to the smallest value in the _rbt,
                    // which is the first node inorder
                    while (_node->left != NULL)
                        _node = _node->left;
                }
                else
                    if (_node->right != NULL)
                    {
                        _node = _node->right;
                        while (_node->left != NULL)
                            _node = _node->left;
                    }
                    else
                    {
                        p = _node->parent;
                        while (p != NULL && _node == p->right)
                        {
                            _node = p;
                            p = p->parent;
                        }
                        _node = p;
                    }
                return *this;
            }
            
            mapIterator &operator-- ()
            {
                Node *p;
                if (_node == NULL)
                {
                    // ++ from end(). get the root of the _rbt
                    _node = _rbt->getRoot();
                    
                    // error! ++ requested for an empty _rbt
                    if (_node == NULL)
                        throw "mmmmkkk";
                    
                    // move to the smallest value in the _rbt,
                    // which is the first node inorder
                    while (_node->right != NULL)
                        _node = _node->right;
                }
                else
                    if (_node->left != NULL)
                    {
                        _node = _node->left;
                        while (_node->right != NULL)
                            _node = _node->right;
                    }
                    else
                    {
                        p = _node->parent;
                        while (p != NULL && _node == p->left)
                        {
                            _node = p;
                            p = p->parent;
                        }
                        _node = p;
                    }
                return *this;
            }
            
            mapIterator operator++(int) { mapIterator tmp(*this); ++(*this); return (tmp); }
            mapIterator operator--(int) { mapIterator tmp(*this); --(*this); return (tmp); }
            
            Node *base() const { return this->_node;}

            operator mapIterator<const T, Node, const Tree>() const { return mapIterator<const T, Node, const Tree>(_node, _rbt);}
            
            friend bool operator== (const mapIterator& lhs, const mapIterator& rhs) { return lhs.base() == rhs.base(); }
            friend bool operator!= (const mapIterator& lhs, const mapIterator& rhs) { return !operator==(lhs, rhs); }
    };
};