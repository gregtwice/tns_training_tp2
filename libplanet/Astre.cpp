#include "Astre.h"
#include "Point.h"
#include "Sphere.h"

#include <iostream>

namespace libPlanet {

Astre::Astre(Sphere s, double density) : Sphere(s), density(density) {

  auto pos = getPosition();
  double x = pos.x;
  double y = pos.y;
  double z = pos.z;

  std::cout << "Created an Astre of mass " << getMass() << ", and diameter "
            << getDiameter() << ", at (" << x << ", " << y << ", " << z << ")"
            << std::endl;
}

Astre::Astre(Point point, double diameter, double density)
    : Sphere(point, diameter), density(density) {}

double Astre::getMass() { return getVolume() * density; }

double Astre::getDensity() { return density; }

bool Astre::operator==(Sphere &rhs) { return rhs == *this; }
bool Astre::operator<=(Sphere &rhs) { return rhs >= *this; }
bool Astre::operator>=(Sphere &rhs) { return rhs <= *this; }
bool Astre::operator>(Sphere &rhs) { return rhs < *this; }
bool Astre::operator<(Sphere &rhs) { return rhs > *this; }

bool Astre::operator==(Astre &rhs) { return getMass() == rhs.getMass(); }
bool Astre::operator<=(Astre &rhs) { return getMass() <= rhs.getMass(); }
bool Astre::operator>=(Astre &rhs) { return getMass() >= rhs.getMass(); }
bool Astre::operator>(Astre &rhs) { return getMass() > rhs.getMass(); }
bool Astre::operator<(Astre &rhs) { return getMass() < rhs.getMass(); }

} // namespace libPlanet