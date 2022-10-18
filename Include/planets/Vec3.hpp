#ifndef INCLUDE_PLANETS_VEC3
#define INCLUDE_PLANETS_VEC3
#include <iostream>

namespace planets {
class Vec3 {
private:
public:
  /**
   * @brief Construct a new Vec 3 object with zeroed values 
   */
  Vec3() : _x(0), _y(0), _z(0){};

  /**
   * @brief Construct a new Vec 3 object
   * 
   * @param x the x coordinate
   * @param y the y coordinate
   * @param z the z coordinate
   */
  Vec3(double x, double y, double z) : _x(x), _y(y), _z(z) {}

  /**
   * @brief Calulate the magnitude of the vector
   * @remark if the calculation requires the squared magnitude of the vector, use
   * Vec3::sqrmag to avoid a costly square root calculation 
   * @return double the magnitude of the vector
   */
  double mag();

  /**
   * @brief Calculates the squared magnitude of the vector
   * 
   * @return double 
   */
  double sqrmag();

  /**
   * @brief Creates a vector with a magnitude of 1 with respect to the vector's coordinates
   * 
   * @return Vec3 a new normalized vector
   */
  Vec3 normalize();

  friend Vec3 operator*(const Vec3& lhs, const double scalar);
  friend Vec3 operator+(const Vec3& lhs, const double scalar);
  friend Vec3 operator/(const Vec3& lhs, const double scalar);
  friend Vec3 operator-(const Vec3& lhs, const double scalar);

  friend Vec3 operator-(const Vec3& lhs, const Vec3& rhs);

  friend std::ostream& operator<<(std::ostream& o, const Vec3 p);

  double _x;
  double _y;
  double _z;
  void operator+=(const Vec3& rhs);
  friend bool operator==(const Vec3& lhs, const Vec3& rhs);

  ~Vec3() = default;
};

}  // namespace planets

#endif /* INCLUDE_PLANETS_VEC3 */
