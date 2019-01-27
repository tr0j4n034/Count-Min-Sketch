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

template <typename T>
class CWSEngine {
    GammaRandomVar<T> r = GammaRandomVar<T>(2, 1);
    GammaRandomVar<T> c = GammaRandomVar<T>(2, 1);
    UniformRandomVar<T> b = UniformRandomVar<T>(0, 1);
public:
    CWSEngine() {
        
    }
};
