//
// Created by Sofia on 06/12/2019.
//

#include "gtest/gtest.h"
#include "../src/Writer.h"

TEST (WriterTest, GSImageIsWritten) {

    Writer w;
    Reader r;
    CImg<int> cImg ("../images/lenna.jpeg");
    Channel image = r.loadGSImage("../images/lenna.jpeg");
    CImg<int> cImg1 = w.createGSImage(image);

    EXPECT_EQ(cImg.height(), cImg1.height());
    EXPECT_EQ(cImg.width(), cImg1.width());

    EXPECT_EQ(cImg, cImg1);
}

TEST (WriterTest, RGBImageIsWritten) {

    Writer w;
    Reader r;
    CImg<int> cImg ("../images/mandrill.png");
    RGBImage image = r.loadRGBImage("../images/mandrill.png");
    CImg<int> cImg1 = w.createRGBImage(image);

    EXPECT_EQ(cImg.height(), cImg1.height());
    EXPECT_EQ(cImg.width(), cImg1.width());

    EXPECT_EQ(cImg, cImg1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}