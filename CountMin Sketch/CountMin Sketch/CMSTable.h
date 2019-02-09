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

#include "HashColumn.h"
#include "Hasher.h"

#include <cmath>
#include <algorithm>

template <typename T>
class CMSTable {
    double errorFactor;
    double confidence;
    int hashesCount;
    int tableSize;
    vector<HashColumn<T>> table;
    vector<Hasher<T>> hashFunctions;
    
public:
    CMSTable() {
        hashesCount = 0;
        tableSize = 0;
        errorFactor = 0.05;
        confidence = 0.99;
    }
    CMSTable(int __hashCount, int __tableSize) {
        hashesCount = __hashCount;
        tableSize = __tableSize;
        table = vector<HashColumn<int>>(hashesCount + 1);
        for (int i = 1; i <= hashesCount; i ++) {
            table[i] = HashColumn<int>(tableSize + 1);
        }
        for (int i = 0; i < hashesCount + 1; i ++) {
            hashFunctions.push_back(Hasher<T>(2, 2, 2));
        }
        errorFactor = 0.05;
        confidence = 0.99;
    }
    CMSTable(int __hashCount, int __tableSize, vector<HashColumn<T>> __table) {
        hashesCount = __hashCount;
        tableSize = __tableSize;
        table = __table;
        hashFunctions = vector<Hasher<T>>(hashesCount + 1);
        setHashFunctions();
    }
    void setParams(double __error, double __confidence) {
        errorFactor = __error;
        confidence = __confidence;
    }
    void setDims(int __hashCount, int __tableSize) {
        hashesCount = __hashCount;
        tableSize = __tableSize;
        hashFunctions = vector<Hasher<T>>(hashesCount + 1);
        table = vector<HashColumn<int>>(hashesCount + 1);
        for (int i = 1; i <= hashesCount; i ++) {
            table[i] = HashColumn<int>(tableSize + 1);
        }
        setHashFunctions();
    }
    void setParamsDefault(bool ORIGINAL_PAPER_PARAMS = true) {
        if (ORIGINAL_PAPER_PARAMS) {
            hashesCount = int(ceil(log(1. / (1. - confidence))));
            tableSize = int(ceil(exp(1.) / errorFactor));
        } else {
            hashesCount = int(ceil(log(1. / (1. - confidence)) / log(2.)));
            tableSize = int(ceil(2. / errorFactor));
        }
        table = vector<HashColumn<int>>(hashesCount + 1);
        for (int i = 1; i <= hashesCount; i ++) {
            table[i] = HashColumn<int>(tableSize + 1);
        }
        for (int i = 0; i < hashesCount + 1; i ++) {
            hashFunctions.push_back(Hasher<T>(INT_MAX));
        }
    }
    void setHashFunctions(T range = INT_MAX) {
        for (int i = 1; i <= hashesCount; i ++) {
            hashFunctions[i] = Hasher<T>(range);
        }
    }
    int getHashesCount() {
        return hashesCount;
    }
    int getTableSize() {
        return tableSize;
    }
    int getValueAt(int row, int column) { // hashID, hashValue
        return table[row].getValueAt(column);
    }
    vector<HashColumn<T>> getTable() {
        return table;
    }
    vector<Hasher<T>> getHashFunctions() {
        return hashFunctions;
    }
    vector<T> getTableElems(bool outliersIN = false, bool includeZeros = false, bool __sorted = false) { // collect elements [not equal to maximum in the columns = outliers]
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
    void insertEntry(T& entry) {
        for (int i = 1; i <= hashesCount; i ++) {
            int hashValue = hashFunctions[i].getHash(entry) % tableSize + 1;
            table[i].incrementValueAt(hashValue);
        }
    }
    int getCount(T& entry) {
        int minimumCount = INT_MAX;
        for (int i = 1; i <= hashesCount; i ++) {
            int hashValue = hashFunctions[i].getHash(entry) % tableSize + 1;
            if (table[i].getValueAt(hashValue) < minimumCount) {
                minimumCount = table[i].getValueAt(hashValue);
            }
        }
        return minimumCount;
    }
    void clearTable() {
        for (auto row: table) {
            for (auto &record: row)
                record = 0;
        }
    }
    string describe() {
        string desc = "";
        desc += "hashes count: " + to_string(hashesCount) + "\n";
        desc += "table width: " + to_string(tableSize) + "\n";
        desc += "error factor: " + to_string(errorFactor) + "\n";
        desc += "confidence: " + to_string(confidence) + "\n";
        return desc;
    }
};
