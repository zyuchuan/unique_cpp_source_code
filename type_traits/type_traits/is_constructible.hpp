//
//  is_constructible.hpp
//  CppTest
//
//  Created by Jack Zou on 2017/9/5.
//  Copyright © 2017年 jack.zou. All rights reserved.
//

#ifndef is_constructible_h
#define is_constructible_h

#include <type_traits>

namespace unique_cpp {
    
    template<class T, class ...Args>
    typename std::__select_2nd<decltype(std::move(T(std::declval<Args>()...))), std::true_type>::type
    is_constructible_test(T&&, Args&&...);
    
    template<class ...Args>
    std::false_type is_constructible_test(std::__any, Args&& ...);
    

    template<bool, class T, class ...Args>
    struct libcpp_is_constructible : public std::common_type<decltype(is_constructible_test(declval<T>(), declval<Args>()...))>::type {};


    // function types are not constructible
    template<class R, class... A1, class...A2>
    struct libcpp_is_constructible<false, R(A1...), A2...> : public std::false_type {};

    // scalars are default constructible, references are not
    template<class T>
    struct libcpp_is_constructible<true, T> : public std::is_scalar<T> {};

    // Scalars and references are constructible from one arg if that arg is
    // implicitly convertible to the scalar or reference.
    template<class T>
    struct is_constructible_ref {
        std::true_type static lxx(T);
        std::false_type static lxx(...);
    };

    template<class T, class A0>
    struct libcpp_is_constructible<true, T, A0> : public std::common_type<decltype(is_constructible_ref<T>::lxx(declval<A0>()))>::type {};

    // Scalars and references are not constructible from multiple args.
    template<class T, class A0, class... Args>
    struct libcpp_is_constructible<true, T, A0, Args...> : public std::false_type {};
    
    template<bool, class T, class... Args>
    struct is_constructible_void_check : public libcpp_is_constructible<std::is_salar<T>::value || std::is_reference<T>::value, T, Args...>{};

    template<class T, class... Args>
    struct is_constructible_void_check<true, T, Args...> : public std::false_type {};

    template<class ...Args> struct contains_void;

    template<> struct contains_void<> : std::false_type{};

    template<class A0, class ...Args>
    struct contains_void<A0, Args...> {
        static const bool value = std::is_void<A0>::value || contains_void<Args...>::value;
    };

    template<class T, class... Args>
    struct is_constructible : public is_constructible_void_check<contains_void<T, Args...>::value || std::is_abstract<T>::value, T, Args...>{};
}

#endif /* is_constructible_h */
