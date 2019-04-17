//
//  MinHash.cpp
//  CountMin Sketch
//
//  Created by Mahmud on 4/14/19.
//  Copyright © 2019 Mahmud. All rights reserved.
//

#include "MinHash.hpp"
#include "ExtraFactory.hpp"

#include <cstring>
#include <vector>
#include <functional>

template<typename Container>
std::vector<string> MinHasher::getShingles(const Container& stream, int shingleSize) {
    int streamSize = int(stream.size());
    std::vector<string> shingles(streamSize - shingleSize + 1);
    for (int i = 0; i < streamSize - shingleSize; i ++) {
        string shingle = "";
        for (int j = i; j < i + shingleSize; j ++) {
            shingle += toString(stream[j]);
        }
        shingles[i] = shingle;
    }
    return shingles;
}
template<typename Container>
std::vector<size_t> MinHasher::getHashes(const Container& stream, int shingleSize) {
    vector<string> shingles = getShingles(stream, shingleSize);
    vector<size_t> output(int(shingles.size()));
    std::hash<string> hasher;
    transform(begin(shingles), end(shingles), output.begin(), [&](string sh) {
        return hasher(sh);
    });
    return output;
}
