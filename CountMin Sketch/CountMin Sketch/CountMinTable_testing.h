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
void CountMinTableSketching() {
    int streamSize = 10'000;
    int sketchSize = 1'000;
    int universeSize = 2'000;
    double error = 0.05, confidence = 0.95;
    int memory = 10000;
    
    cout << "Size of each stream is " << 4. * streamSize / (1 << 20) << " megabytes" << endl;
    cout << "Size of each sketch is " << 4. * sketchSize / (1 << 20) << " megabytes" << endl;
    cout << "Compression ratio is " << 1. * streamSize / sketchSize << endl;
    cout << endl;
    
    cout << "Generating data..." << endl;
    vector<int> stream1 = generateRandomList(streamSize, universeSize);
    vector<int> stream2 = generateRandomList(streamSize, universeSize);
    cout << "Done." << endl << endl;
    
    stream1 = stream2;
    
    int noiseCounter = streamSize / 100;
    default_random_engine generator(0);
    uniform_int_distribution<int> distribution(0, universeSize - 1);
    for (int i = 0; i < noiseCounter; i ++) {
        stream2[distribution(generator)] ++;
    }
    
    
    cout << "Jaccard distance between the original streams: " << endl;
    // cout << JaccardDistanceIterable<vector<int>, int, double>(stream1, stream2, false) << endl;
    cout << "Binned weighted: " << JaccardDistanceBinned<vector<int>, int, double>(stream1, stream2) << endl;
    cout << "Binned unweighted: " << JaccardDistanceBinned<vector<int>, int, double>(stream1, stream2, true) << endl;
    cout << endl;
    
    CMSTable<int> cms1, cms2;
    cms1.setParams(error, confidence);
    cms2.setParams(error, confidence);
    //cms.setDims(20, 50000);
    cms1.scaleDims(memory);
    cms2.scaleDims(memory);
    
    cms2 = cms1;
    
    for (int elem: stream1) cms1.insertEntry(elem);
    for (int elem: stream2) cms2.insertEntry(elem);
    
    CWSSketch<double> cws1 = cms1.getTableSketchIoffe(sketchSize);
    CWSSketch<double> cws2 = cms2.getTableSketchIoffe(sketchSize);
    
    vector<double> sketchData1 = cws1.getSketchElems();
    vector<double> sketchHashes1 = cws1.getSketchHashes();
    //cout << describe(sketchData1) << endl;
    
    vector<double> sketchData2 = cws2.getSketchElems();
    vector<double> sketchHashes2 = cws2.getSketchHashes();
    //cout << describe(sketchData2) << endl;
    cout << "Done." << endl << endl;
    
    cout << "Jaccard distance between the sketches: " << endl;
    // cout << JaccardDistanceIterable<vector<double>, int, double>(sketchData1, sketchData2, false) << endl;
    cout << "Binned weighted: " << JaccardDistanceBinned<vector<double>, int, double>(sketchData1, sketchData2) << endl;
    cout << "Binned unweighted: " << JaccardDistanceBinned<vector<double>, int, double>(sketchData1, sketchData2, true) << endl;
}

#endif /* CountMinTable_testing_h */
