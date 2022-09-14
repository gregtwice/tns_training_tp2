#ifndef planets_POINT_HPP
#define planets_POINT_HPP

#include <iostream>
#include <string>

#include "Position.hpp"

namespace planets {

class Point {
public:
  /**
   * @brief Construct a new Point object from a name and 3D coordinates
   */
  Point(std::string, Position);

  ~Point();
  /**
   * @brief allows to easily stream a point
   *
   * @param os the input stream
   * @param p the Point streamed
   * @return std::ostream&
   */
  friend std::ostream& operator<<(std::ostream& os, const Point p);

  /**
   * @brief Computes the distance between two points
   *
   * @return double the computed distance
   */
  virtual double getDistance(Point&) const;

  Position getPosition() const;

  std::string getName() const;

private:
  std::string name;
  Position position;

  void printInit();
};

}  // namespace planets

#endif  // planets_POINT_HPP