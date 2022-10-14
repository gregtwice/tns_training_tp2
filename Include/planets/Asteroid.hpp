#ifndef INCLUDE_PLANETS_ASTEROID
#define INCLUDE_PLANETS_ASTEROID

#include <utility>
#include "Astre.hpp"
#include "Planet.hpp"
#include "Vec3.hpp"

namespace planets {
class Asteroid : public Planet {
public:
  Asteroid(Asteroid&&) = default;
  ~Asteroid() = default;
  Asteroid(Planet&& rhs);
  Asteroid(Planet&&, Vec3 vel);

  /**
   * @brief Creates an Asteroid with random coordinates and velocity
   * 
   * @param id the number to add at the end of the name of the asteroid
   * @return Asteroid 
   */
  static Asteroid withRandomCoordinates(const int id);

  /**
   * @brief Checks for collisions with the given planets
   * 
   * @param it the collection's iterator to check for collisions 
   */
  void checkCollisions(mycollections::Iterator<Planet*> it) override;
};

}  // namespace planets

#endif /* INCLUDE_PLANETS_ASTEROID */
