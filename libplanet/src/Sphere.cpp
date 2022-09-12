#include "Sphere.h"

#include <math.h>
#include <cmath>
#include <string>

#include "Point.h"
#include "Position.h"
namespace libPlanet {

Sphere::Sphere(Point p, double diameter)
    : Point(p.getName(), p.getPosition()), _diameter(diameter) {
    std::cout << "Created a new Sphere at " << *this
              << " of volume : " << getVolume() << "\n";
}

Sphere::Sphere(Sphere& s)
    : Point(s.getName(), s.getPosition()), _diameter(s.getDiameter()) {}

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

double Sphere::getDiameter() const {
    return _diameter;
}

}  // namespace libPlanet
