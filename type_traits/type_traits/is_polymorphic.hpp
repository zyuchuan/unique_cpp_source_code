//
//  is_polymorphic.hpp
//  CppTest
//
//  Created by Jack Zou on 2017/9/5.
//  Copyright © 2017年 jack.zou. All rights reserved.
//

#ifndef is_polymorphic_h
#define is_polymorphic_h

#include <type_traits>

namespace unique_cpp {
    template<class T> char& is_polymorphic_impl(
                                                typename std::enable_if<sizeof((T*)dynamic_cast<const volatile void*>(T())) != 0, int>::type);
    
    template<class T> std::__two& is_polymorphic_impl(...);
    
    template<class T> struct is_polymorphic : public std::integral_constant<bool, sizeof(is_polymorphic_impl<T>(0)) == 1> {};
}


#endif /* is_polymorphic_h */
