//
//  main.cpp
//  CountMin Sketch
//
//  Created by Mahmud on 1/14/19.
//  Copyright © 2019 Mahmud. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <vector>

#include "CMSTable.cpp"
#include "Generator.cpp"
#include "SimLib.cpp"
#include "CWSLib.cpp"

#include "ExtraFactory.cpp"

using namespace std;

#include "CountMinTable_testing.h"

int main(int argc, const char * argv[]) {
    // CountMinTesting();
    
    vector<int> data1 = generateRandomList(10000, 10000);
    vector<int> data2 = generateRandomList(10000, 10000);
    data2 = data1;
    
    cout << JaccardDistanceIterable<vector<int>, int, double>(data1, data2) << endl;
    
    CWSEngineIoffe<double> engine;
    CWSSketch<double> cws1 = engine.getSketchIterableIoffe(data1, 10000);
    vector<double> sketchData1 = cws1.getSketchElems();
    //cout << describe(sketchData1) << endl;
    
    CWSSketch<double> cws2 = engine.getSketchIterableIoffe(data2, 10000);
    vector<double> sketchData2 = cws2.getSketchElems();
    //cout << describe(sketchData2) << endl;
    
    cout << JaccardDistanceIterable<vector<double>, int, double>(sketchData1, sketchData2) << endl;
    
    return 0;
}
