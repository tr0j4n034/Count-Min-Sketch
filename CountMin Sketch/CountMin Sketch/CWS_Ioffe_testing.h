//
//  CWS_Ioffe_testing.h
//  CountMin Sketch
//
//  Created by Mahmud on 3/28/19.
//  Copyright © 2019 Mahmud. All rights reserved.
//

#ifndef CWS_Ioffe_testing_h
#define CWS_Ioffe_testing_h

void CWS_Ioffe_testing() {
    int streamSize = 10'000;
    int sketchSize = 1'000;
    int universeSize = 2'000;
    
    cout << "Size of each stream is " << 4. * streamSize / (1 << 20) << " megabytes" << endl;
    cout << "Size of each sketch is " << 4. * sketchSize / (1 << 20) << " megabytes" << endl;
    cout << "Compression ratio is " << 1. * streamSize / sketchSize << endl;
    cout << endl;
    
    cout << "Generating data..." << endl;
    vector<int> stream1 = generateRandomList(streamSize, universeSize);
    vector<int> stream2 = generateRandomList(streamSize, universeSize);
    cout << "Done." << endl << endl;
    
    stream1 = stream2;
    
//    int noiseCounter = 100;
//    default_random_engine generator(0);
//    uniform_int_distribution<int> distribution(0, streamSize - 1);
//    for (int i = 0; i < noiseCounter; i ++) {
//        stream2[distribution(generator)] ++;
//    }
    
//    for (int i = 0; i < 1000; i ++) {
//        stream2[i] ++;
//    }
    
    cout << "Jaccard distance between the original streams: " << endl;
    // cout << JaccardDistanceIterable<vector<int>, int, double>(stream1, stream2, false) << endl;
    cout << "Binned weighted: " << JaccardDistanceBinned<vector<int>, int, double>(stream1, stream2) << endl;
    cout << "Binned unweighted: " << JaccardDistanceBinned<vector<int>, int, double>(stream1, stream2, true) << endl;
    cout << endl;
    cout << "Getting sketches..." << endl;
    
    CWSEngineIoffe<double> engine(0);
    CWSSketch<double> cws1 = engine.getSketchIterableIoffe(stream1, sketchSize, universeSize);
    vector<double> sketchData1 = cws1.getSketchElems();
    vector<double> sketchHashes1 = cws1.getSketchHashes();
    //cout << describe(sketchData1) << endl;
    
    CWSSketch<double> cws2 = engine.getSketchIterableIoffe(stream2, sketchSize, universeSize);
    vector<double> sketchData2 = cws2.getSketchElems();
    vector<double> sketchHashes2 = cws2.getSketchHashes();
    //cout << describe(sketchData2) << endl;
    cout << "Done." << endl << endl;
    
    cout << "Jaccard distance between the sketches: " << endl;
    // cout << JaccardDistanceIterable<vector<double>, int, double>(sketchData1, sketchData2, false) << endl;
    cout << "Binned weighted: " << JaccardDistanceBinned<vector<double>, int, double>(sketchData1, sketchData2) << endl;
    cout << "Binned unweighted: " << JaccardDistanceBinned<vector<double>, int, double>(sketchData1, sketchData2, true) << endl;
    
//    for (int i = 0; i < sketchSize; i ++) {
//        cout << i << " --> " << sketchData1[i] << " vs " << sketchData2[i] << endl; // << sketchHashes1[i] << " " << stream1[sketchData1[i]] << endl;
//    }
}

#endif /* CWS_Ioffe_testing_h */

