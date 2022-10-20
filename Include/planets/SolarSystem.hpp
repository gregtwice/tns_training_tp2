#ifndef INCLUDE_PLANETS_SOLARSYSTEM
#define INCLUDE_PLANETS_SOLARSYSTEM

#include <iterator>
#include <memory>
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

  SolarSystem(mycollections::Iterator<std::shared_ptr<planets::Point>> iter);
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

  struct PlanetParams {
    std::string name;
    Position position;
    double radius;
    double surface_gravity;
    Vec3 velocity;
  };
  void createPlanet(PlanetParams params);
};
}  // namespace planets

#endif /* INCLUDE_PLANETS_SOLARSYSTEM */
