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

#include <utility>
#include <algorithm>

#include "CWSSketch.cpp"

#include "CWSLib.hpp"
#include "ExtraFactory.hpp"

template<typename T>
CWSEngineIoffe<T>::CWSEngineIoffe() {
    seed = 42;
    r = GammaRandomVar<T>(2., 1., seed);
    c = GammaRandomVar<T>(2., 1., seed);
    b = UniformRandomVar<T>(0., 1., seed);
}
template<typename T>
CWSEngineIoffe<T>::CWSEngineIoffe(int __seed) {
    seed = __seed;
    r = GammaRandomVar<T>(2., 1., seed);
    c = GammaRandomVar<T>(2., 1., seed);
    b = UniformRandomVar<T>(0., 1., seed);
}
template<typename T>
void CWSEngineIoffe<T>::resetVarsIoffe() {
    r = GammaRandomVar<T>(2., 1., seed);
    c = GammaRandomVar<T>(2., 1., seed);
    b = UniformRandomVar<T>(0., 1., seed);
}
template<typename T>
template<typename R, typename V>
CWSSketch<T> CWSEngineIoffe<T>::getSketchIterableIoffe(const R& stream, int sketchSize, int globeSize) {
    CWSSketch<T> sk;
    // std::map<V, int> streamBins = StreamToBinsIterable(stream);
    auto streamBins = stream;
    
    resetVarsIoffe();
    for (int it = 0; it < sketchSize; it ++) {
        T minHashElement, minHash = 1e308;
        T minArgv = 1e308;
        int elemID = 0;
        for_each(begin(stream), end(stream), [&](auto& element) {
            T rval = r.generate();
            T bval = b.generate();
            T cval = c.generate();
            
            double vlog = std::log(1. * element);
            double delta = std::floor(vlog / rval + bval);
            double lny = (delta - bval) * rval;
            double lna = cval - lny - rval;
            
            if (lna < minArgv) {
                minArgv = lna;
                minHashElement = elemID;
                minHash = int(delta);
            }
            elemID ++;
        });
        sk.append(minHashElement, minHash);
    }
    return sk;
}
template<typename T>
template<typename R, typename V>
CWSSketch<T> CWSEngineIoffe<T>::getSketchIoffe(const R& stream, int sketchSize, int globeSize) {
    resetVarsIoffe();
    CWSSketch<T> sk;
    std::map<V, int> streamBins = StreamToBins(stream);
    for (int it = 0; it < sketchSize; it ++) {
        T minHashElement, minHash = 1e308;
        for_each(stream, *(&stream + 1), [&](auto& element) {
            T rval = r.generate();
            T y = std::exp(std::log(1. * element.second) + rval * b.generate());
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
    seed = 42;
    u = UniformRandomVar<T>(0., 1., seed);
}
template<typename T>
CWSEngineManasse<T>::CWSEngineManasse(int __seed) {
    seed = __seed;
    u = UniformRandomVar<T>(0., 1., seed);
}
template<typename T>
void CWSEngineManasse<T>::resetVarsManasse() {
    u = UniformRandomVar<T>(0., 1., seed);
}
template<typename T>
template<typename R, typename V>
CWSSketch<T> CWSEngineManasse<T>::getSketchIterableManasseNaive(const R& stream, int sketchSize) {
    CWSSketch<T> sk;
    std::hash<std::string> hasher;
    std::map<V, int> streamBins = StreamToBinsIterable(stream);
    std::vector<std::pair<int, int>> starters;
    int counter = 0;
    for_each(begin(streamBins), end(streamBins), [&](auto &element) {
        starters.push_back(std::make_pair(counter, element.first));
        counter += element.second;
    });
    resetVarsManasse();
    for (int it = 0; it < sketchSize; it ++) {
        double uout = u.generate();
        int position = int(std::round(1. * uout * int(stream.size())));
        auto item = --upper_bound(begin(starters), end(starters), std::make_pair(position + 1, -1));
        sk.append((*item).second, hasher(toString((*item).second)));
    }
    return sk;
}

template<typename T>
CWSEngineManasse<T>::~CWSEngineManasse() {
    
}


#endif /* CWSLib_cpp */
