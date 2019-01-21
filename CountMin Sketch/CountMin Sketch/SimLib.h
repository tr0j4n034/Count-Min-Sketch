//
//  SimLib.h
//  CountMin Sketch
//
//  Created by Mahmud on 1/17/19.
//  Copyright © 2019 Mahmud. All rights reserved.
//

#ifndef SimLib_h
#define SimLib_h


#endif /* SimLib_h */


#include <cmath>

#include <cassert>
#include <unordered_map>

template <typename T, typename R>
R EuclideanDistanceIterable(T objectA, T objectB) { // vectors and other iterables
    // for custom data types
    // use (std::is_base_of<your_data_type, iterables>::value) or some other option
    assert((int)objectA.size() == (int)objectB.size());
    auto itB = begin(objectB);
    transform(begin(objectA), end(objectA), begin(objectA), [&](R value) {
        return value - (*itB ++);
    });
    R result = accumulate(begin(objectA), end(objectA), 0, [](R currentResult, R delta) {
        return currentResult + delta * delta;
    });
    return sqrt(result);
}
template <typename T, typename R>
R EuclideanDistance(T objectA, T objectB) { // arrays
    // for custom data types
    // use (std::is_base_of<your_data_type, iterables>::value) or some other option
    assert(sizeof(objectA) && sizeof(objectB));
    assert(sizeof(objectA) / sizeof(objectA[0]) == sizeof(objectB) / sizeof(objectB[0]));
    R result = 0;
    R* ptrB = *objectB;
    for_each(objectA, *(&objectA + 1), [&](R value) {
        T delta = value - *(ptrB ++);
        result += delta * delta;
    });
    return sqrt(result);
}
template <typename T, typename dt, typename R>
R JaccardDistanceIterable(T objectA, T objectB) { // vectors and other iterables
    unordered_map<dt, int> mapA, mapB;
    unordered_map<dt, int> mapUnion;
    for_each(begin(objectA), end(objectA), [=](dt value) {
        mapA[value] ++;
    });
    for_each(begin(objectB), end(objectB), [=](dt value) {
        mapB[value] ++;
    });
    int intersection = 0;
    for_each(begin(mapA), end(mapA), [=](auto record) {
        if (mapB.count(record))
            intersection += min(record.second, mapB[record.first]);
    });
    int unionSize = (int)objectA.size() + (int)objectB.size();
    return 1. - intersection / unionSize;
}
template <typename T, typename dt, typename R>
R JaccardSimilarityIterable(T objectA, T objectB) { // vectors and other iterables
    return 1. - JaccardDistanceIterable<T, dt, R>(objectA, objectB);
}
template <typename T, typename R>
R HammingDistanceIterable(T objectA, T objectB) { // vectors and other iterables
    assert(objectA.size() == objectB.size());
    int deltas = 0;
    auto itB = begin(objectB);
    for_each(begin(objectA), end(objectA), [&](auto record) {
        deltas += int(record == *itB); itB ++;
    });
    return 1. - 1. * deltas / int(objectA.size());
}
template <typename T, typename R>
R HammingDistance(T objectA, T objectB) { // arrays
    // for custom data types
    // use (std::is_base_of<your_data_type, iterables>::value) or some other option
    assert(sizeof(objectA) && sizeof(objectB));
    assert(sizeof(objectA) / sizeof(objectA[0]) == sizeof(objectB) / sizeof(objectB[0]));
    R deltas = 0;
    int length = sizeof(objectA) / sizeof(objectA[0]);
    for (int i = 0; i < length; i ++)
        deltas += int(objectA[i] != objectB[i]);
    return 1. * deltas / length;
}

template <typename T, typename R>
R CosineDistanceIterable(T objectA, T objectB) { // vectors and other iterables
    assert(objectA.size() == objectB.size());
    R dotProduct = 0;
    auto itB = begin(objectB);
    for_each(begin(objectA), end(objectA), [&](auto record) {
        dotProduct += 1. * record * (*itB); itB ++;
    });
    R normA = accumulate(begin(objectA), end(objectA), 0., [](R result, R record) {
        return result + 1. * record * record;
    }); normA = sqrtl(normA);
    R normB = accumulate(begin(objectB), end(objectB), 0., [](R result, R record) {
        return result + 1. * record * record;
    }); normB = sqrtl(normB);
    return 1. * dotProduct / normA / normB;
}
template <typename T, typename R>
R CosineDistance(T objectA, T objectB) { // arrays
    // for custom data types
    // use (std::is_base_of<your_data_type, iterables>::value) or some other option
    assert(sizeof(objectA) && sizeof(objectB));
    assert(sizeof(objectA) / sizeof(objectA[0]) == sizeof(objectB) / sizeof(objectB[0]));
    int length = sizeof(objectA) / sizeof(objectA[0]);
    R dotProduct = 0;
    for (int i = 0; i < length; i ++)
        dotProduct += 1. * objectA[i] * objectB[i];
    R normA = accumulate(objectA, objectA + length, 0., [](R result, R record) {
        return result + 1. * record * record;
    }); normA = sqrtl(normA);
    R normB = accumulate(objectB, objectB + length, 0., [](R result, R record) {
        return result + 1. * record * record;
    }); normB = sqrtl(normB);
    return 1. * dotProduct / normA / normB;
}

template <typename T, typename R>
R EditDistance(T objectA, T objectB) {
    int lA = int(objectA.size());
    int lB = int(objectB.size());
    vector<vector<int>> dpTables(lA + 1);
    for_each(begin(dpTables), end(dpTables), [=](auto &row) {
        row.resize(lB + 1);
    });
    for (int i = 0; i <= lA; i ++) {
        for (int j = 0; j <= lB; j ++) {
            if (i == 0) dpTables[i][j] = j;
            else if (j == 0) dpTables[i][j] = i;
            else if (objectA[i] == objectB[j])
                dpTables[i][j] = dpTables[i - 1][j - 1];
            else dpTables[i][j] = min({dpTables[i - 1][j], dpTables[i][j - 1], dpTables[i - 1][j - 1]}) + 1;
        }
    }
    return dpTables[lA][lB];
}
template <typename T, typename R>
R EditDistanceWithWeights(T objectA, T objectB) {
    // to be implemented
}
