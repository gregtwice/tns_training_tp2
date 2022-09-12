#include "Astre.h"
#include "Point.h"
#include "Sphere.h"

#include <iostream>

namespace libPlanet {

Astre::Astre(Sphere s, double density) : Sphere(s), _density(density) {
    auto pos = getPosition();
    double x = pos._x;
    double y = pos._y;
    double z = pos._z;

    std::cout << "Created an Astre of mass " << getMass() << ", and diameter "
              << getDiameter() << ", at (" << x << ", " << y << ", " << z << ")"
              << std::endl;
}

Astre::Astre(Point point, double diameter, double density)
    : Sphere(point, diameter), _density(density) {}

double Astre::getMass() {
    return getVolume() * _density;
}

double Astre::getDensity() {
    return _density;
}

bool Astre::operator==(Sphere& rhs) {
    return rhs == *this;
}
bool Astre::operator<=(Sphere& rhs) {
    return rhs >= *this;
}
bool Astre::operator>=(Sphere& rhs) {
    return rhs <= *this;
}
bool Astre::operator>(Sphere& rhs) {
    return rhs < *this;
}
bool Astre::operator<(Sphere& rhs) {
    return rhs > *this;
}

bool Astre::operator==(Astre& rhs) {
    return getMass() == rhs.getMass();
}
bool Astre::operator<=(Astre& rhs) {
    return getMass() <= rhs.getMass();
}
bool Astre::operator>=(Astre& rhs) {
    return getMass() >= rhs.getMass();
}
bool Astre::operator>(Astre& rhs) {
    return getMass() > rhs.getMass();
}
bool Astre::operator<(Astre& rhs) {
    return getMass() < rhs.getMass();
}

}  // namespace libPlanet