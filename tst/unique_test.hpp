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
#ifndef __tst_unique_test_hpp__
#define __tst_unique_test_hpp__

#include "test_common.h"

TEST(unique_tests, SimpleTest) {
    using f = unique < 
        list <
            long long, char, int, double, char, float, long, int
        >
    >::type;
    EXPECT_EQ(6, length<f>::value);
    bool eq = equal<
        f, 
        list<
            long long, char, int, double, float, long
        >
    >::value;
    EXPECT_TRUE(eq);
}

TEST(unique_tests, TestSingleType) {
    using f = unique < 
        list<
            int, int, int, int, int, int
        > 
    >::type;
    EXPECT_EQ(1, length<f>::value);
    bool eq = equal< f, list< int > >::value;
    EXPECT_TRUE(eq);
}

TEST(unique_tests, TestAlternatingTypes) {
    using f = unique < 
        list<
            int, char, int, char, int, char, int, char, int, char, int, char
        > 
    >::type;
    EXPECT_EQ(2, length<f>::value);
    bool eq = equal< f, list< int, char > >::value;
    EXPECT_TRUE(eq);
}

TEST(unique_tests, TestEmpty) {
    using f = unique < 
        erase <int, list<int>>::type
    >::type;
    EXPECT_EQ(0, length<f>::value);
}

#endif//__tst_unique_test_hpp__
