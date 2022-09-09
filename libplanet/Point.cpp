#include "Point.h"

#include <cmath>

Point::Point(std::string nom, double x, double y, double z)
    : nom(nom), x(x), y(y), z(z) {}

/// @brief Computes the euclidian distance between two points
/// @param rhs the Point to get the distance from
/// @return the computed distance
double Point::distance(Point& rhs) {
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