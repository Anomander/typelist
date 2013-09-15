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
#ifndef __typelist_utility_h__
#define __typelist_utility_h__

#include "_private.h"

/**
 * Utilities for working with lists.
 */
namespace typelist {

/**
 * Returns the number of elements in the list.
 */
template <typename TL> struct length;

/**
 * Specialization for the general case.
 * Calculates the length of the tail and adds 1.
 */
template <typename T, typename... Args>
struct length< list<T, Args...> > {
    enum {
        value = length<typename list<T, Args...> :: tail> :: value + 1
    };
};

/**
 * Specialization to end recursion.
 */
template <>
struct length<_private::_sentinel> {
    enum {
        value = 0
    };
};

}

#endif//__typelist_utility_h__
