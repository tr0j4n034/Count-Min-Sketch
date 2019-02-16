//
//  Random.h
//  CountMin Sketch
//
//  Created by Mahmud on 1/14/19.
//  Copyright © 2019 Mahmud. All rights reserved.
//

#pragma once

#ifndef Random_h
#define Random_h


#endif /* Random_h */

#include <ctime>
#include <random>

const int PRIME_CHECK_TRIALS = 1 << 7;

template<typename T>
auto isPrime(T N) {
    if (N < 2) return false;
    for (int i = 2; 1LL * i * i <= N; i ++) {
        if (N % i == 0) return false;
    }
    return true;
}

class Random { // PseudoRandom number generator
private:
    int range;
    std::random_device rd;
    std::mt19937 generator;
    std::uniform_int_distribution<int> dist;
public:
    Random() {}
    Random(int __range):
    range(__range), generator(rd()),
    dist(std::uniform_int_distribution<>(0, __range - 1)){
        generator.seed(unsigned(time((NULL))));
    }
    int getRange() {
        return range;
    }
    mt19937 getGenerator() {
        return generator;
    }
    int generate() {
        return dist(generator);
    }
    int generate(int low, int high) { // generate int particular range
        return low + 1ULL * dist(generator) % (high - low + 1);
    }
    int generatePrimeInRange(int low, int high) {
        int result = -1;
        for (int trials = 0; trials < PRIME_CHECK_TRIALS; trials ++) {
            result = generate(low, high);
            if (isPrime(result)) return result;
        }
        return -1;
    }
    vector<int> generateList(int size, int minValue, int maxValue, int scalingFactor = 1) {
        vector<int> list(size);
        for_each(begin(list), end(list), [=](int &elem) {
            elem = scalingFactor * generate(minValue, maxValue);
        });
        return list;
    }
    ~Random() {
        
    }
};

template<typename T>
class GammaRandomVar {
    T alpha;
    T beta;
    default_random_engine dre;
    gamma_distribution<T> distribution;
    
public:
    GammaRandomVar() {
        alpha = 0;
        beta = 0;
        dre = default_random_engine(1ULL * unsigned(time(NULL)) * clock() * rand() % (1 << 30));
        distribution = gamma_distribution<T>(alpha, beta);
    }
    GammaRandomVar(T __alpha, T __beta) {
        alpha = __alpha;
        beta = __beta;
        dre = default_random_engine(1ULL * unsigned(time(NULL)) * clock() * rand() % (1 << 30));
        distribution = gamma_distribution<T>(alpha, beta);
    }
    T getAlpha() {
        return alpha;
    }
    T getBeta() {
        return beta;
    }
    T generate() {
        return distribution(dre);
    }
    vector<T> generateList(int size, T scalingFactor = 1) {
        vector<T> list(size);
        for_each(begin(list), end(list), [=](T &elem) {
            elem = scalingFactor * generate();
        });
        return list;
    }
    ~GammaRandomVar() {
        
    }
};

template <typename T>
class UniformRandomVar {
    T lowBound;
    T highbound;
    default_random_engine dre;
    uniform_real_distribution<T> distribution;
public:
    UniformRandomVar() {}
    UniformRandomVar(T __low, T __high) {
        lowBound = __low;
        highbound = __high;
        dre = default_random_engine(1ULL * unsigned(time(NULL)) * clock() * rand() % (1 << 30));
        distribution = uniform_real_distribution<T>(lowBound, highbound);
    }
    T getLowBound() {
        return lowBound;
    }
    T getHighBound() {
        return highbound;
    }
    T generate() {
        return distribution(dre);
    }
    vector<T> generateList(int size, T scalingFactor = 1) {
        vector<T> list(size);
        for_each(begin(list), end(list), [=](T &elem) {
            elem = scalingFactor * generate();
        });
        return list;
    }
    ~UniformRandomVar() {
        
    }
};


#if __has_include("boost/random.hpp")
#include <boost/random.hpp>

template <typename T>
class BetaRandomVar {
    T alpha;
    T beta;
    boost::random::mt19937 rng = boost::random::mt19937(1ULL * unsigned(time(NULL)) * clock() * rand() % (1 << 30));
    boost::random::beta_distribution<> distribution;
    
public:
    BetaRandomVar() {}
    BetaRandomVar(T __alpha, T __beta) {
        alpha = __alpha;
        beta = __beta;
        distribution = boost::random::beta_distribution<T>(alpha, beta);
    }
    T getAlpha() {
        return alpha;
    }
    T getBeta() {
        return beta;
    }
    T generate() {
        return distribution(rng);
    }
    vector<T> generateList(int size, T scalingFactor = 1) {
        vector<T> list(size);
        for_each(begin(list), end(list), [=](T &elem) {
            elem = scalingFactor * generate();
        });
        return list;
    }
    ~BetaRandomVar() {
        
    }
};

#endif
