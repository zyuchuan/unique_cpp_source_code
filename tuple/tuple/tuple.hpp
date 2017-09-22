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
    template<class ...T> class tuple;
    
    
    // tuple_types
    template<class ...T> struct tuple_types {};
    
    // tuple_size
    template<class T> struct tuple_size;
    
    template<class ...T>
    class tuple_size<tuple<T...> > : public std::integral_constant<size_t, sizeof...(T)> {};
    
    template<class ...T>
    struct tuple_size<tuple_types<T...> > : public std::integral_constant<size_t, sizeof...(T)> {};
    
    
    // tuple element
    template<size_t Index, typename T> struct tuple_element;
    
    template<size_t Index>
    struct tuple_element<Index, tuple_types<> > {};
    
    template<class Head, class ...Tail>
    struct tuple_element<0, tuple_types<Head, Tail...> > {
        typedef Head type;
    };
    
    template<size_t Index, class Head, class ...Tail>
    struct tuple_element<Index, tuple_types<Head, Tail...> > {
        typedef typename tuple_element<Index-1, tuple_types<Tail...> >::type type;
    };
    
    template<size_t Index, class ...T>
    struct tuple_element<Index, tuple<T...> > {
        typedef typename tuple_element<Index, tuple_types<T...> >::type type;
    };
    
    
    // make_tuple_types
    template<class Types, class T, size_t Start, size_t End>
    struct make_tuple_types_imp;
    
    template<class ...Types, class T, size_t Start, size_t End>
    struct make_tuple_types_imp<tuple_types<Types...>, T, Start, End> {
        typedef typename std::remove_reference<T>::type Type;
        
//        typedef typename make_tuple_types_imp<tuple_types<Types...,
//                typename std::conditional<std::is_lvalue_reference<T>::value,
//                    typename tuple_element<Start, Type>::type&,
//                    typename tuple_element<Start, Type>::type>::type>,
//                T, Start+1, End>::type type;
        
        typedef typename make_tuple_types_imp<Types..., tuple_element<Start, Type>::type,
                                              T, Start+1, End>::type type;
    };
    
    template<class ...Types, class T, size_t End>
    struct make_tuple_types_imp<tuple_types<Types...>, T, End, End> {
        typedef tuple_types<Types...> type;
    };
    
    template<class T, size_t End = tuple_size<typename std::remove_reference<T>::type>::value, size_t Start = 0>
    struct make_tuple_types {
        typedef typename make_tuple_types_imp<tuple_types<>, T, Start, End>::type type;
    };
    
    
    // make_tuple_indices
    template<size_t...> struct tuple_indices {};
    
    template<size_t Start, class Tuple, size_t End>
    struct make_indices_imp;
    
    template<size_t Start, size_t ...Indices, size_t End>
    struct make_indices_imp<Start, tuple_indices<Indices...>, End> {
        typedef typename make_indices_imp<Start+1, tuple_indices<Indices..., Start>, End>::type type;
    };
    
    template<size_t End, size_t ...Indices>
    struct make_indices_imp<End, tuple_indices<Indices...>, End> {
        typedef tuple_indices<Indices...> type;
    };
    
    template<size_t End, size_t Start = 0>
    struct make_tuple_indices {
        typedef typename make_indices_imp<Start, tuple_indices<>, End>::type type;
    };
    
    // tuple_leaf
    template<size_t Index, class Head>
    struct tuple_leaf {
        Head value;
        
        tuple_leaf() : value() {}
        
        template<class T>
        explicit tuple_leaf(T &&t) : value(std::forward<T>(t)) {}
        
        Head& get() { return value;}
    };
    
    // tuple_imp
    template<class Index, class ...T> struct tuple_imp;
    
    template<size_t ...Index, class ...T>
    struct tuple_imp<tuple_indices<Index...>, T...> : public tuple_leaf<Index, T>... {

        tuple_imp() {}
    

        template<size_t ...Uf, class ...Tf, size_t ...Ul, class ...Tl, class ...T>
        explicit tuple_imp(tuple_indices<Uf...>, tuple_types<Tf...>, tuple_indices<Ul...>, tuple_types<Tl...>, T&& ...t)
            : tuple_leaf<Uf, Tf>(std::forward<T>(t))..., tuple_leaf<Ul, Tl>()... {
            
            }
    };
    
    template<class ...T>
    struct tuple {
        typedef tuple_imp<typename make_tuple_indices<sizeof...(T)>::type, T...> base;
        
        base base_;
        
        explicit tuple(const T& ...t) : base_(typename make_tuple_indices<sizeof...(T)>::type(),
                                              typename make_tuple_types<tuple, sizeof...(T)>::type(),
                                              typename make_tuple_indices<0>::type(),
                                              typename make_tuple_types<tuple, 0>::type(),
                                              t...) {
        }
    };
    
    template<class T>
    struct make_tuple_return_imp {
        typedef T type;
    };
    
//    template<class T>
//    struct make_tuple_return_imp<std::reference_wrapper<T> > {
//        typedef T& type;
//    };
    
    template<class T>
    struct make_tuple_return {
        typedef typename make_tuple_return_imp<typename std::decay<T>::type>::type type;
    };
    
    template<class ...T>
    inline tuple<typename make_tuple_return<T>::type...> make_tuple(T&& ...t) {
        return tuple<typename make_tuple_return<T>::type...>(std::forward<T>(t)...);
    }
    
    // get
    template<size_t Index, class ...T>
    inline typename tuple_element<Index, tuple<T...> >::type& get(tuple<T...> &t) {
        typedef typename tuple_element<Index, tuple<T...> >::type type;
        return static_cast<tuple_leaf<Index, type>&>(t.base_).get();
    }
}


#endif /* tuple_h */
