//
//  HashColumn.cpp
//  CountMin Sketch
//
//  Created by Mahmud on 1/14/19.
//  Copyright © 2019 Mahmud. All rights reserved.
//

#ifndef HashColumn_cpp
#define HashColumn_cpp

#include "HashColumn.hpp"

template<typename T>
HashColumn<T>::HashColumn() {
    
}
template<typename T>
HashColumn<T>::HashColumn(int __size) {
    size = __size;
    entries = vector<T>(size + 1, 0);
}
template<typename T>
HashColumn<T>::HashColumn(const vector<T>& __entries) {
    size = int(__entries.size());
    entries = __entries;
}
template<typename T>
HashColumn<T>::HashColumn(int __size, const vector<T>& __entries) {
    size = __size;
    entries = __entries;
}
template<typename T>
int HashColumn<T>::getSize() {
    return size;
}
template<typename T>
vector<T> HashColumn<T>::getEntries() {
    return entries;
}
template<typename T>
int HashColumn<T>::getValueAt(int position) {
    return entries[position];
}
template<typename T>
void HashColumn<T>::updateValueAt(int position, T newValue) {
    entries[position] = newValue;
}
template<typename T>
void HashColumn<T>::incrementValueAt(int position) {
    ++entries[position];
}
template<typename T>
int HashColumn<T>::getMinimumNaive() {
    T result = 1 << 30;
    for (int i = 1; i <= size; i ++) {
        if (entries[i] < result)
            result = entries[i];
    }
    return result;
}
template<typename T>
HashColumn<T>::~HashColumn() {
    
}

#endif /* HashColumn_cpp */

