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

template <typename T>
class Hasher { // (AX + B) % C
    T A;
    T B;
    T C;
public:
    Hasher() {
        
    }
    Hasher(T __A, T __B, T __C) {
        A = __A;
        B = __B;
        C = __C;
    }
    Hasher(T maxRange) {
        Random device = Random((int)clock() * (int)rand());
        A = device.generatePrimeInRange(2, maxRange >> 3);
        B = device.generatePrimeInRange(2, maxRange - 1);
        C = device.generatePrimeInRange(maxRange >> 2, maxRange);
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
        return (1ULL * A * data + B) % C;
    }
};
