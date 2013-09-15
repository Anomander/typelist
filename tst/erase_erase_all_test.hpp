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
#ifndef __tst_erase_erase_all_test_hpp__
#define __tst_erase_erase_all_test_hpp__

#include "list.h"
#include "algorithm.h"

using namespace typelist;

using test_list = list <int, char, int, float, double, list<long long, long>>;

TEST(erase_tests, TestEraseOneElement) {
    EXPECT_EQ(7, length<test_list>::value);

    // erase the first int, second should still be present
    using list1 = typename erase <int, test_list> ::type;
    EXPECT_EQ(6, length<list1>::value);
    bool equals = equal<
        list1, 
        list<char, int, float, double, list<long long, long>>
    >::value;
    EXPECT_EQ(true, equals);
    
    // erase the second int
    using list2 = typename erase <int, list1> ::type;
    EXPECT_EQ(5, length<list2>::value);
}

TEST(erase_tests, TestCascadingErase) {
    EXPECT_EQ(7, length<test_list>::value);

    // erase the first int, second should still be present
    using list1 = typename erase <int, test_list> ::type;
    EXPECT_EQ(6, length<list1>::value);
    
    // erase the second int
    using list2 = typename erase <int, list1> ::type;
    EXPECT_EQ(5, length<list2>::value);
    
    // erase both ints
    using list3 = 
        typename erase <int, 
            typename erase <int, 
                test_list
            > ::type
        > ::type;
    EXPECT_EQ(5, length<list3>::value);
}

TEST(erase_tests, TestErasePreservesOrder) {
    EXPECT_EQ(7, length<test_list>::value);

    // erase the first int, second should still be present
    using list1 = typename erase <int, test_list> ::type;
    EXPECT_EQ(6, length<list1>::value);
    bool equals = equal<
        list1, 
        list<char, int, float, double, list<long long, long>>
    >::value;
    EXPECT_EQ(true, equals);
    
    // erase the second int
    using list2 = typename erase <int, list1> ::type;
    EXPECT_EQ(5, length<list2>::value);
    equals = equal <
        list2, 
        list<char, float, double, list<long long, long>>
    >::value;
    EXPECT_EQ(true, equals);
}

TEST(erase_all_tests, SimpleTest) {
    EXPECT_EQ(7, length<test_list>::value);

    using list1 = typename erase_all <int, test_list> ::type;
    EXPECT_EQ(5, length<list1>::value);
    bool equals = equal<
        list1, 
        list<char, float, double, list<long long, long>>
    >::value;
    EXPECT_EQ(true, equals);
}

TEST(erase_all_tests, TestEraseAllPreservesOrder) {
    using l = list<int, char, int, double, int, float, int, long, int, long long>;

    using list1 = typename erase_all <int, l> ::type;
    EXPECT_EQ(5, length<list1>::value);
    bool equals = equal <
        list1, 
        list<char, double, float, long, long long>
    >::value;
    EXPECT_EQ(true, equals);
}

#endif//__tst_erase_erase_all_test_hpp__
