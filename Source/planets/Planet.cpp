#include "Planet.hpp"

#include "Observer.hpp"
#include "Position.hpp"
#include "Vec3.hpp"
#include "Iterator.hpp"

#include <cmath>
#include <iostream>
#include <regex>

namespace planets {

void Planet::printInit() const {
  auto pos = getPosition();
  double x = pos._x;
  double y = pos._y;
  double z = pos._z;
  std::cout << "Created an Planet of mass " << getMass() << ", and diameter "
            << getDiameter() << ", at (" << x << ", " << y << ", " << z << ")"
            << std::endl;
}

Planet::Planet(const std::string& str) {
  // create a regex from the pattern that the planet has been saved to
  std::regex astreRx(savePattern);
  std::smatch m;

  // parse the string and assign each field

  std::regex_match(str, m, astreRx);

  Position p(std::stod(m[2]), std::stod(m[3]), std::stod(m[4]));
  setPosition(p);

  setName(m[1]);
  setDiameter(std::stod(m[5]));
  setDensity(std::stod(m[6]));
  Vec3 vel(std::stod(m[7]), std::stod(m[8]), std::stod(m[9]));
  setVelocity(vel);
}

void Planet::updateVelocity(Planet& other, double timestep) {
  // https://en.wikipedia.org/wiki/Gravitational_acceleration
  // g = -^r * GM / |r²|
  // Since we do other - this to get the position, the negative sign must be removed

  double squaredDistance = (other.getPosition() - getPosition()).sqrmag();

  // get the direction of the force
  Vec3 forceDir = (other.getPosition() - getPosition()).normalize();

  // get g
  Vec3 acceleration = (forceDir * Astre::gravitationnalConstant * (other.getMass())) / squaredDistance;

  _velocity += (acceleration * timestep);
}

void Planet::updateVelocity(mycollections::Iterator<Planet*> it, double timestep) {
  // see the single updateVelocity
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
  double initalspeed = sqrt(((p.getMass() + getMass()) * Astre::gravitationnalConstant) / getDistance_center(p));
  _velocity = Vec3(0, initalspeed, 0);
}

void Planet::updatePosition(double timestep) {
  // if the current position's x coordinate is lower than the previous position's and the next one's then the planet has done a revolution around the sun
  /**    ____
   *    /    \
   * > |      |
   *    \____/
   */
  auto nextPos = getPosition() + _velocity * timestep;
  if (_previousPos._x > getPosition()._x && nextPos._x > getPosition()._x) {
    if (getDiameter() > 150 && getDiameter() < 2000) {
      notifyObservers();
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
    obs->update("The planet " + getName() + " completed a trip around the sun !!");
  }
}

bool Planet::doesItCollide(Planet& rhs) {
  return getDistance_center(rhs) < (getDiameter() + rhs.getDiameter());
}

void Planet::checkCollisions(mycollections::Iterator<Planet*> it) {
  while (it.hasNext()) {
    auto planet = it.next();
    if (this != planet && doesItCollide(*planet)) {
      observers.iter().forEach([this, &planet](cli::Observer* obs) { obs->update("The planet " + getName() + "has collided with the Asteroid [" + planet->getName() + "]"); });
    }
  }
}

void Planet::print(std::ostream& os) const {
  auto pos = getPosition();
  double px = pos._x;
  double py = pos._y;
  double pz = pos._z;

  auto vel = getVelocity();
  double vx = vel._x;
  double vy = vel._y;
  double vz = vel._z;

  os << "Planet:{name: \"" << getName()
     << "\", position: [" << px << "; " << py << "; " << pz << "]"
     << ", diameter: " << getDiameter()
     << ", density: " << getDensity()
     << ", velocity : [" << vx << "; " << vy << "; " << vz << "]"
     << "}";
}

std::ostream& operator<<(std::ostream& os, const Planet& p) {
  p.print(os);
  return os;
}

}  // namespace planets
