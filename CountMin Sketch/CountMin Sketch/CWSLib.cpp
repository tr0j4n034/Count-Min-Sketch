//
//  CWSLib.cpp
//  CountMin Sketch
//
//  Created by Mahmud on 1/26/19.
//  Copyright © 2019 Mahmud. All rights reserved.
//

#pragma once

#ifndef CWSLib_cpp
#define CWSLib_cpp

#include "CWSSketch.cpp"
#include "CWSLib.hpp"

template<typename T>
CWSEngine<T>::CWSEngine() {
    r = GammaRandomVar<T>(2., 1.);
    c = GammaRandomVar<T>(2., 1.);
    b = UniformRandomVar<T>(0., 1.);
}
template<typename T>
void CWSEngine<T>::resetVars() {
    r = GammaRandomVar<T>(2., 1.);
    c = GammaRandomVar<T>(2., 1.);
    b = UniformRandomVar<T>(0., 1.);
}
template<typename T>
template<typename R, typename V>
CWSSketch<T> CWSEngine<T>::getSketchIterable(R& stream, int sketchSize) {
    CWSSketch<T> sk;
    std::map<V, int> streamBins = StreamToBinsIterable(stream);
    for (int it = 0; it < sketchSize; it ++) {
        resetVars();
        T minHashElement, minHash = 1e308;
        for_each(begin(streamBins), end(streamBins), [&](auto &element) {
            T rval = r.generate();
            T bval = b.generate();
            T cval = c.generate();
            T delta = 1. * rval * (int(log(1. * element.second / rval + bval)) - bval);
            T y = exp(delta);
            T z = y * exp(rval);
            T aux = cval / z;
            if (aux < minHash) {
                minHashElement = element.first;
                minHash = aux;
            }
        });
        sk.append(minHashElement, minHash);
    }
    return sk;
}
template<typename T>
template<typename R, typename V>
CWSSketch<T> CWSEngine<T>::getSketch(R& stream, int sketchSize) {
    CWSSketch<T> sk;
    std::map<V, int> streamBins = StreamToBins(stream);
    for (int it = 0; it < sketchSize; it ++) {
        T minHashElement, minHash = 1e308;
        for_each(stream, *(&stream + 1), [&](auto &element) {
            T rval = r.generate();
            T y = exp(log(element.second) + rval * b.generate());
            T aux = c.generate() / (y * exp(rval));
            if (aux < minHash) {
                minHashElement = element.first;
                minHash = aux;
            }
        });
        sk.append(minHashElement, minHash);
    }
    return sk;
}
template<typename T>
CWSEngine<T>::~CWSEngine() {
    
}


#endif /* CWSLib_cpp */
