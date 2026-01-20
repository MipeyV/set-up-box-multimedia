#ifndef TEST_H
#define TEST_H

#include <array>
#include <iostream>

#include "multimedia.h"
#include "video.h"
#include "photo.h"

using namespace std;

void runTest_step_5() {
    std::array<Multimedia*, 4> tabMedia;
    tabMedia[0] = new Photo("Photo1", "photo1.jpg", 48.8566, 2.3522);
    tabMedia[1] = new Video("Video1", "video1.mp4", 120);
    tabMedia[2] = new Photo("Photo2", "photo2.png", 34.0522, -118.2437);
    tabMedia[3] = new Video("Video2", "video2.avi", 300);

    for (const auto& media : tabMedia) {
        media->print(cout) << std::endl;
        media->play();
    }
    return;
}

#include "film.h"

void runTest_step_6() {
    int chapters[] = {10, 20, 15, 30};
    int* chapters_begin = chapters;
    int nbChapters = sizeof(chapters) / sizeof(chapters[0]);

    Film* film = new Film("Film1", "film1.mkv", 200, chapters_begin, nbChapters);
    film->print(cout) << std::endl;
    film->play();
    return;
}

#include "group.h"

void runTest_step_7() {
    Group group_1  = Group ("My Media Group");
    Group  group_2  = Group ("Another Media Group");

    Video video_1 = Video("VideoInGroup", "video_group.mp4", 180);
    Photo photo_1 = Photo("PhotoInGroup", "photo_group.jpg", 40.7128, -74.0060);
    Film film_1 = Film("FilmInGroup", "film_group.mkv", 240, new int[3]{12, 18, 25}, 3);

    group_1.push_back(&video_1);
    group_1.push_back(&photo_1);

    group_2.push_back(&film_1);
    group_2.push_back(&video_1);

    group_1.print(cout);
    group_2.print(cout);
    return;
}



#endif // TEST_H