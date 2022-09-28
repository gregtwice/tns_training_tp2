#include "Position.hpp"
#include <iostream>

#include <regex>
#include <string>

namespace planets {

Position::Position(double x, double y, double z) : _x(x), _y(y), _z(z) {}

// Position::Position(Position& other) : _x(other._x), _y(other._y), _z(other._z) {}

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

std::ostream& operator<<(std::ostream& os, const Position p) {
  os << "Position : [" << p._x << "; " << p._y << "; " << p._z << "]";
  return os;
}

}  // namespace planets