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
#ifndef __tst_sort_test_hpp__
#define __tst_sort_test_hpp__

#include "list.h"
#include "algorithm.h"

using namespace typelist;
struct foo {};
struct bar { int i; };

using sort_test_list = list <
    long long, bar, char, int, double, foo, char, float, long, foo, int, bar
>;

namespace Sorts {
    struct CompareBySize {
        template <typename T, typename U>
        struct less {
            enum {
                value = sizeof(T) < sizeof(U)
            };
        };
    };
}

TEST(sort_tests, SimpleTest) {
    using f = sort < sort_test_list, Sorts::CompareBySize >::type;
    EXPECT_EQ(length<sort_test_list>::value, length<f>::value);
    bool eq = equal<
        f, 
        list<
        char, foo, char, foo, bar, int, float, int, bar, long long, double, long 
        >
    >::value;
    EXPECT_TRUE(eq);
}

TEST(sort_tests, SortEmpty) {
    using f = sort < 
        erase <int, list<int>>::type, 
        Sorts::CompareBySize
    >::type;
    EXPECT_EQ(0, length<f>::value);
}

#endif//__tst_sort_test_hpp__
