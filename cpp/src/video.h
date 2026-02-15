#ifndef VIDEO_H
#define VIDEO_H

#include "multimedia.h"

class Video : public Multimedia {
private:
    int duration;

public:
    // Constructeur par défaut
    Video()
        : Multimedia(), duration(0) {}

    // Constructeur avec arguments
    Video(const std::string& name,
          const std::string& path,
          int duration)
        : Multimedia(name, path), 
          duration(duration >= 0 ? duration : 0) {}

    // Destructeur
    ~Video() {
        std::cout << "Destructeur Video: " << getName() << " destroyed" << std::endl;
    }

    // Getter / Setter
    int getDuration() const {
        return duration;
    }

    void setDuration(int d) {
        if (d >= 0) duration = d;
        else perror("Durée invalide");
    }

    // Affichage
    std::ostream& print(std::ostream& os) const override {
        Multimedia::print(os);
        os << ", Duration: " << duration << " s";
        return os;
    }

    // Lecture de la vidéo
    void play() const override {
        std::string cmd = "mpv " + getPath() + " &";
        system(cmd.c_str());
    }
};

#endif // VIDEO_H