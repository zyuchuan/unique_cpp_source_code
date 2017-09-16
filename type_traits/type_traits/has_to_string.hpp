//
//  has_to_string.hpp
//  type_traits
//
//  Created by Jack Zou on 2017/9/16.
//  Copyright © 2017年 jack.zou. All rights reserved.
//

#ifndef has_to_string_h
#define has_to_string_h

#include <string>
#include <type_traits>
#include <unordered_map>

namespace unique_cpp {
    
    template<typename T, typename = std::string>
    struct has_to_string : std::false_type {
        
    };
    
    template<typename T>
    struct has_to_string<T, decltype(std::declval<T>().to_string())> : public std::true_type {
        
    };
}


#endif /* has_to_string_h */
