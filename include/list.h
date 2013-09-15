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
#ifndef __typelist_list_h__
#define __typelist_list_h__

#include "_private.h"

namespace typelist {

/**
 * Compile-time list of types.
 * Head refers to the current type.
 * Tail refers to the list of the rest of the types.
 */
template<typename T, typename... Args> struct list {
    using head = T;
    using tail = typename _private::_make_list <Args...> :: type;
};

/**
 * Single element specialization.
 */
template<typename T>
struct list<T> {
    using head = T;
    using tail = _private::_sentinel;
};

/**
 * Prepending specialization.
 * Passed argument becomes the head of this list and
 * passed list becomes the tail.
 */
template<typename T, typename U, typename... Args>
struct list<T, list <U, Args...>> {
    using head = T;
    using tail = typename _private::_make_list<U, Args...> :: type;
};

/**
 * Copy specialization.
 */
template<typename U, typename... Args>
struct list<list <U, Args...>> {
    using head = typename list <U, Args...> :: head;
    using tail = typename list<U, Args...> :: tail;
};

/**
 * Appending specialization.
 * Head of the passed list becomes the head of this list
 * and the rest of the arguments are appended after the
 * last element of the passed list.
 */
template<typename U, typename... TLArgs, typename... Args>
struct list<list <U, TLArgs...>, Args...> {
    using head = typename list <U, TLArgs...> :: head;
    using tail = typename _private::_make_list<typename list <U, TLArgs...> :: tail, Args...> :: type;
};

}

#endif//__typelist_list_h__
