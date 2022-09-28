#include "Point.hpp"
#include "Position.hpp"

#include <cmath>
#include <iostream>
#include <optional>
#include <regex>
#include <string>

namespace planets {

void Point::printInit() {
  double x = position._x;
  double y = position._y;
  double z = position._z;
  std::cout << "Creating a point of name " << name << " At Coordinates : {" << x
            << ", " << y << ", " << z << "}" << std::endl;
}

Point::Point(const std::string& name, const Position& p) : name(name), position(p) {
  printInit();
}

Point::Point(const Point& other) : name(other.name), position(other.position) {}

Point::~Point() = default;

double Point::getDistance(const Point& rhs) const {
  double dx = this->position._x - rhs.position._x;
  double dy = this->position._y - rhs.position._y;
  double dz = this->position._z - rhs.position._z;
  return std::sqrt(dx * dx + dy * dy + dz * dz);
}

void Point::print(std::ostream& os) const {
  os << "Point:{name: \"" << name << "\", position: [" << position._x << "; " << position._y << "; " << position._z << "]}";
}

std::ostream& operator<<(std::ostream& os, const Point& p) {
  p.print(os);
  return os;
}

Position Point::getPosition() const { return position; }
std::string Point::getName() const { return name; }

Point Point::pointFromUserInput() {
  std::string userInput = "default";
  Position p = Position::positionFromUserInput();
  std::cout << "What is the name of the object ?\n>>> ";
  std::cin >> userInput;

  return Point(userInput, p);
}

std::optional<Point> Point::fromString(std::string& str) {
  std::regex pointRx(savePattern);
  std::smatch m;
  if (std::regex_match(str, m, pointRx)) {
    Position p(std::stod(m[2]), std::stod(m[3]), std::stod(m[4]));
    return Point(m[1], p);
  }
  return std::nullopt;
}

}  // namespace planets
