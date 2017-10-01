//
//  main.cpp
//  unordered_set
//
//  Created by Jack Zou on 2017/9/30.
//  Copyright © 2017年 jack.zou. All rights reserved.
//

#include <iostream>
#include <unordered_set>

struct Foo {
    int     _i;
    double  _d;
    char    _c;
    
    Foo(int i, double d, char c) : _i(i), _d(d), _c(c) {}
};

template<>
struct std::hash<Foo> : public std::unary_function<Foo, size_t> {
    size_t operator()(const Foo& foo) const noexcept {
        return std::__murmur2_or_cityhash<size_t>()(&foo, sizeof(foo));
    }
};

void test_hash() {
    Foo f(1, 2.0, 'a');
    std::cout << std::hash<Foo>{}(f) << std::endl;
}

int main() {
    test_hash();
}
