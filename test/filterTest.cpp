//
// Created by Sofia on 01/12/2019.
//

#include "gtest/gtest.h"
#include "../src/Filter.h"

using namespace std;

TEST (FilterTest, ZeroPadding) {
    Filter filter;
    Channel testImage = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
    Channel padded = filter.preprocess(testImage);
    Channel test = { {0, 0, 0, 0, 0}, {0, 1, 2, 3, 0}, {0, 4, 5, 6, 0}, {0, 7, 8, 9, 0}, {0, 0, 0, 0, 0} };
    EXPECT_EQ(padded, test);
}
/*TEST (FilterTest, Convolution) {
    Channel testImage = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
    Filter filter ({{1, 0, -1}, {1, 0, -1}, {1, 0, -1}});
    Channel filtered = filter.filter(testImage);
    Channel test =  {{7, 4, -7}, {15, 6, -15}, {13, 4, -13}};
    EXPECT_EQ(filtered, test);
}*/


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}