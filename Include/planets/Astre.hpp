#ifndef INCLUDE_PLANETS_ASTRE
#define INCLUDE_PLANETS_ASTRE

#include <algorithm>
#include <string_view>
#include <vector>
#include <memory>

#include "Point.hpp"
#include "Sphere.hpp"
#include "Iterator.hpp"
namespace planets {
class Astre : public Sphere {
public:
  /**
   * @brief Construct a new Astre object
   *
   * @param sphere a sphere upon which the Astre will be based
   * @param density the Astre's density
   */
  Astre(const Sphere& sphere, const double density);

  /**
   * @brief Construct a new Astre object
   *
   * @param sphere a sphere upon which the Astre will be based
   * @param density the Astre's density
   */
  Astre(Sphere&& sphere, const double density);

  /**
   * @brief Construct a new Astre object
   * 
   * @param rhs 
   */
  Astre(Astre&& rhs);

  /**
   * @brief Construct a new Astre object
   *
   * @param point a Point upon which the Astre will be based
   * @param diameter the diameter of the Astre
   * @param density  the density of the Astre
   */
  Astre(Point& point, const double diameter, const double density);

  /**
   * @brief Constructs a Astre object by copying the properties of the other Astre object
   * @param other the object to copy
   */
  Astre(const Astre& other);

  /**
   * \brief Creates a new Astre object by parsing the string representing the serialized object
   * \param str the string to parse
   */
  Astre(const std::string& str);

  /**
   * @brief Creates an astre interactively
   * @return an Astre
   */
  static Astre astreFromUserInput();

  ~Astre() override;

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
  double getAttraction(const Astre&) const;

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

  bool operator==(const Sphere&);
  bool operator<=(const Sphere&);
  bool operator>=(const Sphere&);
  bool operator>(const Sphere&);
  bool operator<(const Sphere&);

  bool operator==(const Astre&) const;
  bool operator<=(const Astre&) const;
  bool operator>=(const Astre&) const;
  bool operator>(const Astre&) const;
  bool operator<(const Astre&) const;

  void print(std::ostream& where) const override;

  friend std::ostream& operator<<(std::ostream& os, const Astre& a);

  /**
   * \brief Regex pattern to deserialize the Astre object
   *
   * Example of the serialised string :
   * Astre:{name : "<name>", position: [2; 4.5; 3], diameter: 5.0, density: 1}
   */
  static constexpr auto savePattern =
    "Astre:\\{"
    "name: \"([0-9a-zA-Z ]+)\", "
    "position: \\[([+-]?[0-9]*[.]?[0-9]+); ([+-]?[0-9]*[.]?[0-9]+); ([+-]?[0-9]*[.]?[0-9]+)\\], "
    "diameter: ([+-]?[0-9]*[.]?[0-9]+), "
    "density: ([+-]?[0-9]*[.]?[0-9]+)"
    "\\}";

  /**
   * Our universe's gravitationnal constant
   */
  static constexpr double gravitationnalConstant = 6.67430e-11;

  /**
   * A made up constant for a simpler model
   */
  static constexpr double gravitationnalConstantModel = 0.0001;

  /**
   * @brief Set the Mass 
   * 
   * @param mass 
   */
  void setMass(const double mass);

  void setDensity(const double density);

protected:
  Astre() = default;

private:
  double _density;
  virtual void printInit() const override;
};

}  // namespace planets

#endif /* INCLUDE_PLANETS_ASTRE */
