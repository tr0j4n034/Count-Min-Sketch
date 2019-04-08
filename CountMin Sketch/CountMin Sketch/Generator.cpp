//
//  Generator.cpp
//  CountMin Sketch
//
//  Created by Mahmud on 1/17/19.
//  Copyright © 2019 Mahmud. All rights reserved.
//

#ifndef Generator_cpp
#define Generator_cpp

#include "Generator.hpp"

#include <ctime>
#include <cstdlib>

const int MAX_VALUE = 1 << 30;

vector<int> generateRandomList(int setSize, int maxRange, int seed) {
    Random device(seed == -1 ? 1LL * (unsigned int)clock() * rand() % MAX_VALUE : seed);
    vector<int> list(setSize);
    for (auto &element: list) {
        element = device.generate(1, maxRange);
    }
    return list;
}
template <typename T>
vector<T> generateRandomListViaGamma(int setSize, GammaRandomVar<T> g, double scaler, int seed) {
    g.setSeed(seed);
    vector<T> list(setSize);
    for (const auto &element: list) {
        element = T(scaler * g.generate());
    }
    return list;
}
template <typename T>
vector<T> generateRandomListViaGammaParams(int setSize, T alpha, T beta, double scaler, int seed) {
    GammaRandomVar<T> g = GammaRandomVar<T>(alpha, beta, seed);
    vector<T> list(setSize);
    for (const auto &element: list) {
        element = T(scaler * g.generate());
    }
    return list;
}

#if __has_include("boost/random.hpp")
template<typename T>
vector<T> generateRandomListViaBeta(int setSize, BetaRandomVar<T> b, double scaler, int seed) {
    b.setSeed(seed);
    vector<T> list(setSize);
    for (const auto &element: list) {
        element = T(scaler * b.generate());
    }
    return list;
}
template<typename T>
vector<T> generateRandomListViaBetaParams(int setSize, T alpha, T beta, double scaler, int seed) {
    BetaRandomVar<T> b(alpha, beta, seed);
    vector<T> list(setSize);
    for (auto &element: list) {
        element = T(scaler * b.generate());
    }
    return list;
}
#endif

vector<vector<int>> generateRandomDataSet(int dataSetSize, int setSize, int maxRange, int seed) {
    Random device(seed == -1 ? 1LL * (unsigned int)clock() * rand() % MAX_VALUE : seed);
    vector<vector<int>> v(dataSetSize);
    for (auto& list: v) list.resize(setSize);
    for (auto& list: v) {
        for (auto &element: list)
            element = device.generate(1, maxRange);
    }
    return v;
}
vector<vector<int>> generateRandomPair(int sizeA, int sizeB, bool sameSize, int maxRange, int seed) {
    if (sameSize) sizeB = sizeA;
    Random device(seed == -1 ? 1LL * (unsigned int)clock() * rand() % MAX_VALUE : seed);
    vector<vector<int>> v(2);
    v[0].resize(sizeA);
    v[1].resize(sizeB);
    for (auto& list: v) {
        for (auto& element: list) {
            element = device.generate(1, maxRange);
        }
    }
    return v;
}
vector<vector<int>> generatePairWithSimilarity(int sizeA, double similarity, int sizeB, bool sameSize, int seed) {
    if (sameSize) sizeB = sizeA;
    Random device(seed == -1 ? 1LL * (unsigned int)clock() * rand() % MAX_VALUE : seed);
    vector<vector<int>> v(2);
    int common = 0;
    for (int i = MAX_BIT; i >= 0; i --) {
        if (common + (1 << i) > std::min(sizeA, sizeB)) continue;
        int candidate = common + (1 << i);
        int currentUnionSize = sizeA + sizeB - candidate;
        if (1. * candidate / currentUnionSize <= similarity)
            common = candidate;
    }
    int unionSize = sizeA + sizeB - common;
    vector<int> elements(unionSize);
    iota(elements.begin(), elements.end(), 0);
    shuffle(elements.begin(), elements.end(), device.getGenerator());
    for (int i = 0; i < common; i ++) {
        v[0].push_back(elements[i]);
        v[1].push_back(elements[i]);
    }
    for (int i = common; i < sizeA; i ++) {
        int position = device.generate(i + 1, unionSize - 1);
        v[0].push_back(elements[position]);
        std::swap(elements[i], elements[position]);
    }
    for (int i = sizeA; i < unionSize; i ++)
        v[1].push_back(elements[i]);
    for_each(v.begin(), v.end(), [&](std::vector<int> &list) {
        shuffle(list.begin(), list.end(), device.getGenerator());
    });
    return v;
}

#endif /* Generator_h */
