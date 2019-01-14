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

template <typename T>
class CMSTable {
    int hashesCount;
    int tableSize;
    HashColumn<T>* table;
    
public:
    CMSTable() {
        
    }
    CMSTable(int __hashCount, int __tableSize) {
        hashesCount = __hashCount;
        tableSize = __tableSize;
        table = new HashColumn<T>[tableSize + 1];
    }
    CMSTable(int __hashesCount, int __tableSize, HashColumn<T>* __table) {
        hashesCount = __hashesCount;
        tableSize = __tableSize;
        table = __table;
    }
    int getHashesCount() {
        return hashesCount;
    }
    int getTableSize() {
        return tableSize;
    }
    HashColumn<T>* getTable() {
        return table;
    }
};
