#pragma once

#include <string>

#include "Point.h"

namespace libPlanet {

class Sphere : public Point {
private:
  double diameter;

public:
  Sphere(Point p, double diameter);
  Sphere(Sphere &);
  /**
   * @brief Computes the volume of the sphere
   *
   * @return the computed volume
   */
  double getVolume();

  /**
   * @brief Computes the distance between the Sphere and a point
   *
   * @param Point the point to get the distance from
   * @return the computed distance
   */
  double distance_center(Point &) const;

  /**
   * @brief Computes the distance between a Sphere and a Sphere
   *
   * @warning If the spheres overlap, the distance will be positive
   *
   * @param Sphere the sphere to get the distance from
   *
   * @return the computed distance
   */
  double distance(Sphere &) const;

  ~Sphere();

  /**
   * @brief compares the Spheres based on their diameter
   */
  bool operator==(Sphere &);
  bool operator<=(Sphere &);
  bool operator>=(Sphere &);
  bool operator>(Sphere &);
  bool operator<(Sphere &);

  double getDiameter();
};

} // namespace libPlanet
