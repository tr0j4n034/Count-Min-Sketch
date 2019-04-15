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
#include "MinHash.cpp"

#include "ExtraFactory.cpp"

using namespace std;

#include "CountMinTable_testing.h"
#include "CWS_Manasse_testing.h"
#include "CWS_Ioffe_testing.h"

int main(int argc, const char * argv[]) {
    // CountMinTesting();
    
    // CWS_Manasse_testing();
    
    // CWS_Ioffe_testing();
    // CountMinTableSketching();
    
    vector<int> v = vector<int>{3, 1, 4, 1, 5, 9, 2, 6};
    MinHasher mh;
    vector<size_t> hashes = mh.getHashes(v, 3);
    for (auto i: hashes) {
        cout << i << endl;
    }
    
    return 0;
}
