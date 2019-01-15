//
//  main.cpp
//  CountMin Sketch
//
//  Created by Mahmud on 1/14/19.
//  Copyright © 2019 Mahmud. All rights reserved.
//

#include <iostream>
#include <functional>

using namespace std;

#include "CMSTable.h"


int main(int argc, const char * argv[]) {
//    Hasher<int> h = Hasher<int>(4);
//    cout << h.getA() << endl;
//
//    vector<Hasher<int>> hh;
//    hh.push_back(Hasher<int>(1000));
//    hh.push_back(Hasher<int>(1000));
//    hh.push_back(Hasher<int>(2, 2, 2));
//
//    for (int i = 0; i < (int)hh.size(); i ++) {
//        cout << hh[i].getA() << " " << hh[i].getB() << " " << hh[i].getC() << endl;
//    }
    
    int h = 10, c = 100;
    CMSTable<int> cms(h, c);
    cms.setHashFunctions(100);

    vector<Hasher<int>> hs = cms.getHashFunctions();
    for (int i = 0; i < h; i ++) {
        cout << hs[i].getA() << " " << hs[i].getB() << " " << hs[i].getC() << endl;
    }
    
    vector<int> counts(101);
    for (int i = 0; i < 12345; i ++) {
        int position = rand() % 100 + 1;
        counts[position] ++;
    }
    for (int i = 1; i <= 100; i ++) {
        for (int j = 0; j < counts[i]; j ++) {
            cout << "inserting: " << i << endl;
            cms.insertEntry(i);
        }
    }
    for (int i = 1; i <= 100; i ++) {
        cout << counts[i] << " vs " << cms.getCount(i) << endl;
    }
    
    
    return 0;
}
