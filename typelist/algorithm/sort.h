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
template<typename TL, template<typename,typename>class Comp> struct min;

/**
 * Sorts the provided list in the ascending order,
 * using the provided comparison operation.
 * Comparison should be defined as:
 *
 * template <typename T, typename U>
 * struct Compare {
 *     enum {
 *         value = [non-0 means less];// like sizeof(T) < sizeof(U)
 *     };
 * };
 *
 * Stable, i.e. does not change the relative order of equal 
 * items.
 *
 * NOTE: Sort will not fuction properly if the list contains
 *       heterogenous items relative to the comparison 
 *       operation used, i.e. items that can't directly be
 *       compared (e.g. classes from different heirarchy 
 *       branches, if using std::is_base_of as comparator).
 * 
 * Sort is O(n^2).
 */
template <typename TL, template<typename,typename>class Comp> struct sort;

/**
 * General case.
 * Finds the smallest element and removes from the list.
 * Places the element in the head of the result.
 * Recurses to sort the remainder and appends it as tail.
 */
template <typename TL, template<typename,typename>class Comp>
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
template <template<typename,typename>class Comp>
struct sort<_private::_sentinel, Comp> {
    using type = _private::_sentinel;
};

/**
 * General case.
 * Compares the head and recurses into the tail.
 */
template<typename Head, typename... Tail, template<typename,typename>class Comp>
struct min<list<Head, Tail...>, Comp> {
private:
    using TL = list<Head, Tail...>;
    using next = typename min <typename TL :: tail, Comp> :: type;
public:
    using type = typename std::conditional <
        Comp<typename TL :: head, next> :: value 
           || ! Comp<next, typename TL :: head> :: value,
        typename TL :: head, 
        next
    > :: type;
};

/**
 * Specialization to end recursion.
 */
template<typename T, template<typename,typename>class Comp>
struct min <list<T>, Comp> {
    using type = T;
};


}

#endif//__typelist_algorithm_sort_h__
