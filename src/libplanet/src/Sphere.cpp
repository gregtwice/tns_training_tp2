#include "Sphere.hpp"

#include <cmath>
#include <string>

#include "Point.hpp"
#include "Position.hpp"
#include "Validator.hpp"

namespace planets {

void Sphere::printInit() {
  std::cout << "Created a new Sphere" << *this
            << " of volume : " << getVolume() << "\n";
}

Sphere::Sphere(Point& p, double diameter)
    : Point(p.getName(), p.getPosition()), _diameter(diameter) {
  printInit();
}

Sphere::Sphere(Sphere& s)
    : Point(s.getName(), s.getPosition()), _diameter(s.getDiameter()) {
  printInit();
}

Sphere Sphere::sphereFromUserInput() {
  std::string userInput;
  double diameter;
  Point p = Point::pointFromUserInput();

  diameter = utils::Validator::validateDouble("What is the diameter of the object?\n>>> ",
    "Invalid Input! Please input a numerical value.");

  return Sphere(p, diameter);
}

Sphere::~Sphere() = default;

double Sphere::getVolume() const {
  return 4 * M_PI * pow(_diameter / 2, 3) / 3;
}

double Sphere::getDistance_center(Point& rhs) const {
  return Point::getDistance(rhs);
}

double Sphere::getDistance(Sphere& s) const {
  double rawDist = Point::getDistance(s);
  return rawDist - (s._diameter + _diameter) / 2;
}

static bool almostEquals(double a, double b) {
  const double epsilon = 0.00001;
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

}  // namespace planets
