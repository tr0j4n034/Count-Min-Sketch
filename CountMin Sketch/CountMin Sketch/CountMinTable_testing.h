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
    auto getMeanErrorOnStream = [](int streamSize, int universeSize = 10000,
                                   int memory = 1000000, double error = 0.05, double confidence = 0.95) {
        CMSTable<int> cms;
        cms.setParams(error, confidence);
        //cms.setDims(20, 50000);
        cms.scaleDims(memory);
        
        std::vector<int> counts(universeSize + 1);
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
    
    const int universeSize = 100000;
    const int memory = 1000000;
    
    std::cout << "Count-Min sketch average errors over artificial datasets:" << std::endl;
    std::cout << std::fixed << "The size of the Count Min Table is " << 4. * memory / (1 << 20) << " mb" << std::endl;
    std::cout << std::endl;
    
    for (int streamSize = 500000; streamSize <= 50000000; streamSize *= 2) {
        int trials = 10;
        long long errorSum = 0;
        for (int i = 0; i < trials; i ++) {
            errorSum += getMeanErrorOnStream(streamSize, universeSize, memory, 0.01, 0.99);
        }
        std::cout.precision(3);
        std::cout << std::fixed << "for stream size = " << 4. * streamSize / (1 << 20) << " mb"
        << ", the mean average error is: " << 1. * errorSum / trials << std::endl;
    }
}
#endif /* CountMinTable_testing_h */
