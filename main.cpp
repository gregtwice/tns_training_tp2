#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <cstdio>

#include "UserInterface.hpp"

#include "Astre.hpp"
#include "MyStaticVector.hpp"
#include "Planet.hpp"
#include "Point.hpp"
#include "Position.hpp"
#include "Sphere.hpp"
#include "Vec3.hpp"

void createSolarSystem();

void println(std::string str) {
  std::cout << str << std::endl;
}

int main(int, char**) {
  // createSolarSystem();
  auto cli = cli::UserInterface::getInstance();
  cli.loop();
}

void createSolarSystem() {
  using namespace planets;
  println("-------------------------------------------------------------");
  println("SUN");

  auto sun_radius = 1500.0;
  auto sun_position = Position(0, 0, 0);
  auto sun_surface_gravity = 50;
  auto sun_mass = (sun_surface_gravity * sun_radius * sun_radius / Astre::gravitationnalConstantModel);

  Planet sun(Astre(Sphere(Point("Sun", sun_position), sun_radius * 2), sun_surface_gravity), Vec3(0, 0, 0));
  sun.setMass(sun_mass);

  println("-------------------------------------------------------------");
  println("EARTHs");

  auto earth1_position = Position(-11033, 0, 0);
  auto earth2_position = Position(-13038, 0, 0);
  auto earth1_speed = Vec3(0, 115.3, 0);
  auto earth2_speed = Vec3(0, 80.6, 0);

  auto earth_radius = 300;
  auto earth_surface_gravity = 10;
  auto earth_speed = Vec3(0, 102.57, 0);
  auto earth_mass = (earth_surface_gravity * earth_radius * earth_radius / Astre::gravitationnalConstantModel);

  Planet earth1(Astre(Sphere(Point("Earth 1", earth1_position), earth_radius * 2), 0), earth1_speed);
  Planet earth2(Astre(Sphere(Point("Earth 2", earth2_position), earth_radius * 2), 0), earth2_speed);
  earth1.setMass(earth_mass);
  earth2.setMass(earth_mass);

  println("-------------------------------------------------------------");
  println("Green Planet");

  auto gp_position = Position(-24295, 0, 0);
  auto gp_radius = 200;
  auto gp_surface_gravity = 8;
  auto gp_mass = (gp_surface_gravity * gp_radius * gp_radius / Astre::gravitationnalConstantModel);

  Planet green_planet(Astre(Sphere(Point("Green Planet", gp_position), gp_radius * 2), gp_surface_gravity), Vec3(0, 70.23, 0));
  green_planet.setMass(gp_mass);

  println("-------------------------------------------------------------");
  println("Far away sat");

  auto gp_sat_position = Position(-23549, 0, 0);
  auto gp_sat_radius = 50;
  auto gp_sat_surface_gravity = 3;
  auto gp_sat_mass = gp_sat_surface_gravity * gp_sat_radius * gp_sat_radius / Astre::gravitationnalConstantModel;

  Planet gp_sat(Astre(Sphere(Point("Green Planet Satelite", gp_sat_position), gp_sat_radius * 2), 0), Vec3(0, 51, 0));
  gp_sat.setMass(gp_sat_mass);

  println("-------------------------------------------------------------");
  println("Puple gas giant");

  auto pgg_position = Position(-58811, 0, 0);
  auto pgg_radius = 500;
  auto pgg_surface_gravity = 14;
  auto pgg_mass = pgg_surface_gravity * pgg_radius * pgg_radius / Astre::gravitationnalConstantModel;

  Planet pgg(Astre(Sphere(Point("Purple gas giant", pgg_position), pgg_radius * 2), 0), Vec3(0, 50.3, 0));
  pgg.setMass(pgg_mass);

  println("-------------------------------------------------------------");
  println("Puple gas giant's satellite");

  auto pgg_sat_radius = 40;
  auto pgg_sat_position = Position(-55700, 0, 0);
  auto pgg_sat_surface_gravity = 2;
  auto pgg_sat_mass = (pgg_sat_surface_gravity * pgg_sat_radius * pgg_sat_radius / Astre::gravitationnalConstantModel);

  Planet pgg_sat(Astre(Sphere(Point("Purple gas giant sat1", pgg_sat_position), pgg_sat_radius * 2), 0), Vec3(0, 18.3, 0));
  pgg_sat.setMass(pgg_mass);

  FILE* pFile = fopen("/mnt/c/Users/g.defoy/Desktop/dump2.txt", "w");
  double simu_step = 1;

  auto bodies = mycollections::StaticVector<Planet*, 20>();
  bodies.push(&earth1);
  bodies.push(&earth2);
  bodies.push(&sun);
  bodies.push(&gp_sat);
  bodies.push(&pgg);
  bodies.push(&pgg_sat);
  bodies.push(&green_planet);

  for (int i = 0; i < 50000; i++) {
    fprintf(pFile, "%e %e %e %e %e %e %e %e %e %e %e %e %e %e\n",
      earth1.getPosition()._x, earth1.getPosition()._y,
      earth2.getPosition()._x, earth2.getPosition()._y,
      sun.getPosition()._x, sun.getPosition()._y,
      green_planet.getPosition()._x, green_planet.getPosition()._y,
      gp_sat.getPosition()._x, gp_sat.getPosition()._y,
      pgg.getPosition()._x, pgg.getPosition()._y,
      pgg_sat.getPosition()._x, pgg_sat.getPosition()._y);
    for (size_t j = 0; j < bodies.getSize(); j++) {
      bodies[j]->updateVelocity(bodies.iter(), 1);
    }
    for (size_t j = 0; j < bodies.getSize(); j++) {
      bodies[j]->updatePosition(1);
    }
  }
}
