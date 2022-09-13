#include "Point.h"
#include "Position.h"

#include <cmath>
#include <iostream>
#include <string>

namespace libPlanet {

void Point::printInit() {
    double x = position._x;
    double y = position._y;
    double z = position._z;
    std::cout << "Creating a point of name " << name << " At Coordinates : {"
              << x << ", " << y << ", " << z << "}" << std::endl;
}

Point::Point(std::string name, Position p) : name(name), position(p) {
    printInit();
}

Point::~Point() = default;

double Point::getDistance(Point& rhs) const {
    double dx = this->position._x - rhs.position._x;
    double dy = this->position._y - rhs.position._y;
    double dz = this->position._z - rhs.position._z;
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

std::ostream& operator<<(std::ostream& os, const Point p) {
    os << "Point:{ nom: " << p.name << ", x: " << p.position._x
       << ", y: " << p.position._y << ", z: " << p.position._z << " }";
    return os;
}

Position Point::getPosition() const {
    return position;
}
std::string Point::getName() const {
    return name;
}
}  // namespace libPlanet
