#include "Planet.hpp"

#include "Position.hpp"
#include "Vec3.hpp"
#include "Iterator.hpp"

#include <cmath>
#include <iostream>

namespace planets {

void Planet::updateVelocity(Planet& other, double timestep) {
  double squaredDistance = (other.getPosition() - getPosition()).sqrmag();
  Vec3 forceDir = (other.getPosition() - getPosition()).normalize();

  Vec3 acceleration = (forceDir * Astre::gravitationnalConstant * (other.getMass())) / squaredDistance;
  _velocity += (acceleration * timestep);
}

void Planet::updateVelocity(mycollections::Iterator<Planet*> it, double timestep) {
  while (it.hasNext()) {
    auto body = it.next();
    if (this != body) {
      double squaredDistance = (body->getPosition() - getPosition()).sqrmag();
      Vec3 forceDir = (body->getPosition() - getPosition()).normalize();
      Vec3 acceleration = (forceDir * Astre::gravitationnalConstantModel * (body->getMass())) /
                          squaredDistance;
      _velocity += (acceleration * timestep);
    }
  }
}

void Planet::setVelocityRelativeToOrbitDistance(Planet& p) {
  std::cout << getDistance_center(p) << "\n";
  double initalspeed = sqrt(((p.getMass() + getMass()) * Astre::gravitationnalConstant) / getDistance_center(p));
  std::cout << initalspeed << "\n";
  _velocity = Vec3(0, initalspeed, 0);
}

void Planet::updatePosition(double timestep) {
  auto nextPos = getPosition() + _velocity * timestep;
  if (_previousPos._x > getPosition()._x && nextPos._x > getPosition()._x) {
    if (getDiameter() > 150 && getDiameter() < 2000) {
      notifyObservers();
      //std::cout << _previousPos << getPosition() << nextPos << "\n";
    }
  }
  _previousPos = getPosition();
  setPosition(nextPos);
}

void Planet::registerObserver(cli::Observer* observer) {
  observers.push(observer);
}
void Planet::removeObserver(cli::Observer* observer) {
  observers.remove(observer);
}
void Planet::notifyObservers() {
  auto it = observers.iter();
  while (it.hasNext()) {
    auto obs = it.next();
    obs->update("The planet " + this->getName() + " completed a trip around the sun !!");
  }
}

}  // namespace planets
