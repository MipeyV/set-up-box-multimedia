#ifndef PHOTO_H
#define PHOTO_H

#include "multimedia.h"

class Photo : public Multimedia {
private:
    double latitude;
    double longitude;

public:
    // Constructeur par défaut
    Photo()
        : Multimedia(), latitude(0.0), longitude(0.0) {}

    // Constructeur avec arguments
    Photo(const std::string& name,
          const std::string& path,
          double latitude,
          double longitude)
        : Multimedia(name, path),
          latitude(latitude),
          longitude(longitude) {}

    // Destructeur
    ~Photo() {
        std::cout << "Destructeur Photo: " << getName() << " destroyed" << std::endl;
    }

    // Getters
    double getLatitude() const {
        return latitude;
    }

    double getLongitude() const {
        return longitude;
    }

    // Setters
    void setLatitude(double lat) {
        latitude = lat;
    }

    void setLongitude(double lon) {
        longitude = lon;
    }

    // Affichage : même signature que la classe de base
    std::ostream& print(std::ostream& os) const override {
        Multimedia::print(os);
        os << ", Latitude: " << latitude
           << ", Longitude: " << longitude;
        return os;
    }

    // Lecture / affichage de la photo
    void play() const override {
        std::string cmd = "imagej " + getPath() + " &";
        system(cmd.c_str());
    }
};

#endif // PHOTO_H
