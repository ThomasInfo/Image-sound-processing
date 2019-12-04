
#include "Histogram.h"

using namespace std;

Histogram::Histogram() {}

Histogram::~Histogram () {}

Image_Histogram Histogram::compute_Image_Histogram(Image image) const {
    int nb_lines = Image.size();
    int nb_columns = Image[0].size();
    Image_Histogram image_histo (256, vector<vector<int>>(256, vector<int>(256)))

    for(nx=0; nx < nb_lines; nx++) {
        for (ny=0; ny < nb_columns; ny++) {
            for (ncolor=0; ncolor < 3; ncolor++) {
                [r, g, b] = image[nx][ny][ncolor];
                Image_Histogram[r][g][b]++;
            }
        }
    }


CImg <int> Reader::loadCImg(std::string filename) const {
    int n = filename.length();
    char filenameInChar [n + 1];
    strcpy(filenameInChar , filename.c_str());

    CImg<int> image (filenameInChar);
    return image;
}

Image Reader::loadImage(string filename) const {
    CImg<int> image = loadCImg(filename);
    return convertImage(image);
}

Channel Reader::extractRedChannel (string filename) const {
    CImg<int> image = loadCImg(filename);
    return convertChannel(image.get_channel(0));
}

Channel Reader::extractBlueChannel (string filename) const {
    CImg<int> image = loadCImg(filename);
    return convertChannel(image.get_channel(1));
}

Channel Reader::extractGreenChannel (string filename) const {
    CImg<int> image = loadCImg(filename);
    return convertChannel(image.get_channel(2));
}

Image Reader::convertImage (CImg <int> cImg) const {
    int lines = cImg.height();
    int columns = cImg.width();
    int channels = cImg.spectrum();

    Image image (lines, vector<vector<int>>(columns, vector<int>(channels)));

    for(size_t i(0); i < lines; i++) {
        for (size_t j(0); j < columns; ++j) {
            for (size_t k(0); k < channels; ++k) {
                image[i][j][k] = cImg(i,j,k);
            }
        }
    }

    return image;
}

Channel Reader::convertChannel (CImg <int> cImg) const {
    int lines = cImg.height();
    int columns = cImg.width();

    Channel image (lines, vector<int>(columns));

    for(size_t i(0); i < lines; i++) {
        for (size_t j(0); j < columns; ++j) {
                image[i][j] = cImg(i,j);
        }
    }

    return image;
}