//
//  tuple.hpp
//  tuple
//
//  Created by Jack Zou on 2017/9/16.
//  Copyright © 2017年 jack.zou. All rights reserved.
//

#ifndef tuple_h
#define tuple_h

#include <utility>
#include <type_traits>

namespace unique_cpp {
    
    // forward declaration
    template<class ...T> class tuple;
    
    // tuple_element
    template<size_t Index, class T> class tuple_element;
    
    // tuple_size
    template<class ...T> class tuple_size;
    
    template<class ...T>
    class tuple_size<tuple<T...> > : public std::integral_constant<size_t, sizeof...(T)> {};
    
    
    
    // tuple_types
    template<class ...T> struct tuple_types {};
    
    // make_tuple_types
    template<class T, size_t End = tuple_size<T>::value, size_t Start = 0>
    struct make_tuple_types {};
    
    template<class ...T, size_t End>
    struct make_tuple_types<tuple<T...>, End, 0> {
        typedef tuple_types<T...> type;
    };
    
    template<class ...T, size_t End>
    struct make_tuple_types<tuple_types<T...>, End, 0> {
        typedef tuple_types<T...> type;
    };
    
    // tuple_indices
    template<size_t ...value> struct tuple_indices {
        //const static int values = sizeof...(value);
    };
    
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
    
    // tuple_element
    namespace indexer_detail {
        template<size_t Index, class T>
        struct indexed {
            using type = T;
        };
        
        template<class Types, class Indexes> struct indexer;
        
        template<class ...Types, size_t ...Index>
        struct indexer<tuple_types<Types...>, tuple_indices<Index...>>
            : public indexed<Index, Types>... {};
        
        template<size_t Index, class T>
        indexed<Index, T> at_index(indexed<Index, T> const&);
    } // namespace indexer_detail
    
    template<size_t Index, class ...Types>
    using type_pack_element = typename decltype(indexer_detail::at_index<Index>(
          indexer_detail::indexer<tuple_types<Types...>,
            typename make_tuple_indices<sizeof...(Types)>::type>()))::type;
    
    template<size_t Index, class ...T>
    struct tuple_element<Index, tuple_types<T...> > {
        typedef type_pack_element<Index, T...> type;
    };
    
    template<size_t Index, class ...T>
    struct tuple_element<Index, tuple<T...> > {
        typedef type_pack_element<Index, T...> type;
    };
    
    // tuple_leaf
    template<size_t Index, class Head>
    class tuple_leaf {
        Head value;
        
    public:
        tuple_leaf() : value() {}
        
        template<class T>
        explicit tuple_leaf(const T& t) : value(t) {}
        
        Head& get() {return value;}
        const Head& get() const {return value;}
    };
    
    // tuple_imp
    template<class Index, class ...T> struct tuple_imp;

    template<size_t ...Index, class ...T>
    struct tuple_imp<tuple_indices<Index...>, T...> : public tuple_leaf<Index, T>... {
        
        tuple_imp() {}
        
        template<size_t ...Uf, class ...Tf, class ...U>
        tuple_imp(tuple_indices<Uf...>, tuple_types<Tf...>, U&& ...u) :
                tuple_leaf<Uf, Tf>(std::forward<U>(u))... {
                    
                }
    };

    template<class ...T>
    struct tuple {
        typedef tuple_imp<typename make_tuple_indices<sizeof...(T)>::type, T...> base;
        base base_;

        tuple(const T& ...t) : base_(typename make_tuple_indices<sizeof...(T)>::type(),
                                     typename make_tuple_types<tuple, sizeof...(T)>::type(),
                                     t...) {}
    };
    
    template<class T>
    struct make_tuple_return_imp {
        typedef T type;
    };
    
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
    inline typename tuple_element<Index, tuple<T...> >::type& get(tuple<T...>& t) {
        typedef typename tuple_element<Index, tuple<T...> >::type type;
        return static_cast<tuple_leaf<Index, type>&>(t.base_).get();
    }
    
}
#endif /* tuple_h */
