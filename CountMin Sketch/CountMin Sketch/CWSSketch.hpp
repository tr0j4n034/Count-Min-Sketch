//
//  CWSSketch.hpp
//  CountMin Sketch
//
//  Created by Mahmud on 3/25/19.
//  Copyright © 2019 Mahmud. All rights reserved.
//

#ifndef CWSSketch_hpp
#define CWSSketch_hpp

template <typename T>
class CWSSketch {
    std::vector<T> sketchElements;
    std::vector<T> sketchHashes;
public:
    CWSSketch();
    CWSSketch(std::vector<T> __elems, std::vector<T> __hashes);
    CWSSketch(int __size);
    
    void append(T __element, T __hash);
    int getCWSSketchSize();
    std::vector<T> getSketchElems();
    std::vector<T> getSketchHashes();
    
    void clear();
    
    ~CWSSketch();
};

#endif /* CWSSketch_hpp */
