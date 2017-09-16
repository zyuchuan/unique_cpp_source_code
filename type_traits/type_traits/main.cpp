//
//  main.cpp
//  type_traits
//
//  Created by Jack Zou on 2017/9/16.
//  Copyright © 2017年 jack.zou. All rights reserved.
//

#include <iostream>
#include <type_traits>
#include <string>
//#include "is_function.hpp"
//#include "common_type.hpp"
//#include "has_to_string.hpp"

//void test_is_polymorphic() {
//std::cout << std::is_polymorphic<int>::value << std::endl;
//std::cout << std::is_polymorphic<B>::value << std::endl;
//std::cout << typeid(dynamic_cast<void*>(std::declval<B*>())).name() << std::endl;

//    std::cout << typeid(std::declval<B*>()).name() << std::endl;
//
//    std::cout << my_is_polymorphic::is_polymorphic<A>::value << std::endl;
//    std::cout << my_is_polymorphic::is_polymorphic<C>::value << std::endl;

//}

//class Foo {
//    int v1;
//    double v2;
//
//public:
//    Foo(int n) : v1(n), v2() {}
//    Foo(int n, double f)  : v1(n), v2(f) {}
//};
//
//void test_is_constructible() {
//    std::cout << "Foo is ...\n" << std::boolalpha
//    << "\tConstructible from int? " << std::is_constructible<Foo, int>::value << '\n'
//    << "\tConstructible from int and double? " << std::is_constructible<Foo, int, double>::value << '\n';
//}
//
//void test_common_type() {
//    std::cout << typeid(my::common_type<float, int>::type).name() << std::endl;
//}
//
//int&& r_int();
//double&& r_double();

//struct A { int fun(); };
//
//template<typename>
//struct PM_traits {};
//
//template<class T, class U>
//struct PM_traits<U T::*> {
//    using member_type = U;
//};

//int f();

//void test_is_function() {
//    std::cout << std::boolalpha;
//    std::cout << my::is_function<A>::value << std::endl;
//    std::cout << my::is_function<int(int)>::value << std::endl;
//    //std::cout << my::is_function<decltype(f)>::value << std::endl;
//    std::cout << my::is_function<int>::value << std::endl;
//
//    using T = PM_traits<decltype(&A::fun)>::member_type; // T is int()
//    //std::cout << typeid(T).name() << std::endl;
//    std::cout << my::is_function<T>::value << std::endl;
//}

//void f() {}
//auto pf = f;

//struct A {
//public:
//    void to_string();
//};
//
//void test_has_to_string() {
//    std::cout << std::boolalpha;
//    std::cout << my::has_to_string<void>::value << std::endl;
//    std::cout << my::has_to_string<A>::value << std::endl;
//}

using namespace std;

template<class F, class ...Args>
void expand(const F& f, Args&& ... args) {
    initializer_list<int>{(f(std::forward<Args>(args)), 0)...};
}


int main() {
    //test_is_constructible();
    
    //test_common_type();
    //std::cout << typeid(decltype(true ? r_int() : std::declval<double>())).name() << std::endl;
    
    // test is_function
    //test_is_function();
    
    //my::test<decltype(f)>(my::source<decltype(f)>(0));
    //my::test<int>(my::source<int>(0));
    
    //test_has_to_string();
    
    //std::cout << typeid(decltype(std::declval<A>().to_string())).name() << std::endl;
    
    expand([](int i){cout << i << endl;}, 1, 2, 3);
    
}
