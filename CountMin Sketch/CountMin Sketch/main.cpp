//
//  main.cpp
//  CountMin Sketch
//
//  Created by Mahmud on 1/14/19.
//  Copyright © 2019 Mahmud. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <functional>
#include <vector>


#include "CMSTable.cpp"
#include "Generator.cpp"
#include "SimLib.cpp"
#include "CWSLib.cpp"


using namespace std;

#include "CountMinTable_testing.h"

int main(int argc, const char * argv[]) {
//    vector<int> v1 = generateRandomList(10000);
//    vector<int> v2 = generateRandomList(10000);
//    //checkingCWS();
//
//    CMSTable<int> table1 = CMSTable<int>();
//    CMSTable<int> table2 = CMSTable<int>();
//    table1.setParamsDefault(true, -1);
//    table2.setParamsDefault(true, -1);
//
//    cout << table1.describe() << endl;
//
//    for (int i: v1)
//        table1.insertEntry(i);
//    for (int i: v2)
//        table2.insertEntry(i);
//    cout << table1.describe() << endl;
//    cout << endl;
//    cout << table2.describe() << endl;
//
//    cout << HammingDistanceIterable<vector<int>, double>(v1, v2) << endl;
//    cout << JaccardDistanceIterable<vector<int>, int, double>(v1, v2) << endl;
//    cout << HammingDistanceCMSTables<int, double>(table1, table2, false) << endl;
    
    CountMinTesting();
    
    return 0;
}
