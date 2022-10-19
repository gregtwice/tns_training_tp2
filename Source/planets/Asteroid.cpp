#include "Asteroid.hpp"
#include <random>
#include <string>

#include "Astre.hpp"
#include "Planet.hpp"
#include "Point.hpp"
#include "Position.hpp"
#include "Sphere.hpp"
#include "Vec3.hpp"

namespace planets {

Asteroid::Asteroid(Planet&& rhs, const Vec3 vel) : Planet(std::move(rhs)) {
  setVelocity(vel);
}

Asteroid::Asteroid(Planet&& rhs) : Planet(std::move(rhs)){};

Asteroid Asteroid::withRandomCoordinates(const int id) {
  std::random_device rd;

  // asteroids spawn with velocities between -100 and 100
  std::uniform_real_distribution<double> distVel(-100, 100);

  // asteroids spawn with velocities between -50000 and 50000
  std::uniform_real_distribution<double> distPos(-50000, 50000);

  auto vel = Vec3(distVel(rd), distVel(rd), distVel(rd));
  auto position = Position(distPos(rd), distPos(rd), distPos(rd));
  return Asteroid(Planet(Astre(Sphere(Point("A_" + std::to_string(id), position), 0), 0), vel));
}

void Asteroid::checkCollisions(mycollections::Iterator<Planet*> it) {
  while (it.hasNext()) {
    auto planet = it.next();
    if (this != planet && doesItCollide(*planet)) {
      observers.iter().forEach([this, &planet](cli::Observer* obs) {
        obs->update("The planet " + getName() + "has collided with the Asteroid [" + planet->getName() + "]");
      });
      _crashed = true;
    }
  }
}

}  // namespace planets
