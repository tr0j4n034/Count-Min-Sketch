//
//  Random.h
//  CountMin Sketch
//
//  Created by Mahmud on 1/14/19.
//  Copyright © 2019 Mahmud. All rights reserved.
//

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

class Random {
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
};
