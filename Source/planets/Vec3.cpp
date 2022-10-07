
#include "Vec3.hpp"

#include <cmath>
#include <iostream>

namespace planets {

Vec3 operator*(const Vec3& lhs, double scalar) { return Vec3(lhs._x * scalar, lhs._y * scalar, lhs._z * scalar); }
Vec3 operator+(const Vec3& lhs, double scalar) { return Vec3(lhs._x + scalar, lhs._y + scalar, lhs._z + scalar); }
Vec3 operator/(const Vec3& lhs, double scalar) { return Vec3(lhs._x / scalar, lhs._y / scalar, lhs._z / scalar); }
Vec3 operator-(const Vec3& lhs, double scalar) { return Vec3(lhs._x - scalar, lhs._y - scalar, lhs._z - scalar); }

Vec3 operator-(const Vec3& lhs, const Vec3& rhs) {
  return Vec3(lhs._x - rhs._x, lhs._y - rhs._y, lhs._z - rhs._z);
}
void Vec3::operator+=(const Vec3& rhs) {
  _x += rhs._x;
  _y += rhs._y;
  _z += rhs._z;
}

double Vec3::mag() {
  return sqrt(sqrmag());
}

double Vec3::sqrmag() {
  return _x * _x + _y * _y + _z * _z;
}

Vec3 Vec3::normalize() {
  double magnitude = mag();
  return Vec3(_x / magnitude, _y / magnitude, _z / magnitude);
}

std::ostream&
operator<<(std::ostream& os, const Vec3 p) {
  os.precision(3);
  os << "Vec3 : [" << p._x << "; " << p._y << "; " << p._z << "]";
  return os;
}

}  // namespace planets
