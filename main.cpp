//
// main.cpp
// Created on 21/10/2018
//
#include "multimedia.h"
#include "video.h"
#include "photo.h"
#include <iostream>
#include <array>

using namespace std;

int main(int argc, const char* argv[])
{
    std::array<Multimedia*, 4> tabMedia;
    tabMedia[0] = new Photo("Photo1", "photo1.jpg", 48.8566, 2.3522);
    tabMedia[1] = new Video("Video1", "video1.mp4", 120);
    tabMedia[2] = new Photo("Photo2", "photo2.png", 34.0522, -118.2437);
    tabMedia[3] = new Video("Video2", "video2.avi", 300);

    for (const auto& media : tabMedia) {
        media->print(cout) << std::endl;
        media->play();
    }

    return 0;
}