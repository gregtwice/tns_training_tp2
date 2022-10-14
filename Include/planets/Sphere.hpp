#ifndef SRC_INCLUDE_PLANETS_SPHERE
#define SRC_INCLUDE_PLANETS_SPHERE

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
  Sphere(Point&& p, double diameter);

  /**
   * @brief Construct a new Sphere object
   * @param p a Point which holds the sphere's coordinates
   * @param diameter the diameter of the sphere
   */
  Sphere(Point& p, double diameter);

  /**
   * @brief Construct a new Sphere object
   * Copies the sphere object
   */
  Sphere(const Sphere&);

  /**
   * @brief Construct a new Sphere object with a moved sphere object
   * 
   * @param rhs the moved sphere
   */
  Sphere(Sphere&& rhs);

  /**
   * @brief Construct a new Sphere object from a string
   * 
   * @param str 
   */
  Sphere(const std::string& str);

  static Sphere sphereFromUserInput();

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

  virtual void print(std::ostream& where) const override;

  friend std::ostream& operator<<(std::ostream& os, Sphere& s);

  double getDiameter() const;

  static constexpr auto savePattern =
    "Sphere:\\{"
    "name: \"([0-9a-zA-Z ]+)\", "
    "position: \\[([+-]?[0-9]*[.]?[0-9]+); ([+-]?[0-9]*[.]?[0-9]+); ([+-]?[0-9]*[.]?[0-9]+)\\], "
    "diameter: ([+-]?[0-9]*[.]?[0-9]+)"
    "\\}";

protected:
  Sphere() = default;

  void setDiameter(const double d);

private:
  double _diameter;
  void printInit() override;
};

}  // namespace planets

#endif /* SRC_INCLUDE_PLANETS_SPHERE */
