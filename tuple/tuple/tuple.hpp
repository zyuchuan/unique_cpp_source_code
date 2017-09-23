//
//  tuple.hpp
//  tuple
//
//  Created by Jack Zou on 2017/9/16.
//  Copyright © 2017年 jack.zou. All rights reserved.
//

#ifndef tuple_h
#define tuple_h

#include <type_traits>

namespace unique_cpp {
    
    // forward declaration
    template<class ...T> template class tuple;
    
    // tuple_size
    template<class ...T>
    class tuple_size<tuple<T...> > : public integral_constant<size_t, sizeof...(T)> {};
    
    // tuple_types
    template<class ...T> struct tuple_types {};
    
    // make_tuple_types
    template<class ... T, size_t End = tuple_size<T...>::value, size_t Start = 0>
    struct make_tuple_types {};
    
    template<class ...T, size_t End>
    struct make_tuple_types<tuple<T...>, End, 0> {
        typedef tuple_types<T...> type;
    };
    
    // tuple_indices
    template<size_t...> struct tuple_indices {};
    
    template<class IndexType, IndexType ...values>
    struct integer_sequence {
        template<size_t Start>
        using to_tuple_indices = tuple_indices<(values + Start)...>;
    };
    
    template<size_t End, size_t Start>
    using make_indices_imp = typename __make_integer_seq<integer_sequence, size_t, End - Start>::template
        to_tuple_indices<Start>;
    
    template<size_t End, size_t Start = 0>
    struct make_tuple_indices {
        typedef make_indices_imp<End, Start> type;
    };
    
    // tuple_leaf
    template<size_t Index, class Head, bool>
    class tuple_leaf {
        Head value;
        
    public:
        tuple_leaf() : value() {}
        
        template<class T>
        tuple_leaf(T && t) : value(std::forward<Head>(t)) {}
    };
    
    // tuple_imp
    template<class Index, class ...T> struct tuple_imp;
    
    template<size_t ...Index, class ...T>
    struct tuple_imp<tuple_indices<Index...>, T...> : public tuple_leaf<Index, T>... {
        
        template<size_t ...Uf, class ...Tf, size_t ...Ul, class ...Tl, class U>
        tuple_imp(tuple_indices<Uf...>, tuple_types<Tf...>, tuple_indices<Ul...>, tuple_types<Tl...>, U&& ...u) :
                tuple_leaf<Uf, Tf>(std::forward<U>(u))..., tuple_leaf<Ul, Tl>()...
        {}
    };
    
    template<class ...T>
    class tuple {
        typedef tuple_imp<typname make_tuple_indices<sizeof...(T)>::type, T...> base;
        base base_;
        
    public:
        tuple<const T& ...t) : base_(typename make_tuple_indices<sizeof...(T)>::type(),
                                     typename make_tuple_types<tuple, sizeof...(T)>::type(),
                                     typename make_tuple_indices<0>::type(),
                                     typename make_tuple_types<tuple, 0>::type(),
                                     t...) {}
    };
}
#endif /* tuple_h */
