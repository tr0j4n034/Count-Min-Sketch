//
//  HashColumn.h
//  CountMin Sketch
//
//  Created by Mahmud on 1/14/19.
//  Copyright © 2019 Mahmud. All rights reserved.
//

#ifndef HashColumn_h
#define HashColumn_h


#endif /* HashColumn_h */

#include <functional>

#include "Fenwick.h"

template <typename T>
class HashColumn {
    int size;
    T* entries;
    Fenwick<T> fenwickTree;
    
public:
    HashColumn() {
        size = 0;
    }
    HashColumn(int __size) {
        size = __size;
        entries = new T[size + 1]{0};
        fenwickTree = Fenwick<T>(size);
    }
    HashColumn(int __size, T* __entries) {
        size = __size;
        entries = __entries;
        fenwickTree = Fenwick<T>(size, entries);
    }
    int getSize() {
        return size;
    }
    T* getEntries() {
        return entries;
    }
    T* getTree() {
        return fenwickTree.getData();
    }
    int getValueAt(int position) {
        return entries[position];
    }
    void updateValueAt(int position, T newValue) {
        entries[position] = newValue;
        fenwickTree.modify(position, newValue);
    }
    void incrementValueAt(int position) {
        fenwickTree.modify(position, ++entries[position]);
    }
    int getMinimum() {
        return fenwickTree.getAt(size);
    }
    int getMinimumNaive() {
        T result = MAX_VALUE;
        for (int i = 1; i <= size; i ++) {
            if (entries[i] < result)
                result = entries[i];
        }
        return result;
    }
};
