//
//  SimLib.h
//  CountMin Sketch
//
//  Created by Mahmud on 1/17/19.
//  Copyright © 2019 Mahmud. All rights reserved.
//

#ifndef SimLib_h
#define SimLib_h


#endif /* SimLib_h */

#include <cassert>

template <typename T, typename R>
R EuclideanDistance(T objectA, T objectB) { // vectors or other iterables
    // for custom data types
    // use (std::is_base_of<your_data_type, iterables>::value) or some other option
    assert((int)objectA.size() == (int)objectB.size());
    auto itB = begin(objectB);
    transform(begin(objectA), end(objectA), begin(objectA), [&](R value) {
        return value - (*itB ++);
    });
    R result = accumulate(begin(objectA), end(objectA), 0, [](R currentResult, R delta) {
        return currentResult + delta * delta;
    });
    return result;
}
