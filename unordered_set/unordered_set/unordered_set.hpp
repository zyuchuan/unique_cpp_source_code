//
//  unordered_set.hpp
//  unordered_set
//
//  Created by Jack Zou on 2017/10/1.
//  Copyright © 2017年 jack.zou. All rights reserved.
//

#ifndef unordered_set_h
#define unordered_set_h

namespace unique_cpp {

    template<class Value, class Hash = std::hash<Value>, class Pred = std::equal_to<Value>, class Alloc = std::allocator<Value> >
    class unordered_set {
    public:
        typedef Value               key_type;
        typedef key_type            value_type;
        typedef Hash                hasher;
        typedef Pred                key_equal;
        typedef Alloc               allocator_type;
        typedef value_type&         reference;
        typedef const value_type&   const_reference;
        
    private:
        typedef std::__hash_table<value_type, hasher, key_equal, allocator_type> __table;
        
        __table __table_;
    };
}


#endif /* unordered_set_h */
