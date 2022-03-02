#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{
    template < class T, class Container = vector<T> >
    class stack
    {
    public:
        typedef Container                                container_type;
        typedef typename container_type::value_type      value_type;
        typedef typename container_type::reference       reference;
        typedef typename container_type::const_reference const_reference;
        typedef typename container_type::size_type       size_type;

    protected:
        container_type c;

    public:
    explicit stack( const Container& cont = Container() ) : c(cont) {} //컨테이너 기본 생성자 호출해 stack을 생성하거나 인자로 받아 stack을 생성
    stack& operator=( const stack& other ) { c = other.c; return (*this); }
    ~stack() {}

    // Element access
    reference top() { return (c.back()); }
    const_reference top() const { return (c.back()); }
    // Capacity
    bool empty() const { return (c.empty()); }
    size_type size() const { return (c.size()); }
    // Modifiers
    void push( const value_type& value ) { c.push_back(value); }
    void pop() { c.pop_back(); }

    // relational operators
    // Declaring friend function using friend keyword
    template< class Tn, class Cntr >
    friend bool operator==( const stack<Tn,Cntr>& lhs, const stack<Tn,Cntr>& rhs );
    template< class Tn, class Cntr >
    friend bool operator!=( const stack<Tn,Cntr>& lhs, const stack<Tn,Cntr>& rhs );
    template< class Tn, class Cntr >
    friend bool operator<( const stack<Tn,Cntr>& lhs, const stack<Tn,Cntr>& rhs );
    template< class Tn, class Cntr >
    friend bool operator<=( const stack<Tn,Cntr>& lhs, const stack<Tn,Cntr>& rhs );
    template< class Tn, class Cntr >
    friend bool operator>( const stack<Tn,Cntr>& lhs, const stack<Tn,Cntr>& rhs );
    template< class Tn, class Cntr >
    friend bool operator>=( const stack<Tn,Cntr>& lhs, const stack<Tn,Cntr>& rhs );

};
template< class T, class Container >
bool operator==( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {return (lhs.c == rhs.c);}
template< class T, class Container >
bool operator!=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {return (lhs.c != rhs.c);}
template< class T, class Container >
bool operator<( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {return (lhs.c < rhs.c);}
template< class T, class Container >
bool operator<=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {return (lhs.c <= rhs.c);}
template< class T, class Container >
bool operator>( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {return (lhs.c > rhs.c);}
template< class T, class Container >
bool operator>=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {return (lhs.c >= rhs.c);}
}

#endif  