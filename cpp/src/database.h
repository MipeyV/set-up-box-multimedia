#ifndef DATABASE_H
#define DATABASE_H

#include <map>
#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include "multimedia.h"
#include "video.h"
#include "photo.h"
#include "film.h"
#include "group.h"

using MultimediaPtr = std::shared_ptr<Multimedia>;
using GroupPtr = std::shared_ptr<Group>;

class Database {
private:
    std::map<std::string, MultimediaPtr> medias;
    std::map<std::string, GroupPtr> groups;

public:
    // Constructeur et destructeur
    Database() {}
    ~Database() {}

    // Créer des objets multimédia
    MultimediaPtr createPhoto(const std::string& name, const std::string& path, 
                              double latitude, double longitude) {
        auto photo = std::make_shared<Photo>(name, path, latitude, longitude);
        medias[name] = photo;
        return photo;
    }

    MultimediaPtr createVideo(const std::string& name, const std::string& path, 
                              int duration) {
        auto video = std::make_shared<Video>(name, path, duration);
        medias[name] = video;
        return video;
    }

    MultimediaPtr createFilm(const std::string& name, const std::string& path, 
                             int duration, const int* chapters, int nbChapters) {
        auto film = std::make_shared<Film>(name, path, duration, chapters, nbChapters);
        medias[name] = film;
        return film;
    }

    // Créer un groupe
    GroupPtr createGroup(const std::string& name) {
        auto group = std::make_shared<Group>(name);
        groups[name] = group;
        return group;
    }

    // Chercher et afficher
    void search(const std::string& name) {
        auto it = medias.find(name);
        if (it != medias.end()) {
            std::cout << "Objet trouvé : ";
            it->second->print(std::cout) << std::endl;
        } else {
            std::cout << "Objet '" << name << "' non trouvé." << std::endl;
        }
    }

    void searchGroup(const std::string& name) {
        auto it = groups.find(name);
        if (it != groups.end()) {
            std::cout << "Groupe trouvé : " << std::endl;
            it->second->print(std::cout);
        } else {
            std::cout << "Groupe '" << name << "' non trouvé." << std::endl;
        }
    }

    // Jouer un objet multimédia
    void play(const std::string& name) {
        auto it = medias.find(name);
        if (it != medias.end()) {
            std::cout << "Lecture de : " << name << std::endl;
            it->second->play();
        } else {
            std::cout << "Impossible de lire '" << name << "' : objet non trouvé." << std::endl;
        }
    }

    // Afficher tous les objets ou groupes
    void printAll() const {
        std::cout << "=== Tous les objets multimédia ===" << std::endl;
        for (const auto& pair : medias) {
            std::cout << "- " << pair.first << " : ";
            pair.second->print(std::cout) << std::endl;
        }
    }

    void printAllGroups() const {
        std::cout << "=== Tous les groupes ===" << std::endl;
        for (const auto& pair : groups) {
            std::cout << "Groupe : " << pair.first << std::endl;
            pair.second->print(std::cout);
        }
    }
};

#endif // DATABASE_H
