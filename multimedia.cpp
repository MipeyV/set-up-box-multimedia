#include "Multimedia.h"

// Constructeurs sans argument
Multimedia::Multimedia() : name(""), path("") {}

// Constructeurs avec arguments
Multimedia::Multimedia(const std::string& name, const std::string& path)
    : name(name), path(path) {}

// Destructeur
Multimedia::~Multimedia() {}

// Getters
std::string Multimedia::getName() const {
    return name;
}
std::string Multimedia::getPath() const {
    return path;
}

// Setters
void Multimedia::setName(const std::string& name) {
    this->name = name;
}
void Multimedia::setPath(const std::string& path) {
    this->path = path;
}

// Méthode d'affichage
std::ostream& Multimedia::print(std::ostream& os) const {
    os << "Name: " << name << ", Path: " << path;
    return os;
}