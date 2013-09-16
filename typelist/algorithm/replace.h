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
#ifndef _typelist_algorithm_replace_h__
#define _typelist_algorithm_replace_h__

#include "typelist/algorithm/erase.h"
#include "typelist/_private.h"

#include <type_traits>

namespace typelist {

/**
 * Replaces first occurence of the provided type T
 * with type U.
 * Stable, i.e. does not change the relative order 
 * of items.
 */
template <typename T, typename U, typename TL> struct replace;

/**
 * Replaces every occurence of the provided type T
 * with type U.
 * Stable, i.e. does not change the relative order 
 * of items.
 */
template <typename T, typename U, typename TL> struct replace_all;

/**
 * General case.
 * Types do not match, recurse further.
 */
template <typename T, typename U, typename Head, typename... Tail>
struct replace<T, U, list<Head, Tail...>> {
    using type = typename _private :: _make_list <
        Head, 
        typename replace <
            T, U,
            typename list<Head, Tail...>::tail
        > :: type
    > :: type;
};

/**
 * Type is found, replace.
 */
template <typename T, typename U, typename... Tail>
struct replace<T, U, list<T, Tail...>> {
    using type = typename _private :: _make_list <
        U, 
        typename list<T, Tail...> :: tail 
    > :: type;
};

/**
 * General case.
 * Types do not match, recurse further.
 */
template <typename T, typename U, typename Head, typename... Tail>
struct replace_all<T, U, list<Head, Tail...>> {
    using type = typename _private :: _make_list <
        Head, 
        typename replace_all <
            T, U,
            typename list<T, Tail...> :: tail 
        > :: type 
    > :: type;
};

/**
 * Type is found, replace.
 */
template <typename T, typename U, typename... Tail>
struct replace_all<T, U, list<T, Tail...>> {
    using type = typename _private :: _make_list <
        U, 
        typename replace_all <
            T, U,
            typename list<T, Tail...> :: tail 
        > :: type 
    > :: type;
};

/**
 * Specialization to end recursion.
 */
template <typename T, typename U>
struct replace<T, U, _private::_sentinel> {
    using type = _private::_sentinel;
};

/**
 * Specialization to end recursion.
 */
template <typename T, typename U>
struct replace_all<T, U, _private::_sentinel> {
    using type = _private::_sentinel;
};

}

#endif//_typelist_algorithm_replace_h__
