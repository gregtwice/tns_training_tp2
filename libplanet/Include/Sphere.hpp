#ifndef planets_SPHERE_HPP
#define planets_SPHERE_HPP

#include <string>

#include "Point.hpp"

namespace planets {

class Sphere : public Point {
public:
  /**
   * @brief Construct a new Sphere object
   * @param p a Point which holds the sphere's coordinates
   * @param diameter the diameter of the sphere
   */
  Sphere(Point p, double diameter);

  /**
   * @brief Construct a new Sphere object
   * Copies the sphere object
   */
  Sphere(Sphere&);

  /**
   * @brief Computes the volume of the sphere
   *
   * @return the computed volume
   */
  double getVolume() const;

  /**
   * @brief Computes the distance between the Sphere and a point
   *
   * @param Point the point to get the distance from
   * @return the computed distance
   */
  double getDistance_center(Point&) const;

  /**
   * @brief Computes the distance between a Sphere and a Sphere
   *
   * @warning If the spheres overlap, the distance will be positive
   *
   * @param Sphere the sphere to get the distance from
   *
   * @return the computed distance
   */
  double getDistance(Sphere&) const;

  ~Sphere();

  /**
   * @brief compares the Spheres based on their diameter
   */
  bool operator==(Sphere&) const;
  bool operator<=(Sphere&) const;
  bool operator>=(Sphere&) const;
  bool operator>(Sphere&) const;
  bool operator<(Sphere&) const;

  double getDiameter() const;

private:
  double _diameter;
  void printInit();
};

}  // namespace planets

#endif  // planets_SPHERE_HPP