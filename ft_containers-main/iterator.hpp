#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef> //ptrdiff_t 포인터의 차이를 위한 signed 타입

namespace ft
{
    struct input_iterator_tag  {};
    struct output_iterator_tag {};
    struct forward_iterator_tag       : public input_iterator_tag         {};
    struct bidirectional_iterator_tag : public forward_iterator_tag       {};
    struct random_access_iterator_tag : public bidirectional_iterator_tag {};

    template<typename Iterator>
    struct iterator_traits //반복자 타입
    {   //Iterator::이 붙어서 타입이라고 생각 안하고 변수라고 생각할까봐 typename을 붙여줌
        typedef typename Iterator::iterator_category iterator_category;
        typedef typename Iterator::value_type value_type;
        typedef typename Iterator::difference_type difference_type;
        typedef typename Iterator::pointer pointer;
        typedef typename Iterator::reference reference;
    };

    template<typename T>
    struct iterator_traits<T*> //포인터 타입 포인터타입에대한 특수화
    {
        typedef random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef T* pointer;
        typedef T& reference;
    };
    //커버리지를 높혀줌

    template<class Category, class T, class Distance = ptrdiff_t,
         class Pointer = T*, class Reference = T&>
    struct iterator // 반복자 에 필요한 유형의 정의를 단순화하기 위해 제공되는 기본 클래스. 이걸 상속 받아서 iterator 클래스 만듦
    {
        typedef T         value_type;
        typedef Distance  difference_type;
        typedef Pointer   pointer;
        typedef Reference reference;
        typedef Category  iterator_category;
    };
}

#endif