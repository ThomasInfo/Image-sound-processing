
#include <string>

using namespace std;

#include "../src/Reader.h"
#include "../src/HistogramWriter.h"

int main() {

    Reader r;
    Histogram h;

    RGBImage image = r.loadRGBImage("../images/mandrill.png");
    ImageHistogram image_histo = h.computeImageHistogram(image);
    WriteImageHistogram(image_histo, "../histograms/mandrill.txt");

    Channel channel = r.loadGSImage("../images/lenna.jpeg");
    ChannelHistogram channel_histo = h.computeChannelHistogram(channel);
    WriteChannelHistogram(channel_histo, "../histograms/lenna.txt");

    return 0;
}