#include "SolarSystem.hpp"

#include <cstdio>
#include <memory>
#include <chrono>
#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <utility>

#include "Asteroid.hpp"
#include "Astre.hpp"
#include "Point.hpp"
#include "Position.hpp"
#include "Sphere.hpp"
#include "Planet.hpp"
#include "UserInterface.hpp"
#include "Vec3.hpp"

namespace planets {

void SolarSystem::createPlanet(PlanetParams params) {
  Planet p(Astre(Sphere(Point(params.name, params.position), params.radius * 2), 0), params.velocity);
  // as this is not a real solar system, the mass is a function of the radius and the surface gravity of the planet.
  p.setMass(params.surface_gravity * params.radius * params.radius / Astre::gravitationnalConstantModel);
  planets.push_m(std::make_shared<Planet>(std::move(p)));
}

SolarSystem::SolarSystem() {
  // Sun of the system
  {
    PlanetParams sun_params = {
      .name = "S",
      .position = Position(0, 0, 0),
      .radius = 1500,
      .surface_gravity = 50,
      .velocity = Vec3(0, 0, 0),
    };

    createPlanet(sun_params);
  }

  /**********************************  TWIN EARTHS  *****************************************/

  {
    PlanetParams earth1_params = {
      .name = "E1",
      .position = Position(-11033.0, 0, 0),
      .radius = 300,
      .surface_gravity = 10,
      .velocity = Vec3(0, 115.36, 0),
    };

    createPlanet(earth1_params);
  }
  {
    PlanetParams earth2_params = {
      .name = "E2",
      .position = Position(-13038.0, 0, 0),
      .radius = 300,
      .surface_gravity = 10,
      .velocity = Vec3(0, 80.6, 0),
    };

    createPlanet(earth2_params);
  }

  /**********************************************************************************************/
  {
    PlanetParams gp_params = {
      .name = "GP",
      .position = Position(-24295, 0, 0),
      .radius = 200,
      .surface_gravity = 8,
      .velocity = Vec3(0, 70.23, 0),
    };

    createPlanet(gp_params);
  }
  /**********************************************************************************************/

  {
    PlanetParams gp_sat_params = {
      .name = "GPS",
      .position = Position(-23549.0, 0, 0),
      .radius = 50,
      .surface_gravity = 3,
      .velocity = Vec3(0, 51, 0),
    };

    createPlanet(gp_sat_params);
  }

  /**********************************************************************************************/

  {
    PlanetParams pgg_params = {
      .name = "PGG",
      .position = Position(-58811.0, 0, 0),
      .radius = 500,
      .surface_gravity = 14,
      .velocity = Vec3(0, 50.3, 0),
    };

    createPlanet(pgg_params);
  }

  /**********************************************************************************************/

  {
    PlanetParams pgg_sat_params = {
      .name = "PGG",
      .position = Position(-55700.0, 0, 0),
      .radius = 40,
      .surface_gravity = 2,
      .velocity = Vec3(0, 18.3, 0),
    };

    createPlanet(pgg_sat_params);
  }

  /**********************************************************************************************/

  // Add the astroids
  for (size_t i = 0; i < 20; i++) {
    asteroids.push_m(std::make_shared<Asteroid>(Asteroid::withRandomCoordinates(i)));
  }

  // Add the observer for the asteroid crash
  asteroids.iter().forEach([](std::shared_ptr<Asteroid> a) {
    a->registerObserver(&cli::UserInterface::getInstance());
  });

  // add the observer for the planet sun revolution
  planets.iter()
    .forEach([](auto x) {
      x->registerObserver(&cli::UserInterface::getInstance());
    });
}

/**
 * @brief Create a mat file to record the planet positions
 * 
 * @return FILE* 
 */
FILE* create_mat_file() {
  auto t = std::time(nullptr);
  auto tm = *std::localtime(&t);
  std::ostringstream oss;

  // If the OS is windows, there is no /tmp directory
  // so the file goes in the current directory

#if (defined(_WIN32) || defined(_WIN64))
  // windows code
  oss << "./planet_simu_" << std::put_time(&tm, "%d-%m-%Y %H-%M-%S") << ".mat";
#else
  oss << "/tmp/planet_simu_" << std::put_time(&tm, "%d-%m-%Y %H-%M-%S") << ".mat";
#endif

  std::string filename = oss.str();

  FILE* pFile = fopen(filename.c_str(), "w");
  return pFile;
}

void SolarSystem::run(const unsigned int steps) {
  using namespace std::chrono_literals;

  // Create the collection of planets to simulate
  mycollections::StaticVector<planets::Planet*, 40> bodies;

  // add the planets
  for (size_t j = 0; j < planets.getSize(); j++) {
    std::shared_ptr<planets::Planet> p;
    p = std::dynamic_pointer_cast<planets::Planet>(planets[j]);
    bodies.push(p.get());
  }

  // add the asteroids
  for (size_t j = 0; j < asteroids.getSize(); j++) {
    std::shared_ptr<planets::Asteroid> p;
    p = std::dynamic_pointer_cast<planets::Asteroid>(asteroids[j]);
    bodies.push(p.get());
  }

  auto pFile = create_mat_file();

  for (int i = 0; i < steps; i++) {
    bodies
      // it is more stable to update the velocity and then the position
      .iter()
      // update the velocity by applying f= M * A for each body in the system
      .forEach([&bodies](auto body) { body->updateVelocity(bodies.iter(), 1); })
      // print the current position
      .forEach([&pFile](auto body) {
        fprintf(pFile, "%s %e %e ", body->getName().c_str(), body->getPosition()._x, body->getPosition()._y);
      })
      // update the position
      .forEach([](auto body) { body->updatePosition(1); })
      // verify that no body has crashed into each other
      .forEach([&bodies](auto body) { body->checkCollisions(bodies.iter()); });

    planets::Planet* toRemove = nullptr;
    bodies.iter().forEach([&bodies, &toRemove](planets::Planet* body) {
      // if a planet is too far away, then it is better to remove it to facilitate the render of the solar system
      if (body->getDistance(*bodies[0]) > 300000) toRemove = body;
      // if an asteroid has crashed, remove it
      if (body->hasCrashed()) toRemove = body;
    });
    if (toRemove != nullptr) {
      toRemove->removeObserver(&cli::UserInterface::getInstance());
      bodies.remove(toRemove);
    }

    fprintf(pFile, "\n");
  }
  auto t = std::time(nullptr);
  auto tm = *std::localtime(&t);
#if (defined(_WIN32) || defined(_WIN64))
  // windows code
  std::oss << "Outputed results in this file : ./planet_simu_" << std::put_time(&tm, "%d-%m-%Y %H-%M-%S") << ".mat\n";
#else
  std::cout << "Outputed results in this file : /tmp/planet_simu_" << std::put_time(&tm, "%d-%m-%Y %H-%M-%S") << ".mat\n";
#endif
}

}  // namespace planets