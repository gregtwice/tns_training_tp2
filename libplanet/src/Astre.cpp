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
    : Sphere(point, diameter), _density(density) {
    auto pos = getPosition();
    double x = pos._x;
    double y = pos._y;
    double z = pos._z;
    std::cout << "Created an Astre of mass " << getMass() << ", and diameter "
              << getDiameter() << ", at (" << x << ", " << y << ", " << z << ")"
              << std::endl;
}

double Astre::getMass() const {
    return getVolume() * _density;
}

double Astre::getDensity() const {
    return _density;
}

/*
{F}_{{A/B}}={F}_{{B/A}}=G{\frac {M_{A}M_{B}}{d^{2}}}
*/
double Astre::getAttraction(Astre& b) {
    const double G = 6.67430e-11;
    const double d = distance_center(b);
    return (G * getMass() * b.getMass()) / (d * d);
}

double Astre::sumAttraction(std::vector<Astre*> list) {
    double sum = 0;
    for (auto astre : list) {
        sum += this->getAttraction(*astre);
    }
    return sum;
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