#ifndef FILM_H
#define FILM_H

#include "video.h"
#include <iostream>

class Film : public Video {
private:
    int  nbChapters = 0;             
    int* chapters    = nullptr;
public:
    // Constructeur par défaut
    Film() : Video(), nbChapters(0), chapters(nullptr) {}

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

    // Constructeur de copie
    Film(const Film& other)
        : Video(other),
          nbChapters(other.nbChapters),
          chapters(other.nbChapters ? new int[other.nbChapters] : nullptr) {
        for (int i = 0; i < nbChapters; ++i) {
            chapters[i] = other.chapters[i];
        }
    }

    // Opérateur d'affectation
    Film& operator=(const Film& other) {
        if (this == &other) return *this;
        Video::operator=(other);
        int* newChapters = other.nbChapters ? new int[other.nbChapters] : nullptr;
        for (int i = 0; i < other.nbChapters; ++i) {
            newChapters[i] = other.chapters[i];
        }
        delete[] chapters;
        chapters = newChapters;
        nbChapters = other.nbChapters;
        return *this;
    }

    // Destructeur
    ~Film() override {
        std::cout << "Destructeur Film: " << getName() << " destroyed" << std::endl;
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
            this->chapters = nbChapters ? new int[nbChapters] : nullptr;
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
        os << "]";
        return os;
    }
};

#endif // FILM_H
