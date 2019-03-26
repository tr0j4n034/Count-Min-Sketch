//
//  SimLib.h
//  CountMin Sketch
//
//  Created by Mahmud on 3/25/19.
//  Copyright © 2019 Mahmud. All rights reserved.
//

#ifndef SimLib_h
#define SimLib_h

#include <map>
#include <unordered_map>

template <typename T, typename R>
R EuclideanDistanceIterable(T objectA, T objectB);

template <typename T, typename R>
R EuclideanDistance(T objectA, T objectB);

template <typename T, typename R>
R ManhattanDistanceIterable(T objectA, T objectB);

template <typename T, typename R>
R ManhattanDistance(T objectA, T objectB);

template <typename T, typename dt, typename R>
R JaccardDistanceIterable(T objectA, T objectB, bool makeUnweighted = false);

template <typename T, typename dt, typename R>
R JaccardSimilarityIterable(T objectA, T objectB);

template <typename T, typename dt, typename R>
R JaccardDistance(T objectA, T objectB, bool makeUnweighted = false);

template <typename T, typename dt, typename R>
R JaccardSimilarity(T objectA, T objectB);

template <typename T, typename R>
R HammingDistanceIterable(T objectA, T objectB);

template <typename T, typename R>
R HammingSimilarityIterable(T objectA, T objectB);

template <typename T, typename R>
R HammingDistance(T objectA, T objectB);

template <typename T, typename R>
R CosineDistanceIterable(T objectA, T objectB);

template <typename T, typename R>
R CosineSimilarityIterable(T objectA, T objectB);

template <typename T, typename R>
R CosineDistance(T objectA, T objectB);

template <typename T, typename R>
R CosineSimilarity(T objectA, T objectB);

template <typename T>
int EditDistance(T objectA, T objectB);

template <typename T = std::vector<int>, typename R = int>
std::map<R, int> StreamToBinsIterable(T &stream);

template <typename T, typename R = int>
std::map<R, int> StreamToBins(T &stream);

template<typename T = int, typename R = double>
R HammingDistanceCMSTables(CMSTable<T>& tableA, CMSTable<T>& tableB, bool outliersIn = true);


#endif /* SimLib_h */
