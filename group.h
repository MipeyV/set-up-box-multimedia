#ifndef GROUP_H
#define GROUP_H

#include <list>
#include <string>
#include <iostream>
#include "multimedia.h"

class Group : public std::list<Multimedia*> {
private:
    std::string name;

public:
    // Constructeur
    Group(const std::string& name) : name(name) {}

    // Destructeur
    ~Group() {
        for (auto& item : *this) {
            item = nullptr;
        }
    }

    const std::string& getName() const {
        return name;
    }

    void print(std::ostream& os) const {
        os << "Group: " << name << "\n";
        for (const auto& item : *this) {
            item->print(os);
            os << "\n";
        }
    }
};

#endif // GROUP_H