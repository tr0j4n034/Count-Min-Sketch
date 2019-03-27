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
CWSEngineIoffe<T>::CWSEngineIoffe() {
    r = GammaRandomVar<T>(2., 1.);
    c = GammaRandomVar<T>(2., 1.);
    b = UniformRandomVar<T>(0., 1.);
}
template<typename T>
void CWSEngineIoffe<T>::resetVarsIoffe() {
    r = GammaRandomVar<T>(2., 1.);
    c = GammaRandomVar<T>(2., 1.);
    b = UniformRandomVar<T>(0., 1.);
}
template<typename T>
template<typename R, typename V>
CWSSketch<T> CWSEngineIoffe<T>::getSketchIterableIoffe(const R& stream, int sketchSize) {
    CWSSketch<T> sk;
    std::map<V, int> streamBins = StreamToBinsIterable(stream);
    for (int it = 0; it < sketchSize; it ++) {
        resetVarsIoffe();
        T minHashElement, minHash = 1e308;
        for_each(begin(streamBins), end(streamBins), [&](auto& element) {
            T rval = r.generate();
            T bval = b.generate();
            T cval = c.generate();
            T delta = 1. * rval * (int(std::log(1. * element.second / rval + bval)) - bval);
            T y = std::exp(delta);
            T z = y * std::exp(rval);
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
CWSSketch<T> CWSEngineIoffe<T>::getSketchIoffe(const R& stream, int sketchSize) {
    CWSSketch<T> sk;
    std::map<V, int> streamBins = StreamToBins(stream);
    for (int it = 0; it < sketchSize; it ++) {
        T minHashElement, minHash = 1e308;
        for_each(stream, *(&stream + 1), [&](auto& element) {
            T rval = r.generate();
            T y = std::exp(std::log(element.second) + rval * b.generate());
            T aux = c.generate() / (y * std::exp(rval));
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
CWSEngineIoffe<T>::~CWSEngineIoffe() {
    
}



template<typename T>
CWSEngineManasse<T>::CWSEngineManasse() {
    u = UniformRandomVar<T>(0, 1);
}

//template<typename T>
//template<typename R, typename V>
//CWSSketch<T> CWSEngineManasse<T>::getSketchIterableManasse(const R& stream, int sketchSize) {
//    CWSSketch<T> sk;
//    std::map<V, int> streamBins = StreamToBinsIterable(stream);
//    for_each(begin(streamBins), end(streamBins), [&](auto &element) {
//        int counter = int(std::round(u.generate() * element.second));
//        T hashvalue = 0; // ** fix later **
//        double chosingProbability = u.generate();
//        double chosingThreshold = 1. * element.second / int(stream.size());
//        if (chosingProbability >= chosingThreshold)
//    });
//}


template<typename T>
CWSEngineManasse<T>::~CWSEngineManasse() {
    
}


#endif /* CWSLib_cpp */
