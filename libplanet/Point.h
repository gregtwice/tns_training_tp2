#pragma once

#include <iostream>
#include <string>

#include "Position.h"

namespace libPlanet {

class Point {
private:
  std::string name;
  Position position;

public:
  /**
   * @brief Construct a new Point object from a name and 3D coordinates
   */
  Point(std::string, Position);

  ~Point(){};
  /**
   * @brief allows to easily stream a point
   *
   * @param os the input stream
   * @param p the Point streamed
   * @return std::ostream&
   */
  friend std::ostream &operator<<(std::ostream &os, const Point p);

  /**
   * @brief Computes the distance between two points
   *
   * @return double the computed distance
   */
  virtual double distance(Point &) const;

  Position getPosition();
  std::string &getName();
};

} // namespace libPlanet
