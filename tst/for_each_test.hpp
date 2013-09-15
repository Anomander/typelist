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
#ifndef __tst_for_each_test_hpp__
#define __tst_for_each_test_hpp__

#include "list.h"
#include "algorithm.h"

#include <typeinfo>
#include <memory>
#include <cxxabi.h>

using namespace typelist;

using for_each_list = list <int, char, float, double, list<long long, long>>;

namespace ForEachHelpers {
    struct Iterator {
    private:
        static std::string demangle(const char* name) {
            int status = -4; // some arbitrary value to eliminate the compiler warning

            // enable c++11 by passing the flag -std=c++11 to g++
            std::unique_ptr<char, void(*)(void*)> res {
                abi::__cxa_demangle(name, NULL, NULL, &status),
                std::free
            };

            return (status==0) ? res.get() : name ;
        }
    public:
        template<typename T>
        static void run (std::vector<std::string>& vec) {
            vec.push_back(demangle(typeid(T).name()));
        }
    };
}

TEST(for_each_tests, SimpleTest) {
    std::vector<std::string> v;
    for_each <for_each_list> :: run <ForEachHelpers::Iterator> (std::ref(v));
    EXPECT_EQ(v.size(), length<for_each_list>::value);
    EXPECT_EQ("int", v[0]);
    EXPECT_EQ("char", v[1]);
    EXPECT_EQ("float", v[2]);
    EXPECT_EQ("double", v[3]);
    EXPECT_EQ("long long", v[4]);
    EXPECT_EQ("long", v[5]);
}

TEST(for_each_tests, TestEmpty) {
    std::vector<std::string> v;
    for_each <erase<int, list<int>>::type> 
    :: run <ForEachHelpers::Iterator> (std::ref(v));
    EXPECT_EQ(0, v.size());
}

#endif//__tst_for_each_test_hpp__
