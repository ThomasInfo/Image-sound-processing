//
// Created by Sofia on 01/12/2019.
//

#include "gtest/gtest.h"
#include "../src/Reader.h"


TEST (ReaderTest, RGBImageIsLoaded) {

    Reader r;
    RGBImage image = r.loadRGBImage("../images/mandrill.png");

    //Correct height
    EXPECT_EQ(image.size(),480);
    //Correct width
    EXPECT_EQ(image[0].size(),480);
    //Correct spectrum
    EXPECT_EQ(image[0][0].size(),3);
}

TEST (ReaderTest, LennaIsLoaded) {

    Reader r;
    Channel image = r.loadGSImage("../images/lenna.jpeg");

    //Correct height
    EXPECT_EQ(image.size(),512);
    //Correct width
    EXPECT_EQ(image[0].size(),512);

}

TEST (ReaderTest, MountainIsLoaded) {

    Reader r;
    Channel image = r.loadGSImage("../images/mountain.png");

    //Correct height
    EXPECT_EQ(image.size(),640);
    //Correct width
    EXPECT_EQ(image[0].size(),480);

}


TEST (ReaderTest, RGBChannelsAreLoaded) {
    Reader r;

    Channel red = r.extractRedChannel("../images/mandrill.png");
    Channel green = r.extractGreenChannel("../images/mandrill.png");
    Channel blue = r.extractBlueChannel("../images/mandrill.png");

    //Correct height
    EXPECT_EQ(red.size(),480);
    //Correct width
    EXPECT_EQ(red[0].size(),480);


    //Correct height
    EXPECT_EQ(green.size(),480);
    //Correct width
    EXPECT_EQ(green[0].size(),480);

    //Correct height
    EXPECT_EQ(blue.size(),480);
    //Correct width
    EXPECT_EQ(blue[0].size(),480);

}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}