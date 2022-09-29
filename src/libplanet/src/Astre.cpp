#include "Astre.hpp"

#include <iostream>
#include <memory>
#include <regex>

#include "Point.hpp"
#include "Sphere.hpp"
#include "Validator.hpp"

namespace planets {

void Astre::printInit() {
  auto pos = getPosition();
  double x = pos._x;
  double y = pos._y;
  double z = pos._z;
  std::cout << "Created an Astre of mass " << getMass() << ", and diameter "
            << getDiameter() << ", at (" << x << ", " << y << ", " << z << ")"
            << std::endl;
}

Astre::Astre(Sphere& s, double density) : Sphere(s), _density(density) {
  Astre::printInit();
}

Astre::Astre(Point& point, double diameter, double density)
    : Sphere(point, diameter), _density(density) {
    Astre::printInit();
}

Astre::Astre(Astre& other) : Sphere(other), _density(other._density){}

Astre::Astre(const std::string& str) {
  std::regex astreRx(savePattern);
  std::smatch m;

  std::regex_match(str, m, astreRx);

  Position p(std::stod(m[2]), std::stod(m[3]), std::stod(m[4]));
  setPosition(p);

  setName(m[1]);
  setDiameter(std::stod(m[5]));
  _density =  std::stod(m[6]);
};

// Astre::Astre(Astre&& other) : Sphere(other), _density(other._density) {}

Astre Astre::astreFromUserInput() {
  Sphere s = Sphere::sphereFromUserInput();
  std::cout << "What is the density of the object?\n>>>";
  const double density = utils::Validator::validateDouble("What is the density of the object?\n>>>",
    "Invalid Input! Please input a numerical value.");

  return Astre(s, density);
}

Astre::~Astre() = default;

double Astre::getMass() const { return getVolume() * _density; }

double Astre::getDensity() const { return _density; }

/**
{F}_{{A/B}}={F}_{{B/A}}=G{\frac {M_{A}M_{B}}{d^{2}}}
*/
double Astre::getAttraction(Astre& b) const {
  const double G = 6.67430e-11;
  const double d = getDistance_center(b);
  return (G * getMass() * b.getMass()) / (d * d);
}

bool Astre::operator==(const Sphere& rhs) { return rhs == *this; }

bool Astre::operator<=(const Sphere& rhs) { return rhs >= *this; }

bool Astre::operator>=(const Sphere& rhs) { return rhs <= *this; }

bool Astre::operator>(const Sphere& rhs) { return rhs < *this; }

bool Astre::operator<(const Sphere& rhs) { return rhs > *this; }

bool Astre::operator==(const Astre& rhs) const { return getMass() == rhs.getMass(); }

bool Astre::operator<=(const Astre& rhs) const { return getMass() <= rhs.getMass(); }

bool Astre::operator>=(const Astre& rhs) const { return getMass() >= rhs.getMass(); }

bool Astre::operator>(const Astre& rhs) const  { return getMass() > rhs.getMass(); }

bool Astre::operator<(const Astre& rhs) const { return getMass() < rhs.getMass(); }

void Astre::print(std::ostream& os) const {
  auto pos = getPosition();
  double x = pos._x;
  double y = pos._y;
  double z = pos._z;
  os << "Astre:{name: \"" << getName()
     << "\", position: [" << x << "; " << y << "; " << z << "]"
     << ", diameter: " << getDiameter()
     << ", density: " << getDensity() << "}";
}

std::ostream& operator<<(std::ostream& os, const Astre& a) {
  a.print(os);
  return os;
}

}  // namespace planets