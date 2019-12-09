#include <iostream>
#include "Reader.h"
#include "ContourExtractor.h"
#include "Writer.h"

using namespace cimg_library;
using namespace std;

int main() {

    Reader r;
    ContourExtractor c;
    Writer w;

    cout << " a";
    //Channel image = r.convertColoredToGS("../images/fjord.jpeg");
    RGBImage image = r.loadRGBImage("../images/mandrill.png");
    cout << " b";
    //Channel filtered = c.detectAllEdges(image);
    cout << " c";
    //CImg<int> cimg = w.createGSImage(filtered);

    cout << " d";
    //cimg.save("fjords_contour.png");

    return 0;
}