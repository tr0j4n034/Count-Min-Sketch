//
//  CWSSketch.h
//  CountMin Sketch
//
//  Created by Mahmud on 1/28/19.
//  Copyright © 2019 Mahmud. All rights reserved.
//

#ifndef CWSSketch_h
#define CWSSketch_h


#endif /* CWSSketch_h */

#include <vector>

template <typename T>
class CWSSketch {
    vector<T> sketchElements;
    vector<T> sketchHashes;
public:
    CWSSketch() {}
    CWSSketch(vector<T> __elems, vector<T> __hashes) {
        if (int(__elems.size()) != int(__hashes.size()))
            throw runtime_error("the sets should have the same size!");
        sketchElements = __elems;
        sketchHashes = __hashes;
    }
    CWSSketch(int __size) {
        sketchElements.resize(__size);
        sketchHashes.resize(__size);
    }
    void append(T __element, T __hash) {
        sketchElements.push_back(__element);
        sketchHashes.push_back(__hash);
    }
    vector<T> getSketchElems() {
        return sketchElements;
    }
    vector<T> getSketchHashes() {
        return sketchHashes;
    }
    void clear() {
        sketchElements.clear();
        sketchHashes.clear();
    }
};
