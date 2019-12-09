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

    Channel image = r.loadGSImage("../images/lenna.jpeg");
    Channel filtered = c.detectAllEdges(image);
    CImg<int> cimg = w.createGSImage(filtered);

    CImgDisplay mainDisplay;

    mainDisplay.display(cimg);

    return 0;
}