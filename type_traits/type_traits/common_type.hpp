//
//  common_type.hpp
//  type_traits
//
//  Created by Jack Zou on 2017/9/16.
//  Copyright © 2017年 jack.zou. All rights reserved.
//

#ifndef common_type_h
#define common_type_h

#include <type_traits>

namespace unique_cpp {
    template<class ...T> struct common_type;
    
    template<class T>
    struct common_type<T> {
        typedef typename std::decay<T>::type type;
    };
    
    template<class T, class U>
    struct common_type<T, U>{
    private:
        static T&& t();
        static U&& u();
        static bool f();
    public:
        typedef typename std::decay<decltype(f() ? t() : u())>::type type;
    };
    
    template<class T, class U, class ...V>
    struct common_type<T, U, V...> {
        typedef typename common_type<typename common_type<T, U>::type, V...>::type type;
    };
}


#endif /* common_type_h */
