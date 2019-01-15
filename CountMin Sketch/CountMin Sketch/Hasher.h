//
//  Hasher.h
//  CountMin Sketch
//
//  Created by Mahmud on 1/14/19.
//  Copyright © 2019 Mahmud. All rights reserved.
//

#ifndef Hasher_h
#define Hasher_h


#endif /* Hasher_h */

#include "Random.h"

const int MAX_COEFFICIENT = INT_MAX;
long long SALT = 0;

template <typename T>
class Hasher { // (AX + B) % C
    T A;
    T B;
    T C;
public:
    Hasher() {
        A = 0;
        B = 0;
        C = 0;
    }
    Hasher(T __A, T __B, T __C) {
        A = __A;
        B = __B;
        C = __C;
    }
    Hasher(T maxRange = MAX_COEFFICIENT) {
        Random device = Random(1LL * (unsigned int)clock() * SALT % INT_MAX);
        SALT ^= 1LL * rand() * rand() % INT_MAX;
        A = device.generatePrimeInRange(2, ((maxRange >> 3) < 3 ? 3 : (maxRange >> 3)));
        B = device.generatePrimeInRange(2, (maxRange - 1 < 3 ? 3: maxRange - 1));
        C = device.generatePrimeInRange(maxRange >> 2, maxRange);
    }
    Hasher(T fixedC, T maxRange = MAX_COEFFICIENT) {
        Random device = Random(1LL * (unsigned int)clock() * SALT % INT_MAX);
        SALT ^= 1LL * rand() * rand() % INT_MAX;
        A = device.generatePrimeInRange(2, ((maxRange >> 3) < 3 ? 3 : (maxRange >> 3)));
        B = device.generatePrimeInRange(2, (maxRange - 1 < 3 ? 3: maxRange - 1));
        C = fixedC;
    }
    T getA() {
        return A;
    }
    T getB() {
        return B;
    }
    T getC() {
        return C;
    }
    T getHash(T data) {
        return (1ULL * A * data + B) % C + 1;
    }
};
