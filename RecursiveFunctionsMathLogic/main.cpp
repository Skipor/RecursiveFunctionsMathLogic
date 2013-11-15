//
//  main.cpp
//  RecursiveFunctionsMathLogic
//
//  Created by  Vladimir Skipor on 11/15/13.
//  Copyright (c) 2013  Vladimir Skipor. All rights reserved.


#include <array>
#include <iostream>
#include <vector>
#include <assert.h>
#include <initializer_list>
#import <list>


typedef unsigned nat;

using namespace std;

typedef vector<nat> arguments ;


template <nat n, nat m>
struct U {
    static_assert(n != 0 && m != 0 && n >= m, "invalid template parametrs ");
private:
    static const nat arg_num = n;

    static nat apply(arguments const & v) {
        assert(v.size() == arg_num);
        return v[m - 1];
    }

public:
    static nat apl(nat first, ...) {
        va_list list;
        va_start(list, first);
        arguments args(1, first);
        for (int i = 1; i < arg_num; ++i) {
            args.push_back(va_arg(list, nat));
        }
        va_end(list);
        return apply(args);
    }


};

//
//template <typename T>
//void s(initializer_list<T> l) {
//    for(initializer_list<T>::i)
//
//}









int main(int argc, const char * argv[]) {
    cout << U<4, 1>::apl(1, 2, 3, 4);


    return 0;
}
