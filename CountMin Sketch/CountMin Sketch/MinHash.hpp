//
//  MinHash.hpp
//  CountMin Sketch
//
//  Created by Mahmud on 4/14/19.
//  Copyright © 2019 Mahmud. All rights reserved.
//

#ifndef MinHash_hpp
#define MinHash_hpp

#include "ExtraFactory.hpp"

#include <iostream>

using std::string;
using std::vector;

const int DEFAULT_SHINGLE_SIZE = 5;

class MinHasher {
public:
    MinHasher();
    template<typename Container = vector<int>>
    vector<string> getShingles(const Container& stream, int shingleSize = DEFAULT_SHINGLE_SIZE);
    template<typename Container = vector<int>>
    vector<size_t> getHashes(const Container& stream, int shingleSize = DEFAULT_SHINGLE_SIZE);
};




#endif /* MinHash_hpp */
