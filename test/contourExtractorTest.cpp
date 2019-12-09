//
// Created by Sofia on 01/12/2019.
//

#include "gtest/gtest.h"
#include "../src/ContourExtractor.h"

using namespace std;

TEST (ContourExtractorTest, ZeroPadding) {
    ContourExtractor extractor;
    Channel testImage = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12} };
    Channel padded = extractor.preprocess(testImage);
    Channel test = { {0, 0, 0, 0, 0}, {0, 1, 2, 3, 0}, {0, 4, 5, 6, 0}, {0, 7, 8, 9, 0}, {0, 10, 11, 12, 0}, {0, 0, 0, 0, 0} };
    EXPECT_EQ(padded, test);
}
TEST (ContourExtractor, VerticalEdgeDetector) {
    ContourExtractor extractor;
    Channel testImage = { {1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}, {16, 17, 18, 19, 20},};
    Channel filtered = extractor.detectVerticalEdges(testImage);
    Channel test =  { {-11, -6, -6, -6, 17}, {-28, -8, -8, -8, 36}, {-48, -8, -8, -8, 56}, {-46, -6, -6, -6, 52}};
    EXPECT_EQ(filtered, test);
}

TEST (ContourExtractor, HorizontalEdgeDetector) {
    ContourExtractor extractor;
    Channel testImage = { {1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}, {16, 17, 18, 19, 20},};
    Channel filtered = extractor.detectHorizontalEdges(testImage);
    Channel test =  { {-19, -28, -32, -36, -29}, {-30, -40, -40, -40, -30}, {-30, -40, -40, -40, -30}, {34, 48, 52, 56, 44}};
    EXPECT_EQ(filtered, test);
}

TEST (ContourExtractor, AllEdgeDetector) {
    ContourExtractor extractor;
    Channel testImage = { {1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}, {16, 17, 18, 19, 20},};
    Channel filtered = extractor.detectAllEdges(testImage);
    Channel test =  { {21, 28, 32, 36, 33}, {41, 40, 40, 40, 46}, {56, 40, 40, 40, 63}, {57, 48, 52, 56, 68}};
    EXPECT_EQ(filtered, test);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}