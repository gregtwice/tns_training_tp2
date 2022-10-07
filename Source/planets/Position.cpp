#include "Position.hpp"
#include <iostream>

#include <regex>
#include <string>
#include <iomanip>

namespace planets {

Position::Position(const double x, const double y, const double z) : _x(x), _y(y), _z(z) {}

Position::Position() : _x(0), _y(0), _z(0) {}

Position::~Position() = default;

Position Position::positionFromUserInput() {
  std::string userInput;
  std::cout << "What is the object's position ? X,Y,Z\n>>> ";
  std::cin >> userInput;
  std::regex rx(
    "([+-]?[0-9]*[.]?[0-9]+),([+-]?[0-9]*[.]?[0-9]+),([+-]?[0-9]*[.]?[0-9]+"
    ")");
  std::smatch m;
  if (std::regex_match(userInput, m, rx)) {
    return Position(std::stod(m[1]), std::stod(m[2]), std::stod(m[3]));
  }
  throw "Not a valid position";
}

Vec3 operator-(Position lhs, Position rhs) {
  return Vec3(lhs._x - rhs._x, lhs._y - rhs._y, lhs._z - rhs._z);
}

Position operator+(Position lhs, Vec3 rhs) {
  return Position(lhs._x + rhs._x, lhs._y + rhs._y, lhs._z + rhs._z);
}

std::ostream&
operator<<(std::ostream& os, const Position p) {
  os.precision(4);
  os << "Position : [" << std::setw(10) << p._x << "; " << std::setw(10) << p._y << "; " << std::setw(10) << p._z << "]";
  return os;
}

}  // namespace planets