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
#ifndef __tst_find_test_hpp__
#define __tst_find_test_hpp__

#include "list.h"
#include "algorithm.h"

using namespace typelist;

using find_test_list = list <char, double, int, float, list<long long, long>>;

namespace Finders {
    template<typename T>
    struct FindGreaterThan4 {
        enum { value = sizeof(T) > 4 };  
    };
    template<typename T>
    struct NoneShallPassMe {
        enum { value = false };
    };
    template<typename T>
    struct FindInt {
        enum { value = std::is_same<T, int>::value };  
    };
}
TEST(find_tests, SimpleTest) {
    using f = find <find_test_list, Finders::FindInt>::type;
    EXPECT_TRUE(f::valid);
    auto eq = std::is_same<f::type, int>::value;
    EXPECT_TRUE(eq);
}

TEST(find_tests, FindEmpty) {
    using f = find <find_test_list, Finders::NoneShallPassMe>::type;
    EXPECT_FALSE(f::valid);
}

TEST(find_tests, FindOnEmptyList) {
    using f = filter <find_test_list, Finders::NoneShallPassMe>::type;
    EXPECT_EQ(0, length<f>::value);

    using f2 = find <f, Finders::FindInt>::type;
    EXPECT_FALSE(f2::valid);
}

TEST(find_tests, FindReturnsFirstEntry) {
    using f = find <find_test_list, Finders::FindGreaterThan4>::type;
    EXPECT_TRUE(f::valid);
    auto eq = std::is_same<f::type, double>::value;
    EXPECT_TRUE(eq);

    using list2 = typename erase_all <double, find_test_list>::type;

    using f2 = find <list2, Finders::FindGreaterThan4>::type;
    EXPECT_TRUE(f2::valid);
    eq = std::is_same<f2::type, long long>::value;
    EXPECT_TRUE(eq);
}

#endif//__tst_find_test_hpp__
