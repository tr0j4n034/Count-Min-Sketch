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

#include "HashColumn.cpp"
#include "Hasher.cpp"
#include "CWSSketch.hpp"

using std::vector;

template <typename T>
class CMSTable {
    double errorFactor;
    double confidence;
    int hashesCount;
    int tableSize;
    vector<HashColumn<T>> table;
    vector<Hasher<T>> hashFunctions;
    
public:
    CMSTable();
    CMSTable(int __hashCount, int __tableSize);
    CMSTable(int __hashCount, int __tableSize, const vector<HashColumn<T>> __table);
    
    CMSTable& operator= (const CMSTable& rhs);
    
    void setParams(double __error, double __confidence);
    void setDims(int __hashCount, int __tableSize);
    void setParamsDefault(bool ORIGINAL_PAPER_PARAMS = true, long long memory = -1);
    void scaleDims(long long memory = -1);
    
    void setHashFunctions(T range = INT_MAX);
    int getHashesCount();
    
    int getTableSize();
    int getValueAt(int row, int column);
    
    vector<HashColumn<T>> getTable();
    vector<Hasher<T>> getHashFunctions();
    vector<T> getTableElems(bool outliersIN = false, bool includeZeros = false, bool __sorted = false);
    
    double getJaccardDistance(const CMSTable<T>& other, bool outliersIN = false, bool unweighted = false);
    template<typename R = double>
    CWSSketch<R> getTableSketchIoffe(int sketchSize, int seed = 0);
    
    
    void insertEntry(T& entry);
    int getCount(T& entry);
    
    void clearTable();
    ~CMSTable();
    
    std::string describe();
};

#endif /* CMSTable_hpp */
