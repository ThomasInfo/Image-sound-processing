//
// Created by Sofia on 06/12/2019.
//

#include "gtest/gtest.h"
#include "../src/Writer.h"

TEST (WriterTest, GSImageIsWritten) {

    Writer w;
    Reader r;

    //Original cImg greyscale image
    CImg<int> cImg ("../images/lenna.jpeg");
    //Loaded into a Channel
    Channel image = r.loadGSImage("../images/lenna.jpeg");
    //Written back to a CImg
    CImg<int> cImg1 = w.createGSImage(image);

    //Both CImg should be the same
    EXPECT_EQ(cImg.height(), cImg1.height());
    EXPECT_EQ(cImg.width(), cImg1.width());
    EXPECT_EQ(cImg, cImg1);
    cImg.save("../results/original_lena.jpeg");
    cImg1.save("../results/rewritten_lena.jpeg");
}

TEST (WriterTest, RGBImageIsWritten) {

    Writer w;
    Reader r;

    //Original cImg RGB image
    CImg<int> cImg ("../images/mandrill.png");
    //Loaded into a RGB image
    RGBImage image = r.loadRGBImage("../images/mandrill.png");
    CImg<int> cImg1 = w.createRGBImage(image);

    CImg<int> red = cImg.get_channel(0);
    CImg<int> green = cImg.get_channel(1);
    CImg<int> blue = cImg.get_channel(2);

    CImg<int> red1 = cImg1.get_channel(0);
    CImg<int> green1 = cImg1.get_channel(1);
    CImg<int> blue1 = cImg1.get_channel(2);


    //Both images should be the same
    EXPECT_EQ(cImg.height(), cImg1.height());
    EXPECT_EQ(cImg.width(), cImg1.width());
    EXPECT_EQ(red, red1);
    EXPECT_EQ(green, green1);
    EXPECT_EQ(blue, blue1);
    EXPECT_EQ(cImg, cImg1);

    cImg.save("../results/original_mandrill.png");
    cImg1.save("../results/rewritten_mandrill.png");
}

TEST (WriterTest, RGBConvertedtoGS) {
    //Visual test
    Reader r;
    Writer w;
    Channel image = r.convertColoredToGS("../images/mandrill.png");
    CImg<int> cimg = w.createGSImage(image);

    cimg.save("../results/greyscale_mandrill.png");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}