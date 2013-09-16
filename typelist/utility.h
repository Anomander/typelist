/*
 * The MIT License (MIT)
 * 
 * Copyright (c) 2013 Stan Pavlovski
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#ifndef __typelist_utility_h__
#define __typelist_utility_h__

#include "typelist/_private.h"

/**
 * Utilities for working with lists.
 */
namespace typelist {

/**
 * Returns the number of elements in the list.
 */
template <typename TL> struct length;

/**
 * Specialization for the general case.
 * Calculates the length of the tail and adds 1.
 */
template <typename T, typename... Args>
struct length< list<T, Args...> > {
    enum {
        value = length<typename list<T, Args...> :: tail> :: value + 1
    };
};

/**
 * Specialization to end recursion.
 */
template <>
struct length<_private::_sentinel> {
    enum {
        value = 0
    };
};

/**
 * Returns i-th element of the list.
 * Will result in compiler error (probably something about
 * template nesting depth maximum) if the index is out of
 * bounds of the array.
 */
template<unsigned i, typename TL> 
struct at_safe {
    using type = typename at_safe <
        i-1, 
        typename _private::_tail<TL>::type
    >::type;
};

/**
 * Specialization for the case when the element is found.
 */
template<typename Head, typename... Tail> 
struct at_safe <0, list<Head, Tail...>> {
    using type = Head;
};

/**
 * Specialization for the case when the element is NOT found.
 */
template<unsigned i> 
struct at_safe <i, _private::_sentinel> {
    using type = _private::_sentinel;
};

/**
 * Returns i-th element of the list.
 * Will return sentinel if the index is out of bounds of the array.
 */
template<unsigned i, typename TL> 
struct at {
    using type = typename at <
        i-1, 
        typename _private::_tail<TL>::type
    >::type;
};

/**
 * Specialization for the case when the element is found.
 */
template<typename Head, typename... Tail> 
struct at <0, list<Head, Tail...>> {
    using type = Head;
};

/**
 * Specialization for the case when the element is NOT found.
 */
template<unsigned i> 
struct at <i, _private::_sentinel> {
    using type = _private::_sentinel;
};

template<unsigned i, typename T, typename TL> struct insert_at {
    using type = typename _private::_make_list<
        typename TL::head,
        typename insert_at<i-1, T, typename TL::tail>::type
    >::type;    
};

template<typename T, typename TL> 
struct insert_at<0, T, TL> {
    using type = typename _private::_make_list < T, TL > :: type;
};

}

#endif//__typelist_utility_h__
