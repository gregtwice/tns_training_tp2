#ifndef planets_ASTRE_HPP
#define planets_ASTRE_HPP

#include <vector>

#include "Point.hpp"
#include "Sphere.hpp"

namespace planets {
class Astre : public Sphere {
public:
  /**
   * @brief Construct a new Astre object
   *
   * @param sphere a sphere upon which the Astre will be based
   * @param density the Astre's density
   */
  Astre(Sphere sphere, double density);

  /**
   * @brief Construct a new Astre object
   *
   * @param point a Point upon which the Astre will be based
   * @param diameter the diameter of the Astre
   * @param density  the density of the Astre
   */
  Astre(Point point, double diameter, double density);

  ~Astre();

  /**
   * @brief Returns the computed mass of the Astre
   *
   * @return the mass
   */
  double getMass() const;

  /**
   * @brief Get the Density of the sphere
   *
   * @return the density
   */
  double getDensity() const;

  /**
   * @brief computes the gravitation force applied to each Astre using
   * Newton's law of universal gravitation
   *
   * @return double the computed gravitation force in Newtons
   */
  double getAttraction(Astre&);

  /**
   * @brief Computes the sum of the gravitation forces of all the astres in
   * the list applied to the Astre
   *
   * @param list the list of Astres to calculate the gravitational force that
   * they apply
   * @return double the sum of all gravitational forces
   */
  double sumAttraction(std::vector<Astre*> list);

  bool operator==(Sphere&);
  bool operator<=(Sphere&);
  bool operator>=(Sphere&);
  bool operator>(Sphere&);
  bool operator<(Sphere&);

  bool operator==(Astre&);
  bool operator<=(Astre&);
  bool operator>=(Astre&);
  bool operator>(Astre&);
  bool operator<(Astre&);

private:
  double _density;
  void printInit();
};

}  // namespace planets

#endif  // planets_ASTRE_HPP