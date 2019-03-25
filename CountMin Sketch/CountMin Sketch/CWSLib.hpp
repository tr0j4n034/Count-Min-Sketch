//
//  CWSLib.hpp
//  CountMin Sketch
//
//  Created by Mahmud on 3/25/19.
//  Copyright © 2019 Mahmud. All rights reserved.
//

#ifndef CWSLib_hpp
#define CWSLib_hpp

template <typename T>
class CWSEngine {
    GammaRandomVar<T> r;
    GammaRandomVar<T> c;
    UniformRandomVar<T> b;
public:
    CWSEngine();
    void resetVars();
    
    template<typename R, typename V = int>
    CWSSketch<T> getSketchIterable(R &stream, int sketchSize = 5);
    
    template<typename R, typename V = int>
    CWSSketch<T> getSketch(R &stream, int sketchSize = 5);
    
    ~CWSEngine();
};

#endif /* CWSLib_hpp */
