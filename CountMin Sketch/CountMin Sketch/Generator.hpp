//
//  Generator.hpp
//  CountMin Sketch
//
//  Created by Mahmud on 3/25/19.
//  Copyright © 2019 Mahmud. All rights reserved.
//

#ifndef Generator_hpp
#define Generator_hpp

const int MAX_BIT = 29;

std::vector<int> generateRandomList
    (int setSize, int maxRange = 1 << 20, int seed = -1);
template <typename T = double>
std::vector<T> generateRandomListViaGamma
    (int setSize, GammaRandomVar<T> g, double scaler = 1., int seed = -1);

template <typename T = double>
std::vector<T> generateRandomListViaGammaParams
    (int setSize, T alpha, T beta, double scaler = 1., int seed = -1);

#if __has_include("boost/random.hpp")
template<typename T = double>
std::vector<T> generateRandomListViaBeta
    (int setSize, BetaRandomVar<T> b, double scaler = 1., int seed = -1);

template<typename T = double>
std::vector<T> generateRandomListViaBetaParams
    (int setSize, T alpha, T beta, double scaler = 1., int seed = -1);
#endif

std::vector<std::vector<int>> generateRandomDataSet
    (int dataSetSize, int setSize, int maxRange = 1 << 20, int seed = -1);

std::vector<std::vector<int>> generateRandomPair
    (int sizeA, int sizeB = -1, bool sameSize = true, int maxRange = 1 << 20, int seed = -1);

std::vector<std::vector<int>> generatePairWithSimilarity
    (int sizeA, double similarity, int sizeB = -1, bool sameSize = true, int seed = -1);


#endif /* Generator_hpp */
