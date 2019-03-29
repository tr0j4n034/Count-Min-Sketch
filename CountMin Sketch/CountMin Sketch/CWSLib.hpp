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
    int seed;
    GammaRandomVar<T> r;
    GammaRandomVar<T> c;
    UniformRandomVar<T> b;
public:
    CWSEngineIoffe();
    CWSEngineIoffe(int __seed);
    void resetVarsIoffe();
    
    template<typename R, typename V = int>
    CWSSketch<T> getSketchIterableIoffe(const R &stream, int sketchSize = 1000, int globeSize = 1000);
    
    template<typename R, typename V = int>
    CWSSketch<T> getSketchIoffe(const R& stream, int sketchSize = 1000, int globeSize = 1000);
    
    ~CWSEngineIoffe();
};
template<typename T>
class CWSEngineManasse {
    int seed;
    UniformRandomVar<T> u;
public:
    CWSEngineManasse();
    CWSEngineManasse(int __seed);
    
    void resetVarsManasse();
    
    template<typename R, typename V = int>
    CWSSketch<T> getSketchIterableManasseNaive(const R& stream, int sketchSize = 1000);
    
//    template<typename R, typename V = int>
//    CWSSketch<T> getSketchManasse(const R& stream, int sketchSize = 1000);
    
    ~CWSEngineManasse();
};

#endif /* CWSLib_hpp */
