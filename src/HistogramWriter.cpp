
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

using namespace std;

#include "HistogramWriter.h"

void WriteImageHistogram(ImageHistogram imageHisto, string filename) {

    ofstream flow(filename.c_str());
    assert(flow);

    for ( int nred = 0; nred < 256; nred++) {
        flow << "Red intensity is " << nred << endl;
        for ( int ngreen = 0; ngreen < 256; ngreen++) {
            flow << "Green intensity is " << ngreen << endl;
            for ( int nblue = 0; nblue < 256; nblue++) {
                flow << imageHisto[nred][ngreen][nblue] << " ";
            }
        }
    }

}


void WriteChannelHistogram(ChannelHistogram channelHisto, string filename) {

    ofstream flow(filename.c_str());
    assert(flow);

    for ( int intensity = 0; intensity < 256; intensity++) {
        flow << channelHisto[intensity] << endl;
    }

}