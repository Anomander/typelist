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
#ifndef __typelist_algorithm_reverse_h__
#define __typelist_algorithm_reverse_h__

#include "typelist/_private.h"

namespace typelist {

/**
 * Reverses the provided list.
 * Result is the list containing the same elements
 * in reverse order.
 */
template <typename TL> struct reverse;

/**
 * General case.
 * Recurses to reverse the tail, then appends
 * the head at the end.
 */
template<typename Head, typename... Tail>
struct reverse<list<Head, Tail...>> {
    using type = typename _private::_make_list< 
        typename reverse < 
            typename list <Head, Tail...> :: tail
        > :: type, 
        Head
    > :: type;
};

/**
 * Specialization to end recursion.
 */
template<>
struct reverse<_private::_sentinel> {
    using type = _private::_sentinel;
};

}

#endif//__typelist_algorithm_reverse_h__
