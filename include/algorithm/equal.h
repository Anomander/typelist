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
#ifndef __typelist_algorithm_equal_h__
#define __typelist_algorithm_equal_h__

#include "_private.h"

#include <utility>

namespace typelist {

/**
 * Compares two provided lists and figures if they are equal.
 * Equality is defined as the same number of the same elements 
 * in the same order.
 */
template<typename TL1, typename TL2> 
struct equal {
    enum { value = false };  
};

/**
 * Recursive specialization.
 * Compares the head and recurses to the tail.
 */
template<typename Head1, typename Head2, typename... Tail1, typename... Tail2>
struct equal<list<Head1, Tail1...>, list<Head2, Tail2...>> {
private:
    using TL1 = list<Head1, Tail1...>;
    using TL2 = list<Head2, Tail2...>;
public:
    enum { value = std::is_same <typename TL1::head, typename TL2::head> ::value
                       && equal <typename TL1::tail, typename TL2::tail> ::value };
};

/**
 * Specialization to end recursion.
 */
template<>
struct equal<_private::_sentinel, _private::_sentinel> {
    enum { value = true };
};
}

#endif//__typelist_algorithm_equal_h__
