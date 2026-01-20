#ifndef MULTIMEDIA_H
#define MULTIMEDIA_H

#include <string>
#include <iostream>

class Multimedia {
private:
    std::string name;
    std::string path;

public:
    // Constructeurs
    Multimedia();
    Multimedia(const std::string& name, const std::string& path);

    // Destructeur
    virtual ~Multimedia();

    // Getters
    std::string getName() const;
    std::string getPath() const;

    // Setters
    void setName(const std::string& name);
    void setPath(const std::string& path);

    // Méthode d'affichage
    virtual std::ostream& print(std::ostream& os) const;

    // Méthode de lecture (à redéfinir dans les classes dérivées)
    virtual void play() const = 0;
};

#endif // MULTIMEDIA_H