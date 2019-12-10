//
// Created by Sofia on 01/12/2019.
//

#include "gtest/gtest.h"
#include "../src/ContourExtractor.h"
#include "../src/Writer.h"
#include "../src/Reader.h"

using namespace std;

TEST (ContourExtractorTest, ZeroPadding) {
    ContourExtractor extractor;
    Channel testImage = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12} };
    Channel padded = extractor.preprocess(testImage);
    Channel test = { {0, 0, 0, 0, 0}, {0, 1, 2, 3, 0}, {0, 4, 5, 6, 0}, {0, 7, 8, 9, 0}, {0, 10, 11, 12, 0}, {0, 0, 0, 0, 0} };
    EXPECT_EQ(padded, test);
}
TEST (ContourExtractor, ConvolutionVertical) {
    ContourExtractor extractor;
    Channel testImage = { {1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}, {16, 17, 18, 19, 20},};
    Channel filtered = extractor.detectVerticalEdges(testImage);
    Channel test =  { {-11, -6, -6, -6, 17}, {-28, -8, -8, -8, 36}, {-48, -8, -8, -8, 56}, {-46, -6, -6, -6, 52}};
    EXPECT_EQ(filtered, test);
}

TEST (ContourExtractor, ConvolutionHorizontal) {
    ContourExtractor extractor;
    Channel testImage = { {1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}, {16, 17, 18, 19, 20},};
    Channel filtered = extractor.detectHorizontalEdges(testImage);
    Channel test =  { {-19, -28, -32, -36, -29}, {-30, -40, -40, -40, -30}, {-30, -40, -40, -40, -30}, {34, 48, 52, 56, 44}};
    EXPECT_EQ(filtered, test);
}

TEST (ContourExtractor, ConvolutionAllEdge) {
    ContourExtractor extractor;
    Channel testImage = { {1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}, {16, 17, 18, 19, 20},};
    Channel filtered = extractor.detectAllEdges(testImage);
    Channel test =  { {21, 28, 32, 36, 33}, {41, 40, 40, 40, 46}, {56, 40, 40, 40, 63}, {57, 48, 52, 56, 68}};
    EXPECT_EQ(filtered, test);
}

TEST (ContourExtractor, VerticalEdgeDetectorLenna) {
    //Visual test
    Reader r;
    ContourExtractor c;
    Writer w;

    //Greyscale image is loaded from a CImg...
    Channel image = r.loadGSImage("../images/lenna.jpeg");

    //...filtered...
    Channel filtered = c.detectVerticalEdges(image);

    //... written back into a Cimg...
    CImg<int> cimg = w.createGSImage(filtered);

    //...saved
    cimg.save("../results/vertical_contour_lenna.jpeg");

}

TEST (ContourExtractor, HorizontalEdgeDetectorLenna) {
    //Visual test
    Reader r;
    ContourExtractor c;
    Writer w;

    //Greyscale image is loaded from a CImg...
    Channel image = r.loadGSImage("../images/lenna.jpeg");

    //...filtered...
    Channel filtered = c.detectHorizontalEdges(image);

    //... written back into a Cimg...
    CImg<int> cimg = w.createGSImage(filtered);

    //...saved
    cimg.save("../results/horizontal_contour_lenna.jpeg");
}

TEST (ContourExtractor, AllEdgeDetectorLenna) {
    //Visual test
    Reader r;
    ContourExtractor c;
    Writer w;

    //Greyscale image is loaded from a CImg...
    Channel image = r.loadGSImage("../images/lenna.jpeg");

    //...filtered...
    Channel filtered = c.detectAllEdges(image);

    //...saved
    CImg<int> cimg = w.createGSImage(filtered);

    cimg.save("../results/contour_lenna.jpeg");
}

TEST (ContourExtractor, VerticalEdgeDetectorMandrill) {
    //Visual test
    Reader r;
    ContourExtractor c;
    Writer w;

    Channel image = r.convertColoredToGS("../images/mandrill.png");
    Channel filtered = c.detectVerticalEdges(image);
    CImg<int> cimg = w.createGSImage(filtered);

    cimg.save("../results/vertical_contour_mandrill.png");
}


TEST (ContourExtractor, HorizontalEdgeDetectorMandrill) {
    //Visual test
    Reader r;
    ContourExtractor c;
    Writer w;

    Channel image = r.convertColoredToGS("../images/mandrill.png");
    Channel filtered = c.detectHorizontalEdges(image);
    CImg<int> cimg = w.createGSImage(filtered);

    cimg.save("../results/horizontal_contour_mandrill.png");
}

TEST (ContourExtractor, AllEdgeDetectorMandrill) {
    //Visual test
    Reader r;
    ContourExtractor c;
    Writer w;

    Channel image = r.convertColoredToGS("../images/mandrill.png");
    Channel filtered = c.detectAllEdges(image);
    CImg<int> cimg = w.createGSImage(filtered);

    cimg.save("../results/contour_mandrill.jpeg");
}
TEST (ContourExtractor, AllEdgeDetectorFruits) {
    //Visual test
    Reader r;
    ContourExtractor c;
    Writer w;

    Channel image = r.convertColoredToGS("../images/fruits.png");
    Channel filtered = c.detectAllEdges(image);
    CImg<int> cimg = w.createGSImage(filtered);

    cimg.save("../results/contour_fruits.jpeg");
}

TEST (ContourExtractor, AllEdgeDetectorGirl) {
    //Visual test
    Reader r;
    ContourExtractor c;
    Writer w;

    Channel image = r.convertColoredToGS("../images/girl.png");
    Channel filtered = c.detectAllEdges(image);
    CImg<int> cimg = w.createGSImage(filtered);

    cimg.save("../results/contour_girl.jpeg");
}

TEST (ContourExtractor, AllEdgeDetectorLich) {
    //Visual test
    Reader r;
    ContourExtractor c;
    Writer w;

    Channel image = r.convertColoredToGS("../images/lich.png");
    Channel filtered = c.detectAllEdges(image);
    CImg<int> cimg = w.createGSImage(filtered);

    cimg.save("../results/contour_lich.jpeg");
}

TEST (ContourExtractor, AllEdgeDetectorMonarch) {
    //Visual test
    Reader r;
    ContourExtractor c;
    Writer w;

    Channel image = r.convertColoredToGS("../images/monarch.png");
    Channel filtered = c.detectAllEdges(image);
    CImg<int> cimg = w.createGSImage(filtered);

    cimg.save("../results/contour_monarch.jpeg");
}

TEST (ContourExtractor, AllEdgeDetectorTulips) {
    //Visual test
    Reader r;
    ContourExtractor c;
    Writer w;

    Channel image = r.convertColoredToGS("../images/tulips.png");
    Channel filtered = c.detectAllEdges(image);
    CImg<int> cimg = w.createGSImage(filtered);

    cimg.save("../results/contour_tulips.jpeg");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}