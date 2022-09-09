#include "Point.h"

#include "Position.h"

#include <cmath>
#include <string>
namespace libPlanet {

Point::Point(std::string name, Position p) : name(name), position(p) {}

double Point::distance(Point &rhs) const {
  double dx = this->position.x - rhs.position.x;
  double dy = this->position.y - rhs.position.y;
  double dz = this->position.z - rhs.position.z;
  return std::sqrt(dx * dx + dy * dy + dz * dz);
}

std::ostream &operator<<(std::ostream &os, const Point p) {
  os << "Point:{ nom: " << p.name << ", x: " << p.position.x
     << ", y: " << p.position.y << ", z: " << p.position.z << " }";
  return os;
}

Position Point::getPosition() { return position; }
std::string &Point::getName() { return name; }
} // namespace libPlanet
