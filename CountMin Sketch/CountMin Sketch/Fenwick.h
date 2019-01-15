//
//  Fenwick.h
//  CountMin Sketch
//
//  Created by Mahmud on 1/14/19.
//  Copyright © 2019 Mahmud. All rights reserved.
//

#ifndef Fenwick_h
#define Fenwick_h


#endif /* Fenwick_h */

#include <vector>
#include <climits>

const int DUMMY = 0;
const int KERNEL_DUMMY = INT_MAX;

template <typename T>
T kernel(T a, T b) {
    return a < b ? a : b;
}

template <typename T>
class Fenwick {
    int size;
    vector<T> data;
    
public:
    Fenwick() {
        size = 0;
    }
    Fenwick(int __size) {
        size = __size;
        data = vector<T>(size + 1, KERNEL_DUMMY);
    }
    Fenwick(int __size, T __dummy) {
        size = __size;
        data = vector<T>(size + 1, KERNEL_DUMMY);
    }
    Fenwick(int __size, T* entries) {
        size = __size;
        data = vector<T>(size + 1, KERNEL_DUMMY);
        int ptr = 0;
        for_each(entries, entries + size, [&](T& entry){
            modify(++ptr, entry);
        });
    }
    int getSize() {
        return size;
    }
    T* getData() {
        return data;
    }
    T getAt(int position) { // prefix minimum
        T value = KERNEL_DUMMY;
        while (position > 0) {
            value = kernel(value, data[position]);
            position -= (position & -position);
        }
        return value;
    }
    void modify(int position, T newValue) {
        while (position <= size) {
            data[position] = kernel(data[position], newValue);
            position += (position & -position);
        }
    }
};
