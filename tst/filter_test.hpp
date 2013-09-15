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
#ifndef __tst_filter_test_hpp__
#define __tst_filter_test_hpp__

#include "list.h"
#include "algorithm.h"

using namespace typelist;

using filter_test_list = list <int, char, float, double, list<long long, long>>;

namespace Filters {
    template<typename T>
    struct FilterLessThan4 {
        enum { value = sizeof(T) < 4 };  
    };

    template<typename T>
    struct NoneShallPassMe {
        enum { value = false };
    };
}
TEST(filter_tests, SimpleTest) {
    using f = filter <filter_test_list, Filters::FilterLessThan4>::type;
    EXPECT_EQ(1, length<f>::value);
    bool eq = equal<f, list<char>>::value;
    EXPECT_TRUE(eq);
}

TEST(filter_tests, FilterEmpty) {
    using f = filter <filter_test_list, Filters::NoneShallPassMe>::type;
    EXPECT_EQ(0, length<f>::value);
}

TEST(filter_tests, FilterOnEmptyList) {
    using f = filter <filter_test_list, Filters::NoneShallPassMe>::type;
    EXPECT_EQ(0, length<f>::value);

    using f2 = filter <f, Filters::FilterLessThan4>::type;
    EXPECT_EQ(0, length<f2>::value);
}

#endif//__tst_filter_test_hpp__
