#include "Sphere.h"

#include <math.h>
#include <cmath>
#include <string>

namespace libPlanet {

Sphere::Sphere(std::string nom, double x, double y, double z, double diameter)
    : Point(nom, x, y, z), diameter(diameter) {
  std::cout << "Created a new planet at " << *this
            << " of volume : " << volume() << "\n";
}

Sphere::~Sphere() {}

double Sphere::volume() {
  return 4 * M_PI * pow(diameter / 2, 3) / 3;
}

double Sphere::distance(Point& rhs) const {
  return Point::distance(rhs) - diameter / 2;
}

double Sphere::distance(Sphere& s) const {
  double rawDist = Point::distance(s);
  std::cout << "R\n";
  return rawDist - (s.diameter + diameter) / 2;
}
}  // namespace libPlanet
