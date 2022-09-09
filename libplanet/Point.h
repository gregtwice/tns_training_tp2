#pragma once

#include <iostream>
#include <string>

namespace libPlanet {

class Point {
 private:
  std::string nom;
  double x;
  double y;
  double z;

 public:
  /**
   * @brief Construct a new Point object from a name and 3D coordinates
   */
  Point(std::string, double, double, double);

  ~Point(){};
  /**
   * @brief allows to easily stream a point
   *
   * @param os the input stream
   * @param p the Point streamed
   * @return std::ostream&
   */
  friend std::ostream& operator<<(std::ostream& os, const Point p);

  double getX();
  double getY();
  double getZ();
  /**
   * @brief Computes the distance between two points
   *
   * @return double the computed distance
   */
  virtual double distance(Point&) const;
};

}  // namespace libPlanet
