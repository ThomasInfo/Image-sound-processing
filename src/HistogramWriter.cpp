
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

using namespace std;

#include "HistogramWriter.h"

int WriteImageHistogram(ImageHistogram image_histo, string const file_name) {

    ofstream flow(file_name.c_str());
    assert(flow);

    for ( int nred = 0; nred < 256; nred++) {
        flow << "Red intensity is " << nred << endl;
        for ( int ngreen = 0; ngreen < 256; ngreen++) {
            flow << "Green intensity is " << ngreen << endl;
            for ( int nblue = 0; nblue < 256; nblue++) {
                flow << image_histo[nred][ngreen][nblue] << " ";
            }
        }
    }

    return 0;
}


int WriteChannelHistogram(ChannelHistogram channel_histo, string const file_name) {

    ofstream flow(file_name.c_str());
    assert(flow);

    for ( int intensity = 0; intensity < 256; intensity++) {
        flow << channel_histo[intensity] << endl;
    }

    return 0;
}