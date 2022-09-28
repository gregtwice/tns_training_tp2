#ifndef planets_POINT_HPP
#define planets_POINT_HPP

#include <iostream>
#include <optional>
#include <string>
#include <string_view>

#include "Position.hpp"

namespace planets {

class Point {
public:
  /**
   * @brief Construct a new Point object from a name and 3D coordinates
   */
  Point(const std::string&, const Position&);

  Point(const Point& other);

  Point(Point&& other) = default;

  ~Point();
  /**
   * @brief allows to easily stream a point
   *
   * @param os the input stream
   * @param p the Point streamed
   * @return std::ostream&
   */
  friend std::ostream& operator<<(std::ostream& os, const Point& p);

  /**
   * @brief Computes the distance between two points
   *
   * @return double the computed distance
   */
  virtual double getDistance(const Point&) const;

  Position getPosition() const;

  std::string getName() const;

  static Point pointFromUserInput();

  static std::optional<Point> fromString(std::string& str);

  virtual void print(std::ostream& where) const;

  static constexpr auto& savePattern = "Point:\\{name: \"([0-9a-zA-Z ]+)\", position: \\[([+-]?[0-9]*[.]?[0-9]+); ([+-]?[0-9]*[.]?[0-9]+); ([+-]?[0-9]*[.]?[0-9]+)\\]\\}";

private:
  std::string name;
  Position position;

  void printInit();
};

}  // namespace planets

#endif  // planets_POINT_HPP