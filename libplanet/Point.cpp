#include "Point.h"

#include <cmath>
namespace libPlanet {
Point::Point(std::string nom, double x, double y, double z)
    : nom(nom), x(x), y(y), z(z) {}

double Point::distance(Point& rhs) const {
  double dx = this->x - rhs.x;
  double dy = this->y - rhs.y;
  double dz = this->z - rhs.z;
  return std::sqrt(dx * dx + dy * dy + dz * dz);
}

double Point::getX() {
  return x;
}
double Point::getY() {
  return y;
}
double Point::getZ() {
  return z;
}

std::ostream& operator<<(std::ostream& os, const Point p) {
  os << "Point:{ nom: " << p.nom << ", x: " << p.x << ", y: " << p.y
     << ", z: " << p.z << " }";
  return os;
}
}  // namespace libPlanet
