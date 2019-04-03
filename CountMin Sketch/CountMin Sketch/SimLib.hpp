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
R EuclideanDistanceIterable(const T& objectA, const T& objectB);

template <typename T, typename R>
R EuclideanDistance(const T& objectA, const T& objectB);

template <typename T, typename R>
R ManhattanDistanceIterable(const T& objectA, const T& objectB);

template <typename T, typename R>
R ManhattanDistance(const T& objectA, const T& objectB);

template <typename T, typename dt, typename R>
R JaccardDistanceIterable(const T& objectA, const T& objectB, bool makeUnweighted = false);

template<typename T, typename dt, typename R>
R JaccardDistanceBinned(const T& binsA, const T& binsB, bool makeUnweighted = false);

template<typename T, typename dt, typename R>
R JaccardSimilarityBinned(const T& binsA, const T& binsB, bool makeUnweighted = false);

template <typename T, typename dt, typename R>
R JaccardSimilarityIterable(const T& objectA, const T& objectB);

template <typename T, typename dt, typename R>
R JaccardDistance(const T& objectA, const T& objectB, bool makeUnweighted = false);

template <typename T, typename dt, typename R>
R JaccardSimilarity(const T& objectA, const T& objectB);

template <typename T, typename R>
R HammingDistanceIterable(const T& objectA, const T& objectB);

template <typename T, typename R>
R HammingSimilarityIterable(const T& objectA, const T& objectB);

template <typename T, typename R>
R HammingDistance(const T& objectA, const T& objectB);

template <typename T, typename R>
R CosineDistanceIterable(const T& objectA, const T& objectB);

template <typename T, typename R>
R CosineSimilarityIterable(const T& objectA, const T& objectB);

template <typename T, typename R>
R CosineDistance(const T& objectA, const T& objectB);

template <typename T, typename R>
R CosineSimilarity(const T& objectA, const T& objectB);

template <typename T>
int EditDistance(const T& objectA, const T& objectB);

template <typename T = std::vector<int>, typename R = int>
std::map<R, int> StreamToBinsIterable(const T &stream);

template <typename T, typename R = int>
std::map<R, int> StreamToBins(const T &stream);

template <typename T, typename R = int>
std::vector<R> StreamToBinsIterableGlobe(const T& stream, int globeSize = -1);

template <typename T, typename R = int>
std::vector<R> StreamToBinsGlobe(const T& stream, int globeSize = -1);

template<typename R = int>
std::vector<R> BinsToStream(const std::vector<R>& bins);

template<typename T = int, typename R = double>
R HammingDistanceCMSTables(const CMSTable<T>& tableA, const CMSTable<T>& tableB, bool outliersIn = true);


#endif /* SimLib_h */
