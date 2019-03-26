//
//  Hasher.cpp
//  CountMin Sketch
//
//  Created by Mahmud on 1/14/19.
//  Copyright © 2019 Mahmud. All rights reserved.
//

#include "Hasher.hpp"

const int MAX_COEFFICIENT = INT_MAX;
int SALT = 0;

template<typename T>
Hasher<T>::Hasher() {
    A = 0;
    B = 0;
    C = 0;
}
template<typename T>
Hasher<T>::Hasher(T __A, T __B, T __C) {
    A = __A;
    B = __B;
    C = __C;
}
template<typename T>
Hasher<T>::Hasher(T maxRange) {
    Random device(1LL * (unsigned int)clock() * SALT % INT_MAX);
    SALT ^= 1LL * rand() * rand() % (1 << 30);
    A = 1ULL * (SALT + device.generate(2, ((maxRange >> 1) < 3 ? 3 : (maxRange >> 1)))) % MAX_COEFFICIENT + 1;
    B = 1ULL * (SALT + device.generate(2, (maxRange - 1 < 3 ? 3: maxRange - 1))) % MAX_COEFFICIENT + 1;
    C = device.generatePrimeInRange(1 << 27, 1 << 30);
    A %= C;
    B %= C;
}
template<typename T>
T Hasher<T>::getA() {
    return A;
}
template<typename T>
T Hasher<T>::getB() {
    return B;
}
template<typename T>
T Hasher<T>::getC() {
    return C;
}
template<typename T>
T Hasher<T>::getHash(T data) {
    return (1ULL * A * data + B) % C;
}
template<typename T>
Hasher<T>::~Hasher() {
    
}
template<typename T>
std::string Hasher<T>::describe() {
    std::string desc = "hash(x) = (Ax + B) % C\n";
    desc += "A = " + to_string(A) + "\n";
    desc += "B = " + to_string(B) + "\n";
    desc += "C = " + to_string(C) + "\n";
    return desc;
}
