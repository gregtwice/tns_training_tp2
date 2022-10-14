#include "Sphere.hpp"

#include <algorithm>
#include <cmath>
#include <string>
#include <regex>

#include "Point.hpp"
#include "Position.hpp"
#include "Validator.hpp"

namespace planets {

void Sphere::printInit() const {
  std::cout << "Created a new Sphere " << *this
            << " of volume : " << getVolume() << "\n";
}

Sphere::Sphere(const Point& p, double diameter) : Point(p), _diameter(diameter) {
  Sphere::printInit();
}

Sphere::Sphere(Point&& p, double diameter) : Point(std::move(p)), _diameter(diameter) {}

Sphere::Sphere(Sphere&& rhs) : Point(std::move(rhs)), _diameter(rhs._diameter) {}

Sphere::Sphere(const Sphere& s)
    : Point(s.getName(), s.getPosition()), _diameter(s.getDiameter()) {
  Sphere::printInit();
}

Sphere::Sphere(const std::string& str) {
  static std::regex sphereRx(savePattern);
  std::smatch m;
  std::regex_match(str, m, sphereRx);
  Position p(std::stod(m[2]), std::stod(m[3]), std::stod(m[4]));
  setName(m[1]);
  setPosition(p);
  _diameter = std::stod(m[5]);
}

Sphere Sphere::sphereFromUserInput() {
  std::string userInput;
  Point p = Point::pointFromUserInput();

  const double diameter = utils::Validator::validateDouble("What is the diameter of the object?\n>>> ",
    "Invalid Input! Please input a numerical value.");

  return Sphere(std::move(p), diameter);
}

Sphere::~Sphere() = default;

double Sphere::getVolume() const {
  return 4 * M_PI * pow(_diameter / 2, 3) / 3;
}

double Sphere::getDistance_center(const Point& rhs) const {
  return Point::getDistance(rhs);
}

double Sphere::getDistance(const Sphere& s) const {
  const double rawDist = Point::getDistance(s);
  return rawDist - (s._diameter + _diameter) / 2;
}

static bool almostEquals(double a, double b) {
  constexpr double epsilon = 0.00001;
  return std::abs(a - b) < epsilon;
}

bool Sphere::operator==(Sphere& rhs) const {
  return almostEquals(_diameter, rhs._diameter);
}

bool Sphere::operator<=(Sphere& rhs) const {
  return _diameter <= rhs._diameter;
}

bool Sphere::operator>=(Sphere& rhs) const {
  return _diameter >= rhs._diameter;
}

bool Sphere::operator>(Sphere& rhs) const {
  return _diameter > rhs._diameter;
}

bool Sphere::operator<(Sphere& rhs) const {
  return _diameter < rhs._diameter;
}

void Sphere::print(std::ostream& os) const {
  auto pos = getPosition();
  double x = pos._x;
  double y = pos._y;
  double z = pos._z;
  os << "Sphere:{"
     << "name: \"" << getName() << "\""
     << ", position: [" << x << "; " << y << "; " << z << "]"
     << ", diameter: " << _diameter
     << "}";
}

std::ostream& operator<<(std::ostream& os, Sphere& s) {
  s.print(os);
  return os;
}

double Sphere::getDiameter() const { return _diameter; }

void Sphere::setDiameter(const double d) { _diameter = d; }

}  // namespace planets
