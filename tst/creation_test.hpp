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
#ifndef __tst_creation_test_hpp__
#define __tst_creation_test_hpp__

#include "test_common.h"

TEST(creation_tests, TestSimpleCreate) {
    using l0 = list <int>;
    EXPECT_EQ(1, length<l0>::value);
    auto same = std::is_same<l0::head, int>::value;
    EXPECT_TRUE(same);

    using l1 = list <int, char>;
    EXPECT_EQ(2, length<l1>::value);
    same = std::is_same<l1::head, int>::value;
    EXPECT_TRUE(same);
    same = std::is_same<l1::tail::head, char>::value;
    EXPECT_TRUE(same);
}

TEST(creation_tests, TestFlattening) {
    using l0 = list <list<int>>;
    EXPECT_EQ(1, length<l0>::value);
    auto same = std::is_same<l0::head, int>::value;
    EXPECT_TRUE(same);

    using l1 = list <list<int, char>>;
    EXPECT_EQ(2, length<l1>::value);
    same = std::is_same<l1::head, int>::value;
    EXPECT_TRUE(same);
    same = std::is_same<l1::tail::head, char>::value;
    EXPECT_TRUE(same);

    using l2 = list <list<list<int, char>>>;
    EXPECT_EQ(2, length<l2>::value);
    same = std::is_same<l2::head, int>::value;
    EXPECT_TRUE(same);
    same = std::is_same<l2::tail::head, char>::value;
    EXPECT_TRUE(same);
}

TEST(creation_tests, TestAppending) {
    using l0 = list <list<int>, int>;
    EXPECT_EQ(2, length<l0>::value);
    auto same = std::is_same<l0::head, int>::value;
    EXPECT_TRUE(same);
    same = std::is_same<l0::tail::head, int>::value;
    EXPECT_TRUE(same);
}

TEST(creation_tests, TestPrepending) {
    using l0 = list <int, list<int>>;
    EXPECT_EQ(2, length<l0>::value);
    auto same = std::is_same<l0::head, int>::value;
    EXPECT_TRUE(same);
    same = std::is_same<l0::tail::head, int>::value;
    EXPECT_TRUE(same);
}

#endif//__tst_creation_test_hpp__
