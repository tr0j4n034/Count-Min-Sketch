//
//  CWSSketch.cpp
//  CountMin Sketch
//
//  Created by Mahmud on 1/28/19.
//  Copyright © 2019 Mahmud. All rights reserved.
//


#include "CWSSketch.hpp"

template<typename T>
CWSSketch<T>::CWSSketch() {
    
}
template<typename T>
CWSSketch<T>::CWSSketch(const vector<T> &__elems, const vector<T> &__hashes) {
    if (int(__elems.size()) != int(__hashes.size()))
        throw std::runtime_error("the sets should have the same size!");
    sketchElements = __elems;
    sketchHashes = __hashes;
}
template<typename T>
CWSSketch<T>::CWSSketch(int __size) {
    sketchElements.resize(__size);
    sketchHashes.resize(__size);
}
template<typename T>
void CWSSketch<T>::append(const T& __element, const T& __hash) {
    sketchElements.push_back(__element);
    sketchHashes.push_back(__hash);
}
template<typename T>
int CWSSketch<T>::getCWSSketchSize() {
    return int(sketchElements.size());
}
template<typename T>
vector<T> CWSSketch<T>::getSketchElems() {
    return sketchElements;
}
template<typename T>
vector<T> CWSSketch<T>::getSketchHashes() {
    return sketchHashes;
}
template<typename T>
void CWSSketch<T>::clear() {
    sketchElements.clear();
    sketchHashes.clear();
}
template<typename T>
CWSSketch<T>::~CWSSketch() {
    
}

