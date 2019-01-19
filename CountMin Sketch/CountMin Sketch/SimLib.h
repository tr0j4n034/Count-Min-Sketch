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
    
}
template <typename T, typename R>
R HammingDistance(T objectA, T objectB) { // array
}

template <typename T, typename R>
R CosineDistanceIterable(T objectA, T objectB) { // vectors and other iterables
    
}
template <typename T, typename R>
R CosineDistance(T objectA, T objectB) { // arrays
    
}

template <typename T, typename R>
R EditDistance(T objectA, T objectB) {
    
}
