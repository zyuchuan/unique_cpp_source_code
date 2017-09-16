//
//  is_function.hpp
//  type_traits
//
//  Created by Jack Zou on 2017/9/16.
//  Copyright © 2017年 jack.zou. All rights reserved.
//

#ifndef is_function_h
#define is_function_h

#include <type_traits>

namespace unique_cpp {
    
    struct two { char lx[2];};
    
    struct dummy_type{};
    
    template<class T> char test(T*);
    template<class T> char test;
    template<class T> two test(...);
    template<class T> T& source(int);
    template<class T> dummy_type source(...);
    
    template<class T, bool = std::is_class<T>::value ||
    std::is_union<T>::value     ||
    std::is_void<T>::value      ||
    std::is_reference<T>::value ||
    __is_nullptr_t<T>::value>
    struct libcpp_is_function : public std::integral_constant<bool, sizeof(test<T>(source<T>(0))) == 1> {};
    
    template<class T> struct libcpp_is_function<T, true> : public std::false_type{};
    
    template<class T> struct is_function : public libcpp_is_function<T>{};
}


#endif /* is_function_h */
