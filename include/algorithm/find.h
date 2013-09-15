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
#ifndef __typelist_algorithm_find_h__
#define __typelist_algorithm_find_h__

#include "_private.h"

namespace typelist {

/**
 * The result of the find.
 * Provides two aliases.
 * valid is a 0|non-0 value that describes whether the
  *     provided result is meaninful.
 * type describes the found type; if valid is 0, then
  *    this type will be _private::_sentinel.                   
 */
template<typename T> struct find_result;

/**
 * Finds the first occurence of the type that passes
 * the provided criteria.
 * The criteria should be destibed in the following 
 * format:
 *
 * template<typename T>
 * struct|class Filter {
  *   enum { value = true|false|0|non-0 };
 * };
 */
template<typename TL, template<typename>class Comp> struct find;

/**
 * General case that checks the head of the list
 * and recurses into the tail.
 */
template<typename Head, typename... Tail, template<typename>class Comp>
struct find<list<Head, Tail...>, Comp> {
private:
    using tl = list <Head, Tail...>;
    using next = typename find <typename tl :: tail, Comp> :: type;
public:
    using type = 
    find_result <
        typename std::conditional <
            Comp<typename tl :: head> :: value,
            typename tl :: head, 
            typename next::type
        > :: type
    >;
};

/**
 * Specialization to end recursion.
 */
template<template<typename>class Comp>
struct find <_private::_sentinel, Comp>{
    using type = find_result< _private::_sentinel> ;
};

/**
 * General case for find result.
 */
template<typename T>
struct find_result {
    enum { valid = true };
    using type = T;  
};

/**
 * Specialization for no result.
 */
template<>
struct find_result<_private::_sentinel> {
    enum { valid = false };
    using type = _private::_sentinel;  
};

}

#endif//__typelist_algorithm_find_h__
