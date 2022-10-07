#ifndef INCLUDE_PLANETS_POSITION
#define INCLUDE_PLANETS_POSITION

#include <string>

#include "Vec3.hpp"

namespace planets {

/**
 * @brief Position reprensents a tuple of x,y,z coordinates in 3D space
 */
class Position {
public:
  double _x;
  double _y;
  double _z;
  /**
   * @brief Construct a new Position object
   *
   * @param x the X coordinate
   * @param y the Y coordinate
   * @param z the Z coordinate
   */
  Position(double x, double y, double z);

  /**
   * @brief Construct a new Position object with zeroed coordinates
   */
  Position();

  /**
   * @brief Construct a new Position from user input in the terminal
   */
  static Position positionFromUserInput();

  /**
   * @brief Calculates the Vector resulting in the diffrence of positions
   * 
   * @param lhs a Position
   * @param rhs a Position
   * @return Vec3 the vector reprensenting the distance between the positions
   */
  friend Vec3 operator-(Position lhs, Position rhs);

  /**
   * @brief Adds a vector to a position, moving in in 3D space
   * 
   * @param lhs the Position
   * @param rhs the Vec3
   * @return Position the shifted position
   */
  friend Position operator+(Position lhs, Vec3 rhs);

  friend std::ostream& operator<<(std::ostream& o, const Position p);

  ~Position();
};
}  // namespace planets

#endif /* INCLUDE_PLANETS_POSITION */
