//
//  CWSSketch.hpp
//  CountMin Sketch
//
//  Created by Mahmud on 3/25/19.
//  Copyright © 2019 Mahmud. All rights reserved.
//

#ifndef CWSSketch_hpp
#define CWSSketch_hpp

using std::vector;

template <typename T>
class CWSSketch {
    vector<T> sketchElements;
    vector<T> sketchHashes;
public:
    CWSSketch();
    CWSSketch(const vector<T> &__elems, const vector<T> &__hashes);
    CWSSketch(int __size);
    
    void append(T __element, T __hash);
    int getCWSSketchSize();
    vector<T> getSketchElems();
    vector<T> getSketchHashes();
    
    void clear();
    
    ~CWSSketch();
};

#endif /* CWSSketch_hpp */
