#ifndef planets_ASTRE_HPP
#define planets_ASTRE_HPP

#include <string_view>
#include <vector>
#include <memory>
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
  Astre(Sphere& sphere, double density);

  /**
   * @brief Construct a new Astre object
   *
   * @param point a Point upon which the Astre will be based
   * @param diameter the diameter of the Astre
   * @param density  the density of the Astre
   */
  Astre(Point& point, double diameter, double density);

  Astre(Astre& other);

  /**
   * @brief Creates an astre interractively
   * @return an Astre
   */
  static Astre astreFromUserInput();

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
  template <class Iterator>
  double sumAttraction(Iterator first, Iterator last) {
    double sum = 0;
    for (auto it = first; it != last; it++) {
      // the iterator is a pointer to a pointer so double dereference to get the value
      sum += getAttraction(**it);
    }
    return sum;
  }

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

  void print(std::ostream& where) const override;

  friend std::ostream& operator<<(std::ostream& os, const Astre& a);

  static constexpr auto savePattern =
    "Astre:\\{"
    "name: \"([0-9a-zA-Z ]+)\", "
    "position: \\[([+-]?[0-9]*[.]?[0-9]+); ([+-]?[0-9]*[.]?[0-9]+); ([+-]?[0-9]*[.]?[0-9]+)\\], "
    "diameter: ([+-]?[0-9]*[.]?[0-9]+), "
    "density: ([+-]?[0-9]*[.]?[0-9]+)"
    "\\}";

private:
  double _density;
  void printInit();
};

}  // namespace planets

#endif  // planets_ASTRE_HPP