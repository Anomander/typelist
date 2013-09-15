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
#ifndef __typelist_algorithm_filter_h__
#define __typelist_algorithm_filter_h__

#include "_private.h"

namespace typelist {

/**
 * Creates the list from the provided one which only contains
 * elements that passed the provided filter.
 * The format of the filter is expected to be like this:
 *
 * template<typename T>
 * struct|class Filter {
  *   enum { value = true|false|0|non-0 };
 * };
 */
template<typename TL, template<typename>class Comp> struct filter;

/**
 * General case.
 * Filters the head and recurses into the tail.
 */
template<template<typename>class Comp, typename T, typename... Args>
struct filter <list<T, Args...>, Comp> {
private:
    using next = 
        typename filter <typename list<T, Args...> :: tail, Comp> :: type;
public:
    using type =    
        typename std::conditional <
            Comp<T> :: value,
            typename _private::_make_list < T, next > :: type,
            typename _private::_make_list < 
                typename _private::_head<next> :: type, 
                typename _private::_tail<next> :: type 
            > :: type
        > :: type;
};

/**
 * Specialization to end recursion.
 */
template<template<typename>class Comp>
struct filter <_private::_sentinel, Comp> {
    using type = _private::_sentinel;
};

}

#endif//__typelist_algorithm_filter_h__
