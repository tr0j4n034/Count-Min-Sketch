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
    vector<T> entries;
//    SegmentTree<T> segmentTree;
    
public:
    HashColumn() {
        size = 0;
    }
    HashColumn(int __size) {
        size = __size;
        entries = vector<T>(size + 1, 0);
//        segmentTree = SegmentTree<T>(size);
    }
    HashColumn(int __size, vector<T> __entries) {
        size = __size;
        entries = __entries;
//        segmentTree = SegmentTree<T>(size, entries);
    }
    int getSize() {
        return size;
    }
    vector<T> getEntries() {
        return entries;
    }
//    T* getTree() {
//        return segmentTree;
//    }
    int getValueAt(int position) {
        return entries[position];
    }
    void updateValueAt(int position, T newValue) {
        entries[position] = newValue;
//        segmentTree.update(position, newValue);
    }
    void incrementValueAt(int position) {
        ++entries[position];
//        segmentTree.update(position, entries[position]);
    }
//    int getMinimum() {
//        return segmentTree.get(1, size);
//    }
    int getMinimumNaive() {
        T result = KERNEL_DUMMY;
        for (int i = 1; i <= size; i ++) {
            if (entries[i] < result)
                result = entries[i];
        }
        return result;
    }
};
