
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

    Channel red = r.extractRedChannel("../images/mandrill.png");
    Channel green = r.extractGreenChannel("../images/mandrill.png");
    Channel blue = r.extractBlueChannel("../images/mandrill.png");
    ChannelHistogram red_histo = h.computeChannelHistogram(red);
    ChannelHistogram green_histo = h.computeChannelHistogram(green);
    ChannelHistogram blue_histo = h.computeChannelHistogram(blue);
    WriteChannelHistogram(red_histo, "../histograms/red_mandrill.txt");
    WriteChannelHistogram(green_histo, "../histograms/green_mandrill.txt");
    WriteChannelHistogram(blue_histo, "../histograms/blue_mandrill.txt");

    return 0;
}