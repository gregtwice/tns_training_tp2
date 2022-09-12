#include "Sphere.h"

#include <cmath>
#include <math.h>
#include <string>

#include "Point.h"
#include "Position.h"
namespace libPlanet {

Sphere::Sphere(Point p, double diameter)
    : Point(p.getName(), p.getPosition()), diameter(diameter) {
  std::cout << "Created a new Sphere at " << *this
            << " of volume : " << getVolume() << "\n";
}

Sphere::~Sphere() {}

double Sphere::getVolume() { return 4 * M_PI * pow(diameter / 2, 3) / 3; }

double Sphere::distance_center(Point &rhs) const {
  return Point::distance(rhs);
}

double Sphere::distance(Sphere &s) const {
  double rawDist = Point::distance(s);
  return rawDist - (s.diameter + diameter) / 2;
}

static bool almostEquals(double a, double b) {
  const double epsilon = 0.00001;
  return std::abs(a - b) < epsilon;
}

bool Sphere::operator==(Sphere &rhs) {
  return almostEquals(diameter, rhs.diameter);
}
bool Sphere::operator<=(Sphere &rhs) { return diameter <= rhs.diameter; }
bool Sphere::operator>=(Sphere &rhs) { return diameter >= rhs.diameter; }
bool Sphere::operator>(Sphere &rhs) { return diameter > rhs.diameter; }
bool Sphere::operator<(Sphere &rhs) { return diameter < rhs.diameter; }

double Sphere::getDiameter() { return diameter; }

Sphere::Sphere(Sphere &s)
    : Point(s.getName(), s.getPosition()), diameter(s.getDiameter()) {}
} // namespace libPlanet