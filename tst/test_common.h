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
#ifndef __tst_test_common_h__
#define __tst_test_common_h__

#include "typelist/list.h"
#include "typelist/utility.h"
#include "typelist/algorithm.h"

 #include <typeinfo>
 #include <memory>
 #include <cxxabi.h>

using namespace typelist;

namespace test_helpers {
    template <typename T, typename U>
    struct CompareBySize {
        enum {
            value = sizeof(T) < sizeof(U)
        };
    };

    struct PairWithSame {
        template<typename T>
        using type = std::pair<T,T>;  
    };

    template<typename T>
    struct TypeDemangler {
        static std::string demangle() {
            const char* name = typeid(T).name();
            int status = -4; // some arbitrary value to eliminate the warning

            // enable c++11 by passing the flag -std=c++11 to g++
            std::unique_ptr<char, void(*)(void*)> res {
                abi::__cxa_demangle(name, NULL, NULL, &status),
                std::free
            };

            return (status==0) ? res.get() : name ;
        }
    };

    struct Iterator {
        template<typename T>
        static void run (std::vector<std::string>& vec) {
            vec.push_back(TypeDemangler<T>::demangle());
        }
    };

    template<typename T>
    struct GreaterThan4Bytes {
        enum { value = sizeof(T) > 4 };  
    };
    template<typename T>
    struct LessThan4Bytes {
        enum { value = sizeof(T) < 4 };  
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

#endif//__tst_test_common_h__
