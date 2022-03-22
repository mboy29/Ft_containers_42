/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setIterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcadmin <mcadmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 17:29:15 by sel-fadi          #+#    #+#             */
/*   Updated: 2022/01/30 00:03:57 by mcadmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "../tools/reverse_iterator.hpp"

namespace ft
{
    template < class T, class Node, class Tree >
    class SetIterator
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

            // typedef MapIterator<const T, Node, Tree> const_iterator;
        
            SetIterator() : _node(), _rbt() {};
            SetIterator( Node *node, const Tree *rbt ) : _node(node), _rbt(rbt) {};
            SetIterator( const SetIterator& rhs ) { *this = rhs; }
            SetIterator& operator= ( const SetIterator& rhs ) { this->_node = rhs._node; this->_rbt = rhs._rbt; return *this; }
            virtual ~SetIterator() {};

            reference operator*() const { return *this->_node->data; }
            pointer   operator->() const { return this->_node->data; }

            SetIterator &operator++ ()
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
            
            SetIterator &operator-- ()
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
            
            SetIterator operator++(int) { SetIterator tmp(*this); ++(*this); return (tmp); }
            SetIterator operator--(int) { SetIterator tmp(*this); --(*this); return (tmp); }
            
            Node *base() const { return this->_node;}

            operator SetIterator<const T, Node, const Tree>() const { return SetIterator<const T, Node, const Tree>(_node, _rbt);}
            
            friend bool operator== (const SetIterator& lhs, const SetIterator& rhs) { return lhs.base() == rhs.base(); }
            friend bool operator!= (const SetIterator& lhs, const SetIterator& rhs) { return !operator==(lhs, rhs); }
    };
    
};