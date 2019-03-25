//
//  CMSTable.h
//  CountMin Sketch
//
//  Created by Mahmud on 1/14/19.
//  Copyright © 2019 Mahmud. All rights reserved.
//

#pragma once

#ifndef CMSTable_h
#define CMSTable_h


#endif /* CMSTable_h */

#include "CMSTable.hpp"

template<typename T>
CMSTable<T>::CMSTable() {
    hashesCount = 0;
    tableSize = 0;
    errorFactor = 0.05;
    confidence = 0.99;
}
template<typename T>
CMSTable<T>::CMSTable(int __hashCount, int __tableSize) {
    hashesCount = __hashCount;
    tableSize = __tableSize;
    table = std::vector<HashColumn<int>>(hashesCount + 1);
    for (int i = 1; i <= hashesCount; i ++) {
        table[i] = HashColumn<int>(tableSize + 1);
    }
    for (int i = 0; i < hashesCount + 1; i ++) {
        hashFunctions.push_back(Hasher<T>(2, 2, 2));
    }
    errorFactor = 0.05;
    confidence = 0.99;
}
template<typename T>
CMSTable<T>::CMSTable(int __hashCount, int __tableSize, std::vector<HashColumn<T>> __table) {
    hashesCount = __hashCount;
    tableSize = __tableSize;
    table = __table;
    hashFunctions = vector<Hasher<T>>(hashesCount + 1);
    setHashFunctions();
}
template<typename T>
void CMSTable<T>::setParams(double __error, double __confidence) {
    errorFactor = __error;
    confidence = __confidence;
}
template<typename T>
void CMSTable<T>::setDims(int __hashCount, int __tableSize) {
    hashesCount = __hashCount;
    tableSize = __tableSize;
    hashFunctions = vector<Hasher<T>>(hashesCount + 1);
    table = vector<HashColumn<int>>(hashesCount + 1);
    for (int i = 1; i <= hashesCount; i ++) {
        table[i] = HashColumn<int>(tableSize + 1);
    }
    setHashFunctions();
}


template<typename T>
void CMSTable<T>::setParamsDefault(bool ORIGINAL_PAPER_PARAMS, long long memory) {
    if (ORIGINAL_PAPER_PARAMS) {
        hashesCount = int(ceil(log(1. / (1. - confidence))));
        tableSize = int(ceil(exp(1.) / errorFactor));
    } else {
        hashesCount = int(ceil(log(1. / (1. - confidence)) / log(2.)));
        tableSize = int(ceil(2. / errorFactor));
    }
    if (memory != -1) {
        while (memory >= 2LL * hashesCount * tableSize) {
            tableSize <<= 1;
            if (memory >= 2LL * hashesCount * tableSize)
                hashesCount <<= 1;
        }
    }
    table = vector<HashColumn<int>>(hashesCount + 1);
    for (int i = 1; i <= hashesCount; i ++) {
        table[i] = HashColumn<int>(tableSize + 1);
    }
    for (int i = 0; i < hashesCount + 1; i ++) {
        hashFunctions.push_back(Hasher<T>(1 << 30));
    }
}
template<typename T>
void CMSTable<T>::setHashFunctions(T range) {
    for (int i = 1; i <= hashesCount; i ++) {
        hashFunctions[i] = Hasher<T>(range);
    }
}
template<typename T>
int CMSTable<T>:: getHashesCount() {
    return hashesCount;
}
template<typename T>
int CMSTable<T>::getTableSize() {
    return tableSize;
}
template<typename T>
int CMSTable<T>::getValueAt(int row, int column) {
    return table[row].getValueAt(column);
}
template<typename T>
std::vector<HashColumn<T>> CMSTable<T>::getTable() {
    return table;
}
template<typename T>
std::vector<Hasher<T>> CMSTable<T>::getHashFunctions() {
    return hashFunctions;
}
template<typename T>
std::vector<T> CMSTable<T>:: getTableElems(bool outliersIN, bool includeZeros, bool __sorted) {
    vector<T> elems;
    if (!outliersIN) {
        vector<T> columnMax(tableSize + 1, 0);
        for (int i = 1; i <= hashesCount; i ++) {
            for (int j = 1; j <= tableSize; j ++) {
                if (table[i].getValueAt(j) > columnMax[j])
                    columnMax[j] = table[i].getValueAt(j);
            }
        }
        for (int i = 1; i <= hashesCount; i ++) {
            for (int j = 1; j <= tableSize; j ++) {
                if (table[i].getValueAt(j) != columnMax[j] && (includeZeros || table[i].getValueAt(j) > 0))
                    elems.push_back(table[i].getValueAt(j));
            }
        }
    } else {
        for (int i = 1; i <= hashesCount; i ++) {
            for (int j = 1; j <= tableSize; j ++) {
                if (includeZeros || table[i].getValueAt(j) > 0)
                    elems.push_back(table[i].getValueAt(j));
            }
        }
    }
    if (__sorted)
        sort(elems.begin(), elems.end());
    return elems;
}
template<typename T>
void CMSTable<T>::insertEntry(T& entry) {
    for (int i = 1; i <= hashesCount; i ++) {
        int hashValue = hashFunctions[i].getHash(entry) % tableSize + 1;
        table[i].incrementValueAt(hashValue);
    }
}
template<typename T>
int CMSTable<T>::getCount(T &entry) {
    int minimumCount = INT_MAX;
    for (int i = 1; i <= hashesCount; i ++) {
        int hashValue = hashFunctions[i].getHash(entry) % tableSize + 1;
        if (table[i].getValueAt(hashValue) < minimumCount) {
            minimumCount = table[i].getValueAt(hashValue);
        }
    }
    return minimumCount;
}
template<typename T>
void CMSTable<T>::clearTable() {
    for (auto row: table) {
        for (auto &record: row) {
            record = 0;
        }
    }
}
template<typename T>
CMSTable<T>::~CMSTable() {
    
}
template<typename T>
std::string CMSTable<T>::describe() {
    string desc = "";
    desc += "hashes count: " + to_string(hashesCount) + "\n";
    desc += "table width: " + to_string(tableSize) + "\n";
    desc += "error factor: " + to_string(errorFactor) + "\n";
    desc += "confidence: " + to_string(confidence) + "\n";
    return desc;
}
