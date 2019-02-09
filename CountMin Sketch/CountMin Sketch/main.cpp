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
#include <algorithm>

using namespace std;

#include "CMSTable.h"
#include "Generator.h"
#include "SimLib.h"
#include "CWSLib.h"

void checkingCWS() {
    int streamSize = 10000;
    int streamMax = 1 << 15;
    vector<int> data1 = generateRandomList(streamSize, streamMax);
    
    //data1 = {25, 644, 32, 619, 332, 925, 415, 77, 64, 974 };
    
    //iota(data1.begin(), data1.end(), 1);
    
    //    copy(begin(data1), end(data1),
    //         ostream_iterator<int>(cout, " "));
    //    cout << endl;
    //
    //    cout << endl;
    
    vector<int> data2 = generateRandomList(streamSize, streamMax);
    //data2 = {644, 619, 925, 415, 77, 64, 974, 842, 923, 888};
    
    //    copy(begin(data2), end(data2),
    //         ostream_iterator<int>(cout, " "));
    //    cout << endl;
    
    //    vector<int> v = {1, 2, 10, 6, 4, 7};
    //    CWSEngine<double> cwse;
    //    CWSSketch<double> sk = cwse.getSketchIterable(v);
    //
    //    for (double v: sk.getSketchElems()) {
    //        cout << v << endl;
    //    }
    
    int sketchSize = 100;
    CWSEngine<double> cwse;
    CWSSketch<double> sk1 = cwse.getSketchIterable(data1, sketchSize);
    CWSSketch<double> sk2 = cwse.getSketchIterable(data2, sketchSize);
    vector<double> skelems1 = sk1.getSketchElems();
    vector<double> skelems2 = sk2.getSketchElems();
    
    cout << "sketches here:" << endl;
    //copy(begin(skelems1), end(skelems1), ostream_iterator<double>(cout, " ")); cout << endl;
    //copy(begin(skelems2), end(skelems2), ostream_iterator<double>(cout, " ")); cout << endl;
    
    cout << "Jaccard distances between data: ";
    cout << JaccardDistanceIterable<vector<int>, int, double>(data1, data2, false) << endl;
    cout << JaccardDistanceIterable<vector<int>, int, double>(data1, data2, true) << endl;
    cout << "Jaccard distance between CWS sketches: ";
    cout << JaccardDistanceIterable<vector<double>, double, double>(skelems1, skelems2, false) << endl;
    cout << JaccardDistanceIterable<vector<double>, double, double>(skelems1, skelems2, true) << endl;
    
    cout << endl;
    
    cout << "Euclidean distances in the same fashion:" << endl;
    cout << EuclideanDistanceIterable<vector<int>, double>(data1, data2) / sqrt(streamSize) << endl;
    cout << EuclideanDistanceIterable<vector<double>, double>(skelems1, skelems2) / sqrt(sketchSize) << endl;
}


void CountMinTesting() {
    freopen("output.txt", "w", stdout);
    
    auto getMinErrorOnStream = [](int streamSize, int universeSize = 100000, double error = 0.05, double confidence = 0.95) {
        CMSTable<int> cms;
        cms.setParamsDefault(streamSize);
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
    
    for (int i = 0; i < 1000; i ++) {
        double error = 0.01 * (rand() % 100 + 1);
        double confidence = 0.01 * (rand() % 100 + 1);
        int stream_size = int(100000 * max(0.5, error / confidence));
        cout << error << " " << confidence << " " << getMinErrorOnStream(stream_size, error, confidence) << endl;
    }
    
    
    cout << "Count-Min sketch average errors over artificial datasets:" << endl;
    cout << endl;
    cout << "The values per line shows" << endl;
    cout << "1. sketch error parameter" << endl;
    cout << "2. sketch confidence parameter" << endl;
    cout << "3. mean average error of the sketch on all possible inputs" << endl;
    cout << endl;
    for (int stream = 8192; stream <= 200000; stream *= 2) {
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
                cout.precision(3);
                cout << fixed << 1. * error << " " << 1. * confidence << " " << 1. * errorSum / trials << endl;
            }
        }
        cout << endl; cout << endl;
        cout << "--------------------" << endl;
        cout << endl;
    }
    
}
void checkDefaultSettings() {
    int streamSize = 100000;
    vector<int> stream1 = generateRandomList(streamSize);
    vector<int> stream2 = generateRandomList(streamSize);
    CMSTable<int> table1 = CMSTable<int>();
    CMSTable<int> table2 = CMSTable<int>();
    table1.setParamsDefault(streamSize);
    table2.setParamsDefault(streamSize);
    cout << table1.getTableSize() << " " << table1.getHashesCount() << endl;
    
    
    for (int i: stream1)
        table1.insertEntry(i);
    for (int i: stream2)
        table2.insertEntry(i);
    
    cout << table1.describe() << endl;
    cout << table2.describe() << endl;
    
    cout << JaccardDistanceIterable<vector<int>, int, double>(stream1, stream2) << endl;
}


int main(int argc, const char * argv[]) {
    vector<int> v1 = generateRandomList(10000);
    vector<int> v2 = generateRandomList(10000);
    //checkingCWS();
    
    CMSTable<int> table1 = CMSTable<int>();
    CMSTable<int> table2 = CMSTable<int>();
    table1.setParamsDefault();
    table2.setParamsDefault();
    table1.setDims(10, 2000);
    table2.setDims(10, 2000);
    
    cout << table1.describe() << endl;
    
    for (int i: v1)
        table1.insertEntry(i);
    for (int i: v2)
        table2.insertEntry(i);
    cout << table1.describe() << endl;
    cout << endl;
    cout << table2.describe() << endl;

    cout << HammingDistanceIterable<vector<int>, double>(v1, v2) << endl;
    cout << JaccardDistanceIterable<vector<int>, int, double>(v1, v2) << endl;
    cout << HammingDistanceCMSTables<int, double>(table1, table2, false) << endl;
    
    return 0;
}
