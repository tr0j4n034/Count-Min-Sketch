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

template<typename T>
std::string toString(const T& element);

template<typename T>
std::string describe(const std::vector<T>& stream);


template<typename T = int, typename R=  int>
std::vector<T> reduceToUnWeighted(const std::vector<T>& stream, int offset = 0);

#endif /* ExtraFactory_hpp */
