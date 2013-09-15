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
#ifndef __tst_equals_test__hpp__
#define __tst_equals_test__hpp__

#include "list.h"
#include "algorithm.h"

using namespace typelist;

TEST(equal_tests, TestEqualsSimple) {
    auto value = (bool) equal< list<int>, list<int> >::value;
    EXPECT_TRUE(value);
    
    value = (bool) equal< list<char>, list<int> >::value;
    EXPECT_FALSE(value);

    struct foo { int i; };
    value = (bool) equal< list<foo>, list<int> >::value;
    EXPECT_FALSE(value);

    value = (bool) equal< list<int, int>, list<int> >::value;
    EXPECT_FALSE(value);
}

TEST(equal_tests, TestFlattenedLists) {
    auto value = (bool) equal< list<int>, list<list<list<int>>> >::value;
    EXPECT_TRUE(value);

    value = (bool) equal< list<int, list<char>, double>, list<int, list<char, list<double>>> >::value;
    EXPECT_TRUE(value);

    value = (bool) equal< list<list<int>, list<char>, double>, list<int, list<char, list<double>>> >::value;
    EXPECT_TRUE(value);

    value = (bool) equal< list<list<int>, list<char>, list<double>>, list<int, list<char, list<double>>> >::value;
    EXPECT_TRUE(value);
}

#endif//__tst_equals_test__hpp__
