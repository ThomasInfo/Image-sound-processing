//
// Created by Sofia on 06/12/2019.
//

#include "gtest/gtest.h"
#include "../src/Writer.h"


TEST (WriterTest, GSImageIsWritten) {

    Writer w;
    Reader r;
    CImg<int> cImg ("../images/mandrill.png");
    RGBImage image = r.loadRGBImage("../images/mandrill.png");
    CImg<int> cImg1 = w.createImage(image);
    EXPECT_EQ(cImg.height(), cImg1.height());
    EXPECT_EQ(cImg.width(), cImg1.width());
    //EXPECT_EQ(cImg.spectrum(), cImg1.spectrum());
    EXPECT_EQ(cImg, cImg1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}