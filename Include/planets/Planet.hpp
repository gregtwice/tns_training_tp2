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

  Vec3 getVelocity() { return _velocity; }
  void setVelocity(Vec3 v) { _velocity = v; }

private:
  /**
   * @brief the curent velocity of the planet moving in the simulated universe
   */
  Vec3 _velocity;
  /**
   * @brief Previous position of the planet used to calculate if a revolution around the sun has been made
   */
  Position _previousPos;
  mycollections::StaticVector<cli::Observer*, 3> observers;
  bool revolutionComplete = true;

  void printInit() override;
};
}  // namespace planets

#endif /* INCLUDE_PLANETS_PLANET */
