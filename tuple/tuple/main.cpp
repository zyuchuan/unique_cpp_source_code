//
//  main.cpp
//  tuple
//
//  Created by Jack Zou on 2017/9/16.
//  Copyright © 2017年 jack.zou. All rights reserved.
//

#include <iostream>
#include "tuple.hpp"

using namespace std;

void test_std_tuple() {
    
}

void test_my_tuple() {
    
}

int main() {
    //cout << typeid(unique_cpp::tuple_element<2, unique_cpp::tuple_types<char, int, std::string>>::type).name() << endl;
    //cout << typeid(unique_cpp::make_tuple_types<double, 1>::type).name();
    
    //cout << typeid(unique_cpp::make_tuple_indices<3>::type).name() << endl;
    
    //auto t = unique_cpp::make_tuple(10, "test", 3.14);
    //cout << unique_cpp::get<1>(t) << endl;
    //cout << unique_cpp::tuple_size<t>::value << endl;
    
//    cout << typeid(unique_cpp::tuple_indices<0>).name() << endl;
//    cout << typeid(unique_cpp::tuple_indices<0, 1>).name() << endl;
//    cout << typeid(unique_cpp::tuple_indices<0, 1, 2>).name() << endl;
//    
//    cout << typeid(unique_cpp::make_tuple_indices<3>).name() << endl;
    
    typedef unique_cpp::tuple<int, int, double> IIDType;
    cout << unique_cpp::tuple_size<IIDType>::value << endl;
}
