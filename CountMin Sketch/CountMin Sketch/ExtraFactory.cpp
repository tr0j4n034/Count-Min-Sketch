//
//  ExtraFactory.cpp
//  CountMin Sketch
//
//  Created by Mahmud on 3/26/19.
//  Copyright © 2019 Mahmud. All rights reserved.
//

#include "ExtraFactory.hpp"

template<typename T>
std::string toString(const T& element) {
    std::ostringstream os;
    os << element;
    return os.str();
}

template<typename T>
std::string describe(const std::vector<T>& stream) {
    std::string result = "[";
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

template<typename T>
std::vector<int> reduceToUnWeighted(const std::vector<T>& stream, int offset) { // Haeupler 2014
    std::vector<int> unweighted;
    UniformRandomVar<double> urv(0, 1);
    int value = offset;
    for (int i = 0; i < (int)stream.size(); i ++) {
        for (int j = 0; j < int(stream[i]); j ++) {
            unweighted.push_back(value);
        }
        if (stream[i] - std::floor(stream[i]) > 1.e-9) {
            if (urv.generate() <= stream[i] - int(stream[i])) {
                unweighted.push_back(value);
            }
        }
        ++value;
    }
    return unweighted;
}
