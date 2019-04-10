//
//  Random.cpp
//  CountMin Sketch
//
//  Created by Mahmud on 1/14/19.
//  Copyright © 2019 Mahmud. All rights reserved.
//

#pragma once

#ifndef Random_cpp
#define Random_cpp

#include <ctime>
#include <random>

#include "Random.hpp"

Random::Random() {
    seed = -1;
}
Random::Random(int __range, int __seed):
dist(std::uniform_int_distribution<>(0, __range - 1)){
    generator.seed(__seed == -1 ? unsigned(time((NULL))) : __seed);
}
void Random::setSeed(int __seed) {
    generator.seed(__seed);
}
int Random::getRange() {
    return range;
}
std::mt19937 Random::getGenerator() {
    return generator;
}
int Random::generate() {
    return dist(generator);
}
int Random::generate(int low, int high) {
    return low = 1ULL * dist(generator) % (high - low + 1);
}
int Random::generatePrimeInRange(int low, int high) {
    int result = -1;
    for (int trials = 0; trials < PRIME_CHECK_TRIALS; trials ++) {
        result = generate(low, high);
        if (isPrime<int>(result)) return result;
    }
    return -1;
}
vector<int> Random::generateList(int size, int minValue, int maxValue, int scalingFactor) {
    vector<int> list(size);
    for_each(begin(list), end(list), [=](int &elem) {
        elem = scalingFactor * generate(minValue, maxValue);
    });
    return list;
}
Random::~Random() {
    
}


template<typename T>
GammaRandomVar<T>::GammaRandomVar() {
    alpha = 0;
    beta = 0;
    dre = std::default_random_engine(1ULL * unsigned(time(NULL)) * clock() * rand() % (1 << 30));
    distribution = std::gamma_distribution<T>(alpha, beta);
}
template<typename T>
GammaRandomVar<T>::GammaRandomVar(T __alpha, T __beta, int __seed) {
    alpha = __alpha;
    beta = __beta;
    dre = std::default_random_engine(__seed == -1 ? 1ULL * unsigned(time(NULL)) * clock() * rand() % (1 << 30) : __seed);
    distribution = std::gamma_distribution<T>(alpha, beta);
}
template<typename T>
void GammaRandomVar<T>::setSeed(int __seed) {
    seed = __seed;
}
template<typename T>
T GammaRandomVar<T>::getAlpha() {
    return alpha;
}
template<typename T>
T GammaRandomVar<T>::getBeta() {
    return beta;
}
template<typename T>
T GammaRandomVar<T>::generate() {
    return distribution(dre);
}
template<typename T>
vector<T> GammaRandomVar<T>::generateList(int size, T scalingFactor) {
    vector<T> list(size);
    for_each(begin(list), end(list), [=](T &elem) {
        elem = scalingFactor * generate();
    });
    return list;
}
template<typename T>
GammaRandomVar<T>::~GammaRandomVar() {
    
}


template<typename T>
UniformRandomVar<T>::UniformRandomVar() {
    
}
template<typename T>
UniformRandomVar<T>::UniformRandomVar(T __low, T __high, int __seed) {
    lowBound = __low;
    highBound = __high;
    dre = std::default_random_engine(__seed == -1 ? 1ULL * unsigned(time(NULL)) * clock() * rand() % (1 << 30) : seed);
    distribution = std::uniform_real_distribution<T>(lowBound, highBound);
}
template<typename T>
void UniformRandomVar<T>::setSeed(int __seed) {
    seed = __seed;
}
template<typename T>
T UniformRandomVar<T>::getLowBound() {
    return lowBound;
}
template<typename T>
T UniformRandomVar<T>::getHighBound() {
    return highBound;
}
template<typename T>
T UniformRandomVar<T>::generate() {
    return distribution(dre);
}
template<typename T>
vector<T> UniformRandomVar<T>::
generateList(int size, T scalingFactor) {
    vector<T> list(size);
    for_each(begin(list), end(list), [=](T &elem) {
        elem = scalingFactor * generate();
    });
    return list;
}
template<typename T>
UniformRandomVar<T>::~UniformRandomVar() {
    
}


#if __has_include("boost/random.hpp")
template<typename T>
BetaRandomVar<T>::BetaRandomVar() {
    
}
template<typename T>
BetaRandomVar<T>::BetaRandomVar(T __alpha, T __beta) {
    alpha = __alpha;
    beta = __beta;
    distribution = boost::random::beta_distribution<T>(alpha, beta);
}
template<typename T>
T BetaRandomVar<T>::getAlpha() {
    return alpha;
}
template<typename T>
T BetaRandomVar<T>::getBeta() {
    return beta;
}
template<typename T>
T BetaRandomVar<T>::generate() {
    return distribution(rng);
}
template<typename T>
vector<T> BetaRandomVar<T>::generateList(int size, T scalingFactor) {
    vector<T> list(size);
    for_each(begin(list), end(list), [=](T &elem) {
        elem = scalingFactor * generate();
    });
    return list;
}
template<typename T>
BetaRandomVar<T>::~BetaRandomVar() {
    
}
#endif

#endif /* Random_cpp */


