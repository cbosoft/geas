#pragma once

#include <string>

class ImageData {

  public:
    ImageData(std::string filename);
    ~ImageData();

    unsigned char *data;
    int width, height, nChannels;

};
