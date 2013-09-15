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
#ifndef __typelist_algorithm_for_each_h__
#define __typelist_algorithm_for_each_h__

#include "_private.h"

namespace typelist {

/**
 * Cycles through the list and runs the provided operation
 * on each element.
 * The operation should be defined as:
  *   
 * struct Iterator { 
  *   template<typename Type, typename Arg0, typename Arg1, typename... ArgN > 
  *   static void run (Arg0 arg0, Arg1 arg1, ArgN... argn) { 
  *       // Do stuff;
  *   } 
 * };
 *
 * The parameters required by the method `run` should match those
 * that will be passed to
 *
 * for_each <the_list> :: run <Iterator> (arg0, arg1, arg2, arg3 [, ...]);
 */
template <typename T> struct for_each;

/**
 * General case.
 * Runs the operation on the head and recurses into the tail.
 */
template <typename T, typename... TLArgs>
struct for_each <list <T, TLArgs...> > {
private:
    using TL = list <T, TLArgs...>;
public:
    template <typename Iterator, typename... Args>
    static void run (Args... args) {
        Iterator :: template run <typename TL :: head>(args...);
        for_each <typename TL :: tail> :: template run <Iterator>(args...);
    }
};

/**
 * Specialization to end recursion.
 */
template <>
struct for_each <_private::_sentinel> {
    template <typename Iterator, typename... Args>
    static void run (Args... args) {}
};

}

#endif//__typelist_algorithm_for_each_h__
