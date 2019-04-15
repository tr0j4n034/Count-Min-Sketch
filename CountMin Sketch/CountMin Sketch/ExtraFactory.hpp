//
//  ExtraFactory.hpp
//  CountMin Sketch
//
//  Created by Mahmud on 3/26/19.
//  Copyright © 2019 Mahmud. All rights reserved.
//

#ifndef ExtraFactory_hpp
#define ExtraFactory_hpp

#include <iostream>
#include <stdlib.h>
#include <sstream>

using std::string;
using std::vector;

template<typename T>
string toString(const T& element);

template<typename T>
string describe(const vector<T>& stream);

template<typename T = int, typename R = int>
vector<T> reduceToUnWeighted(const vector<T>& stream, int offset = 0);

#endif /* ExtraFactory_hpp */
