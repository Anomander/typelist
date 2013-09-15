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
#ifndef __typelist_algorithm_map_h__
#define __typelist_algorithm_map_h__

#include "_private.h"

namespace typelist {

/**
 * Provides the ability to create a type list from
 * another by mapping elements of the original list
 * to elements of the new ones.
 * The mapping should be defined as follows:
 * 
 * struct Mapper { 
 *     template<typename T> 
 *     using type = [mapped_type]; // like std::pair<T,T>
 * };
 */
template<typename TL, typename Conv>
struct map;

/**
 * General case.
 * Maps the head and recurses to the tail.
 */
template<typename C, typename T, typename... Args>
struct map <list<T, Args...>, C> {
private:
    using next = 
        typename map <typename list<T, Args...> :: tail, C> :: type;
public:
    using type = typename _private::_make_list < 
        typename _private::_make_list < typename C::template type<T>, next > :: type
    > :: type;
};

/**
 * Specialization to end recursion.
 */
template<typename C>
struct map <_private::_sentinel, C> {
    using type = _private::_sentinel;
};

}

#endif//__typelist_algorithm_map_h__
