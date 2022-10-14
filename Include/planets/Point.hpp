#ifndef INCLUDE_PLANETS_POINT
#define INCLUDE_PLANETS_POINT

#include <iostream>
#include <string>

#include "Position.hpp"

namespace planets {

class Point {
public:
  /**
   * @brief Construct a new Point object from a name and 3D coordinates
   */
  Point(std::string, const Position&);

  /**
   * @brief Constructs a Point by copying another Point
   * @param other the point to copy
   */
  Point(const Point& other);

  /**
   * @brief Constructs a Point from a serialized string
   * @param str the serialized string
   */
  Point(const std::string& str);

  virtual ~Point();
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

  void setPosition(const Position& pos) { _position = pos; }

  std::string getName() const;

  void setName(const std::string& name);

  /**
   * @brief Creates a point with interactive user input
   * @return a new Point
   */
  static Point pointFromUserInput();

  virtual void print(std::ostream& where) const;

  static constexpr auto& savePattern = "Point:\\{name: \"([0-9a-zA-Z ]+)\", position: \\[([+-]?[0-9]*[.]?[0-9]+); ([+-]?[0-9]*[.]?[0-9]+); ([+-]?[0-9]*[.]?[0-9]+)\\]\\}";

protected:
  Point();

private:
  std::string _name;
  Position _position;

  virtual void printInit() const;
};

}  // namespace planets

#endif /* INCLUDE_PLANETS_POINT */
