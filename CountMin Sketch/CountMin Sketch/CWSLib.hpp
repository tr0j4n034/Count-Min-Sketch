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
class CWSEngineIoffe {
    GammaRandomVar<T> r;
    GammaRandomVar<T> c;
    UniformRandomVar<T> b;
public:
    CWSEngineIoffe();
    void resetVarsIoffe();
    
    template<typename R, typename V = int>
    CWSSketch<T> getSketchIterableIoffe(const R &stream, int sketchSize = 1000);
    
    template<typename R, typename V = int>
    CWSSketch<T> getSketchIoffe(const R& stream, int sketchSize = 1000);
    
    ~CWSEngineIoffe();
};
template<typename T>
class CWSEngineManasse {
    UniformRandomVar<T> u;
public:
    CWSEngineManasse();
    template<typename R, typename V = int>
    CWSSketch<T> getSketchIterableManasse(const R& stream, int sketchSize = 1000);
    
    template<typename R, typename V = int>
    CWSSketch<T> getSketchManasse(const R& stream, int sketchSize = 1000);
    
    ~CWSEngineManasse();
};

#endif /* CWSLib_hpp */
