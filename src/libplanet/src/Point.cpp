#include "Point.hpp"
#include "Position.hpp"

#include <cmath>
#include <iostream>
#include <optional>
#include <regex>
#include <string>

namespace planets {

void Point::printInit() {
  double x = _position._x;
  double y = _position._y;
  double z = _position._z;
  std::cout << "Creating a point of name " << _name << " At Coordinates : {" << x
            << ", " << y << ", " << z << "}" << std::endl;
}

Point::Point(std::string name, const Position& p) : _name(std::move(name)), _position(p) {
  Point::printInit();
}

Point::Point(const Point& other) : _name(other._name), _position(other._position) {}

Point::Point(const std::string& str) {
  const std::regex pointRx(savePattern);
  std::smatch m;
  std::regex_match(str, m, pointRx);
  Position p(std::stod(m[2]), std::stod(m[3]), std::stod(m[4]));
  _position = p;
  _name = m[1];
  Point::printInit();
}

Point::~Point() = default;

double Point::getDistance(const Point& rhs) const {
  const double dx = this->_position._x - rhs._position._x;
  const double dy = this->_position._y - rhs._position._y;
  const double dz = this->_position._z - rhs._position._z;
  return std::sqrt(dx * dx + dy * dy + dz * dz);
}

void Point::print(std::ostream& where) const {
  where << "Point:{name: \"" << _name << "\", position: [" << _position._x << "; " << _position._y << "; " << _position._z << "]}";
}

Point::Point() = default;

std::ostream& operator<<(std::ostream& os, const Point& p) {
  p.print(os);
  return os;
}

Position Point::getPosition() const { return _position; }
std::string Point::getName() const { return _name; }

void Point::setName(const std::string& name) { _name = name; }

Point Point::pointFromUserInput() {
  std::string userInput = "default";
  Position p = Position::positionFromUserInput();
  std::cout << "What is the name of the object ?\n>>> ";
  std::cin >> userInput;

  return Point(userInput, p);
}

}  // namespace planets
