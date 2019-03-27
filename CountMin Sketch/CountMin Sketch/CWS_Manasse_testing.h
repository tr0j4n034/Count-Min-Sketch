//
//  CWS_Manasse_testing.h
//  CountMin Sketch
//
//  Created by Mahmud on 3/27/19.
//  Copyright © 2019 Mahmud. All rights reserved.
//

#ifndef CWS_Manasse_testing_h
#define CWS_Manasse_testing_h

void CWS_Manasse_testing() {
    int streamSize = 100'000'000;
    int sketchSize = 10'000'000;
    int universeSize = 200'000;
    
    cout << "Size of each stream is " << 4. * streamSize / (1 << 20) << " megabytes" << endl;
    cout << "Size of each sketch is " << 4. * sketchSize / (1 << 20) << " megabytes" << endl;
    cout << "Compression ratio is " << 1. * streamSize / sketchSize << endl;
    cout << endl;
    
    cout << "Generating data..." << endl;
    vector<int> stream1 = generateRandomList(streamSize, universeSize);
    vector<int> stream2 = generateRandomList(streamSize, universeSize);
    cout << "Done." << endl << endl;
    
    // stream1 = stream2;
    
    cout << "Jaccard distance between the original streams: ";
    cout << JaccardDistanceIterable<vector<int>, int, double>(stream1, stream2) << endl;
    
    cout << endl;
    cout << "Getting sketches..." << endl;
    
    CWSEngineManasse<double> engine;
    CWSSketch<double> cws1 = engine.getSketchIterableManasseNaive(stream1, sketchSize);
    vector<double> sketchData1 = cws1.getSketchElems();
    //cout << describe(sketchData1) << endl;
    
    CWSSketch<double> cws2 = engine.getSketchIterableManasseNaive(stream2, sketchSize);
    vector<double> sketchData2 = cws2.getSketchElems();
    //cout << describe(sketchData2) << endl;
    cout << "Done." << endl << endl;
    
    cout << "Jaccard distance between the sketches: ";
    cout << JaccardDistanceIterable<vector<double>, int, double>(sketchData1, sketchData2) << endl;
}

#endif /* CWS_Manasse_testing_h */
