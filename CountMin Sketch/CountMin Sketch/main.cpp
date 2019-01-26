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

using namespace std;

#include "CMSTable.h"
#include "Generator.h"
#include "SimLib.h"

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
    
    
    freopen("output.txt", "w", stdout);
    
    auto getMinErrorOnStream = [](int streamSize, int universeSize = 100000, double error = 0.05, double confidence = 0.95) {
        CMSTable<int> cms;
        cms.setParamsViaStreamSize(streamSize);
        cms.setHashFunctions();
        int to = streamSize;
        vector<int> counts(to + 1);
        for (int i = 0; i < streamSize; i ++) {
            int position = rand() % to + 1;
            counts[position] ++;
        }
        for (int i = 1; i <= streamSize; i ++) {
            for (int j = 0; j < counts[i]; j ++) {
                //cout << "inserting: " << i << endl;
                cms.insertEntry(i);
            }
        }
        int deltaSum = 0;
        for (int i = 1; i <= to; i ++) {
            deltaSum += abs(counts[i] - cms.getCount(i));
        }
        return 1. * deltaSum / streamSize;
    };
    
    //cout << getMinErrorOnStream(100000) << endl;
    
    
//    for (int i = 0; i < 5000; i ++) {
//        double error = 0.01 * (rand() % 20 + 1);
//        double confidence = 0.8 + 1. * (rand() % 21) / 100.;
//        int stream_size = 100000;
//        cout << error << " " << confidence << " " << getMinErrorOnStream(stream_size, error, confidence) << endl;
//    }
    
    for (int stream = 4096; stream <= 20000; stream *= 2) {
        cout << "for stream size = " << stream << endl;
        for (int e = 10; e <= 100; e += 10) {
            double error = 1. * e / 100;
            for (int c = 10; c <= 100; c += 10) {
                double confidence = 1. * c / 100;
                int stream_size = stream;
                double errorSum = 0.;
                int trials = 10;
                for (int i = 0; i < trials; i ++) {
                    errorSum += getMinErrorOnStream(stream_size, error, confidence);
                }
                cout << 1. * error << " " << 1. * confidence << " " << 1. * errorSum / trials << endl;
            }
        }
        cout << endl; cout << endl;
        cout << "--------------------" << endl;
        cout << endl;
    }
    
    
    
//    int h = 5, c = 10001;
//    int streamSize = 100000;
//    CMSTable<int> cms(h, c);
//    cms.setParams(0.0005, 0.995);
//    cms.setParamsViaStreamSize(streamSize);
//    cout << cms.getHashesCount() << endl;
//    cout << cms.getTableSize() << endl;
//    cms.setHashFunctions();
//
////    vector<Hasher<int>> hs = cms.getHashFunctions();
////    for (int i = 1; i <= cms.getHashesCount(); i ++) {
////        cout << hs[i].getA() << " " << hs[i].getB() << " " << hs[i].getC() << endl;
////    }
//    int to = 10000;
//    vector<int> counts(to + 1);
//    for (int i = 0; i < streamSize; i ++) {
//        int position = rand() % to + 1;
//        counts[position] ++;
//    }
//    for (int i = 1; i <= to; i ++) {
//        for (int j = 0; j < counts[i]; j ++) {
//            //cout << "inserting: " << i << endl;
//            cms.insertEntry(i);
//        }
//    }
//    int deltaSum = 0;
//    for (int i = 1; i <= to; i ++) {
//        deltaSum += abs(counts[i] - cms.getCount(i));
//    }
//    cout << "Average error is: ";
//    cout << 1. * deltaSum / streamSize << endl;
    
    
//    vector<vector<int>> v = generatePairWithSimilarity(50, 0.5, 40, true);
//
//    for (auto list: v) {
//        for_each(list.begin(), list.end(), [](int x) {
//            cout << x << " ";
//        });
//        cout << endl;
//    }
    
    
    
    
//    vector<int>a = {1, 2, 3};
//    int f = accumulate(begin(a), end(a), 0, [](int x, int y) {
//        return x + y * y;
//    });
//    cout << f << endl;
//
//    vector<int> v = {1, 2, 4};
//    vector<int> g = {3, 2, 4};
//    cout << HammingDistanceIterable<vector<int>, double>(v, g) << endl;
//
//    cout << EditDistance<vector<int>>(v, g) << endl;
    
    
//    GammaRandomVar<float> g(2, 2);
//    for (int i = 0; i < 10; i ++) {
//        cout << i << " --> " << g.generate() << endl;
//    }
//    UniformRandomVar<float> u(0, 1);
//    for (int i = 0; i < 10; i ++) {
//        cout << "uniform: " << i << " --> " << u.generate() << endl;
//    }
    
    
    return 0;
}
