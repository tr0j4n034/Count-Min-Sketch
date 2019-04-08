//
//  Random.hpp
//  CountMin Sketch
//
//  Created by Mahmud on 3/25/19.
//  Copyright © 2019 Mahmud. All rights reserved.
//

#ifndef Random_hpp
#define Random_hpp

#include <random>

using std::vector;

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
    int seed;
    std::random_device rd;
    std::mt19937 generator;
    std::uniform_int_distribution<int> dist;
public:
    Random();
    Random(int __range, int seed = 42);
    
    void setSeed(int __seed);
    
    int getRange();
    std::mt19937 getGenerator();
    int generate();
    int generate(int low, int high);
    
    int generatePrimeInRange(int low, int high);
    
    vector<int> generateList(int size, int minValue, int maxValue, int scalingFactor = 1);
    
    ~Random();
};

template<typename T>
class GammaRandomVar {
    T alpha;
    T beta;
    int seed;
    std::default_random_engine dre;
    std::gamma_distribution<T> distribution;
    
public:
    GammaRandomVar();
    GammaRandomVar(T __alpha, T __beta, int seed = 42);
    
    void setSeed(int seed);
    
    T getAlpha();
    T getBeta();
    T generate();
    vector<T> generateList(int size, T scalingFactor = 1);
    
    ~GammaRandomVar();
};

template <typename T>
class UniformRandomVar {
    T lowBound;
    T highBound;
    int seed;
    std::default_random_engine dre;
    std::uniform_real_distribution<T> distribution;
public:
    UniformRandomVar();
    UniformRandomVar(T __low, T __high, int seed = 42);
    
    void setSeed(int seed);
    
    T getLowBound();
    T getHighBound();
    T generate();
    vector<T> generateList(int size, T scalingFactor = 1);
    
    ~UniformRandomVar();
};


#if __has_include("boost/random.hpp")
#include <boost/random.hpp>

template <typename T>
class BetaRandomVar {
    T alpha;
    T beta;
    int seed;
    boost::random::mt19937 rng = boost::random::mt19937(1ULL * unsigned(time(NULL)) * clock() * rand() % (1 << 30));
    boost::random::beta_distribution<> distribution;
    
public:
    BetaRandomVar();
    BetaRandomVar(T __alpha, T __beta);
    T getAlpha();
    T getBeta();
    T generate();
    vector<T> generateList(int size, T scalingFactor = 1);
    
    ~BetaRandomVar();
};

#endif


#endif /* Random_hpp */
