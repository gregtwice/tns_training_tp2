#ifndef INCLUDE_PLANETS_PLANET
#define INCLUDE_PLANETS_PLANET

#include "Astre.hpp"
#include "MyStaticVector.hpp"
#include "Position.hpp"
#include "Vec3.hpp"
#include "Iterator.hpp"

#include "Subject.hpp"
#include "Observer.hpp"

namespace planets {

class Planet : public Astre, public cli::Subject {
public:
  /**
   * @brief Construct a new Planet object from an astre and a velocity
   * 
   * @param a an Astre
   * @param velocity 
   */
  Planet(Astre& a, Vec3 velocity) : Astre(a), _velocity(velocity){};

  /**
   * @brief Construct a new Planet object with the move contructor of Astre
   * 
   * @param a the astre to be moved
   * @param velocity the velocity of the planet
   */
  Planet(Astre&& a, Vec3 velocity) : Astre(std::move(a)), _velocity(velocity) { Planet::printInit(); };

  /**
   * @brief Construct a new Planet object by copying the astre object
   * 
   * @param other the astre to copy
   */
  Planet(Planet& other) : Astre(other), _velocity(other._velocity) {}

  /**
   * @brief Construct a new Planet object with a moved planet
   * 
   * @param rhs the moved planet
   */
  Planet(Planet&& rhs) = default;

  /**
   * \brief Creates a new Planet object by parsing the string representing the serialized object
   * \param str the string to parse
   */
  Planet(const std::string& str);

  /**
   * @brief Set the Velocity Relative To Orbit Distance of the given plannet  
   * 
   * @param p the planet to calculate the velocity needed to orbit it
   */
  void setVelocityRelativeToOrbitDistance(Planet& p);

  /**
   * @brief Updates the velocity of the planet based on the list of planets given to it
   * 
   * @param it an iterator of the planets that influence the velocity
   * @param timestep the simulation's timestep
   */
  void updateVelocity(mycollections::Iterator<Planet*> it, double timestep);

  /**
   * @brief Updates the velocity of the planet based on the planet given to it
   * 
   * @param other the planet that influence the velocity
   * @param timestep the simulation's timestep
   */
  void updateVelocity(Planet& other, double timestep);

  /**
   * @brief updates the position of the planet based on its velocity
   * 
   * @param timestep the simulation's timestep
   */
  void updatePosition(double timestep);

  /**
   * @brief Adds an observer to the notification group
   *
   * @param observer the observer to add
   */
  void registerObserver(cli::Observer* observer) override;

  /**
   * @brief Remove the observer from the notfication group
   * 
   * @param observer the observer to remove
   */
  void removeObserver(cli::Observer* observer) override;

  /**
   * @brief Sends a message to all the observers in the notification group
   */
  void notifyObservers() override;

  Vec3 getVelocity() const { return _velocity; }
  void setVelocity(Vec3 v) { _velocity = v; }

  /**
   * @brief Checks whether two bodies collide into each other 
   * 
   * @param rhs the body to check against
   * @return whether two bodies collide into each other 
   */
  bool doesItCollide(Planet& rhs);

  /**
   * @brief Checks for collisions with the given planets
   * 
   * @param it the collection's iterator to check for collisions 
   */
  virtual void checkCollisions(mycollections::Iterator<Planet*> it);

  bool hasCrashed() { return _crashed; }

  /**
   * @brief displays the planet on a stream given as parameter
   * 
   * @param where the stream to print to
   */
  void print(std::ostream& where) const override;

  friend std::ostream& operator<<(std::ostream& os, const Planet& p);

  static constexpr auto savePattern =
    "Planet:\\{"
    "name: \"([0-9a-zA-Z ]+)\", "
    "position: \\[([+-]?[0-9]*[.]?[0-9]+); ([+-]?[0-9]*[.]?[0-9]+); ([+-]?[0-9]*[.]?[0-9]+)\\], "
    "diameter: ([+-]?[0-9]*[.]?[0-9]+), "
    "density: ([+-]?[0-9]*[.]?[0-9]+), "
    "velocity: \\[([+-]?[0-9]*[.]?[0-9]+); ([+-]?[0-9]*[.]?[0-9]+); ([+-]?[0-9]*[.]?[0-9]+)\\]"
    "\\}";

protected:
  mycollections::StaticVector<cli::Observer*, 3> observers;
  bool _crashed = false;

private:
  /**
   * @brief the curent velocity of the planet moving in the simulated universe
   */
  Vec3 _velocity;
  /**
   * @brief Previous position of the planet used to calculate if a revolution around the sun has been made
   */
  Position _previousPos;
  bool revolutionComplete = true;

  void printInit() const override;
};
}  // namespace planets

#endif /* INCLUDE_PLANETS_PLANET */
