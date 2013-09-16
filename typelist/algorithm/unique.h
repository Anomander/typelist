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
#ifndef _typelist_algorithm_unique_h__
#define _typelist_algorithm_unique_h__

#include "typelist/algorithm/erase.h"
#include "typelist/_private.h"

#include <type_traits>

namespace typelist {

/**
 * Removes the second and all subsequent entries 
 * of each type the provided list. Does not require
 * a sorted list.
 * Stable, i.e. does not change the relative order 
 * of remaining items.
 */
template <typename TL> struct unique;

/**
 * General case.
 */
template <typename Head, typename... Tail>
struct unique<list<Head, Tail...>> {
    using type = typename _private :: _make_list <
        Head, 
        typename unique <
            typename erase_all< 
                Head, 
                typename list<Head, Tail...> :: tail 
            > :: type 
        > :: type
    > :: type;
};

/**
 * Specialization to end recursion.
 */
template <>
struct unique<_private::_sentinel> {
    using type = _private::_sentinel;
};

}

#endif//_typelist_algorithm_unique_h__
