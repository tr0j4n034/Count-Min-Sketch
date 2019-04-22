//
//  MinHash.hpp
//  CountMin Sketch
//
//  Created by Mahmud on 4/14/19.
//  Copyright © 2019 Mahmud. All rights reserved.
//

#ifndef MinHash_hpp
#define MinHash_hpp

#include <iostream>

using std::string;
using std::vector;

const int DEFAULT_SHINGLE_SIZE = 5;

class MinHasher {
private:
    size_t bitCount; // mask for b-minwise hash
public:
    MinHasher(): bitCount(-1) {};
    MinHasher(int __bitCount): bitCount((1 << __bitCount) - 1) {};
    template<typename Container = vector<int>>
    vector<string> getShingles(const Container& stream, int shingleSize = DEFAULT_SHINGLE_SIZE);
    template<typename Container = vector<int>>
    vector<size_t> getHashes(const Container& stream, int shingleSize = DEFAULT_SHINGLE_SIZE);
};

#endif /* MinHash_hpp */
