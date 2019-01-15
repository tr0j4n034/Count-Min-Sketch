//
//  CMSTable.h
//  CountMin Sketch
//
//  Created by Mahmud on 1/14/19.
//  Copyright © 2019 Mahmud. All rights reserved.
//

#ifndef CMSTable_h
#define CMSTable_h


#endif /* CMSTable_h */

#include "HashColumn.h"
#include "Hasher.h"

#include <cmath>

template <typename T>
class CMSTable {
    double epsilon;
    int hashesCount;
    int tableSize;
    vector<HashColumn<T>> table;
    vector<Hasher<T>> hashFunctions;
    
public:
    CMSTable() {
        hashesCount = 0;
        tableSize = 0;
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
    }
    CMSTable(int __hashCount, int __tableSize, vector<HashColumn<T>> __table) {
        hashesCount = __hashCount;
        tableSize = __tableSize;
        table = __table;
        hashFunctions = vector<Hasher<T>>(hashesCount + 1);
    }
    void setSizesOnStream(int streamSize) {
        d =
    }
    void setHashFunctions(T range = INT_MAX) {
        for (int i = 1; i <= hashesCount; i ++) {
            hashFunctions[i] = Hasher<T>(tableSize, range);
        }
    }
    int getHashesCount() {
        return hashesCount;
    }
    int getTableSize() {
        return tableSize;
    }
    vector<HashColumn<T>> getTable() {
        return table;
    }
    vector<Hasher<T>> getHashFunctions() {
        return hashFunctions;
    }
    void insertEntry(T entry) {
        for (int i = 1; i <= hashesCount; i ++) {
            int hashValue = hashFunctions[i].getHash(entry);
            cout << "entry = " << entry << ", hashval = " << hashValue << endl;
            table[i].incrementValueAt(hashValue);
        }
    }
    int getCount(T entry) {
        int minimumCount = INT_MAX;
        for (int i = 1; i <= hashesCount; i ++) {
            int hashValue = hashFunctions[i].getHash(entry);
            if (table[i].getValueAt(hashValue) < minimumCount) {
                minimumCount = table[i].getValueAt(hashValue);
            }
        }
        return minimumCount;
    }
};
