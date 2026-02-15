#ifndef TEST_H
#define TEST_H

#include <array>
#include <iostream>
#include <memory>

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

    auto video_1 = std::make_shared<Video>("VideoInGroup", "video_group.mp4", 180);
    auto photo_1 = std::make_shared<Photo>("PhotoInGroup", "photo_group.jpg", 40.7128, -74.0060);
    auto film_1 = std::make_shared<Film>("FilmInGroup", "film_group.mkv", 240, new int[3]{12, 18, 25}, 3);

    group_1.push_back(video_1);
    group_1.push_back(photo_1);

    group_2.push_back(film_1);
    group_2.push_back(video_1);

    group_1.print(cout);
    group_2.print(cout);
    return;
}

void runTest_step_7_copy() {
    int chapters[] = {5, 10, 15};
    Film original("CopyFilm", "copy_film.mkv", 90, chapters, 3);
    Film copied = original;

    std::cout << "Original: ";
    original.print(std::cout) << std::endl;
    std::cout << "Copied: ";
    copied.print(std::cout) << std::endl;
}



#endif // TEST_H
