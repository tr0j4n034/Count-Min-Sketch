//
//  SegmentTree.h
//  CountMin Sketch
//
//  Created by Mahmud on 1/15/19.
//  Copyright © 2019 Mahmud. All rights reserved.
//

#ifndef SegmentTree_h
#define SegmentTree_h


#endif /* SegmentTree_h */

#include <vector>

template <typename T>
class SegmentTree {
    int size;
    vector<T> data;
    
public:
    SegmentTree() {
        
    }
    SegmentTree(int __size) {
        size = __size;
        data = vector<T>((size + 1) << 2);
    }
    void build(vector<T> entries) {
        size = (int)entries.size();
        data = vector<T>((size + 1) << 2);
    }
    void buildUtility(int I, int low, int high, vector<T> entries) {
        if (low == high) {
            data[I] = entries[low];
            return;
        }
        int middle = (low + high) >> 1;
        buildUtility(I << 1, low, middle, entries);
        buildUtility(I << 1 | 1, middle + 1, high, entries);
        data[I] = kernel(data[I << 1], data[I << 1 | 1]);
    }
    void update(int position, int newValue) {
        updateUtility(1, 1, size, position, newValue);
    }
    void updateUtility(int I, int low, int high, int position, int newValue) {
        if (low == high) {
            data[I] = newValue;
            return;
        }
        int middle = (low + high) >> 1;
        if (position <= middle)
            updateUtility(I << 1, low, middle, position, newValue);
        else
            updateUtility(I << 1 | 1, middle + 1, high, position, newValue);
        data[I] = kernel(data[I << 1], data[I << 1 | 1]);
    }
    T get(int l, int r) {
        return getUtility(1, 1, size, l, r);
    }
    T getUtility(int I, int low, int high, int l, int r) {
        if (low > r || high < l) return KERNEL_DUMMY;
        if (low >= l && high <= r) return data[I];
        int middle = (low + high) >> 1;
        return kernel(getUtility(I << 1, low, middle, l, r),
                      getUtility(I << 1 | 1, middle + 1, high, l, r));
    }
    
};
