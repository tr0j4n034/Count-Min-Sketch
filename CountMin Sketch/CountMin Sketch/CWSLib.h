//
//  CWSLib.h
//  CountMin Sketch
//
//  Created by Mahmud on 1/26/19.
//  Copyright © 2019 Mahmud. All rights reserved.
//

#ifndef CWSLib_h
#define CWSLib_h


#endif /* CWSLib_h */

#include "CWSSketch.h"

template <typename T>
class CWSEngine {
    GammaRandomVar<T> r;
    GammaRandomVar<T> c;
    UniformRandomVar<T> b;
public:
    CWSEngine() {
        r = GammaRandomVar<T>(2, 1);
        c = GammaRandomVar<T>(2, 1);
        b = UniformRandomVar<T>(0, 1);
    }
    template<typename R>
    CWSSketch<T> getSketchIterable(R &stream, int sketchSize = 5) {
        CWSSketch<T> sk;
        for (int it = 0; it < sketchSize; it ++) {
            T minHashElement, minHash = 1e308;
            for_each(begin(stream), end(stream), [&](auto &element){
                T rval = r.generate();
                T y = exp(log(element) + rval * b.generate());
                T aux = c.generate() / (y * exp(rval));
                if (aux < minHash) {
                    minHashElement = element;
                    minHash = aux;
                }
            });
            sk.append(minHashElement, minHash);
        }
        return sk;
    }
};
