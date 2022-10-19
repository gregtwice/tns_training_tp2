#ifndef INCLUDE_PLANETS_SOLARSYSTEM
#define INCLUDE_PLANETS_SOLARSYSTEM

#include "Asteroid.hpp"
#include "MyStaticVector.hpp"
#include "Planet.hpp"

namespace planets {

class SolarSystem {
public:
  /**
   * @brief Construct a new Solar System object with hardcoded parameters
   */
  SolarSystem();
  ~SolarSystem() = default;

  /**
   * @brief Runs the system for the number of specified steps
   * 
   * @param steps the number of steps to run the system for
   */
  void run(const unsigned int steps);

private:
  mycollections::StaticVector<std::shared_ptr<planets::Planet>, 20> planets;
  mycollections::StaticVector<std::shared_ptr<planets::Asteroid>, 20> asteroids;
};
}  // namespace planets

#endif /* INCLUDE_PLANETS_SOLARSYSTEM */
