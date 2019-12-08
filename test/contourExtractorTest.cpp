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
TEST (ContourExtractor, EdgeDetector) {
    ContourExtractor extractor;
    Channel testImage = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
    Channel filtered = extractor.verticalEdgeDetector(testImage);
    Channel test =  {{-9, -6, 9}, {-20, -8, 20}, {-21, -6, 21}};
    EXPECT_EQ(filtered, test);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}