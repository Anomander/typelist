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
#ifndef __typelist_algorithm_sort_h__
#define __typelist_algorithm_sort_h__

#include <type_traits>

namespace typelist {

/**
 * Returns the type that is the smallest from
 * the provided list when a provided comparison
 * operation is applied.
 */
template<typename TL, typename Comp> struct min;

/**
 * Sorts the provided list in the ascending order,
 * using the provided comparison operation.
 * Comparison should be defined as:
 *
 * struct Compare {
 *     template <typename T, typename U>
 *     struct less {
 *     enum {
 *         value = [non-0 means less];// like sizeof(T) < sizeof(U)
 *     };
 * };
 */
template <typename TL, typename Comp> struct sort;

/**
 * General case.
 * Finds the smallest element and removes from the list.
 * Places the element in the head of the result.
 * Recurses to sort the remainder and appends it as tail.
 *
 * Sort is O(n^2).
 */
template <typename TL, typename Comp>
struct sort {
private:
    using smallest = typename min < TL, Comp > :: type;
public:
    using type = list <
        smallest, 
        typename sort<typename erase< smallest, TL > :: type, Comp> :: type
    >;
};

/**
 * Specialization to end recursion.
 */
template <typename Comp>
struct sort<_private::_sentinel, Comp> {
    using type = _private::_sentinel;
};

/**
 * General case.
 * Compares the head and recurses into the tail.
 */
template<typename Head, typename... Tail, typename Comp>
struct min<list<Head, Tail...>, Comp> {
private:
    using TL = list<Head, Tail...>;
    using next = typename min <typename TL :: tail, Comp> :: type;
public:
    using type = typename std::conditional <
        Comp :: template less<typename TL :: head, next> :: value || ! Comp :: template less<next, typename TL :: head> :: value,
        typename TL :: head, 
        next
    > :: type;
};

/**
 * Specialization to end recursion.
 */
template<typename T, typename Comp>
struct min <list<T>, Comp> {
    using type = T;
};


}

#endif//__typelist_algorithm_sort_h__
