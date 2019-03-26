//
//  Hasher.hpp
//  CountMin Sketch
//
//  Created by Mahmud on 3/25/19.
//  Copyright © 2019 Mahmud. All rights reserved.
//

#ifndef Hasher_hpp
#define Hasher_hpp

#include "Random.cpp"

template <typename T>
class Hasher { // (AX + B) % C
    T A;
    T B;
    T C;
public:
    Hasher();
    Hasher(T __A, T __B, T __C);
    Hasher(T maxRange);
    
    T getA();
    T getB();
    T getC();
    T getHash(T data);
    
    ~Hasher();
    
    std::string describe();
};

#endif /* Hasher_hpp */
