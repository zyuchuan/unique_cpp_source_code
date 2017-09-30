//
//  main.cpp
//  tuple
//
//  Created by Jack Zou on 2017/9/16.
//  Copyright © 2017年 jack.zou. All rights reserved.
//

#include <iostream>
#include "tuple.hpp"
//#include <tuple>
#include <string>

using namespace std;

int main() {
    unique_cpp::tuple<int, double, char> tp = unique_cpp::make_tuple(1, 2.0, 'a');
    cout << typeid(tp).name() << endl;
    unique_cpp::get<1>(tp);
    cout << unique_cpp::get<0>(tp) << endl;
    cout << unique_cpp::get<1>(tp) << endl;
    cout << unique_cpp::get<2>(tp) << endl;
    
    //auto t1 = std::make_tuple(1, 2.0, 'a');
    //cout << typeid(t1).name() << endl;
    
    //auto t = std::make_tuple(1, 2.0, 'a');
    //cout <<  std::get<0>(t) << ", " << std::get<1>(t) << ", " << std::get<2>(t) << endl;

    //using tuple_type = std::tuple<int, double, char>;
    //cout << typeid(std::tuple_element<2, tuple_type>::type).name() << endl;
}
