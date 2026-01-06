#ifndef FILM_H
#define FILM_H

#include "video.h"
#include <iostream>

class Film : public Video {
private:
    int* chapters = nullptr; 
int  nbChapters = 0;             

public:
    // Constructeur par défaut
    Film() : Video(), chapters(nullptr), nbChapters(0) {}

    // Constructeur avec arguments
    Film(const std::string& name,
         const std::string& path,
         int duration,
         const int* chapters,
         int nbChapters):
        Video(name, path, duration),
        nbChapters(nbChapters),
        chapters(new int[nbChapters])
    {
        setChapters(chapters, nbChapters);
    }

    // Destructeur
    ~Film() override {
        delete[] chapters;
    }

    // Getters
    int getNbChapters() const {
        return nbChapters;
    }

    const int* getChapters() const {
        return chapters;
    }

    // Setters
    void setChapters(const int* chapters, int nbChapters) {
        if (this->nbChapters != nbChapters) {
            delete[] this->chapters;
            this->chapters = new int[nbChapters];
        }
        this->nbChapters = nbChapters;
        for (int i = 0; i < nbChapters; ++i) {
            this->chapters[i] = chapters[i];
        }
    }

    // Affichage
    std::ostream& print(std::ostream& os) const override {
        Video::print(os);
        os << ", Chapters: [";
        for (int i = 0; i < nbChapters; ++i) {
            os << chapters[i];
            if (i < nbChapters - 1) {
                os << ", ";
            }
        }
    }
};

#endif // FILM_H