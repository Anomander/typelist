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
#ifndef __typelist__private_h__
#define __typelist__private_h__

#include <type_traits>

namespace typelist {
// Forward declaration of list.
template<typename, typename...> struct list;

/**
 * These are private utility classes which are
 * not supposed for external use.
 */
namespace _private {

/**
 * Signals the end of the list.
 * Should not be exposed to the users of the 
 * library.
 */
struct _sentinel { ~_sentinel() = delete; };

/**
 * Utility for list creations. Handles various
 * conditions that might otherwise result in
 * creating a bad list.
 */
template<typename T, typename... Args>
struct _make_list {
private:
    using tail = typename _make_list<Args..., _sentinel> :: type;
public:
    using type = typename std::conditional <
        std :: is_same<_sentinel, tail> :: value,
        list<T>,
        list<T, tail>
    > :: type;
};

/**
 * Appending specialization.
 */
template<typename Head, typename... Tail, typename... Args>
struct _make_list<list<Head, Tail...>, Args...> {
    using type = typename _make_list<Head, Tail..., Args...> :: type;
};

/**
 * Specialization that skips leading sentinel.
 */
template<typename... Args>
struct _make_list<_sentinel, Args...> {
    using type = typename _make_list<Args...> :: type;
};

/**
 * Specialization to end recursion.
 */
template<>
struct _make_list<_sentinel> {
    using type = _sentinel;
};

/**
 * Returns the head of a list or a sentinel.
 */
template<typename> struct _head;

/**
 * Specialization for sentinel.
 */
template<>
struct _head<_private::_sentinel> {
    using type = _private::_sentinel;
};

/**
 * Specialization for the general case.
 */
template<typename T, typename... Args>
struct _head<list<T, Args...>> {
    using type = typename list<T, Args...> :: head;
};

/**
 * Returns the tail of a list or a sentinel.
 */
template<typename> struct _tail;

/**
 * Specialization for sentinel.
 */
template<>
struct _tail<_private::_sentinel> {
    using type = _private::_sentinel;
};

/**
 * Specialization for the general case.
 */
template<typename T, typename... Args>
struct _tail<list<T, Args...>> {
    using type = typename _private::_make_list<T, Args...> :: type :: tail;
};

} // namespace _private
} // namespace typelist

#endif//__typelist__private_h__
