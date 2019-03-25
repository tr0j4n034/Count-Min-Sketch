//
//  CMSTable.hpp
//  CountMin Sketch
//
//  Created by Mahmud on 3/25/19.
//  Copyright © 2019 Mahmud. All rights reserved.
//

#ifndef CMSTable_hpp
#define CMSTable_hpp

#include <cmath>
#include <algorithm>

#include "HashColumn.cpp"
#include "Hasher.cpp"

template <typename T>
class CMSTable {
    double errorFactor;
    double confidence;
    int hashesCount;
    int tableSize;
    std::vector<HashColumn<T>> table;
    std::vector<Hasher<T>> hashFunctions;
    
public:
    CMSTable();
    CMSTable(int __hashCount, int __tableSize);
    CMSTable(int __hashCount, int __tableSize, std::vector<HashColumn<T>> __table);
    void setParams(double __error, double __confidence);
    void setDims(int __hashCount, int __tableSize);
    void setParamsDefault(bool ORIGINAL_PAPER_PARAMS = true, long long memory = -1);
    
    void setHashFunctions(T range = INT_MAX);
    int getHashesCount();
    
    int getTableSize();
    int getValueAt(int row, int column);
    
    std::vector<HashColumn<T>> getTable();
    std::vector<Hasher<T>> getHashFunctions();
    std::vector<T> getTableElems(bool outliersIN = false, bool includeZeros = false, bool __sorted = false);
    
    void insertEntry(T& entry);
    int getCount(T& entry);
    
    void clearTable();
    ~CMSTable();
    
    std::string describe();
};

#endif /* CMSTable_hpp */
