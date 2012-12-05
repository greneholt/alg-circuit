//
//  matrix.h
//  CircuitLayout
//
//  Created by Connor McKay on 12/5/12.
//  Copyright (c) 2012 Connor McKay. All rights reserved.
//

#ifndef __CircuitLayout__matrix__
#define __CircuitLayout__matrix__

#include <vector>

template < class T >
struct matrix {
    typedef T value_type;
    typedef std::vector<value_type> container;
    
private:
    container _data;
    long _b;
    
public:
    matrix(long a, long b) : _b(b), _data(a*b) {};
    
    value_type* operator[](int a) {
        return &_data[a * _b];
    }
    
    value_type const* operator[](int a) const {
        return &_data[a * _b];
    }
};

#endif /* defined(__CircuitLayout__matrix__) */
