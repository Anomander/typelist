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
#ifndef __typelist_algorithm_erase_h__
#define __typelist_algorithm_erase_h__

#include "_private.h"

namespace typelist {

/**
 * Removes the first occurence of the provided type from the list.
 */
template<typename T, typename TL> struct erase;

/**
 * Specialization for the case when the head of the list
 * is equal to the erased element and should be removed.
 */
template<typename T, typename... Tail>
struct erase <T, list <T, Tail...>> {
    using type = typename list<T, Tail...> :: tail;
};

/**
 * Recursive specialization for the case when the head
 * should not be removed.
 */
template<typename T, typename Head, typename... Tail >
struct erase <T, list <Head, Tail...>> {
    using type = typename _private::_make_list <
        Head, 
        typename erase <
            T, 
            typename list <Head, Tail...> :: tail
        > :: type
    > :: type;
};

/**
 * Specialization to end recursion.
 */
template<typename T>
struct erase <T, _private::_sentinel> {
    using type = _private::_sentinel;
};

/**
 * Removes all occurences of the provided type from the list.
 */
template<typename T, typename TL> struct erase_all;

/**
 * Specialization for the case when the head of the list
 * is equal to the erased element and should be removed.
 * Recurses to the tail to remove the rest.
 */
template<typename T, typename... Tail>
struct erase_all <T, list <T, Tail...>> {
    using type = typename erase_all <T, typename list<T, Tail...> :: tail> :: type;
};

/**
 * Recursive specialization for the case when the head
 * should not be removed.
 */
template<typename T, typename Head, typename... Tail >
struct erase_all <T, list <Head, Tail...>> {
    using type = typename _private::_make_list <
        Head, 
        typename erase_all <
            T, 
            typename list <Head, Tail...> :: tail
        > :: type
    > :: type;
};

/**
 * Specialization to end recursion.
 */
template<typename T>
struct erase_all <T, _private::_sentinel> {
    using type = _private::_sentinel;
};

}

#endif//__typelist_algorithm_erase_h__
