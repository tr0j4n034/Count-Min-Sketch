//
//  ExtraFactory.cpp
//  CountMin Sketch
//
//  Created by Mahmud on 3/26/19.
//  Copyright © 2019 Mahmud. All rights reserved.
//

#include "ExtraFactory.hpp"
#include "Random.hpp"

template<typename T>
string toString(const T& element) {
    std::ostringstream os;
    os << element;
    return os.str();
}

template<typename T>
string describe(const vector<T>& stream) {
    string result = "[";
    for (auto element: stream) {
        if (result.back() != '[') {
            result.push_back(',');
            result.push_back(' ');
        }
        result += toString(element);
    }
    result.push_back(']');
    return result;
}

template<typename T, typename R>
vector<R> reduceToUnWeighted(const vector<T>& stream, int offset) { // Haeupler 2014
    vector<R> unweighted;
    UniformRandomVar<double> urv(0, 1);
    int value = offset;
    for (int i = 0; i < (int)stream.size(); i ++) {
        for (int j = 0; j < int(stream[i]); j ++) {
            unweighted.push_back(value);
        }
        if (stream[i] - int(stream[i]) > 1.e-9) {
            if (urv.generate() <= stream[i] - int(stream[i])) {
                unweighted.push_back(value);
            }
        }
        ++value;
    }
    return unweighted;
}
