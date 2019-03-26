//
//  CountMinTable_testing.h
//  CountMin Sketch
//
//  Created by Mahmud on 3/25/19.
//  Copyright © 2019 Mahmud. All rights reserved.
//

#ifndef CountMinTable_testing_h
#define CountMinTable_testing_h

void CountMinTesting() {
    auto getMeanErrorOnStream = [](int streamSize, int universeSize = 10000, double error = 0.05, double confidence = 0.95) {
        CMSTable<int> cms;
        cms.setParams(error, confidence);
        //cms.setDims(20, 50000);
        cms.scaleDims(1000000);
        
        vector<int> counts(universeSize + 1);
        for (int i = 0; i < streamSize; i ++) {
            int position = rand() % universeSize + 1;
            counts[position] ++;
        }
        for (int i = 1; i <= universeSize; i ++) {
            for (int j = 0; j < counts[i]; j ++) {
                //cout << "inserting: " << i << endl;
                cms.insertEntry(i);
            }
        }
        long long deltaSum = 0;
        for (int i = 1; i <= universeSize; i ++) {
            deltaSum += std::abs(counts[i] - cms.getCount(i));
        }
        return 1. * deltaSum / streamSize;
    };
    
//    for (int i = 0; i < 50; i ++) {
//        double errorTolerance = 0.01 * (rand() % 100 + 1);
//        double confidence = 0.01 * (rand() % 100 + 1);
//        int stream_size = int(100000 * max(0.5, errorTolerance / confidence));
//        cout << errorTolerance << " " << confidence << " " <<
//            getMeanErrorOnStream(stream_size, universeSize, errorTolerance, confidence) << endl;
//    }
    
    int universeSize = 100000;
    
    cout << "Count-Min sketch average errors over artificial datasets:" << endl;
    cout << endl;
    
    for (int streamSize = 50000; streamSize <= 50000000; streamSize *= 2) {
        int trials = 10;
        long long errorSum = 0;
        for (int i = 0; i < trials; i ++) {
            errorSum += getMeanErrorOnStream(streamSize, universeSize, 0.01, 0.99);
        }
        cout.precision(3);
        cout << fixed << "for stream size = " << streamSize << ", mean average error is: " << 1. * errorSum / trials << endl;
    }
}

#endif /* CountMinTable_testing_h */
