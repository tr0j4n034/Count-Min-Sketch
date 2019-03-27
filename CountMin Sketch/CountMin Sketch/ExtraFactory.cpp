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
