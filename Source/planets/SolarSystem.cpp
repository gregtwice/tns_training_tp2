#include "SolarSystem.hpp"

#include <cstdio>
#include <memory>
#include <chrono>
#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>

#include "Asteroid.hpp"
#include "Point.hpp"
#include "Sphere.hpp"
#include "Planet.hpp"
#include "UserInterface.hpp"

namespace planets {

SolarSystem::SolarSystem() {
  auto sun_radius = 1500.0;
  auto sun_position = Position(0, 0, 0);
  auto sun_surface_gravity = 50;
  auto sun_mass = (sun_surface_gravity * sun_radius * sun_radius / Astre::gravitationnalConstantModel);

  // Planet sun(Astre(Sphere(Point("Sun", sun_position), sun_radius * 2), sun_surface_gravity), Vec3(0, 0, 0));
  Planet sun(Astre(Sphere(Point("S", sun_position), sun_radius * 2), sun_surface_gravity), Vec3(0, 0, 0));
  sun.setMass(sun_mass);
  std::cout << sun_mass << "\n";

  /**********************************************************************************************/

  auto earth1_position = Position(-11033.0, 0, 0);
  auto earth2_position = Position(-13038.0, 0, 0);
  auto earth1_speed = Vec3(0, 115.36, 0);
  auto earth2_speed = Vec3(0, 80.6, 0);

  auto earth_radius = 300;
  auto earth_surface_gravity = 10;
  auto earth_mass = (earth_surface_gravity * earth_radius * earth_radius / Astre::gravitationnalConstantModel);

  // Planet earth1(Astre(Sphere(Point("Earth 1", earth1_position), earth_radius * 2), 0), earth1_speed);
  Planet earth1(Astre(Sphere(Point("E1", earth1_position), earth_radius * 2), 0), earth1_speed);
  // Planet earth2(Astre(Sphere(Point("Earth 2", earth2_position), earth_radius * 2), 0), earth2_speed);
  Planet earth2(Astre(Sphere(Point("E2", earth2_position), earth_radius * 2), 0), earth2_speed);
  earth1.setMass(earth_mass);
  earth2.setMass(earth_mass);
  std::cout << earth1.getMass() << "\n";

  /**********************************************************************************************/

  auto gp_position = Position(-24295, 0, 0);
  auto gp_radius = 200;
  auto gp_surface_gravity = 8;
  auto gp_mass = (gp_surface_gravity * gp_radius * gp_radius / Astre::gravitationnalConstantModel);

  // Planet green_planet(Astre(Sphere(Point("Green Planet", gp_position), gp_radius * 2), gp_surface_gravity), Vec3(0, 70.23, 0));
  Planet green_planet(Astre(Sphere(Point("GP", gp_position), gp_radius * 2), gp_surface_gravity), Vec3(0, 70.23, 0));
  green_planet.setMass(gp_mass);

  /**********************************************************************************************/

  auto gp_sat_position = Position(-23549.0, 0, 0);
  auto gp_sat_radius = 50;
  auto gp_sat_surface_gravity = 3;
  auto gp_sat_mass = gp_sat_surface_gravity * gp_sat_radius * gp_sat_radius / Astre::gravitationnalConstantModel;

  // Planet gp_sat(Astre(Sphere(Point("Green Planet Satelite", gp_sat_position), gp_sat_radius * 2), 0), Vec3(0, 51, 0));
  Planet gp_sat(Astre(Sphere(Point("GPS", gp_sat_position), gp_sat_radius * 2), 0), Vec3(0, 51, 0));
  gp_sat.setMass(gp_sat_mass);

  auto pgg_position = Position(-58811.0, 0, 0);
  auto pgg_radius = 500;
  auto pgg_surface_gravity = 14;
  auto pgg_mass = pgg_surface_gravity * pgg_radius * pgg_radius / Astre::gravitationnalConstantModel;

  // Planet pgg(Astre(Sphere(Point("Purple gas giant", pgg_position), pgg_radius * 2), 0), Vec3(0, 50.3, 0));
  Planet pgg(Astre(Sphere(Point("PGG", pgg_position), pgg_radius * 2), 0), Vec3(0, 50.3, 0));
  pgg.setMass(pgg_mass);
  /**********************************************************************************************/
  auto pgg_sat_radius = 40;
  auto pgg_sat_position = Position(-55700.0, 0, 0);
  auto pgg_sat_surface_gravity = 2;
  auto pgg_sat_mass = (pgg_sat_surface_gravity * pgg_sat_radius * pgg_sat_radius / Astre::gravitationnalConstantModel);

  // Planet pgg_sat(Astre(Sphere(Point("Purple gas giant sat1", pgg_sat_position), pgg_sat_radius * 2), 0), Vec3(0, 18.3, 0));
  Planet pgg_sat(Astre(Sphere(Point("PPGS", pgg_sat_position), pgg_sat_radius * 2), 0), Vec3(0, 18.3, 0));
  pgg_sat.setMass(pgg_sat_mass);

  planets.push_m(std::make_shared<Planet>(std::move(sun)));
  planets.push_m(std::make_shared<Planet>(std::move(earth1)));
  planets.push_m(std::make_shared<Planet>(std::move(earth2)));
  planets.push_m(std::make_shared<Planet>(std::move(green_planet)));
  planets.push_m(std::make_shared<Planet>(std::move(gp_sat)));
  planets.push_m(std::make_shared<Planet>(std::move(pgg)));
  planets.push_m(std::make_shared<Planet>(std::move(pgg_sat)));

  for (size_t i = 0; i < 20; i++) {
    asteroids.push_m(std::make_shared<Asteroid>(Asteroid::withRandomCoordinates(i)));
  }

  asteroids.iter().forEach([](std::shared_ptr<Asteroid> a) {
      a->registerObserver(&cli::UserInterface::getInstance());
      std::cout << a->getVelocity() << "\n"; });

  planets.iter()
    .forEach([](auto x) {
      x->registerObserver(&cli::UserInterface::getInstance());
    });
}

FILE* create_mat_file() {
  auto t = std::time(nullptr);
  auto tm = *std::localtime(&t);
  std::ostringstream oss;
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

  mycollections::StaticVector<planets::Planet*, 40> bodies;
  for (size_t j = 0; j < planets.getSize(); j++) {
    std::shared_ptr<planets::Planet> p;
    p = std::dynamic_pointer_cast<planets::Planet>(planets[j]);
    bodies.push(p.get());
  }

  for (size_t j = 0; j < asteroids.getSize(); j++) {
    std::shared_ptr<planets::Asteroid> p;
    p = std::dynamic_pointer_cast<planets::Asteroid>(asteroids[j]);
    bodies.push(p.get());
  }

  std::cout << bodies.getSize() << "\n";

  auto pFile = create_mat_file();

  for (int i = 0; i < steps; i++) {
    bodies
      .iter()
      .forEach([&bodies](auto body) { body->updateVelocity(bodies.iter(), 1); })
      .forEach([&pFile](auto body) {
        fprintf(pFile, "%s %e %e ", body->getName().c_str(), body->getPosition()._x, body->getPosition()._y);
      })
      .forEach([](auto body) { body->updatePosition(1); })
      .forEach([&bodies](auto body) { body->checkCollisions(bodies.iter()); });

    planets::Planet* toRem = nullptr;
    bodies.iter().forEach([&bodies, &toRem](planets::Planet* body) {
      if (body->getDistance(*bodies[0]) > 300000) toRem = body;
      if (body->hasCrashed()) toRem = body;
    });
    if (toRem != nullptr)
      toRem->removeObserver(&cli::UserInterface::getInstance());
    bodies.remove(toRem);

    fprintf(pFile, "\n");
  }
}

}  // namespace planets