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
#ifndef __tst_replace_test_hpp__
#define __tst_replace_test_hpp__

#include "test_common.h"

TEST(replace_tests, TestSingleElement) {
    using list1 = replace <
        int, char, list <int>
    > ::type;

    EXPECT_EQ(1, length<list1>::value);
    bool equals = equal<
        list1, 
        list<char>
    >::value;
    EXPECT_EQ(true, equals);
    
    using list2 = replace_all <
        int, char, list <int>
    > ::type;

    EXPECT_EQ(1, length<list2>::value);
    equals = equal<
        list2, 
        list<char>
    >::value;
    EXPECT_EQ(true, equals);
}

TEST(replace_tests, TestFirstElement) {
    using list1 = replace <
        int, char, list <int, double>
    > ::type;
    EXPECT_EQ(2, length<list1>::value);
    bool equals = equal<
        list1, 
        list<char, double>
    >::value;
    EXPECT_EQ(true, equals);
    
    using list2 = replace_all <
        int, char, list <int, double>
    > ::type;
    EXPECT_EQ(2, length<list2>::value);
    equals = equal<
        list2, 
        list<char, double>
    >::value;
    EXPECT_EQ(true, equals);
}

TEST(replace_tests, TestNonFirstElement) {
    using list1 = replace <
        int, char, list <float, int, double>
    > ::type;
    EXPECT_EQ(3, length<list1>::value);
    bool equals = equal<
        list1, 
        list<float, char, double>
    >::value;
    EXPECT_EQ(true, equals);
    
    using list2 = replace_all <
        int, char, list <float, int, double>
    > ::type;
    EXPECT_EQ(3, length<list2>::value);
    equals = equal<
        list2, 
        list<float, char, double>
    >::value;
    EXPECT_EQ(true, equals);
}

TEST(replace_tests, TestCascading) {
    using list1 = replace <
        int, char,
        replace <
            int, double,
            list <int, int>
        > ::type
    > ::type;
    EXPECT_EQ(2, length<list1>::value);
    bool equals = equal <
        list1, 
        list<double, char>
    >::value;
    EXPECT_EQ(true, equals);
}

#endif//__tst_replace_test_hpp__
